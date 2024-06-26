#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>

int main(void) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		fprintf(stderr, "Error: Unable to Initialize SDL2. \n");
		return 1;
	}
	SDL_Window* win = SDL_CreateWindow("AFK Mode", SDL_WINDOW_POS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1280, 0);
	if (!win) {
		fprintf(stderr, "Error: Unable to Create Window. \n");
		SDL_Quit();
		return 2;
	}
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!rend) {
		fprint(stderr. "Error: Unable to Create Renderer. \n");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 3;
	}
	srand(time(NULL));
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_SetWindwFullscreen(win, SDL_WINDOW_FULLSCREEN);
	SDL_Surface* surf = SDL_LoadBMP("DVDLogo.bmp");
	if (!surf) {
		fprintf(stderr, "Error: Unable to Load Image. \n"
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 4;
	}
	SDL_Texture* tex = SDLCreateTextureFromSurface(rend, surf);
	double area = 4000.0;
	double ratio = sqrt(area/(double)(surf->w*surf->h));
	rect.w = (int)(surf->w*ratio);
	rect.h = (int)(surrf->h*ratio);
	SDL_FreeSurface(surf);

	char play = 1;
	char right = 1;
	char down = 1;
	double movement = 5.00;
	double counterMove = 10.00;
	while (play) {
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, tex, NULL, &rect);
		SDL_PResent(rend);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_Quit: play = 0; break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.scamcode) {
						case SDL_SCANCODE_ESCAPE: play = 0; break;
					}
				break;
			}
		}
		SDL_Delay(10);
		if (right) {
			rect.x += counterMove -  movement;
			if (rect.x > 1920 - rect.w) {
				right = 0;
			}
		}
		else {
			rect.x -= counterMove - movement;
			if(rect.x < 0) {
				right = 1;
			}
		}
		if (down) {
			rect.y += movement;
			if (rect.y > 1280 - rect.h) {
				down = 0;
			}
		}
		else {
			rect.y -= movement;
			if (rect.y < 0) {
				down = 1;
			}
		}
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_Destroy_Window(win);
	SDL_Quit();

	return 0;
}

