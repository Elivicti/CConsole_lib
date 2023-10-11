# Console Library for C on Windows

[toc]

## Description

Encapsulated some of the most-used APIs in `Windows.h` and `conio.h`, for a better and more convenient use.

As this library uses `Windows.h`, it will _**only**_ work on Windows.

And it's also my final homework of C language class.

## How To Build

1. Use `git clone` command or other method to download all source files.

   ```powershell
   git clone https://github.com/Elivicti/CConsole_lib.git
   ```

2. Run `build.bat`, and it will automatically build and generate a `CConsole.lib` file under `.\build\` folder:

   _NOTE_: `build.bat` uses `gcc` compiler. Please make sure it's properly installed.
   
   ```powershell
   .\build.bat
   ```

   `build.bat` also provide a convenient functionality to run a quick test.
   
   + `.\build.bat test` will build and compile source file under `.\test`
   + `.\build.bat test -r` will build, compile source file under `.\test`, and run `test.exe`
   
   You will find lib file under `build\src` and exe file under `build\test`.
   
   Or use `CMake`:
   
   ```powershell
   mkdir build
   ```
   ```powershell
   cd build
   ```
   ```powershell
   cmake ..
   ```
   ```powershell
   make .
   ```
   You will find lib file under `build\src` and exe file under `build\test`.

# Documentation

See [Documentation](Documentation.md)













