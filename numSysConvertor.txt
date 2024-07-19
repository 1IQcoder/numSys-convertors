@echo off
set title_script=numSys convertor
title %title_script%
setlocal enabledelayedexpansion

for /F "delims=#" %%a in ('prompt #$E# ^& for %%a in ^(1^) do rem') do set "ESC=%%a"
set "alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ"

:start
echo %ESC%[33;1m=====================%ESC%[0m
set /p "fsys=FROM system: "
set /p "tsys=TO system: "
set /p "str=Number: "
call :getLen %str% len
if %fsys% NEQ 10 (
    call :toDec %str% !len! %fsys% decnum
) else (
    set "decnum=%str%"
)
echo %ESC%[32;102mDEC: !decnum!
call :fromDec !decnum! %tsys% hexnum
echo %tsys% base system: !hexnum!%ESC%[0m
goto :start

pause
exit


rem Преобразование букв в числовой код (%1symbol, %2res)
:charToInt
    setlocal
    set "i=-1"
        :loop2
        set /a "i+=1"
        set "elem=!alphabet:~%i%,1!"
        if "%elem%" NEQ "%1" goto :loop2
    set /a "res=i+10"
    endlocal & set "%~2=%res%"
goto :eof


:intToChar
    setlocal
    set /a "num=%1-10"
    set "char=!alphabet:~%num%,1!"
    endlocal & set "%~2=%char%"
goto :eof


@REM Получение длинны строки
:getLen
    setlocal
    set "len=0"
        :loop1
        if not "!str:~%len%,1!"=="" set /a len+=1 & goto loop1
    endlocal & set "%~2=%len%"
goto :eof


@REM (%1строка, %2длинна, %3fsys, %4result)
:toDec
    setlocal
    set "str=%1"
    set "i=%2"
    set "x=-1"
    set "res=0"
    set "fsys=%3"
    set "pow=1"

    :loop4
    set /a "i-=1"
    set /a "x+=1"
    set "char=!str:~%i%,1!"

    @REM Проверка на букву
    if %char% EQU 0 goto :skip1
    set /a "isNum=10-char"
    if %isNum% NEQ 10 goto :skip1
    @REM Преобразование буквы в число
    call :charToInt %char% int
    set "char=!int!"

    :skip1
    if %x% EQU 0 (
        set /a "res+=%char%"
    ) else (
        set /a "res+=%char%*%fsys%*%pow%"
        set /a "pow*=%fsys%"
    )
    if %i% NEQ 0 goto :loop4

    endlocal & set "%~4=%res%"
goto :eof


@REM (%1dec-число, %2tsys, %3result)
:fromDec
    set "num=%1"
    set "tsys=%2"
    set "res="
    :fdLoop
    set /a "ost=num%%tsys"
    set /a "num/=tsys"
    if %ost% GTR 9 (
        @REM число в букву
        call :intToChar %ost% char
        set "ost=!char!"
    )
    set "res=%ost%%res%"
    if %num% NEQ 0 goto :fdLoop
    endlocal & set "%~3=%res%"
goto :eof

