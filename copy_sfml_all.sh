#!/bin/bash

# Thư mục đích trong project
INCLUDE_DIR="./include"
LIB_DIR="./lib"
DLL_DIR="./dll"

# Tạo các thư mục nếu chưa có
mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DLL_DIR"

echo "➡️ Copying SFML include files..."
cp -r /mingw64/include/SFML "$INCLUDE_DIR/"
echo "✅ Include files copied to $INCLUDE_DIR/SFML/"

echo "➡️ Copying SFML .dll.a (linker libraries)..."
cp /mingw64/lib/libsfml-graphics.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-window.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-system.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-audio.dll.a "$LIB_DIR/"
echo "✅ Libraries copied to $LIB_DIR/"

echo "➡️ Copying runtime .dll files..."
DLL_LIST=(
    "libsfml-graphics-2.dll"
    "libsfml-window-2.dll"
    "libsfml-system-2.dll"
    "libsfml-audio-2.dll"
    "libfreetype-6.dll"
    "libopenal-1.dll"
    "libsndfile-1.dll"
    "libogg-0.dll"
    "libvorbis-0.dll"
    "libvorbisfile-3.dll"
)

for dll in "${DLL_LIST[@]}"; do
    src="/mingw64/bin/$dll"
    if [[ -f "$src" ]]; then
        cp "$src" "$DLL_DIR/"
        echo "✅ Copied: $dll"
    else
        echo "⚠️ Not found: $dll"
    fi
done

echo "🎉 All SFML files copied successfully."
