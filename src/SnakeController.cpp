#include "SnakeController.h"
#include <SDL2/SDL.h>

void SnakeController::update() {
	if (current_key_states_[SDL_SCANCODE_W]) last_key_pressed_ = SDL_SCANCODE_W;
	else if (current_key_states_[SDL_SCANCODE_A]) last_key_pressed_ = SDL_SCANCODE_A;
	else if (current_key_states_[SDL_SCANCODE_S]) last_key_pressed_ = SDL_SCANCODE_S;
	else if (current_key_states_[SDL_SCANCODE_D]) last_key_pressed_ = SDL_SCANCODE_D;
	if (current_key_states_[SDL_SCANCODE_E]) reverse_requested_ = true;
}
