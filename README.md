## Build and run

To build this project, open "Terminal" and type following lines:

### Windows :

``` shell
mkdir build && cd build
cmake ..
start 2048.sln
```

Select any project and type Ctrl+F5 to build and run it.

### macOS :

``` shell
mkdir build && cd build
cmake .. -G "Xcode"
open ./2048.xcodeproj
```

Select any project and type Cmd+R to build and run it.

### Linux :

``` shell
mkdir build && cd build
cmake ..
cmake --build . --config Debug
./2048
```

