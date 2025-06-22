# 🎮 SFML Game Project

This is a simple 2D game built using **C++** and the **SFML** (Simple and Fast Multimedia Library).  
All required headers, libraries, and DLLs are included, so **no external SFML installation is required**.

---

## 📁 Project Structure

```
SFML_Game_Project/
├── include/           # SFML headers (Graphics.hpp, etc.)
├── lib/               # SFML linker libraries (.dll.a)
├── dll/               # Required SFML runtime DLLs
├── src/               # Game source code
├── main.cpp           # Entry point
├── game.bat           # Compile & run script for Windows
├── copy_sfml_all.sh   # Script to collect SFML components
├── bin/               # Output .exe (created after build)
└── README.md
```

---

## 🛠️ Requirements

- A **Windows system**
- Installed **MinGW-w64 (G++)** or **MSYS2 MinGW64 shell**
- No need to install SFML (already included)

---

## ⚙️ How to Compile & Run

### 🔸 On Windows using `game.bat`

1. Open `cmd.exe`
2. Navigate to project folder
3. Run:
   ```cmd
   game.bat
   ```

The compiled game will appear in `bin/main.exe` and will run automatically.

---

## 🧪 Alternative: Compile manually with g++

```bash
g++ -Iinclude -Llib -o bin/main.exe main.cpp src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
xcopy /Y dll\*.dll bin\
bin\main.exe
```

---

## 📦 Included SFML Version

This project includes:
- SFML headers from MSYS2 (`/mingw64/include/SFML`)
- Linker libraries (`libsfml-graphics.dll.a`, etc.)
- DLLs (`sfml-graphics-2.dll`, `libfreetype-6.dll`, `libopenal-1.dll`, ...)

All collected using the script: `copy_sfml_all.sh`.

---

## ✨ Notes

- If you want to build a **standalone installer or ZIP** for others, use:
  ```bash
  bash package_project.sh
  ```

- Make sure `g++` from MinGW-w64 is on your PATH when using `game.bat`

---

## 🔗 License

This game and source code are released for educational and non-commercial purposes.
