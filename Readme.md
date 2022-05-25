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
   + `.\build.bat test -r` will build, compile source file under `.\test`, and run `test.exe`
   
   Or use `gcc` compiler and `ar` command.
   
   ```powershell
   gcc -std=c11 -c CConsole_lib.c
   ar -cr CConsole.lib CConsole_lib.o
   ```
   
   You may delete `CConsole_lib.o` as it's an intermediate file in the build process.

## How to Use

There are mainly two ways to use this library in your program.

1. Use `CConsole.h`

   Put `CConsole.h`, `CConsole_lib.h` and `CConsole.lib` in your source folder, then simply include `CConsole.h` in your program.

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

### List of Functions

+ `void initConsole()`
+ `void setTitle(const char* title)`
+ `void setCursorVisible(BOOL visible)`
+ `void clearConsole()`
+ `CursorAnchor createCursorAnchor(SHORT x, SHORT y)`
+ `void setCursorAnchor(CursorAnchor* anchor, SHORT x, SHORT y)`
+ `void moveCursorAnchor(CursorAnchor* anchor, SHORT dx, SHORT dy)`
+ `CursorAnchor getCursor()`
+ `void setCursor(CursorAnchor* anchor)`
+ `void moveCursor(SHORT dx, SHORT dy)`
+ `void setTextColor(StdColor col)`
+ `void setTextBackgroundColor(StdColor col)`
+ `void setTextAttribute(StdColor textColor, StdColor bgColor)`
+ `void resetTextAttribute(TextAttributeType attri)`
+ `void pauseConsole(const char* tip)`
+ `BOOL isCharKeyPressed(char ch)`
+ `BOOL isKeyPressed(KeyType key)`
+ `BOOL isKeyToggled(KeyType key)`
+ `int getPressedKey()`
+ `TextUi* readTextUi(const char* filepath)`
+ `BOOL saveTextUi(TextUi* ui, const char* filepath)`
+ `void drawTextUi(TextUi* ui, CursorAnchor* anchor)`
+ `void deleteTextUi(TextUi* ui)`

### Basic Control

+ ~~~c
  void initConsole()
  ~~~

  This function is used to get console handle, thus it must be called before all other functions are called.

+ ```c
  void setTitle(const char* title)
  ```

  Set the title of the console.

+ ```c
  void setCursorVisible(BOOL visible)
  ```

  Set the visibility of console cursor.

+ ```c
  void clearConsole()
  ```

  Clear all content on the console, and set cursor to the upper left.

+ ```c
  void pauseConsole(const char* tip)
  ```

  Pause console until user hit a key, and print `tip` as a tooltip.

### Cursor Control

+ ```c
  typedef struct __C_Console_Cursor_Anchor_Instance CursorAnchor
  ```

  Define an anchor for cursor. To the right is the `X` direction, and to the bottom is the `Y` direction.

+ ```c
  CursorAnchor createCursorAnchor(SHORT x, SHORT y)
  ```

  Create a `CursorAnchor` instance, and set it to `(x, y)`.

+ ```c
  void setCursorAnchor(CursorAnchor* anchor, SHORT x, SHORT y)
  ```

  Set `anchor` to `(x, y)`.

+ ```c
  void moveCursorAnchor(CursorAnchor* anchor, SHORT dx, SHORT dy)
  ```

  Move `anchor` relative to its current position.

+ ```c
  CursorAnchor getCursor()
  ```

  Create a `CursorAnchor` instance, and set it to current cursor position.

+ ```c
  void setCursor(CursorAnchor* anchor)
  ```

  Set cursor position to `anchor`'s position.

+ ```c
  void moveCursor(SHORT dx, SHORT dy)
  ```

  Move cursor relative to its current position.

### Keyboard Events

+ ```c
  typedef enum __STD_KEY_TYPE KeyType
  ```

  Wrapped `VK_` macros of some most used keys.

  | Value  | `VK_` Macro |     Key     |
  | :----: | :---------: | :---------: |
  |  ESC   |  VK_ESCAPE  |     ESC     |
  |  TAB   |   VK_TAB    |     Tab     |
  |  CAP   | VK_CAPITAL  |  CapsLock   |
  | Space  |  VK_SPACE   |    Space    |
  | Shift  |  VK_SHIFT   |    Shift    |
  | LShift |  VK_LSHIFT  | Left Shift  |
  | RShift |  VK_RSHIFT  | Right Shift |
  |  Alt   |   VK_MENU   |     Alt     |
  |  LAlt  |  VK_LMENU   |  Left Alt   |
  |  RAlt  |  VK_RMENU   |  Right Alt  |
  |  Ctrl  | VK_CONTROL  |    Ctrl     |
  | LCtrl  | VK_LCONTROL |  Left Ctrl  |
  | RCtrl  | VK_RCONTROL | Right Ctrl  |
  |   Up   |    VK_UP    |  Up Arrow   |
  |  Down  |   VK_DOWN   | Down Arrow  |
  |  Left  |   VK_LEFT   | Left Arrow  |
  | Right  |  VK_RIGHT   | Right Arrow |

+ ```c
  BOOL isCharKeyPressed(char ch)
  ```

  Returns if character key (`ASCII` value) is pressed.

  This function will NOT wait for user input.

+ ```c
  BOOL isKeyPressed(KeyType key)
  ```

  Returns if a `KeyType` value key is pressed. Both `KeyType` values and `VK_` macros are supported.

  This function will NOT wait for user input.

+ ```c
  BOOL isKeyToggled(KeyType key)
  ```

  Checks if a key is toggled, primarily used for keys like`CapsLock`. Both `KeyType` values and `VK_` macros are supported.

  This function will NOT wait for user input.

+ ```c
  int getPressedKey()
  ```

  Returns the value of pressed key, `ASCII` value if pressed a character key, `KeyType` value if pressed other key. `VK_` macros are NOT supported.

  This function will wait for user input.

### Text Attribute

+ ```c
  typedef enum __STD_TEXT_ATTRIBUTE_TYPE TextAttributeType
  ```

  Defines the attribute type. Used in `resetTextAttribute()`.

  |      Name       |             Value              |     Attribute      |
  | :-------------: | :----------------------------: | :----------------: |
  |       All       | `TextColor \| BackgroundColor` | All Text Attribute |
  |    TextColor    |             `0b01`             |     Text Color     |
  | BackgroundColor |             `0b10`             |  Background Color  |

+ ```c
  typedef enum __STD_CONSOLE_COLOR StdColor
  ```

  Defines colors. All available colors are as follows.

  + `Black`
  + `DarkBlue`
  + `Green`
  + `LightBlue`
  + `DarkRed`
  + `Purple`
  + `Yellow`
  + `LightGray`
  + `Gray`
  + `Blue`
  + `Lime`
  + `Cyan`
  + `Red`
  + `Megenta`
  + `Gold`
  + `White`


+ ```c
  void setTextColor(StdColor col)
  ```

  Set the color of the text.

+ ```c
  void setTextBackgroundColor(StdColor col)
  ```

  Set the color of text background.

+ ```c
  void setTextAttribute(StdColor textColor, StdColor bgColor)
  ```

  Set the color of text and background at the same time.

+ ```c
  void resetTextAttribute(TextAttributeType attri)
  ```

  Reset text attribute to default. By default, text color is `LightGray`, background color is `Black`.

### Text UI

Text UI allows you to use text file as a UI file. For example, you can write a menu UI in a `.txt` file, then let Text UI to draw it on the console.

To make a text file usable for Text UI, `linebreaks` MUST be `LF`.

+ ```c
  typedef struct __ASCII_SIMPLE_TEXT_UI TextUi
  ```

  Defines the instance of Text UI.

+ ```c
  TextUi* readTextUi(const char* filepath)
  ```

  Read file from `filepath` and create a `TextUi` instance.

  If read is failed, return `NULL`.

+ ```c
  BOOL saveTextUi(TextUi* ui, const char* filepath)
  ```

  Save `TextUi` instance to a file. If target file does not exist, it will create one.

  Return if the saving process is successful.

+ ```c
  void drawTextUi(TextUi* ui, CursorAnchor* anchor)
  ```

  Draws the `ui` on the console. The cursor starts at `anchor` position.

  After draw completes, the cursor stays at the end of `ui`, but `anchor` will not be changed.

+ ```c
  void deleteTextUi(TextUi* ui)
  ```

  Delete `TextUi` instance, free memory of its data.



















