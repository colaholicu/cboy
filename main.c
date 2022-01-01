#include "sdl_utils.h"

const Uint32 k_max_ticks_per_frame = 16;

void DrawLogo()
{
	SDL_Rect rect;
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	rect.h = (int)(HEIGHT * .25f);
	rect.w = (int)(WIDTH * .25f);
	rect.y = (int)(HEIGHT * .5f - rect.h * .5f);
	rect.x = (int)(WIDTH *.5f - rect.w * .5f);
	SDL_RenderFillRect(g_renderer, &rect);

	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);	
}

void GameLoop()
{
	int gameRunning = 1;
	while (gameRunning)
	{
		SDL_RenderClear(g_renderer);

		const Uint32 previous_ticks = SDL_GetTicks();
		if (previous_ticks < 3000) // show the logo only for ~3 seconds
			DrawLogo();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					keypressed = event.key.keysym.sym;
					if (keypressed == QUITKEY)
					{
						gameRunning = 0;
						break;
					}

					break;
				case SDL_QUIT: /* if mouse click to close window */
					gameRunning = 0;
					break;

				case SDL_KEYUP:
					break;
			}

		} /* while SDL_PollEvent */

		SDL_RenderPresent(g_renderer);

		const Uint32 curent_ticks = SDL_GetTicks();
		const Uint32 ticks_this_frame = curent_ticks - previous_ticks;
		if (ticks_this_frame > k_max_ticks_per_frame)
			continue;

		Uint32 sleep_delay = k_max_ticks_per_frame - ticks_this_frame;
		if (sleep_delay > 0)
			SDL_Delay(sleep_delay);
	}
}

int main(int argc, char* args[])
{
	InitSetup();
	GameLoop();
	FinishOff();
	return 0;
}