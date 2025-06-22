@echo off
echo Build and Run 
g++ -o bin\main main.cpp src\game.cpp src\map.cpp src\camera.cpp src\player.cpp -lsfml-graphics -lsfml-window -lsfml-system

if %ERRORLEVEL% NEQ 0 (
    echo Compile Error
    pause
    exit /b %ERRORLEVEL%
)

echo Run Game:
bin\main.exe
pause
