#!/bin/bash

# Thư mục đích trong project
INCLUDE_DIR="./include"
LIB_DIR="./lib"
DLL_DIR="./dll"

# Tạo các thư mục nếu chưa có
mkdir -p "$INCLUDE_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DLL_DIR"

## =============================
## COPY SFML FILES
## =============================
echo "➡️ Copying SFML include files..."
cp -r /mingw64/include/SFML "$INCLUDE_DIR/"
echo "✅ Include files copied to $INCLUDE_DIR/SFML/"

echo "➡️ Copying SFML .dll.a (linker libraries)..."
cp /mingw64/lib/libsfml-graphics.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-window.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-system.dll.a "$LIB_DIR/"
cp /mingw64/lib/libsfml-audio.dll.a "$LIB_DIR/"
echo "✅ SFML libraries copied to $LIB_DIR/"

echo "➡️ Copying SFML runtime .dll files..."
SFML_DLL_LIST=(
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

for dll in "${SFML_DLL_LIST[@]}"; do
    src="/mingw64/bin/$dll"
    if [[ -f "$src" ]]; then
        cp "$src" "$DLL_DIR/"
        echo "✅ Copied: $dll"
    else
        echo "⚠️ Not found: $dll"
    fi
done

## =============================
## COPY TINYXML2 FILES
## =============================
echo "➡️ Copying TinyXML2 files..."

# Tạo thư mục tinyxml2 trong include
mkdir -p "$INCLUDE_DIR/tinyxml2"

# Copy header file
if [[ -f "/mingw64/include/tinyxml2.h" ]]; then
    cp "/mingw64/include/tinyxml2.h" "$INCLUDE_DIR/tinyxml2/"
    echo "✅ Copied: tinyxml2.h"
else
    echo "⚠️ TinyXML2 header not found in /mingw64/include/"
fi

# Copy library files
if [[ -f "/mingw64/lib/libtinyxml2.dll.a" ]]; then
    cp "/mingw64/lib/libtinyxml2.dll.a" "$LIB_DIR/"
    echo "✅ Copied: libtinyxml2.dll.a"
fi

if [[ -f "/mingw64/lib/libtinyxml2.a" ]]; then
    cp "/mingw64/lib/libtinyxml2.a" "$LIB_DIR/"
    echo "✅ Copied: libtinyxml2.a"
fi

# Copy DLL file
if [[ -f "/mingw64/bin/libtinyxml2.dll" ]]; then
    cp "/mingw64/bin/libtinyxml2.dll" "$DLL_DIR/"
    echo "✅ Copied: libtinyxml2.dll"
else
    echo "⚠️ TinyXML2 DLL not found in /mingw64/bin/"
fi

echo "🎉 All files (SFML + TinyXML2) copied successfully."