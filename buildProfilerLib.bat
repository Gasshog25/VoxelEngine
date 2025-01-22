echo off
cls

REM ////////////////////////////////////////////////////////////////////////
REM /////////                        VAR                           /////////
REM ////////////////////////////////////////////////////////////////////////

setlocal enabledelayedexpansion


SET sources=
for /f "delims=" %%f in ('dir /b /a-d Libraries\src\Profiler\*.cpp') do SET sources=!sources! Libraries\src\Profiler\%%f

SET includes=-I Libraries/includes -I Libraries/includes/ThirdParty -I Libraries\includes\Graphics -I Libraries\includes\Profiler
SET links=


rmdir "Libraries\libs\Profiler" /S /Q
if not exist "Libraries\libs\Profiler" mkdir "Libraries\libs\Profiler"

echo Building Profiler.dll
g++ -std=c++23 -Wall -Wextra -Werror -O3 -m64 -shared -o Libraries/libs/Profiler/profiler.dll %sources% %includes% %defines% %links% && (
    echo Compilation successful
)