#include "SDL3/SDL.h"
#include <cmath>
#include <iostream>

void checkSubsystemStatus(SDL_InitFlags subsystem) {
  // check if there where any errors when starting a subsystem 
  if(!SDL_InitSubSystem(subsystem)) {
    SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }
}

int main() {
  checkSubsystemStatus(SDL_INIT_VIDEO); 

  bool isRunning = true;

  // Window stuff 
  unsigned const int WINDOW_WIDTH = 700;
  unsigned const int WINDOW_HEIGHT = 700;

  SDL_Window *window = SDL_CreateWindow(
    "Get'em all",
    WINDOW_WIDTH, 
    WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE
  );

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  // player stuff 
  unsigned const int PLAYER_WIDTH = 50;
  unsigned const int PLAYER_HEIGHT = 50;

	int playerXDirection = 0;
	int playerYDirection = 0;

  float playerXPos = (WINDOW_WIDTH - PLAYER_WIDTH) / 2; 
  float playerYPos = (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2; 

  float playerSpeed = 500;

  SDL_FRect player; 

  player = {playerXPos, playerYPos, PLAYER_WIDTH, PLAYER_HEIGHT};

  // frame-rate independent movement stuff
  Uint64 currentFrame = SDL_GetPerformanceCounter();
  Uint64 lastFrame = 0;

  double delta = 0;

  while(isRunning) {
    SDL_Event event; 

    // get currently pressed keys 
    const bool* keys = SDL_GetKeyboardState(NULL);

    // check for "unlistened" events
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
    }
    // UPDATE
    lastFrame = currentFrame;
    currentFrame = SDL_GetPerformanceCounter();

    delta = (double)((currentFrame - lastFrame) * 1000) / (double)SDL_GetPerformanceFrequency();
    delta /= 1000.0;

    if (keys[SDL_SCANCODE_W]) playerYDirection = -1;
    if (keys[SDL_SCANCODE_S]) playerYDirection = 1;
    if (keys[SDL_SCANCODE_A]) playerXDirection = -1;
    if (keys[SDL_SCANCODE_D]) playerXDirection = 1;

    // vector normalization
		float magnitude = sqrt(pow(playerXDirection, 2) + pow(playerYDirection, 2));

    if(magnitude != 0) {
      float normalizedX = playerXDirection / magnitude;
      float normalizedY = playerYDirection / magnitude;

      playerXPos += normalizedX * playerSpeed * delta;
      playerYPos += normalizedY * playerSpeed * delta;
    }

    player.x = playerXPos;
    player.y = playerYPos;

    // reset direction when no keys are pressed 
    playerXDirection = 0;
    playerYDirection = 0;

    // DRAW
    // set background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // color for the player
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &player);

    SDL_RenderPresent(renderer);
  }

  // freeing memory 
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
