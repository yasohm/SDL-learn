#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_TITLE "My FIRST SDL2 Game"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

bool sdl_initialize(struct Game *game);



void game_cleanup(struct Game *game) {
    if (game->renderer) {
        SDL_DestroyRenderer(game->renderer);
    }
    if (game->window) {
        SDL_DestroyWindow(game->window);
    }
    SDL_Quit(); 
};


bool sdl_initialize(struct Game *game){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return true;
    }

    game->window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
    
    if(!game->window){
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        //SDL_Quit();
        return true;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);

    if(!game->renderer){
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(game->window);
        // SDL_Quit();
        return true;
    }

    return false;
}

int main(){
    struct Game game={
        .window = NULL,
        .renderer = NULL
    };

    if(sdl_initialize(&game)){
        game_cleanup(&game);
        printf("Failed to initialize SDL.\n");
        exit(1);
    }

    SDL_RenderClear(game.renderer);

    SDL_RenderPresent(game.renderer);

    SDL_Delay(3000);

    game_cleanup(&game);  

    printf("SDL Initialized successfully!\n");
    return 0;
}