#ifndef __C_CONCOLE_LIB_HEADER___
#define __C_CONCOLE_LIB_HEADER___

#if !defined(_WIN32)
#error "CConsole Lib only works on Windows."
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <Windows.h>

typedef struct __C_Console_Cursor_Instance
{
	SHORT x;	// Cursor x
	SHORT y;	// Cursor y

#ifdef __cplusplus
	__C_Console_Cursor_Instance() : x(0), y(0) {}
	__C_Console_Cursor_Instance(SHORT _x, SHORT _y) : x(_x), y(_y) {}
#endif
} CConsole;

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
/** @brief Get cursor, which will be set to (x, y). */
CConsole getCursor(SHORT x, SHORT y);

/** @brief Set Cursor Position to (x, y). */
void setCursor(CConsole* cursor, SHORT x, SHORT y);
/** @brief Set Cursor Position to (cursor.x + dx, cursor.y + dy). */
void moveCursor(CConsole* cursor, SHORT dx, SHORT dy);
/** @brief Set the console cursor position. @param cursor Cursor position to be set. */
void setConsoleCursor(CConsole* cursor);

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

#ifdef __cplusplus
}
#endif

#endif //! __C_CONCOLE_LIB_HEADER___