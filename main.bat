@echo off
echo =============================
echo BUILDING THE SFML GAME...
echo =============================

:: Compile the C++ source code with tinyxml2
g++ -Iinclude -Iinclude/tinyxml2 -Llib -o bin\main.exe main.cpp src\*.cpp src\menu\*.cpp src\menu\commands\*.cpp src\menu\states\*.cpp include/tinyxml2/tinyxml2.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

:: Kiểm tra lỗi biên dịch
if %ERRORLEVEL% NEQ 0 (
    echo COMPILE ERROR!
    pause
    exit /b %ERRORLEVEL%
)

:: Copy các DLL vào thư mục chạy
echo Copying runtime DLLs to bin\...
xcopy /Y dll\*.dll bin\

:: Chạy game
echo =============================
echo RUNNING THE GAME...
echo =============================
bin\main.exe
pause