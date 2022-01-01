#pragma once

#include "SDL.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define QUITKEY SDLK_ESCAPE
#define WIDTH 1024
#define HEIGHT 768

SDL_Window* g_screen = NULL;
SDL_Renderer* g_renderer;
SDL_Event event;
SDL_Rect source, destination, dst;

int errorCount = 0;
int keypressed;

/* returns a number between 1 and max */
int Random(int max)
{
	return (rand() % max) + 1;
}

void LogError(char* msg)
{
	printf("%s\n", msg);
	errorCount++;
}

/* Sets Window caption according to state - eg in debug mode or showing fps */
void SetCaption(char* msg)
{
	SDL_SetWindowTitle(g_screen, msg);
}

/* Initialize all setup, set screen mode, load images etc */
void InitSetup()
{
	srand((int)time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &g_screen, &g_renderer);
	if (!g_screen) {
		LogError("InitSetup failed to create window");
	}
	SetCaption("C-boy");
}

/* Cleans up after game over */
void FinishOff()
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_screen);
	//Quit SDL
	SDL_Quit();
	exit(0);
}

/* read a character */
char getaChar()
{
	int result = -1;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
		{
			result = event.key.keysym.sym;
			break;
		}
	}
	return result;
}