#ifndef __C_CONCOLE_LIB_HEADER___
#define __C_CONCOLE_LIB_HEADER___

#if !defined(_WIN32)
#error "CConsole Lib only works on Windows."
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <Windows.h>

/** @brief Cursor anchor. Defines the coordinate of the console cursor */
typedef struct __C_Console_Cursor_Anchor
{
	SHORT x;	// Cursor x
	SHORT y;	// Cursor y

#ifdef __cplusplus
	__C_Console_Cursor_Anchor() : x(0), y(0) {}
	__C_Console_Cursor_Anchor(SHORT _x, SHORT _y) : x(_x), y(_y) {}
#endif
} CursorAnchor;

typedef enum __STD_DEVICE_HANDLE_ENUM_TYPE
{
	StdIn  = STD_INPUT_HANDLE,		// Standard Input Device
	StdOut = STD_OUTPUT_HANDLE,		// Standard Output Device
	StdErr = STD_ERROR_HANDLE		// Standard Error Device
} StdDevice;

typedef enum __STD_CONSOLE_COLOR
{
	Black		= 0x00,
	DarkBlue	= 0x01,
	Green		= 0x02,
	LightBlue	= 0x03,
	DarkRed		= 0x04,
	Purple		= 0x05,
	Yellow		= 0x06,
	LightGray	= 0x07,
	Gray		= 0x08,
	Blue		= 0x09,
	Lime		= 0x0A,
	Cyan		= 0x0B,
	Red			= 0x0C,
	Megenta		= 0x0D,
	Gold		= 0x0E,
	White		= 0x0F
} StdColor;

typedef enum __STD_TEXT_ATTRIBUTE_TYPE
{
	All				= 0b11,
	TextColor		= 0b01,
	BackgroundColor	= 0b10
} TextAttributeType;

typedef enum __STD_KEY_TYPE
{
	ESC		= VK_ESCAPE,
	TAB		= VK_TAB,
	CAP		= VK_CAPITAL,
	Space	= VK_SPACE,
	// SHIFT
	Shift	= VK_SHIFT,
	LShift	= VK_LSHIFT,
	Rshift	= VK_RSHIFT,
	// ALT
	Alt		= VK_MENU,
	LAlt	= VK_LMENU,
	RAlt	= VK_RMENU,
	// CTRL
	Ctrl	= VK_CONTROL,
	LCtrl	= VK_LCONTROL,
	RCtrl	= VK_RCONTROL,
	// Directions
	Up		= VK_UP,
	Down	= VK_DOWN,
	Left	= VK_LEFT,
	Right	= VK_RIGHT
} KeyType;

/** @brief Init console handle, must be called before other functions are called. */
void initConsole();
/** @brief Set the title of the console. */
void setConsoleTitle(const char* title);
/** @brief Set the cursor's visibility. */
void setCursorVisible(BOOL visible);
/** @brief Clear console and reset cursor to the upper left. */
void clearConsole();

/** @brief Get cursor anchor, which will be set to (x, y). */
CursorAnchor createCursorAnchor(SHORT x, SHORT y);
/** @brief Set anchor position to (x, y). */
void setCursorAnchor(CursorAnchor* anchor, SHORT x, SHORT y);
/** @brief Set anchor position to (anchor.x + dx, anchor.y + dy). */
void moveCursorAnchor(CursorAnchor* anchor, SHORT dx, SHORT dy);

/** @brief Get current console cursor position. */
CursorAnchor getCursor();
/** @brief Set the console cursor position. @param anchor Set the cursor to where anchor is. */
void setCursor(CursorAnchor* anchor);
/** @brief Move the console cursor position. @param dx Horizontal direction. @param dy Vertical direction.  */
void moveCursor(SHORT dx, SHORT dy);

/** @brief Set color of all the text behind this function. */
void setTextColor(StdColor col);
/** @brief Set color of all text background behind this function. */
void setTextBackgroundColor(StdColor col);
/** @brief Set color of text and background. */
void setTextAttribute(StdColor textColor, StdColor bgColor);
/** 
 * @brief Reset Text Color and Background Color to default. (Text = Light Gray; Background = Black)
 * @param attri Attribute to be reset.
**/
void resetTextAttribute(TextAttributeType attri);

/**
 * @brief Pause until user hit a keyboard key.
 * @param tip Tooltip to show when paused.
**/
void pauseConsole(const char* tip);

/**
 * @brief Checks if the character key is pressed. 
 * @param ch ASCII value of the key.
**/
BOOL isCharKeyPressed(char ch);
/**
 * @brief Checks if the key is pressed. 
 * @param key Only KeyType values and VK_ macros are supported.
**/
BOOL isKeyPressed(KeyType key);
/**
 * @brief Checks if the key is toggled. 
 * @param key Only KeyType values and VK_ macros are supported.
**/
BOOL isKeyToggled(KeyType key);
/**
 * @brief  Return the value of pressed key.
 * @return ASCII value if pressed a character key, KeyType value if pressed other key.
**/
int getPressedKey();

/**  @brief Text Ui type. See README.md for more */
typedef struct __ASCII_SIMPLE_TEXT_UI
{
	BYTE**	data;
	DWORD	width;
	DWORD	height;

#ifdef __cpluscplus
	__ASCII_SIMPLE_TEXT_UI() : data(nullptr), width(0), height(0) {}
#endif
} TextUi;

/**  @brief Text Ui shape type. See README.md for more */
typedef struct ___ASCII_TEXT_UI_SHAPE
{
	BYTE**	data;	// Ui shape, default to NULL
	DWORD	width;
	DWORD	height;

#ifdef __cpluscplus
	___ASCII_TEXT_UI_SHAPE() : data(nullptr), width(0), height(0) {}
#endif
} TextUiShape;

/**
 * @brief Read from text file.
 * @param filepath Path to the text file.
 * @return If failed to read, return NULL.
**/
TextUi* readTextUi(const char* filepath);
/** @brief Copy from existing TextUi */
TextUi* copyTextUi(const TextUi* ui);
/**
 * @brief Save TextUi to a text file. Will overwrite existing file.
 * @param ui Text Ui data to be saved.
 * @param filepath Where you want to save the data. If file does not exist, create the file.
 * @return Whether the save is successful.
**/
BOOL saveTextUi(TextUi* ui, const char* filepath);
/**
 * @brief Print loaded ui to the console.
 * @param ui TextUi to be printed.
 * @param anchor Console coordinate where print begins. If NULL, print begins at the upper left of the console.
**/
void drawTextUi(const TextUi* ui, CursorAnchor* anchor);
/** 
 * @brief Rotate TextUi relative to its upper left.
 * @param clockwise Whether the rotation operation is clockwise. 
**/
TextUi* rotateTextUi(TextUi* ui, BOOL clockwise);
/**
 * @brief Flip TextUi.
 * @param vertical If FALSE, TextUi will be flipped horizontally.
**/
void flipTextUi(TextUi* ui, BOOL vertical);
/** @brief Free memory and set the data pointer to NULL. */
void deleteTextUi(TextUi* ui);

/**
 * @brief Create a TestUiShape instance from existing TextUi.
 * @param shape If NULL, it will create a new instance, otherwise it will update existing shape.
 * @return Created or updated shape instance.
**/
TextUiShape* getTextUiShape(TextUiShape* shape, TextUi* ui);
/** @brief Copy shape data from existing shape. */
TextUiShape* copyTextUiShape(TextUiShape* shape);
/** @brief Free memory of TextUiShape. */
void deleteTextUiShape(TextUiShape* shape);

#ifdef __cplusplus
}
#endif

#endif //! __C_CONCOLE_LIB_HEADER___