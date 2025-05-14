#include "SDL3/SDL.h"

void checkSubsystemStatus(SDL_InitFlags subsystem) {
  // check if there where any errors when starting a subsystem 
  if(!SDL_InitSubSystem(subsystem)) {
    SDL_LogCritical(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }
}

void update() {

}

void draw(SDL_Renderer *master) {
}

int main() {
  checkSubsystemStatus(SDL_INIT_VIDEO); 

  bool isRunning = true;

  // Window stuff 
  unsigned const int WINDOW_WIDTH = 700;
  unsigned const int WINDOW_HEIGHT = 700;

  // player stuff 
  unsigned const int PLAYER_WIDTH = 50;
  unsigned const int PLAYER_HEIGHT = 50;

  float playerXPos = (WINDOW_WIDTH - PLAYER_WIDTH) / 2; 
  float playerYPos = (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2; 

  float playerSpeed = 0.2;

  SDL_Window *window = NULL; 
  SDL_Renderer *renderer = NULL; 

  SDL_FRect player; 

  window = SDL_CreateWindow(
    "Get'em all",
    WINDOW_WIDTH, 
    WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE
  );

  renderer = SDL_CreateRenderer(window, NULL);

  player = {playerXPos, playerYPos, PLAYER_WIDTH, PLAYER_HEIGHT};


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

    if (keys[SDL_SCANCODE_W]) player.y -= playerSpeed;
    if (keys[SDL_SCANCODE_S]) player.y += playerSpeed;
    if (keys[SDL_SCANCODE_A]) player.x -= playerSpeed;
    if (keys[SDL_SCANCODE_D]) player.x += playerSpeed;

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