#include "SDLRenderer.h"
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <sstream>

#include <Rpc.h>
#pragma comment(lib, "rpcrt4.lib")

SDLRenderer::SDLRenderer(SDL_Window* window)
: m_sdlRenderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
, m_font(NULL)
{
	SDL_SetRenderDrawBlendMode(m_sdlRenderer, SDL_BLENDMODE_BLEND);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
}

SDLRenderer::~SDLRenderer()
{
	FontMap::iterator itToFontMap = m_fontMap.begin();

	while ( itToFontMap != m_fontMap.end() )
	{
		TTF_CloseFont(itToFontMap->second);
		itToFontMap++;
	}

	TextureMap::iterator itToTextureMap = m_textureMap.begin();

	while ( itToTextureMap != m_textureMap.end() )
	{
		SDL_DestroyTexture(itToTextureMap->second.texture);
		itToTextureMap++;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(m_sdlRenderer);
}

void SDLRenderer::DrawBackground(const Color& color)
{
	SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_sdlRenderer);
}

void SDLRenderer::DrawLine(const Point& start, const Point& end, const Color& color)
{
	SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_sdlRenderer, start.x, start.y, end.x, end.y);
}

void SDLRenderer::DrawRect(const Rect& rect, const Color& color)
{
	SDL_Rect sdlRect = {rect.x, rect.y, rect.w, rect.h};
	SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(m_sdlRenderer, &sdlRect);
}

void SDLRenderer::FillRect(const Rect& rect, const Color& color)
{
	SDL_Rect sdlRect = {rect.x, rect.y, rect.w, rect.h};
	SDL_SetRenderDrawColor(m_sdlRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(m_sdlRenderer, &sdlRect);
}

std::wstring SDLRenderer::CreateText(const wchar_t* text, const Color& color)
{
	SDL_Color forecolor = {color.r, color.g, color.b, color.a};
	SDL_Surface* surface = TTF_RenderUNICODE_Blended(m_font, (Uint16*)text, forecolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
	SDL_FreeSurface(surface);

	TextureInfo info = {texture, surface->w, surface->h};

	UUID id = {0};
	UuidCreate(&id);
	wchar_t* strId = NULL;
	UuidToStringW(&id, (RPC_WSTR*)&strId);
	std::wstring identifer = (wchar_t*)strId;
	RpcStringFreeW((RPC_WSTR*)&strId);

	m_textureMap[identifer] = info;

	return identifer;
}

void SDLRenderer::RenderText(std::wstring identifer, const Rect& rect)
{
	TextureInfo info = m_textureMap[identifer];
	SDL_Rect dstRect = {rect.x+(rect.w-info.w)/2, rect.y+(rect.h-info.h)/2, info.w, info.h};
	SDL_RenderCopy(m_sdlRenderer, info.texture, NULL, &dstRect);
}

void SDLRenderer::DestroyText(std::wstring identifer)
{
	TextureMap::iterator it = m_textureMap.find(identifer);
	SDL_DestroyTexture(it->second.texture);
	m_textureMap.erase(it);
}

std::wstring SDLRenderer::CreatePicture(const char* picPath)
{
	SDL_Surface* surface = IMG_Load(picPath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_sdlRenderer, surface);
	SDL_FreeSurface(surface);

	TextureInfo info = {texture, surface->w, surface->h};

	UUID id = {0};
	UuidCreate(&id);
	wchar_t* strId = NULL;
	UuidToStringW(&id, (RPC_WSTR*)&strId);
	std::wstring identifer = (wchar_t*)strId;
	RpcStringFreeW((RPC_WSTR*)&strId);

	m_textureMap[identifer] = info;

	return identifer;
}

void SDLRenderer::RenderPicture(std::wstring identifer, const Rect& srcRect, const Rect& dstRect)
{
	TextureInfo info = m_textureMap[identifer];
	SDL_Rect sdlDstRect = {dstRect.x, dstRect.y, dstRect.w, dstRect.w};
	SDL_Rect sdlSrcRect = {srcRect.x, srcRect.y, srcRect.w, srcRect.h};
	SDL_RenderCopy(m_sdlRenderer, info.texture, &sdlSrcRect, &sdlDstRect);
}

void SDLRenderer::RenderPicture(std::wstring identifer, const Rect& dstRect)
{
	TextureInfo info = m_textureMap[identifer];
	SDL_Rect sdlDstRect = {dstRect.x, dstRect.y, dstRect.w, dstRect.w};
	SDL_Rect sdlSrcRect = {0, 0, info.w, info.h};
	SDL_RenderCopy(m_sdlRenderer, info.texture, &sdlSrcRect, &sdlDstRect);
}

void SDLRenderer::BeginRender()
{
	SDL_RenderPresent(m_sdlRenderer);
}

void SDLRenderer::AddFont(std::wstring fontName, const char* fontPath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
	m_fontMap[fontName] = font;
}

void SDLRenderer::SetFont(std::wstring fontName)
{
	m_font = m_fontMap[fontName];
}