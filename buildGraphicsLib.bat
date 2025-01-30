echo off
cls

REM ////////////////////////////////////////////////////////////////////////
REM /////////                        VAR                           /////////
REM ////////////////////////////////////////////////////////////////////////

setlocal enabledelayedexpansion


SET sources=
REM Libraries\src\ThirdParty\glad\glad.c
for /f "delims=" %%f in ('dir /b /a-d Libraries\src\Graphics\*.cpp') do SET sources=!sources! Libraries\src\Graphics\%%f

SET includes=-I Libraries/includes -I Libraries/includes/ThirdParty -I Libraries\includes\Graphics -I Libraries\includes\Profiler
SET links=-L Libraries/libs/ThirdParty -lglfw3dll -lglad -lstb_image -L Libraries/libs/Profiler -lprofiler


rmdir "Libraries\libs\Graphics" /S /Q
if not exist "Libraries\libs\Graphics" mkdir "Libraries\libs\Graphics"

echo Building Graphics.dll
g++ -std=c++23 -Wall -Wextra -Werror -O3 -m64 -shared -o Libraries/libs/Graphics/graphics.dll %sources% %includes% %defines% %links% && (
    echo Compilation successful
)