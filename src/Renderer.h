#pragma once
#include <SDL2/SDL.h>
#include <set>
#include "Entity.h"
#include "globals.h"


class Renderer {
public:
	Renderer() {
		unsigned int screen_width = global::CELL_SIZE * global::CELL_COUNT;
		unsigned int screen_height = global::CELL_SIZE * global::CELL_COUNT;
		
		window_ = SDL_CreateWindow("CSCSnake", 
				SDL_WINDOWPOS_UNDEFINED, 
				SDL_WINDOWPOS_UNDEFINED, 
				screen_width, 
				screen_height, 
				SDL_WINDOW_SHOWN);
		sdl_renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(sdl_renderer_, 0x0, 0x0, 0x0, 0xFF);
	}

	~Renderer() {
		SDL_DestroyRenderer(sdl_renderer_);
		SDL_DestroyWindow(window_);
	}

	void render();

	void add(std::weak_ptr<Entity> entity) {
		rend_list_.insert(entity);
	}

	void remove(const std::weak_ptr<Entity>& entity) {
		rend_list_.erase(rend_list_.find(entity));
	}

	SDL_Renderer *get_renderer() const {
		return sdl_renderer_;
	}

private:
	std::multiset<std::weak_ptr<Entity>, EntityLayerComparator> rend_list_;
	SDL_Window *window_;
	SDL_Renderer *sdl_renderer_;
};

