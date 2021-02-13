#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "globals.h"
#include "Renderer.h"
#include "GameManager.h"
#include <memory>
#include <ctime>
#include <cstdlib>

#include <iostream>


bool quit_called = false;

double target_frame_duration = 1000. / global::TARGET_FPS;

void update_SDL_input(const uint8_t **current_key_states) { 
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit_called = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				quit_called = true;
			}
		}
	}
	
	*current_key_states = SDL_GetKeyboardState(NULL);
}

int main() {
	srand(time(nullptr));

	SDL_Init(SDL_INIT_VIDEO);
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	
	const uint8_t *current_key_states = nullptr;
	bool game_over = false;

	uint32_t frame_start_time = 10;

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>();
	GameManager game_manager(renderer, current_key_states, frame_start_time);

	while (true) {
		frame_start_time = SDL_GetTicks();
		
		update_SDL_input(&current_key_states);

		game_over = game_manager.manage();

		renderer->render();

		if (quit_called) {
			break;
		}
		else if (game_over) {
			SDL_Delay(5000);
			break;
		}

		double frame_execution_time = target_frame_duration - (SDL_GetTicks() - frame_start_time);
		if (frame_execution_time > 0) {
			SDL_Delay(frame_execution_time);
		}
	}

	return 0;
}
