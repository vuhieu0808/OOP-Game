@echo off
echo =============================
echo 🚀 BUILDING THE SFML GAME...
echo =============================

:: Compile the C++ source code
g++ -Iinclude -Llib -o bin\main.exe main.cpp src\*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

:: Kiểm tra lỗi biên dịch
if %ERRORLEVEL% NEQ 0 (
    echo ❌ COMPILE ERROR!
    pause
    exit /b %ERRORLEVEL%
)

:: Copy các DLL vào thư mục chạy
echo ✅ Copying runtime DLLs to bin\...
xcopy /Y dll\*.dll bin\

:: Chạy game
echo =============================
echo 🎮 RUNNING THE GAME...
echo =============================
bin\main.exe
pause
