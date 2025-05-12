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

  // Window stuff 
  unsigned const int WINDOW_WIDTH = 700;
  unsigned const int WINDOW_HEIGHT = 700;

  bool isRunning = true;

  SDL_Window *window = NULL; 
  SDL_Renderer *renderer = NULL; 

  window = SDL_CreateWindow(
    "Get'em all",
    WINDOW_WIDTH, 
    WINDOW_HEIGHT,
    SDL_WINDOW_RESIZABLE
  );

  renderer = SDL_CreateRenderer(window, NULL);

  while(isRunning) {
    SDL_Event event; 

    // check for "unlistened" events
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) {
        isRunning = false;
      }
    }

    // window background color 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
  }

  // freeing memory 
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}