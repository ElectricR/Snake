#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
#include <set>
#include "Renderer.h"
#include "Action.h"
#include "globals.h"
#include "Fruit.h"
#include "SnakeBody.h"


class GameManager {
public:
	GameManager(const std::shared_ptr<Renderer>& renderer, 
			const uint8_t *&current_key_states,
			const uint32_t &frame_start_time):
		frame_start_time_(frame_start_time),
		renderer_(renderer)
	{
		texture_collection_ = std::make_unique<TextureCollection>(renderer_->get_renderer());

		for (int x = 0; x != global::CELL_COUNT; ++x) {
			for (int y = 0; y != global::CELL_COUNT; ++y) {
				free_cells_.emplace_back(x, y);
				index_map_[x * global::CELL_COUNT + y] = free_cells_.size() - 1;
			}
		}

		this->init_world(current_key_states);
	}

	bool manage();
private:

	class TextureCollection {
	public:
		TextureCollection(SDL_Renderer *sdl_renderer) {
			bg_img = this->load_texture("bg", sdl_renderer);
			fruit_img = this->load_texture("fruit", sdl_renderer);
			head_img = this->load_texture("head", sdl_renderer);
			body_img = this->load_texture("body", sdl_renderer);
		}

		~TextureCollection() {
			SDL_DestroyTexture(bg_img);
			SDL_DestroyTexture(fruit_img);
			SDL_DestroyTexture(body_img);
			SDL_DestroyTexture(head_img);
		}

		SDL_Texture *bg_img;
		SDL_Texture *fruit_img;
		SDL_Texture *head_img;
		SDL_Texture *body_img;
	private:
		SDL_Texture *load_texture(const std::string& name, SDL_Renderer *sdl_renderer) {
			SDL_Surface *img_pre = IMG_Load(("res/" + name + ".png").c_str());
			SDL_Texture *img = SDL_CreateTextureFromSurface(sdl_renderer, img_pre);

			SDL_FreeSurface(img_pre);
			return img;
		}
	};

	void init_world(const uint8_t *&);
	std::shared_ptr<Fruit> create_fruit();
	std::shared_ptr<SnakeBody> create_part(unsigned, 
			unsigned, 
			const std::shared_ptr<SnakeController>&,
			const std::shared_ptr<SnakePart>&);

	const uint32_t &frame_start_time_;
	std::vector<std::pair<unsigned, unsigned>> free_cells_;
	std::vector<int> index_map_ = std::vector<int>(global::CELL_COUNT * global::CELL_COUNT, 0);
	std::unordered_set<std::shared_ptr<Entity>> world_entities_;
	std::multiset<std::unique_ptr<ActionBase>, ActionComparator> actions_;
	std::shared_ptr<Renderer> renderer_ = nullptr;
	std::unique_ptr<TextureCollection> texture_collection_ = nullptr;
};
