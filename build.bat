@echo off
setlocal enabledelayedexpansion


set "DIR_SRC=src\win"
set "DIR_INC=inc"

set "DIR_BIN=bin"
if exist "!DIR_BIN!" rmdir /s /q "!DIR_BIN!"
mkdir "!DIR_BIN!"
set LIBNAME=Fcoolib-win

set "DIR_RUN=run"

set "GPP_ARGS=-Wall -Wextra -Wpedantic -Werror -pedantic-errors -Wconversion -Wsign-conversion -Wshadow -Wold-style-cast -Wcast-align -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wdouble-promotion -Wformat=2"
set "GPP_OPTI=-nostdinc++ -nostdlib++ -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-elide-constructors"
set "GPP_BASE=-m64 -std=c++20"

echo building !DIR_SRC!

for %%I in ( "!DIR_SRC!\*" ) do (
    set "SRC=%%~fI"
    set "OBJ=!DIR_BIN!\%%~nxI.o"
    ::
    echo Compiling !OBJ! ...
    g++ !GPP_BASE! !GPP_OPTI! !GPP_ARGS! -c "!SRC!" -I"!DIR_INC!" -o "!OBJ!"
    if errorlevel 1 exit /b 1
    set "OBJ_LIST=!OBJ_LIST! "!OBJ!""
)
set "OBJ_LIST=!OBJ_LIST! "
echo Objects=[!OBJ_LIST!];

echo Compiling !LIBNAME!

ar rcs "!DIR_BIN!\lib!LIBNAME!.a" !OBJ_LIST!
if errorlevel 1 exit /b 1

set "RUN_EXE=!DIR_BIN!\run.exe"
echo Compiling !RUN_EXE!

g++ !GPP_BASE! "!DIR_RUN!\*" -I"!DIR_INC!" -L"!DIR_BIN!" -l!LIBNAME! -o "!RUN_EXE!"
if errorlevel 1 exit /b 1

echo Run!

!RUN_EXE!

set "EXIT_CODE=!ERRORLEVEL!"
echo Done (code: !EXIT_CODE!).
exit /b !EXIT_CODE!


