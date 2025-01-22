echo off
cls

REM ////////////////////////////////////////////////////////////////////////
REM /////////                        VAR                           /////////
REM ////////////////////////////////////////////////////////////////////////

setlocal enabledelayedexpansion


SET MainSource=src/main.cpp

SET sources=Libraries\src\ThirdParty\glad\glad.c
REM for /f "delims=" %%f in ('dir /b /a-d Libraries\src\Graphics\*.cpp') do SET sources=!sources! Libraries\src\Graphics\%%f
REM for /f "delims=" %%f in ('dir /b /a-d Libraries\src\Profiler\*.cpp') do SET sources=!sources! Libraries\src\Profiler\%%f
REM for /f "delims=" %%f in ('dir /b /a-d Libraries\src\*.cpp') do SET sources=!sources! Libraries\src\%%f

SET includes=-I Libraries/includes -I Libraries/includes/ThirdParty -I Libraries\includes\Graphics -I Libraries\includes\Profiler
SET links=-L Libraries/libs/ThirdParty -lglfw3dll -lstb_image -lpsapi -L Libraries/libs/Profiler -lprofiler -L Libraries/libs/Graphics -lgraphics

SET outputName=main

set defines=-D STB_IMAGE_IMPLEMENTATION
SET definesDEBUG=-D DEBUG -D NDEBUG
SET definesRELEASE=-D RELEASE

REM ////////////////////////////////////////////////////////////////////////
REM ////////////////////////////////////////////////////////////////////////
REM ////////////////////////////////////////////////////////////////////////

setlocal

REM 
set "IsDEBUG=true"
set "IsRELEASE=true"



for %%x in (%*) DO (
    set p=%%x1
    if /i "!p:~0,1!"=="-" (
        SET outputName="!p:~1,-1!"
    ) else if /i %%x==DEBUG (
        set "IsDEBUG=true"
        set "IsRELEASE=false"
    ) else if /i %%x==RELEASE  (
        set "IsDEBUG=false"
        set "IsRELEASE=true"
    ) else if exist src/%%x (
        SET MainSource=src/%%x
    )
)

echo File : %MainSource%
echo output name : %outputName%
echo/

REM BUILD DEBUG
if %IsDEBUG%==true (
    echo/
    rmdir "bin\debug" /S /Q
    if not exist "bin\debug" mkdir "bin\debug"
    echo Copy res to debug ...
    xcopy "res" "bin\debug\res" /E /I /H /Y
    echo/
    echo Copy lib to Debug
    for /D %%D IN (Libraries\libs\*) DO (
        xcopy %%D\*.dll "bin\debug\" /s /i /y /Q
        xcopy %%D\*.lib "bin\debug\" /s /i /y /Q
    )  
    echo/

    echo Building DEBUG...
    g++ %MainSource% %sources% -o bin/debug/%outputName% -std=c++23 -g -Og -Wall -Wextra -m64 %includes% %defines% %definesDEBUG% %links% && (
        echo Compilation successful 
        if %IsRELEASE%==false (
            start launch.exe -d -n %outputName%
        ) 
    )
    
)


REM BUILD RELEASE
if %IsRELEASE%==true (
    echo/
    rmdir "bin\release" /S /Q
    if not exist "bin\release" mkdir "bin\release"
    echo Copy res to release ...
    xcopy "res" "bin\release\res" /E /I /H /Y
    echo/
    echo Copy lib to release
    for /D %%D IN (Libraries\libs\*) DO (
        xcopy %%D\*.dll "bin\release\" /s /i /y /Q
        xcopy %%D\*.lib "bin\release\" /s /i /y /Q
    ) 
    echo/

    echo Building RELEASE...
    g++ %MainSource% %sources% -o bin/release/%outputName% -Wall -Wextra -Werror -std=c++23 -O3 -m64 %includes% %defines% %definesRELEASE% %links% && (
         echo Compilation successful 
         if %IsDEBUG%==false ( 
            start bin\release\%outputName%.exe 
        )
    )
)

REM g++ -std=c++23 -shared -o mylib.dll mylib.cpp