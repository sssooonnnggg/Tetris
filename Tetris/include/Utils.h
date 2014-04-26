/*!
	Description : Utility tool functions.
	Author		: Ruining Song
	Date		: 2014/3/8
*/

#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <string>
#include "Base.h"

inline int GetWindowX()
{
	return (::GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2;
}

inline int GetWindowY()
{
	return (::GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2;
}

/*!
\brief
	Rotate a rectangle around a point.
*/
inline void Rotate(Rect& rect, const Point& point, bool clockwize)
{
 	Point rectCenter(rect.x + rect.w / 2, rect.y + rect.h / 2);
	
	// Set point as (0, 0)
	Point transform(rectCenter - point);

	if ( clockwize )
	{
		if ( transform.x * transform.y > 0 )
			transform.x = -transform.x;
		else
			transform.y = -transform.y;
	}
	else
	{
		if ( transform.x * transform.y > 0 )
			transform.y = -transform.y;
		else
			transform.x = -transform.x;
	}

	// Exchange x & y
	int temp = transform.x;

	transform.x = ( transform.x == 0 ? transform.y
		: transform.x/abs(transform.x)*abs(transform.y) );

	transform.y = ( transform.y == 0 ? temp
		: transform.y/abs(transform.y)*abs(temp) );

	Point newRectCenter(transform + point);

	rect.x = newRectCenter.x - rect.w / 2;
	rect.y = newRectCenter.y - rect.h / 2;
}

inline bool PointInRect(const Point& point, const Rect& rect)
{
	return ( point.x > rect.x && point.x < rect.x + rect.w 
		&& point.y > rect.y && point.y < rect.y + rect.h );
}

inline std::wstring IntToStr(int number)
{
	WCHAR wzStr[256] = {0};
	wsprintfW(wzStr, L"%d", number);
	return std::wstring(wzStr);
}

inline void DebugOutW(LPCWSTR ptzFormat, ...)
{
#ifdef _DEBUG
	va_list vlArgs;
	WCHAR szText[1024];
	va_start(vlArgs, ptzFormat);
	wvsprintfW(szText, ptzFormat, vlArgs);
	OutputDebugStringW(szText);
	va_end(vlArgs);
#endif
}

inline void DebugOutA(LPCSTR ptzFormat, ...)
{
#ifdef _DEBUG
	va_list vlArgs;
	CHAR szText[1024];
	va_start(vlArgs, ptzFormat);
	wvsprintfA(szText, ptzFormat, vlArgs);
	OutputDebugStringA(szText);
	va_end(vlArgs);
#endif
}

#endif // UTILS_H