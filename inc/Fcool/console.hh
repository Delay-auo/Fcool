/**
 * @headerfile Fcool/console.hh
 * @version 1.0
 * @author Matias Viitanen
 * @since Fcool 0.2
 * @copyright (C) Matias Viitanen 2026
 * This file is part of the Fcool library
 */


#ifndef FCOOL_HEAD_CONSOLE
#define FCOOL_HEAD_CONSOLE 0.1


#include "_text.hh"
#include "_init.hh"
#include "_time.hh"


namespace Fcool::console
{
    //
    bool is_loaded( ) noexcept;
    bool hard_reload( bool& stable ) noexcept;
    bool soft_reload( bool& stable ) noexcept;
    bool unload( ) noexcept;
    //
    inline bool hard_reload( ) noexcept { bool stable; return hard_reload( stable ); }
    inline bool soft_reload( ) noexcept { bool stable; return soft_reload( stable ); }
    /// @brief initialize the module
    /// @return result
    inline const _init::type init( ) noexcept {
        if ( !is_loaded( ) ) {
            bool stable;
            if ( !hard_reload( stable ) )
                return _init::get_fail( stable );
            else
                return _init::get_success( stable );
        }
        return { };
    }
    /// @brief safely reinitialize the module
    /// @return result
    inline const _init::type reinit( ) noexcept {
        if ( !is_loaded( ) ) {
            bool stable;
            if ( soft_reload( stable ) )
                return _init::get_success( stable );
            else
                return _init::get_fail( stable );
        }
        return { };
    }
    /// @brief uninitialize the module
    /// @return result
    inline const _init::type uninit( ) noexcept {
        if ( is_loaded( ) ) {
            if ( unload( ) )
                return _init::get_success( fail );
            else
                return _init::get_fail( fail );
        }
        return { };
    }
    /// @brief console colors
    enum class color
    {
        Black,
        DarkBlue,
        DarkGreen,
        DarkCyan,
        DarkRed,
        DarkMagenta,
        DarkYellow,
        Gray,
        DarkGray,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Yellow,
        White
    };
    struct bufferX_t {
        size_t x;
        constexpr bufferX_t( ) noexcept
        : x(zero) {}
        constexpr bufferX_t( size_t _x ) noexcept
        : x(_x) { }
        constexpr operator size_t( ) noexcept {
            return x;
        }
    };
    struct bufferY_t {
        size_t y;
        constexpr bufferY_t( ) noexcept
        : y(zero) {}
        constexpr bufferY_t( size_t _y ) noexcept
        : y(_y) { }
        constexpr operator size_t( ) noexcept {
            return y;
        }
    };
    struct bufferW_t {
        size_t w;
        constexpr bufferW_t( ) noexcept
        : w(zero) {}
        constexpr bufferW_t( size_t _w ) noexcept
        : w(_w) { }
        constexpr operator size_t( ) noexcept {
            return w;
        }
    };
    struct bufferH_t {
        size_t h;
        constexpr bufferH_t( ) noexcept
        : h(zero) {}
        constexpr bufferH_t( size_t _h ) noexcept
        : h(_h) { }
        constexpr operator size_t( ) noexcept {
            return h;
        }
    };
    struct bufferPos_t {
        size_t x;
        size_t y;
        constexpr bufferPos_t( ) noexcept
        : x(zero), y(zero) { }
        constexpr bufferPos_t( size_t _x, size_t _y ) noexcept
        : x(_x), y(_y) { }
        constexpr operator bufferX_t( ) noexcept {
            return x;
        }
        constexpr operator bufferY_t( ) noexcept {
            return y;
        }
    };
    struct bufferSze_t {
        size_t w;
        size_t h;
        constexpr bufferSze_t( ) noexcept
        : w(zero), h(zero) { }
        constexpr bufferSze_t( size_t _w, size_t _h ) noexcept
        : w(_w), h(_h) { }
        constexpr operator bufferW_t( ) noexcept {
            return w;
        }
        constexpr operator bufferH_t( ) noexcept {
            return h;
        }
    };
    struct bufferArea_t {
        size_t x;
        size_t y;
        size_t w;
        size_t h;
        constexpr bufferArea_t( ) noexcept
        : x(zero), y(zero), w(zero), h(zero) { }
        constexpr bufferArea_t( size_t _x, size_t _y, size_t _w, size_t _h ) noexcept
        : x(_x), y(_y), w(_w), h(_h) { }
        constexpr operator bufferX_t( ) noexcept {
            return x;
        }
        constexpr operator bufferY_t( ) noexcept {
            return y;
        }
        constexpr operator bufferW_t( ) noexcept {
            return w;
        }
        constexpr operator bufferH_t( ) noexcept {
            return h;
        }
        constexpr operator bufferPos_t( ) noexcept {
            return { x, y };
        }
        constexpr operator bufferSze_t( ) noexcept {
            return { w, h };
        }
    };
    /// @brief #### virtual key enumeter
    enum class VKey : word_t
    {
        None,
        Backspace = 8,
        Tab = 9,
        Clear = 12,
        Enter = 13,
        Pause = 19,
        Escape = 27,
        Spacebar = 32,
        PageUp = 33,
        PageDown = 34,
        End = 35,
        Home = 36,
        LeftArrow = 37,
        UpArrow = 38,
        RightArrow = 39,
        DownArrow = 40,
        Select = 41,
        Print = 42,
        Execute = 43,
        PrintScreen = 44,
        Insert = 45,
        Delete = 46,
        Help = 47,
        D0 = 48,
        D1 = 49,
        D2 = 50,
        D3 = 51,
        D4 = 52,
        D5 = 53,
        D6 = 54,
        D7 = 55,
        D8 = 56,
        D9 = 57,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftSystem = 91,
        RightSystem = 92,
        Applications = 93,
        Sleep = 95,
        NumPad0 = 96,
        NumPad1 = 97,
        NumPad2 = 98,
        NumPad3 = 99,
        NumPad4 = 100,
        NumPad5 = 101,
        NumPad6 = 102,
        NumPad7 = 103,
        NumPad8 = 104,
        NumPad9 = 105,
        Multiply = 106,
        Add = 107,
        Separator = 108,
        Subtract = 109,
        Decimal = 110,
        Divide = 111,
        F1 = 112,
        F2 = 113,
        F3 = 114,
        F4 = 115,
        F5 = 116,
        F6 = 117,
        F7 = 118,
        F8 = 119,
        F9 = 120,
        F10 = 121,
        F11 = 122,
        F12 = 123,
        F13 = 124,
        F14 = 125,
        F15 = 126,
        F16 = 127,
        F17 = 128,
        F18 = 129,
        F19 = 130,
        F20 = 131,
        F21 = 132,
        F22 = 133,
        F23 = 134,
        F24 = 135,
        NumLock = 144,
        Scroll = 145,
        LeftShift = 160,
        RightShift = 161,
        LeftControl = 162,
        RightControl = 163,
        LeftAlt = 164,
        RightAlt = 165,
        BrowserBack = 166,
        BrowserForward = 167,
        BrowserRefresh = 168,
        BrowserStop = 169,
        BrowserSearch = 170,
        BrowserFavorites = 171,
        BrowserHome = 172,
        VolumeMute = 173,
        VolumeDown = 174,
        VolumeUp = 175,
        MediaNext = 176,
        MediaPrevious = 177,
        MediaStop = 178,
        MediaPlay = 179,
        LaunchMail = 180,
        SelectMedia = 181,
        LaunchApplication1 = 182,
        LaunchApplication2 = 183,
        Oem1 = 186,
        OemPlus = 187,
        OemComma = 188,
        OemMinus = 189,
        OemPeriod = 190,
        Oem2 = 191,
        Oem3 = 192,
        Oem4 = 219,
        Oem5 = 220,
        Oem6 = 221,
        Oem7 = 222,
        Oem8 = 223,
        Oem102 = 226,
        Process = 229,
        Packet = 231,
        Attn = 246,
        CrSel = 247,
        ExSel = 248,
        EraseEof = 249,
        Play = 250,
        Zoom = 251,
        NoName = 252,
        Pa1 = 253,
        OemClear = 254
    };
    /// @brief #### modifiers for key info
    enum class KeyModifier : byte_t
    {
        None = zero,
        Alt = unit,
        Shift = Alt * dual,
        Control = Shift * dual,
        KeyDown = Control * dual
    };
    /// @brief 
    /// @param keycode 
    /// @return weather a key code is a valid virtual key
    constexpr bool is_vk( word_t keycode ) noexcept {
        if (
            ( keycode >= 8 && keycode <= 9 ) ||
            keycode == 12 || keycode == 13 || keycode == 19 || keycode == 27 ||
            ( keycode >= 32 && keycode <= 57 ) ||
            ( keycode >= 65 && keycode <= 93 ) ||
            ( keycode >= 95 && keycode <= 135 ) ||
            ( keycode >= 144 && keycode <= 145 ) ||
            ( keycode >= 160 && keycode <= 183 ) ||
            ( keycode >= 186 && keycode <= 192 ) ||
            ( keycode >= 219 && keycode <= 223 ) || keycode == 226 ||
            keycode == 229 || keycode == 231 ||
            ( keycode >= 246 && keycode <= 254 ) )
            return pass;
        return fail;
    }
    /// @brief keyboard input key info
    struct key_info_t
    {
        constexpr key_info_t( ) noexcept
        : keycode( zero ), scancode( zero ),
        modifiers( static_cast<byte_t>( KeyModifier::KeyDown ) & (hexa-unit) ), repeat( zero ) { }
        constexpr key_info_t(
            word_t _keycode, word_t _scancode, _cpu::unicode_t _chr_key,
            byte_t _modifiers = zero, size_t _repeat = unit
        ) noexcept
        : keycode( _keycode ), scancode( _scancode ), chr_key( _chr_key ),
        modifiers( _modifiers & (hexa-unit) ),
        repeat( ( _repeat > repeat_max ? repeat_max : _repeat ) & (hexa-unit) ) { }
        word_t keycode;
        word_t scancode;
        _cpu::unicode_t chr_key;
        byte_t modifiers : quad;
        byte_t repeat : quad;
        constexpr static byte_t repeat_max = octa - unit;
        constexpr operator VKey( ) {
            return static_cast<VKey>( keycode );
        }
        constexpr bool operator==( VKey vk ) const noexcept {
            return keycode == static_cast<word_t>( vk );
        }
        constexpr bool operator/( KeyModifier km ) const noexcept {
            return ( modifiers & static_cast<byte_t>( km ) ) != zero;
        }
    };
    /// @brief 
    /// @param key 
    /// @return weather a key is pressed down virtual key
    constexpr bool is_pressed( key_info_t key ) noexcept {
        return ( key / KeyModifier::KeyDown && key.repeat > zero );
    }
    /// @brief 
    /// @param key 
    /// @return weather a key is pressed down virtual key
    constexpr bool is_released( key_info_t key ) noexcept {
        return ( !( key / KeyModifier::KeyDown ) && key.repeat > zero );
    }
    /// @brief 
    /// @param keycode 
    /// @return weather a key info is a valid virtual key
    constexpr bool is_vk( key_info_t key ) noexcept {
        return is_vk( key.keycode );
    }
    /// @brief get everything the implementation can and cannot do
    namespace capability
    {
        using _cap_t = _cpu::nat_quad;
        enum _cap : _cap_t
        {
            None = zero,
            TextOutput              = unit << 0,
            TextInput               = unit << 1,
            StdErr                  = unit << 2,
            TextBold                = unit << 3,
            TextItalic              = unit << 4,
            TextUnderline           = unit << 5,
            TextStriketrough        = unit << 6,
            TextColor_Get           = unit << 7,
            TextColor_Set           = unit << 8,
            TextBackColor_Get       = unit << 9,
            TextBackColor_Set       = unit << 10,
            TextClear               = unit << 11,
            //
            KeyInput                = unit << 12,
            KeyInput_modifiers      = unit << 13,
            KeyInput_repeat         = unit << 14,
            KeyInput_FunctionKeys   = unit << 15,
            KeyInput_ArrowKeys      = unit << 16,
            KeyInput_Numpad         = unit << 17,
            //
            Cursor_Get              = unit << 18,
            Cursor_Set              = unit << 19,
            Area_Get                = unit << 20,
            Area_Set                = unit << 21,
            //
            Locks                   = unit << 22,
            Title_Get               = unit << 23,
            Title_Set               = unit << 24,
            PlayBeep                = unit << 25
            //
        };
        _cap_t get_all( ) noexcept;
    }
    //
    #pragma region // properties
    /// @brief #### the property getter/setter functions
    namespace _property
    {
        bool try_get_background_color( color& ) noexcept;
        bool try_set_background_color( color&& ) noexcept;
        bool try_get_foreground_color( color& ) noexcept;
        bool try_set_foreground_color( color&& ) noexcept;
        //
        bool try_get_cursor_rows( bufferX_t& ) noexcept;
        bool try_set_cursor_rows( bufferX_t&& ) noexcept;
        bool try_get_cursor_cols( bufferY_t& ) noexcept;
        bool try_set_cursor_cols( bufferY_t&& ) noexcept;
        bool try_get_cursor_pos( bufferPos_t& ) noexcept;
        bool try_set_cursor_pos( bufferPos_t&& ) noexcept;
        bool try_get_cursor_visible( bool& ) noexcept;
        bool try_set_cursor_visible( bool&& ) noexcept;
        //
        bool try_get_window_rows_l( bufferX_t& ) noexcept;
        bool try_get_window_rows_r( bufferX_t& ) noexcept;
        bool try_get_window_cols_t( bufferY_t& ) noexcept;
        bool try_get_window_cols_b( bufferY_t& ) noexcept;
        bool try_get_window_pos_tl( bufferPos_t& ) noexcept;
        bool try_get_window_pos_br( bufferPos_t& ) noexcept;
        bool try_get_window_limit_r( bufferX_t& ) noexcept;
        bool try_get_window_limit_b( bufferY_t& ) noexcept;
        bool try_get_window_limit_br( bufferPos_t& ) noexcept;
        bool try_get_window_size( bufferSze_t& ) noexcept;
        bool try_get_window_area( bufferArea_t& ) noexcept;
        //
        bool try_get_title( _text::wstring& ) noexcept;
        bool try_set_title( _text::view_wide_str&& ) noexcept;
        bool try_get_capslock( bool& ) noexcept;
        bool try_set_capslock( bool&& ) noexcept;
        bool try_get_numberlock( bool& ) noexcept;
        bool try_set_numberlock( bool&& ) noexcept;
        //
        bool try_get_keyavailable( bool& ) noexcept;
        //
    }
    /// @brief gets or sets the background color of the console
    constexpr _init::property<color> BackgroundColor = {
        _property::try_get_background_color,
        _property::try_set_background_color
    };
    /// @brief gets or sets the foreground color of the console
    constexpr _init::property<color> ForegroundColor = {
        _property::try_get_foreground_color,
        _property::try_set_foreground_color
    };
    constexpr _init::property<bufferX_t> CursorX = {
        _property::try_get_cursor_rows,
        _property::try_set_cursor_rows
    };
    constexpr _init::property<bufferY_t> CursorY = {
        _property::try_get_cursor_cols,
        _property::try_set_cursor_cols
    };
    constexpr _init::property<bufferPos_t> Cursor = {
        _property::try_get_cursor_pos,
        _property::try_set_cursor_pos
    };
    constexpr _init::property<bool> CursorVisible = {
        _property::try_get_cursor_visible,
        _property::try_set_cursor_visible
    };
    constexpr _init::property_get<bufferY_t> SideT = {
        _property::try_get_window_cols_t
    };
    constexpr _init::property_get<bufferX_t> SideL = {
        _property::try_get_window_rows_l
    };
    constexpr _init::property_get<bufferY_t> SideB = {
        _property::try_get_window_cols_b
    };
    constexpr _init::property_get<bufferX_t> SideR = {
        _property::try_get_window_rows_r
    };
    constexpr _init::property_get<bufferPos_t> CornerTL = {
        _property::try_get_window_pos_tl
    };
    constexpr _init::property_get<bufferPos_t> CornerBR = {
        _property::try_get_window_pos_br
    };
    constexpr _init::property_get<bufferSze_t> Size = {
        _property::try_get_window_size
    };
    constexpr _init::property_get<bufferArea_t> Area = {
        _property::try_get_window_area
    };
    constexpr _init::property_get<bufferX_t> LimitR = {
        _property::try_get_window_limit_r
    };
    constexpr _init::property_get<bufferY_t> LimitB = {
        _property::try_get_window_limit_b
    };
    constexpr _init::property_get<bufferPos_t> LimitBR = {
        _property::try_get_window_limit_br
    };
    constexpr _init::property<bool> CapsLock = {
        _property::try_get_capslock,
        _property::try_set_capslock
    };
    constexpr _init::property<bool> NumbLock = {
        _property::try_get_numberlock,
        _property::try_set_numberlock
    };
    constexpr _init::property_get<bool> KeyAvailable = {
        _property::try_get_keyavailable
    };
    constexpr _init::property< _text::wstring, _text::view_wide_str > Title = {
        _property::try_get_title,
        _property::try_set_title
    };
    #pragma endregion
    //
    /// @brief plays the sound of a beep through the console speaker
    /// @return weather the sound played successfully
    bool beep( ) noexcept;
    /// @brief plays the sound of a beep through the console speaker
    /// @param frequency 
    /// @param duration 
    /// @return weather the sound played successfully
    bool beep( _cpu::int_quad, _time::duration_fast ) noexcept;
    /// @brief clears the console buffer and corresponding console display of display information
    bool clear( ) noexcept;
    /// @brief read user input
    /// @param output base range pointer string
    /// @param length max input characters
    /// @return characters read
    _text::len_t read_msg( _text::ptr_base, _text::len_t ) noexcept;
    /// @brief read user input
    /// @param output wide range pointer string
    /// @param length max input characters
    /// @return characters read
    _text::len_t read_msg( _text::ptr_wide, _text::len_t ) noexcept;
    extern bool __read_key_default_is_wide;
    bool _read_key_base( key_info_t& ) noexcept;
    bool _read_key_wide( key_info_t& ) noexcept;
    /// @brief clear the read_key queue
    /// @return weather the queue was cleared
    bool flush_keys( ) noexcept;
    /// @brief assign the color to the original value
    /// @return weather the color was reset
    bool reset_color( ) noexcept;
    /// @brief write a single console message
    /// @param output base range string pointer
    /// @param length output characters
    /// @return written characters
    _text::len_t write_msg( _text::str_base, _text::len_t ) noexcept;
    /// @brief write a single console message
    /// @param output wide range string pointer
    /// @param length output characters
    /// @return written characters
    _text::len_t write_msg( _text::str_wide, _text::len_t ) noexcept;
    /// @brief write a single console error
    /// @param output base range string pointer
    /// @param length output characters
    /// @return written characters
    _text::len_t write_err( _text::str_base, _text::len_t ) noexcept;
    /// @brief write a single console error
    /// @param output wide range string pointer
    /// @param length output characters
    /// @return written characters
    _text::len_t write_err( _text::str_wide, _text::len_t ) noexcept;
    //
    #if defined(FCOOLMACRO_NO_IMPL) && FCOOLMACRO_NO_IMPL
        inline bool is_loaded( ) noexcept {
            return fail;
        }
        inline bool hard_reload( bool& stable ) noexcept {
            stable = true;
            return fail;
        }
        inline bool soft_reload( bool& stable ) noexcept {
            stable = true;
            return fail;
        }
        inline bool unload( ) noexcept {
            return pass;
        }
        inline bool beep( ) noexcept { return fail; }
        inline bool beep( _cpu::int_quad, _time::duration_fast ) noexcept { return fail; }
        inline bool clear( ) noexcept { return fail; }
        inline _text::len_t read_msg( _text::ptr_base, _text::len_t ) noexcept { return zero; }
        inline _text::len_t read_msg( _text::ptr_wide, _text::len_t ) noexcept { return zero; }
        inline bool __read_key_default_is_wide = fail;
        inline bool _read_key_base( key_info_t& ) noexcept { return fail; }
        inline bool _read_key_wide( key_info_t& ) noexcept { return fail; }
        inline bool flush_keys( ) noexcept { return fail; }
        inline bool reset_color( ) noexcept { return fail; }
        inline _text::len_t write_msg( _text::str_base, _text::len_t ) noexcept { return zero; }
        inline _text::len_t write_msg( _text::str_wide, _text::len_t ) noexcept { return zero; }
        inline _text::len_t write_err( _text::str_base, _text::len_t ) noexcept { return zero; }
        inline _text::len_t write_err( _text::str_wide, _text::len_t ) noexcept { return zero; }
        namespace _property
        {
            inline bool try_get_background_color( color& ) noexcept { return fail; }
            inline bool try_set_background_color( color&& ) noexcept { return fail; }
            inline bool try_get_foreground_color( color& ) noexcept { return fail; }
            inline bool try_set_foreground_color( color&& ) noexcept { return fail; }
            inline bool try_get_cursor_rows( bufferX_t& ) noexcept { return fail; }
            inline bool try_set_cursor_rows( bufferX_t&& ) noexcept { return fail; }
            inline bool try_get_cursor_cols( bufferY_t& ) noexcept { return fail; }
            inline bool try_set_cursor_cols( bufferY_t&& ) noexcept { return fail; }
            inline bool try_get_cursor_pos( bufferPos_t& ) noexcept { return fail; }
            inline bool try_set_cursor_pos( bufferPos_t&& ) noexcept { return fail; }
            inline bool try_get_cursor_visible( bool& ) noexcept { return fail; }
            inline bool try_set_cursor_visible( bool&& ) noexcept { return fail; }
            inline bool try_get_window_rows_l( bufferX_t& ) noexcept { return fail; }
            inline bool try_get_window_rows_r( bufferX_t& ) noexcept { return fail; }
            inline bool try_get_window_cols_t( bufferY_t& ) noexcept { return fail; }
            inline bool try_get_window_cols_b( bufferY_t& ) noexcept { return fail; }
            inline bool try_get_window_pos_tl( bufferPos_t& ) noexcept { return fail; }
            inline bool try_get_window_pos_br( bufferPos_t& ) noexcept { return fail; }
            inline bool try_get_window_limit_r( bufferX_t& ) noexcept { return fail; }
            inline bool try_get_window_limit_b( bufferY_t& ) noexcept { return fail; }
            inline bool try_get_window_limit_br( bufferPos_t& ) noexcept { return fail; }
            inline bool try_get_window_size( bufferSze_t& ) noexcept { return fail; }
            inline bool try_get_window_area( bufferArea_t& ) noexcept { return fail; }
            inline bool try_get_title( _text::wstring& ) noexcept { return fail; }
            inline bool try_set_title( _text::view_wide_str&& ) noexcept { return fail; }
            inline bool try_get_capslock( bool& ) noexcept { return fail; }
            inline bool try_set_capslock( bool&& ) noexcept { return fail; }
            inline bool try_get_numberlock( bool& ) noexcept { return fail; }
            inline bool try_set_numberlock( bool&& ) noexcept { return fail; }
            inline bool try_get_keyavailable( bool& ) noexcept { return fail; }
        }
    #endif
    //
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __write( _text::_str<T_Chr> str ) {
        return write_msg( str, _text::nt_len( str ) );
    }
    template < _cpu::check_any_chr T_Chr, size_t T_len >
    inline _text::len_t __write( const T_Chr(&str)[T_len] ) {
        return write_msg( str, T_len );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __write( const T_Chr* const& str ) {
        return write_msg( str, _text::nt_len( str ) );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __write( const T_Chr* const&& str ) {
        return __write( str );
    }
    template < _cpu::check_any_chr T_Chr >
        requires ( !_cpu::check_any_nat<T_Chr> && !_cpu::check_any_int<T_Chr> && !_cpu::check_any_flt<T_Chr> && !_cpu::check_bool<T_Chr> )
    inline _text::len_t __write( T_Chr chr ) {
        return write_msg( &chr, unit );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __write( _text::_edit<T_Chr>& edit) {
        return write_msg( edit.str( ), edit.len( ) );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __write( _text::_edit<T_Chr>&& edit) {
        return __write<T_Chr>( edit );
    }
    template < _cpu::check_any_nat T_Nat >
    inline _text::len_t __write( T_Nat v, _text::len_t min_w = unit ) {
        return __write<_cpu::chr_base>( _text::edit_base{ v, min_w } );
    }
    template < _cpu::check_any_int T_Int >
    inline _text::len_t __write( T_Int v, _text::len_t min_w = unit ) {
        return __write<_cpu::chr_base>( _text::edit_base{ v, min_w } );
    }
    template < _cpu::check_any_flt T_Flt >
    inline _text::len_t __write( T_Flt v, size_t prec = _text::__flt_default_prec( _cpu::val_flt_fraction<T_Flt>, 10 ) ) {
        return __write<_cpu::chr_base>( _text::edit_base{ v, prec } );
    }
    template < _cpu::check_bool T_Bool >
    inline _text::len_t __write( T_Bool v ) {
        return __write<_cpu::chr_base>( _text::edit_base{ v } );
    }
    template < _cpu::check_any_chr T_Chr = _cpu::chr_base >
    inline _text::len_t __write( _mem::_raw_ptr<void> ptr ) {
        return __write<T_Chr>( _text::_edit<T_Chr>( ptr ) );
    }
    //
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __error( _text::_str<T_Chr> str ) {
        return write_err( str, _text::nt_len( str ) );
    }
    template < _cpu::check_any_chr T_Chr, size_t T_len >
    inline _text::len_t __error( const T_Chr(&str)[T_len] ) {
        return write_err( str, T_len );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __error( const T_Chr* const& str ) {
        return write_err( str, _text::nt_len( str ) );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __error( const T_Chr* const&& str ) {
        return __error( str );
    }
    template < _cpu::check_any_chr T_Chr >
        requires ( !_cpu::check_any_nat<T_Chr> && !_cpu::check_any_int<T_Chr> && !_cpu::check_any_flt<T_Chr> && !_cpu::check_bool<T_Chr> )
    inline _text::len_t __error( T_Chr chr ) {
        return write_err( &chr, unit );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __error( _text::_edit<T_Chr>& edit) {
        return write_err( edit.str( ), edit.len( ) );
    }
    template < _cpu::check_any_chr T_Chr >
    inline _text::len_t __error( _text::edit_base&& edit) {
        return __error<T_Chr>( edit );
    }
    template < _cpu::check_any_nat T_Nat >
    inline _text::len_t __error( T_Nat v, _text::len_t min_w = unit ) {
        return __error<_cpu::chr_base>( _text::edit_base{ v, min_w } );
    }
    template < _cpu::check_any_int T_Int >
    inline _text::len_t __error( T_Int v, _text::len_t min_w = unit ) {
        return __error<_cpu::chr_base>( _text::edit_base{ v, min_w } );
    }
    template < _cpu::check_any_flt T_Flt >
    inline _text::len_t __error( T_Flt v, size_t prec = _text::__flt_default_prec( _cpu::val_flt_fraction<T_Flt>, 10 ) ) {
        return __error<_cpu::chr_base>( _text::edit_base{ v, prec } );
    }
    template < _cpu::check_bool T_Bool >
    inline _text::len_t __error( T_Bool v ) {
        return __error<_cpu::chr_base>( _text::edit_base{ v } );
    }
    //
    /// @brief writes text on the console
    /// @tparam ...T_Args
    /// @param ...args
    /// @return the length in written characters
    template < typename... T_Args >
    inline _text::len_t write( T_Args&&... args ) {
        _text::len_t len = zero;
        ( ( len += __write( _type::forward<T_Args>( args ) ) ), ... );
        return len;
    }
    /// @brief writes an error on the console
    /// @tparam ...T_Args 
    /// @param ...args 
    /// @return the length in written characters
    template < typename... T_Args >
    inline _text::len_t error( T_Args&&... args ) {
        _text::len_t len = zero;
        ( ( len += __error( _type::forward<T_Args>( args ) ) ), ... );
        return len;
    }
    //
    constexpr _text::len_t __read_base_maxlen = 256;
    constexpr _text::len_t __read_wide_maxlen = 192;
    /// @brief read user input string
    /// @return 
    inline _text::bstring _readb( ) {
        _cpu::chr_base buffer[__read_base_maxlen];
        Fcool::_text::len_t input_len = read_msg( buffer, __read_base_maxlen );
        return { buffer, input_len };
    }
    /// @brief read user input string
    /// @return 
    inline _text::wstring _readw( ) {
        _cpu::chr_wide buffer[__read_wide_maxlen];
        Fcool::_text::len_t input_len = read_msg( buffer, __read_wide_maxlen );
        return { buffer, input_len };
    }
    //
    inline bool _read_key( key_info_t& out ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( out );
        else
            return _read_key_base( out );
    }
    inline bool _read_key_pressed_base( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_base( key ) ) {
                if ( is_pressed( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool _read_key_pressed_wide( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_wide( key ) ) {
                if ( is_pressed( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool _read_key_pressed( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_pressed_wide( out, query_limit );
        else
            return _read_key_pressed_base( out, query_limit );
    }
    inline bool _read_key_released_base( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_base( key ) ) {
                if ( is_released( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool _read_key_released_wide( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_wide( key ) ) {
                if ( is_released( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool _read_key_released( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_released_wide( out, query_limit );
        else
            return _read_key_released_base( out, query_limit );
    }
    inline bool read_key_base( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_base( key ) ) {
                if ( is_vk( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key_wide( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_wide( key ) ) {
                if ( is_vk( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key( key_info_t& out ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( out );
        else
            return _read_key_base( out );
    }
    inline bool read_key_pressed_base( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_base( key ) ) {
                if ( is_vk( key ) && is_pressed( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key_pressed_wide( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_wide( key ) ) {
                if ( is_vk( key ) && is_pressed( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key_pressed( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        if ( __read_key_default_is_wide )
            return read_key_pressed_wide( out, query_limit );
        else
            return read_key_pressed_base( out, query_limit );
    }
    inline bool read_key_released_base( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_base( key ) ) {
                if ( is_vk( key ) && is_released( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key_released_wide( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key_wide( key ) ) {
                if ( is_vk( key ) && is_released( key ) ) {
                    out = key;
                    return pass;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    inline bool read_key_released( key_info_t& out, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        if ( __read_key_default_is_wide )
            return read_key_released_wide( out, query_limit );
        else
            return read_key_released_base( out, query_limit );
    }
    //
    inline key_info_t _read_key_base( bool& r ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_base( key ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_base( ) noexcept {
        key_info_t key;
        if ( _read_key_base( key ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_wide( bool& r ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_wide( key ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_wide( ) noexcept {
        key_info_t key;
        if ( _read_key_wide( key ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key( bool& r ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( r );
        else
            return _read_key_base( r );
    }
    inline key_info_t _read_key( ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( );
        else
            return _read_key_base( );
    }
    inline key_info_t _read_key_pressed_base( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_pressed_base( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_pressed_base( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_pressed_base( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_pressed_wide( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_pressed_wide( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_pressed_wide( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_pressed_wide( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_pressed( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_pressed( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_pressed( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_pressed( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released_base( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_released_base( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released_base( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_released_base( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released_wide( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_released_wide( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released_wide( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_released_wide( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = _read_key_released( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t _read_key_released( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( _read_key_released( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_base( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_base( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_base( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_base( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_wide( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_wide( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_wide( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_wide( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key( bool& r ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( r );
        else
            return _read_key_base( r );
    }
    inline key_info_t read_key( ) noexcept {
        if ( __read_key_default_is_wide )
            return _read_key_wide( );
        else
            return _read_key_base( );
    }
    inline key_info_t read_key_pressed_base( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_pressed_base( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_pressed_base( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_pressed_base( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_pressed_wide( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_pressed_wide( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_pressed_wide( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_pressed_wide( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_pressed( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_pressed( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_pressed( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_pressed( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released_base( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_released_base( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released_base( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_released_base( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released_wide( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_released_wide( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released_wide( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_released_wide( key, query_limit ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released( bool& r, size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( ( r = read_key_released( key, query_limit ) ) )
            return key;
        else
            return { };
    }
    inline key_info_t read_key_released( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) noexcept {
        key_info_t key;
        if ( read_key_released( key, query_limit ) )
            return key;
        else
            return { };
    }
    /// @brief wait for user input
    /// @tparam T_Chr 
    /// @return true if pressed enter and fail if pressed escape
    inline bool wait_input( size_t query_limit = _cpu::val_max_int<_cpu::int_dual> ) {
        key_info_t key;
        size_t i = zero;
        while ( query_limit > i ) {
            if ( _read_key( key ) ) {
                if ( is_vk( key ) && is_pressed( key ) ) {
                    if ( key == VKey::Enter || key == VKey::Spacebar )
                        return pass;
                    if ( key == VKey::Escape || key == VKey::Backspace )
                        return fail;
                }
                i = zero;
            }
            else ++i;
        }
        return fail;
    }
    //
}


#endif





