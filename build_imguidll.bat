echo off
setlocal enabledelayedexpansion

set sources=Libraries\src\ThirdParty\glad\glad.c
for /f "delims=" %%f in ('dir /b /a-d Libraries\src\ThirdParty\imgui\*.cpp') do SET sources=!sources! Libraries\src\ThirdParty\imgui\%%f

SET includes=-I Libraries/includes -I Libraries/includes/ThirdParty -I Libraries\includes\Graphics
set links=-L Libraries/libs/ThirdParty -lglfw3dll

echo file:
echo %sources%
echo/
echo Building ImGui.dll...
g++ -std=c++20 -shared -o Libraries/libs/ThirdParty/imgui.dll %includes% %sources% %links% && (
    echo Compilation successful 
    exit 0
)