/*
 * overallObjects.cpp
 *
 *  Created on: 25.01.2017
 *      Author: SFG
 */

#ifndef OVERALLOBJECTS_H_
#define OVERALLOBJECTS_H_

// Including SDL headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

static uint16_t gridWidth = 32;

// Setting up window
static uint16_t SCREEN_WIDTH = 25 * gridWidth;
static uint16_t SCREEN_HEIGHT = 19 * gridWidth;
// Our window
static SDL_Window* window = NULL;
// Our window surface
static SDL_Surface* windowScreen = NULL;

// Milliseconds since start of programm
static uint64_t msPassed = 0;
static uint64_t msLastFrame = 0;

static uint16_t gravity = 1500;

typedef struct {
	double x, y;
} twoDPos;

static SDL_Rect* pixel = new SDL_Rect { 0, 0, 1, 1 };

#endif /* OVERALLOBJECTS_H_ */
