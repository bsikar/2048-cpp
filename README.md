# 2048 Game

2048 is a popular puzzle game where the player slides numbered tiles on a grid to combine them and create a tile with the number 2048. This project includes a C++ implementation of the game and a test maker written in Python and C++ using OpenCV and PyTesseract for image processing.

## Features

- A GUI interface for the 2048 game in C++
- A test maker that generates test cases for the game using image processing techniques

## Build and run

To build this project, open "Terminal" and type the following lines:

### Windows :

```
mkdir build && cd build
cmake ..
start 2048.sln
```

Select any project and type Ctrl+F5 to build and run it.

### macOS :

```
mkdir build && cd build
cmake .. -G "Xcode"
open ./2048.xcodeproj
```

Select any project and type Cmd+R to build and run it.

### Linux :

```
mkdir build && cd build
cmake ..
cmake --build . --config Debug
./src/2048
```

## Contributing

Contributions to the project are welcome. If you find a bug or want to add a feature, feel free to open an issue or submit a pull request.

## License

The code in this project is licensed under the MIT License. See the LICENSE file for details.

