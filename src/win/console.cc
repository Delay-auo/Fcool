

#include <win/fcoolwin.hh>
#include <win/print.hh>
#include <Fcool/console.hh>


namespace Fcool::console
{
    //
    static_assert( _type::is_same< _cpu::unicode_t, WCHAR > );
    inline _text::len_t fwh_write_ANSI( const HANDLE console, UINT CP, const void* text, _text::len_t len ) noexcept
    {
        if constexpr ( sizeof(_text::len_t) < sizeof(DWORD) )
            return 0;
        else if constexpr ( sizeof(_text::len_t) == sizeof(DWORD) )
            return fwh_printA( console, CP, text, len );
        else {
            _text::len_t r = 0;
            while ( pass ) {
                DWORD chunk = ( len > MAXDWORD )
                    ? MAXDWORD
                    : static_cast<DWORD>(len);
                r += fwh_printA(
                    console,
                    CP,
                    static_cast<const CHAR*>(text) + r,
                    chunk
                );
                if ( len <= chunk )
                    break;
                len -= chunk;
            }
            return r;
        }
    }
    inline _text::len_t fwh_write_WIDE( const HANDLE console, const void* text, _text::len_t len ) noexcept
    {
        if constexpr ( sizeof(_text::len_t) < sizeof(DWORD) )
            return 0;
        else if constexpr ( sizeof(_text::len_t) == sizeof(DWORD) )
            return fwh_printW( console, text, len );
        else {
            _text::len_t r = 0;
            while ( pass ) {
                DWORD chunk = ( len > MAXDWORD )
                    ? MAXDWORD
                    : static_cast<DWORD>(len);
                r += fwh_printW(
                    console,
                    static_cast<const WCHAR*>(text) + r,
                    chunk
                );
                if ( len <= chunk )
                    break;
                len -= chunk;
            }
            return r;
        }
    }
    inline DWORD fwh_read_ANSI( const HANDLE console, UINT CP, void* text, _text::len_t len ) noexcept
    {
        SetConsoleCP( CP );
        DWORD read = static_cast<DWORD>( len );
        if ( read < len )
            read = 0;
        DWORD r = 0;
        ReadConsoleA(
            console,
            text, read,
            &r, NULL
        );
        FlushConsoleInputBuffer( console );
        return r;
    }
    inline DWORD fwh_read_WIDE( const HANDLE console, void* text, _text::len_t len ) noexcept
    {
        DWORD read = static_cast<DWORD>( len );
        if ( read < len )
            read = 0;
        DWORD r = 0;
        ReadConsoleW(
            console,
            text, read,
            &r, NULL
        );
        FlushConsoleInputBuffer( console );
        return r;
    }
    constexpr WCHAR fwh_ASCII_to_Unicode( CHAR c ) noexcept {
        return static_cast<WCHAR>( static_cast<unsigned char>( c ) );
    }
    inline bool fwh_readkey_ANSI( const HANDLE console, key_info_t& out ) noexcept {
        INPUT_RECORD record;
        DWORD eventsRead;
        DWORD i = zero;
        while ( MAXWORD > i++ ) {
            if ( ReadConsoleInputA(
                console,
                &record,
                unit,
                &eventsRead
            ) ) {
                if ( eventsRead == unit && record.EventType == KEY_EVENT ) {
                    KEY_EVENT_RECORD key = record.Event.KeyEvent;
                    byte_t modifiers = static_cast<byte_t>( KeyModifier::None );
                    if ( key.bKeyDown )
                        modifiers |= static_cast<byte_t>( KeyModifier::KeyDown );
                    if ( ( key.dwControlKeyState & ( LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED ) ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Alt );
                    if ( ( key.dwControlKeyState & SHIFT_PRESSED ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Shift );
                    if ( ( key.dwControlKeyState & ( LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED ) ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Control );
                    out = key_info_t(
                        key.wVirtualKeyCode, key.wVirtualScanCode,
                        fwh_ASCII_to_Unicode( key.uChar.AsciiChar ),
                        modifiers, key.wRepeatCount
                    );
                    return pass;
                }
            }
        }
        return fail;
    }
    inline bool fwh_readkey_WIDE( const HANDLE console, key_info_t& out ) noexcept {
        INPUT_RECORD record;
        DWORD eventsRead;
        DWORD i = zero;
        while ( MAXWORD > i++ ) {
            if ( ReadConsoleInputW(
                console,
                &record,
                unit,
                &eventsRead
            ) ) {
                if ( eventsRead == unit && record.EventType == KEY_EVENT ) {
                    KEY_EVENT_RECORD key = record.Event.KeyEvent;
                    byte_t modifiers = static_cast<byte_t>( KeyModifier::None );
                    if ( key.bKeyDown )
                        modifiers |= static_cast<byte_t>( KeyModifier::KeyDown );
                    if ( ( key.dwControlKeyState & ( LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED ) ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Alt );
                    if ( ( key.dwControlKeyState & SHIFT_PRESSED ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Shift );
                    if ( ( key.dwControlKeyState & ( LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED ) ) != 0 )
                        modifiers |= static_cast<byte_t>( KeyModifier::Control );
                    out = key_info_t(
                        key.wVirtualKeyCode, key.wVirtualScanCode,
                        key.uChar.UnicodeChar,
                        modifiers, key.wRepeatCount
                    );
                    return pass;
                }
            }
        }
        return fail;
    }
    //
    HANDLE impl_say = NULL;
    HANDLE impl_ask = NULL;
    //
    inline bool fwh_load_say( HANDLE& _impl ) noexcept {
        _impl = GetStdHandle( STD_OUTPUT_HANDLE );
        return ( _impl != NULL && _impl != INVALID_HANDLE_VALUE );
    }
    inline bool fwh_load_ask( HANDLE& _impl ) noexcept {
        _impl = GetStdHandle( STD_INPUT_HANDLE );
        return ( _impl != NULL && _impl != INVALID_HANDLE_VALUE );
    }
    bool fwh_window_open( ) noexcept {
        if ( GetConsoleWindow( ) != NULL )
            return pass;
        if ( AttachConsole( ATTACH_PARENT_PROCESS ) != 0 )
            return pass;
        return AllocConsole( ) != 0;
    }
    //
    bool is_loaded( ) noexcept {
        if (
            impl_say == NULL ||
            impl_say == INVALID_HANDLE_VALUE
            || impl_ask == NULL ||
            impl_ask == INVALID_HANDLE_VALUE
        )
            return fail;
        DWORD mode = 0;
        return GetConsoleMode( impl_say, &mode ) != 0 && GetConsoleMode( impl_ask, &mode ) != 0;
    }
    bool hard_reload( bool& stable ) noexcept {
        stable = fail;
        fwh_window_open( );
        if( fwh_load_say( impl_say ) )
            if ( fwh_load_ask( impl_ask ) ) {
                FlushConsoleInputBuffer( impl_ask );
                return pass;
            }
        return fail;
    }
    bool soft_reload( bool& stable ) noexcept {
        stable = fail;
        HANDLE _impl_say;
        if ( fwh_load_say( _impl_say ) ) {
            HANDLE _impl_ask;
            if ( fwh_load_ask( _impl_ask ) )
                impl_ask = _impl_ask;
            else
                return fail;
            impl_say = _impl_say;
            return pass;
        } else {
            return fail;
        }
    }
    bool unload( ) noexcept {
        impl_say = NULL;
        impl_ask = NULL;
        return pass;
    }
    //
    _text::len_t write_msg( _text::str_code msg, _text::len_t len ) noexcept {
        return fwh_write_ANSI( impl_say, CP_ACP, static_cast<const void*>( _mem::cast_buffer_c( msg ) ), len );
    }
    _text::len_t write_msg( _text::str_wide msg, _text::len_t len ) noexcept {
        return fwh_write_WIDE( impl_say, static_cast<const void*>( _mem::cast_buffer_c( msg ) ), len );
    }
    _text::len_t write_err( _text::str_code msg, _text::len_t len ) noexcept {
        return write_msg( msg, len );
    }
    _text::len_t write_err( _text::str_wide msg, _text::len_t len ) noexcept {
        return write_msg( msg, len );
    }
    _text::len_t read_msg( _text::ptr_code out, _text::len_t len ) noexcept {
        _text::len_t r = fwh_read_ANSI( impl_ask, CP_UTF8, static_cast<_cpu::chr_code*>(out), len );
        if (
            r >= 2
            && out[r - 2] == u8'\r'
            && out[r - 1] == u8'\n'
        ) r -= 2;
        return r;
    }
    _text::len_t read_msg( _text::ptr_wide out, _text::len_t len ) noexcept {
        _text::len_t r = fwh_read_WIDE( impl_ask, static_cast<_cpu::chr_wide*>(out), len );
        if (
            r >= 2
            && out[r - 2] == u'\r'
            && out[r - 1] == u'\n'
        ) r -= 2;
        return r;
    }
    //
    bool __read_key_default_is_wide = false;
    bool _read_key_code( key_info_t& out ) noexcept {
        return fwh_readkey_ANSI( impl_ask, out );
    }
    bool _read_key_wide( key_info_t& out ) noexcept {
        return fwh_readkey_WIDE( impl_ask, out );
    }
    bool flush_keys( ) noexcept {
        return FlushConsoleInputBuffer( impl_ask );
    }
    //
    namespace _property
    {
        //
        bool try_get_background_color( color& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = static_cast<color>( ( info.wAttributes >> 4 ) & 0x0F );
            return pass;
        }
        bool try_set_background_color( color&& col ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            WORD attributes = static_cast<WORD>( info.wAttributes & 0x0F );
            attributes |= static_cast<WORD>( ( static_cast<WORD>( col ) & 0x0F ) << 4 );
            return SetConsoleTextAttribute( impl_say, attributes ) != 0;
        }
        bool try_get_foreground_color( color& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = static_cast<color>( info.wAttributes & 0x0F );
            return pass;
        }
        bool try_set_foreground_color( color&& col ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            WORD attributes = static_cast<WORD>( info.wAttributes & 0xF0 );
            attributes |= static_cast<WORD>( static_cast<WORD>( col ) & 0x0F );
            return SetConsoleTextAttribute( impl_say, attributes ) != 0;
        }
        bool try_get_cursor_rows( bufferX_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferX_t( static_cast<size_t>( info.dwCursorPosition.X ) );
            return pass;
        }
        bool try_set_cursor_rows( bufferX_t&& new_row ) noexcept {
            if ( new_row.x > MAXSHORT )
                return fail;
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            COORD pos = { info.dwCursorPosition.X, static_cast<SHORT>( new_row.x ) };
            return SetConsoleCursorPosition( impl_say, pos ) != 0;
        }
        bool try_get_cursor_cols( bufferY_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferY_t( static_cast<size_t>( info.dwCursorPosition.Y ) );
            return pass;
        }
        bool try_set_cursor_cols( bufferY_t&& new_col ) noexcept {
            if ( new_col.y > MAXSHORT )
                return fail;
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            COORD pos = { static_cast<SHORT>( new_col.y ), info.dwCursorPosition.Y };
            return SetConsoleCursorPosition( impl_say, pos ) != 0;
        }
        bool try_get_cursor_pos( bufferPos_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferPos_t(
                static_cast<size_t>( info.dwCursorPosition.X ),
                static_cast<size_t>( info.dwCursorPosition.Y )
            );
            return pass;
        }
        bool try_set_cursor_pos( bufferPos_t&& new_pos ) noexcept {
            if ( new_pos.x > MAXSHORT || new_pos.y > MAXSHORT )
                return fail;
            COORD pos = {
                static_cast<SHORT>( new_pos.x ),
                static_cast<SHORT>( new_pos.y )
            };
            return SetConsoleCursorPosition( impl_say, pos ) != 0;
        }
        bool try_get_cursor_visible( bool& out ) noexcept {
            CONSOLE_CURSOR_INFO info;
            if ( GetConsoleCursorInfo( impl_say, &info ) == 0 )
                return fail;
            out = info.bVisible != FALSE;
            return pass;
        }
        bool try_set_cursor_visible( bool&& visible ) noexcept {
            CONSOLE_CURSOR_INFO info;
            if ( GetConsoleCursorInfo( impl_say, &info ) == 0 )
                return fail;
            info.bVisible = visible ? TRUE : FALSE;
            return SetConsoleCursorInfo( impl_say, &info ) != 0;
        }
        //
        bool try_get_window_rows_l( bufferX_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferX_t( static_cast<size_t>( info.srWindow.Left ) );
            return pass;
        }
        bool try_get_window_rows_r( bufferX_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferX_t( static_cast<size_t>( info.srWindow.Right ) );
            return pass;
        }
        bool try_get_window_cols_t( bufferY_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferY_t( static_cast<size_t>( info.srWindow.Top ) );
            return pass;
        }
        bool try_get_window_cols_b( bufferY_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferY_t( static_cast<size_t>( info.srWindow.Bottom ) );
            return pass;
        }
        bool try_get_window_pos_tl( bufferPos_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferPos_t(
                static_cast<size_t>( info.srWindow.Left ),
                static_cast<size_t>( info.srWindow.Top )
            );
            return pass;
        }
        bool try_get_window_pos_br( bufferPos_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            out = bufferPos_t(
                static_cast<size_t>( info.srWindow.Right ),
                static_cast<size_t>( info.srWindow.Bottom )
            );
            return pass;
        }
        bool try_get_window_limit_r( bufferX_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            if ( info.srWindow.Right < info.srWindow.Left )
                return fail;
            out = bufferX_t( static_cast<size_t>( info.srWindow.Right - info.srWindow.Left ) );
            return pass;
        }
        bool try_get_window_limit_b( bufferY_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            if ( info.srWindow.Bottom < info.srWindow.Top )
                return fail;
            out = bufferY_t( static_cast<size_t>( info.srWindow.Bottom - info.srWindow.Top ) );
            return pass;
        }
        bool try_get_window_limit_br( bufferPos_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            if ( info.srWindow.Right < info.srWindow.Left || info.srWindow.Bottom < info.srWindow.Top )
                return fail;
            out = bufferPos_t(
                static_cast<size_t>( info.srWindow.Right - info.srWindow.Left ),
                static_cast<size_t>( info.srWindow.Bottom - info.srWindow.Top )
            );
            return pass;
        }
        bool try_get_window_size( bufferSze_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            if ( info.srWindow.Right <= info.srWindow.Left || info.srWindow.Bottom <= info.srWindow.Top )
                return fail;
            out = bufferSze_t(
                static_cast<size_t>( info.srWindow.Right - info.srWindow.Left + unit ),
                static_cast<size_t>( info.srWindow.Bottom - info.srWindow.Top + unit )
            );
            return pass;
        }
        bool try_get_window_area( bufferArea_t& out ) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO info;
            if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
                return fail;
            if ( info.srWindow.Right <= info.srWindow.Left || info.srWindow.Bottom <= info.srWindow.Top )
                return fail;
            out = bufferArea_t(
                static_cast<size_t>( info.srWindow.Left ),
                static_cast<size_t>( info.srWindow.Top ),
                static_cast<size_t>( info.srWindow.Right - info.srWindow.Left + unit ),
                static_cast<size_t>( info.srWindow.Bottom - info.srWindow.Top + unit )
            );
            return pass;
        }
        //
        bool try_get_title( _text::wstring& out ) noexcept {
            DWORD len = hexa;
            for ( ; ; ) {
                out.wipe( );
                out.add_back_l( len );
                DWORD title_len = GetConsoleTitleW( static_cast<LPWSTR>( out.ptr( ) ), len );
                if ( title_len != 0 && title_len < len - unit ) {
                    out.pop_back( len - title_len );
                    out.compress( );
                    return pass;
                }
                if ( title_len == 0 ) {
                    out.wipe( );
                    return ( len <= hexa );
                }
                if ( len > MAXWORD / 2 ) {
                    out.wipe( );
                    out.compress( );
                    return fail;
                }
                len *= 2;
            }
        }
        bool try_set_title( _text::view_wide_str&& new_title ) noexcept {
            _text::ptr_wide title = _text::make_ptr_wide( new_title.length( ) + unit );
            _text::nt_get( new_title.view( ), new_title.length( ), title );
            bool r = SetConsoleTitleW( static_cast<LPWSTR>( title ) );
            _text::free_str_wide( title );
            return r;
        }
        bool try_get_capslock( bool& out ) noexcept {
            out = ( GetKeyState( VK_CAPITAL ) & 0x0001 ) != 0;
            return pass;
        }
        bool try_set_capslock( bool&& enabled ) noexcept {
            bool current = false;
            if ( !try_get_capslock( current ) )
                return fail;
            if ( current != enabled ) {
                keybd_event( VK_CAPITAL, 0, 0, 0 );
                keybd_event( VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0 );
            }
            return try_get_capslock( current ) && current == enabled;
        }
        bool try_get_numberlock( bool& out ) noexcept {
            out = ( GetKeyState( VK_NUMLOCK ) & 0x0001 ) != 0;
            return pass;
        }
        bool try_set_numberlock( bool&& enabled ) noexcept {
            bool current = false;
            if ( !try_get_numberlock( current ) )
                return fail;
            if ( current != enabled ) {
                keybd_event( VK_NUMLOCK, 0, 0, 0 );
                keybd_event( VK_NUMLOCK, 0, KEYEVENTF_KEYUP, 0 );
            }
            return try_get_numberlock( current ) && current == enabled;
        }
        bool try_get_keyavailable( bool& out ) noexcept {
            DWORD event_count = 0;
            if ( GetNumberOfConsoleInputEvents( impl_ask, &event_count ) == 0 )
                return fail;
            out = event_count != 0;
            return pass;
        }
    }
    //
    bool beep( ) noexcept {
        return Beep( 800, 200 );
    }
    bool beep( _cpu::int_quad frec, _time::duration_fast duration ) noexcept {
        if ( frec < zero )
            frec = -frec;
        _time::__prec_t ms = duration.get_millisecs( );
        if ( ms > MAXDWORD )
            ms = MAXDWORD;
        return Beep( static_cast<DWORD>( frec ), static_cast<DWORD>(ms) );
    }
    bool clear( ) noexcept {
        if ( !is_loaded( ) )
            return fail;
        CONSOLE_SCREEN_BUFFER_INFO info;
        if ( GetConsoleScreenBufferInfo( impl_say, &info ) == 0 )
            return fail;
        const DWORD size = static_cast<DWORD>( info.dwSize.X ) *
            static_cast<DWORD>( info.dwSize.Y );
        COORD origin = { 0, 0 };
        DWORD written = 0;
        if ( FillConsoleOutputCharacterW( impl_say, L' ', size, origin, &written ) == 0 )
            return fail;
        if ( FillConsoleOutputAttribute( impl_say, info.wAttributes, size, origin, &written ) == 0 )
            return fail;
        return SetConsoleCursorPosition( impl_say, origin ) != 0;
    }
    bool reset_color( ) noexcept {
        return SetConsoleTextAttribute( impl_say, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ) != 0;
    }
    //
    capability::_cap_t capability::get_all( ) noexcept {
        constexpr _cap_t automatic = (
            _cap::PlayBeep |
            _cap::Title_Get |
            _cap::Title_Set
        );
        constexpr _cap_t loaded = (
            automatic |
            _cap::TextOutput |
            _cap::TextInput |
            _cap::TextColor_Get |
            _cap::TextColor_Set |
            _cap::TextBackColor_Get |
            _cap::TextBackColor_Set |
            _cap::TextClear |
            _cap::KeyInput |
            _cap::KeyInput_modifiers |
            _cap::KeyInput_repeat |
            _cap::KeyInput_FunctionKeys |
            _cap::KeyInput_ArrowKeys |
            _cap::KeyInput_Numpad |
            _cap::Cursor_Get |
            _cap::Cursor_Set |
            _cap::Area_Get |
            _cap::Locks
        );
        if ( !is_loaded( ) )
            return automatic;
        //
        return loaded;
        //
    }
    //
}






