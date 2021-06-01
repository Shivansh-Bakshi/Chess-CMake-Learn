# Chess
This repository is my practice for understanding CMake and its usage to manage large projects.  
For this, I have modularised extensively, what seems to be overkill for a simple program such as Chess.  
This is all done for my understanding on the working of CMake in the process of building applications.  

## Build Instructions
In short, make a build directory inside the project folder, call cmake to configure in the build directory. Then build

```
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

Change the generator to whatever build system you prefer.