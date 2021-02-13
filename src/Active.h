#pragma once
#include "Entity.h"
#include <algorithm>
#include "globals.h"

class Active:
	public Entity
{
public:
	Active(SDL_Texture *img, 
			unsigned x_cell, 
			unsigned y_cell, 
			int layer,
			std::vector<std::pair<unsigned, unsigned>>& free_cells,
			std::vector<int>& index_map):
		Entity(img, x_cell * global::CELL_SIZE, y_cell * global::CELL_SIZE, layer),
		free_cells_(free_cells),
		index_map_(index_map),
		x_cell_(x_cell),
		y_cell_(y_cell)
	{
		if (cell_in_pool(get_x_cell(), get_y_cell())) {
			remove_cell_from_pool(get_x_cell(), get_y_cell());
		}
	}

	int get_x_cell() const {
		return x_cell_;
	}

	int get_y_cell() const {
		return y_cell_;
	}

	void add_x_cell(int v) {
		x_cell_ += v;
	}

	void add_y_cell(int v) {
		y_cell_ += v;
	}

	void set_x_cell(int v) {
		x_cell_ = v;
	}

	void set_y_cell(int v) {
		y_cell_ = v;
	}

	std::pair<unsigned, unsigned> get_location() {
		return {x_cell_, y_cell_};
	}
protected:
	void remove_cell_from_pool(unsigned x_cell, unsigned y_cell) {
		index_map_.at(free_cells_.back().first * global::CELL_COUNT + free_cells_.back().second) = 
			index_map_.at(x_cell * global::CELL_COUNT + y_cell);
		std::swap(free_cells_.at(index_map_.at(x_cell * global::CELL_COUNT + y_cell)), free_cells_.back());
		free_cells_.pop_back();
		index_map_.at(x_cell * global::CELL_COUNT + y_cell) = -1;
	}

	bool cell_in_pool(unsigned x, unsigned y) {
		return index_map_[x * global::CELL_COUNT + y] != -1;
	}

	std::vector<std::pair<unsigned, unsigned>>& free_cells_;
	std::vector<int>& index_map_;

private:
	int x_cell_ = 0;
	int y_cell_ = 0;
};	
