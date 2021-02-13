#include "Entity.h"
#include "globals.h"

void Entity::render(SDL_Renderer *sdl_renderer) {
	SDL_Rect frame_rect{ 0, 0, image_w_, image_h_ };
	SDL_Rect dest_rect{ x_, y_, image_w_, image_h_ };
	SDL_RenderCopyEx(sdl_renderer, img_, &frame_rect, &dest_rect, 360 - 90 * direction_, nullptr, SDL_FLIP_NONE);
	if (x_ < 0) {
		dest_rect = {x_ + global::CELL_SIZE * global::CELL_COUNT, y_, image_w_, image_h_ };
		SDL_RenderCopyEx(sdl_renderer, img_, &frame_rect, &dest_rect, 360 - 90 * direction_, nullptr, SDL_FLIP_NONE);
	}
	if (y_ < 0) {
		dest_rect = {x_, y_ + global::CELL_SIZE * global::CELL_COUNT, image_w_, image_h_ };
		SDL_RenderCopyEx(sdl_renderer, img_, &frame_rect, &dest_rect, 360 - 90 * direction_, nullptr, SDL_FLIP_NONE);
	}
	if (y_ > global::CELL_SIZE * (global::CELL_COUNT - 1)) {
		dest_rect = {x_, y_ - global::CELL_SIZE * global::CELL_COUNT, image_w_, image_h_ };
		SDL_RenderCopyEx(sdl_renderer, img_, &frame_rect, &dest_rect, 360 - 90 * direction_, nullptr, SDL_FLIP_NONE);
	}
	if (x_ > global::CELL_SIZE * (global::CELL_COUNT - 1)) {
		dest_rect = {x_ - global::CELL_SIZE * global::CELL_COUNT, y_, image_w_, image_h_ };
		SDL_RenderCopyEx(sdl_renderer, img_, &frame_rect, &dest_rect, 360 - 90 * direction_, nullptr, SDL_FLIP_NONE);
	}
}
