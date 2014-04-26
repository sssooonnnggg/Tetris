/*!
	Description : Shape definition
	Author		: Ruining Song
	Date		: 2014/3/8
*/

#ifndef SHAPE_H
#define SHAPE_H

#pragma warning(disable:4244)

///< window consts
const unsigned int WindowWidth = 800;
const unsigned int WindowHeight = 600;

///< block consts
const int PoolsWidth = 10;
const int PoolsHeight = 24;

const int BlockUnitWidth = 20;
const int BlockUnitHeight = 20;

const int BlockQueueSize = 3;

const int NextBlockX = 300;

///< opacity config
const int IndicatorOpacity = 30;
const int CutsceneOpacity = 100;

///< interval consts
const unsigned int LevelInterval[] = {1000, 500, 300, 200, 150, 130, 110, 100, 90, 80};
const unsigned int SoftDropInterval = 20;

///< score consts, socre = linefactor * level
const int ScoreFactor[] = {40, 100, 300, 1200};

///< ui consts
const int ButtonWidth = 200;
const int ButtonHeight = 50;
const int ButtonX = (WindowWidth - ButtonWidth) / 2;

class Color
{
public:
	Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255)
		: r(red), g(green), b(blue), a(alpha)
	{}

	Color(const Color& color)
		: r(color.r), g(color.g), b(color.b), a(color.a)
	{}

	Color& operator=(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};

const Color ColorBackGround(255, 255, 255, 255);
const Color ColorPoolsBackground(220, 220, 220, 220);
const Color ColorWhite(255, 255, 255);
const Color ColorBlack(0, 0, 0);
const Color ColorRed(229, 20, 0);
const Color ColorGreen(51, 153, 51);
const Color ColorBlue(27, 161, 226);
const Color ColorBrown(160, 80, 0);
const Color ColorLime(162, 193, 57);
const Color ColorMagenta(216, 0, 115);
const Color ColorMango(240, 150, 9);
const Color ColorLightMango(240, 150, 9, 100);
const Color ColorPink(230, 113, 184);
const Color ColorPurple(162, 0, 225);
const Color ColorTeal(0, 171, 169);

const Color ColorGroup[] = {ColorRed, ColorGreen, ColorBlue, ColorBrown, ColorLime, ColorMagenta, ColorMango, ColorPink, ColorPurple, ColorTeal};
const int ColorCount = sizeof(ColorGroup) / sizeof(Color);

class Point
{
public:

	Point()
		: x(0), y(0)
	{}

	Point(int xPos, int yPos)
		: x(xPos), y(yPos)
	{}

	Point(const Point& point)
	{
		x = point.x;
		y = point.y;
	}

	Point operator-(const Point& point)
	{
		return Point(x - point.x, y - point.y);
	}

	Point operator+(const Point& point)
	{
		return Point(x + point.x, y + point.y);
	}

	int x;
	int y;
};

class Rect
{
public:
	Rect(int xPos, int yPos, int width, int height)
		: x(xPos) ,y(yPos) ,w(width) ,h(height)
	{}

	bool operator==(Rect& rect)
	{
		return (x == rect.x && y == rect.y && w == rect.w && h == rect.h);
	}

	int x;
	int y;
	int w;
	int h;
};

class BlockUnit : public Rect
{
public:
	BlockUnit()
		: Rect(0, 0, 0, 0)
		, fill(false)
		, color(ColorRed)
	{}
	BlockUnit(int xPos, int yPos, int width = BlockUnitWidth, int height = BlockUnitHeight)
		: Rect(xPos, yPos, width, height)
		, fill(false)
		, color(ColorRed)
	{}

	BlockUnit(const BlockUnit& block)
		: Rect(block.x, block.y, block.w, block.h)
		, fill(block.fill)
		, color(block.color)
	{

	}

	void Copy(const BlockUnit* block)
	{
		x = block->x;
		y = block->y;
		w = block->w;
		h = block->h;
		fill = block->fill;
		color = block->color;
	}

	Color& GetColor()
	{
		return color;
	}

public:
	bool fill;
	Color color;
};

class Event
{
public:
	enum EventType{WINDOW, MOUSE, KEYBOARD};
	virtual const int Type() = 0;
};

class WindowEvent : public Event
{
public:

	enum WindowEventType{WINDOW_CLOSE};

	WindowEvent(WindowEventType type)
		: m_windowEventType(type)
	{

	}

	const int Type()
	{
		return WINDOW;
	}

	const int GetWindowEventType()
	{
		return m_windowEventType;
	}

private:
	WindowEventType m_windowEventType;
};

class MouseEvent : public Event
{
public:
	enum MouseEventType{MOUSE_MOVE, MOUSE_BUTTON_CLICKED};

	MouseEvent(MouseEventType type, Point& pos)
		: m_mouseEventType(type)
		, m_pos(pos)
	{

	}

	const int Type()
	{
		return MOUSE;
	}

	const int GetMouseEventType()
	{
		return m_mouseEventType;
	}

	const Point& GetPos()
	{
		return m_pos;
	}

private:
	MouseEventType m_mouseEventType;
	Point m_pos;
};

class KeyboardEvent : public Event
{
public:
	enum KeyboardEventType{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_ESCAPE};

	KeyboardEvent(KeyboardEventType type, bool pressed)
		: m_keyboardEventType(type)
		, m_pressed(pressed)
	{

	}

	const int Type()
	{
		return KEYBOARD;
	}

	const int GetKeyboardEventType()
	{
		return m_keyboardEventType;
	}

	bool IsPressed()
	{
		return m_pressed;
	}

private:
	bool m_pressed;
	KeyboardEventType m_keyboardEventType;
};

#endif // SHAPE_H