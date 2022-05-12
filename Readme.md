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

2. Run `build.bat`, and it will automatically build and generate a `CConsole.lib` file under `.\build\` folder.

   ```powershell
   .\build.bat
   ```

   `build.bat` also provide a convenient functionality to run a quick test.

   + `.\build.bat test` will build and compile source file under `.\test`
   + `.\build.bat test` will build, compile source file under `.\test`, and run `test.exe`
   
   Or use `gcc` compiler and `ar` command.
   
   ```powershell
   gcc -std=c11 -c CConsole_lib.c
   ar -cr CConsole.lib CConsole_lib.o
   ```
   
   You may delete `CConsole_lib.o` as it's an intermediate file in the build process.

## How to Use

There are mainly two ways to use this library in your program.

1. Use `CConsole.h`

   Put `CConsole.h`, `CConsole_lib.h` and `CConsole.lib` in your source's folder, then simply include `CConsole.h` in your program.

   ```c
   #include <stdio.h>
   #include "CConsole.h"                // just include here
   int main()
   {
       initConsole();                   // must be called before all other CConsole functions are called
       setTextColor(Red);               // set text color to red
       printf("Hello CConsole!\n");
       resetTextAttribute(TextColor);   // reset text color to default
       return 0;
   }
   ```

2.  Use `CConsole_lib.h`

   Put `CConsole_lib.h` and `CConsole.lib` in your source folder, then include `CConsole_lib.h` in your program. Use `#pragma comment(lib,"CConsole.lib")` to link `.lib` file to your program.

   ```c
   #include <stdio.h>
   #include "CConsole_lib.h"
   #pragma comment(lib,"CConsole.lib")
   int main()
   {
       initConsole();                   // must be called before all other CConsole functions are called
       setTextColor(Red);               // set text color to red
       printf("Hello CConsole!\n");
       resetTextAttribute(TextColor);   // reset text color to default
       return 0;
   }
   ```


Note that all methods above have some issues when using `gcc` command line to compile. You may need to refer to the following command.

```powershell
gcc -std=c11 src.c -l:CConsole.lib -L.\ -o out.exe
```

Option `-l` is used to specify `.lib` file, `-L` is used to specify the path containing `.lib` file.

## Documentation

