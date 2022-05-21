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
typedef struct __C_Console_Cursor_Anchor_Instance
{
	SHORT x;	// Cursor x
	SHORT y;	// Cursor y

#ifdef __cplusplus
	__C_Console_Cursor_Anchor_Instance() : x(0), y(0) {}
	__C_Console_Cursor_Anchor_Instance(SHORT _x, SHORT _y) : x(_x), y(_y) {}
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
void setTitle(const char* title);
/** @brief Set the cursor's visibility. */
void setCursorVisible(BOOL visible);

/** @brief Get cursor anchor, which will be set to (x, y). */
CursorAnchor getCursorAnchor(SHORT x, SHORT y);
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

/**  @brief Text Ui instance. See README.md for more */
typedef struct __ASCII_SIMPLE_TEXT_UI
{
	BYTE**	data;
	DWORD	width;
	DWORD	height;

#ifdef __cpluscplus
	__ASCII_SIMPLE_TEXT_UI() : data(nullptr), width(0), height(0) {}
#endif
} TxtUi;

/**
 * @brief Read from text file.
 * @param filepath Path to the text file.
 * @return If failed to read, return NULL.
**/
TxtUi* readTextUi(const char* filepath);
/**
 * @brief Save TxtUi to a text file. Will overwrite existing file.
 * @param ui Text Ui data to be saved.
 * @param filepath Where you want to save the data. If file does not exist, create the file.
 * @return Whether the save is successful.
**/
BOOL saveTextUi(TxtUi* ui, const char* filepath);
/**
 * @brief Print loaded ui to the console.
 * @param ui TxtUi to be printed.
 * @param anchor Console coordinate where print begins. If NULL, print begins at the upper left of the console.
**/
void printUi(TxtUi* ui, CursorAnchor* anchor);
/**
 * @brief Free memory and set the pointer to NULL.
**/
void deleteTextUi(TxtUi* ui);

#ifdef __cplusplus
}
#endif

#endif //! __C_CONCOLE_LIB_HEADER___