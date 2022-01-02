#include "sdl_utils.h"
#include "gb_cpu.h"
#include "gb_memory.h"

const Uint32 k_max_ticks_per_frame = 16;

void DrawLogo()
{
	SDL_FRect rect;
	rect.h = HEIGHT * .25f;
	rect.w = WIDTH * .25f;
	rect.y = HEIGHT * .5f - rect.h * .5f;
	rect.x = WIDTH *.5f - rect.w * .5f;
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderDrawRectF(g_renderer, &rect);
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
}

typedef enum _EGameState
{
	EGameState_INIT = 0,
	EGameState_LOAD,
	EGameState_MAIN,
} EGameState;

void GameLoop()
{
	EGameState game_state = EGameState_INIT;
	Uint32 starting_ticks = 0;

	FILE* f = NULL;
	errno_t err;

	int gameRunning = 1;
	while (gameRunning)
	{		
		SDL_RenderClear(g_renderer);
		const Uint32 previous_ticks = SDL_GetTicks();

		switch (game_state)
		{
			case EGameState_INIT:
				cpu_init();
				game_state = EGameState_LOAD;
				break;

			case EGameState_LOAD:
				err = fopen_s(&f, ".\..\\..\\..\\bgb\\bgbtest.gb", "rb");
				SDL_assert(err == 0);
				if (err == 0)
				{
					load_file(f);
					fclose(f);
				}				

				game_state = EGameState_MAIN;
				break;

			case EGameState_MAIN:
				cpu_tick();
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
				break;
		}

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