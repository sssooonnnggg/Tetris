/*!
	Description : A simple SDL wrapper
	Author		: Ruining Song
	Date		: 2014/3/8
*/

#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Base.h"

#include <map>
#include <string>

class Renderer
{
public:
	virtual void DrawBackground(const Color& color) = 0;

	virtual void DrawLine(const Point& start, const Point& end, const Color& color) = 0;

	virtual void DrawRect(const Rect& rect, const Color& color) = 0;
	virtual void FillRect(const Rect& rect, const Color& color) = 0;

	/*!
	\brief
		Create a texture within the client's intialize methods, so that 
		the renderer can draw the text without creating it.
		Return an unique identifer of the text.
	*/
	virtual std::wstring CreateText(const wchar_t* text, const Color& color) = 0;
	virtual void RenderText(std::wstring identifer, const Rect& rect) = 0;
	virtual void DestroyText(std::wstring identifer) = 0;

	virtual std::wstring CreatePicture(const char* picPath) = 0;
	virtual void RenderPicture(std::wstring identifer, const Rect& srcRect, const Rect& dstRect) = 0;
	virtual void RenderPicture(std::wstring identifer, const Rect& dstRect) = 0;
	
	virtual void BeginRender() = 0;

	virtual void AddFont(std::wstring fontName, const char* fontPath, int fontSize) = 0;
	virtual void SetFont(std::wstring fontName) = 0;
};

class SDLRenderer : public Renderer
{
public:
	SDLRenderer(SDL_Window* window);
	~SDLRenderer();

	void DrawBackground(const Color& color);

	void DrawLine(const Point& start, const Point& end, const Color& color);

	void DrawRect(const Rect& rect, const Color& color);
	void FillRect(const Rect& rect, const Color& color);

	std::wstring CreateText(const wchar_t* text, const Color& color);
	void RenderText(std::wstring identifer, const Rect& rect);
	void DestroyText(std::wstring identifer);

	std::wstring CreatePicture(const char* picPath);
	void RenderPicture(std::wstring identifer, const Rect& srcRect, const Rect& dstRect);
	void RenderPicture(std::wstring identifer, const Rect& dstRect);

	void BeginRender();

	void AddFont(std::wstring fontName, const char* fontPath, int fontSize);
	void SetFont(std::wstring fontName);

private:
	SDL_Renderer* m_sdlRenderer;
	TTF_Font* m_font;
	typedef std::map<std::wstring, TTF_Font*> FontMap;
	FontMap m_fontMap;

	typedef struct tagTextureInfo
	{
		SDL_Texture* texture;
		int w;
		int h;
	}TextureInfo;

	typedef std::map<std::wstring, TextureInfo> TextureMap;
	TextureMap m_textureMap;
}; 

#endif // SDLRENDERER_H