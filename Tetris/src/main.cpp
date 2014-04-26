#include <SDL.h>

#include <algorithm>

#include "Utils.h"
#include "GameManager.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2main.lib")

int main(int argc, char *argv[])
{
	SDLGameManager gm;
	gm.Init();
	gm.Loop();
	return 0;
}