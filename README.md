# Ardelio

A simple, lightweight 2D game engine written in C++ with SFML as the backend.

![ArdelioEditor](https://github.com/user-attachments/assets/212f783a-9ee4-4a47-9976-a91822b81488)

# Philosophy

Ardelio is built around the principle of simplicity. The entire engine architecture revolves around just two fundamental object types: `GameObject` (object with state) and `Resource` (object with no state). The idea is to give the developer the most control possible when developing games without any black-box type optimizations. The developer should always be aware of what's happening under the hood.

# Features
- Simple architecture
- Tree-based scene hierarchy
- Custom 2D physics engine
- Editor program for building scenes

# Dependencies
- SFML - Graphics, audio, input
- ImGUI - GUI for the editor
- CMake - Build system

# Getting Started
Before building the engine from source, you must have a **C++17 compiler** and **CMake 3.28+** installed.

1. Clone the repository
```
git clone https://github.com/snakeworks/ardelio.git
cd ardelio
```

2. Generate build files
```
cmake -B build
cmake -build build
```
This will build the Ardelio library and the editor.

3. Run Ardelio Editor (optional)
```
./build/ArdelioEditor[.exe]
```
