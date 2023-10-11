# Documentation

## List of Functions

+ `void initConsole()`
+ `void setConsoleTitle(const char* title)`
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
+ `TextUi* copyTextUi(const TextUi* ui)`
+ `BOOL saveTextUi(TextUi* ui, const char* filepath)`
+ `void drawTextUi(TextUi* ui, CursorAnchor* anchor)`
+ `TextUi* rotateTextUi(TextUi* ui, BOOL clockwise)`
+ `void flipTextUi(TextUi* ui, BOOL vertical)`
+ `void deleteTextUi(TextUi* ui)`
+ `TextUiShape* getTextUiShape(TextUiShape* shape, TextUi* ui)`
+ `TextUiShape* copyTextUiShape(TextUiShape* shape)`
+ `void deleteTextUiShape(TextUiShape* shape)`

## Basic Control

+ ~~~c
  void initConsole()
  ~~~

  This function is used to get console handle, thus it must be called before all other functions are called.

+ ```c
  void setConsoleTitle(const char* title)
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

## Cursor Control

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

## Keyboard Events

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

## Text Attribute

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

## Text UI

Text UI allows you to use text file as a UI file. For example, you can write a menu UI in a `.txt` file, then let Text UI to draw it on the console.

To make a text file usable for Text UI, `linebreaks` MUST be `LF`.

+ ```c
  typedef struct __ASCII_SIMPLE_TEXT_UI TextUi
  ```

  Defines the type of Text UI.

+ ```c
  typedef struct ___ASCII_TEXT_UI_SHAPE TextUiShape
  ```

  Defines the type of the shape of Text UI. It contains a 2D `BYTE` array, and uses `1` for non empty characters, `0` for empty characters.

+ ```c
  TextUi* readTextUi(const char* filepath)
  ```

  Read file from `filepath` and create a `TextUi` instance.

  If read is failed, return `NULL`.

+ ```c
  TextUi* copyTextUi(const TextUi* ui)
  ```

  Create a `TextUi` instance from a existing one.

  Return `NULL` if `ui` is `NULL`.

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
  TextUi* rotateTextUi(TextUi* ui, BOOL clockwise)
  ```

  Rotate `TextUi` relative to its upper left.

  If `clockwilse` is `FALSE`, rotate counterclockwise.

+ ```c
  TextUi* flipTextUi(TextUi* ui, BOOL vertical)
  ```

  Flip `TextUi`.

  If `vertical` is `FALSE`, flip horizontally.

+ ```c
  void deleteTextUi(TextUi* ui)
  ```

  Delete `TextUi` instance, free memory of its data.
  
+ ```c
  TextUiShape* getTextUiShape(TextUiShape* shape, TextUi* ui)
  ```

  Create or update a `TextUiShape` instance from an existing `TextUi`.

  If `shape` is `NULL`, create a new instance, otherwise update the existing `TextUiShape`.

+ ```c
  TextUiShape* copyTextUiShape(TextUiShape* shape)
  ```

  Create a `TextUiShape` instance from an existing `TextUiShape`.

  If `shape` is `NULL`, return `NULL`;

+ ```c
  void deleteTextUiShape(TextUiShape* shape)
  ```

  Delete `TextUiShape` instance and free memory.
