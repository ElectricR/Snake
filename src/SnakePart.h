#pragma once
#include <memory>
#include "Active.h"
#include "ActionStatus.h"
#include "SnakeController.h"

class SnakePart:
	public Active
{
public:
	SnakePart(SDL_Texture *img, 
			unsigned x_cell, 
			unsigned y_cell, 
			int layer, 
			const std::shared_ptr<SnakeController>& snake_controller,
			std::vector<std::pair<unsigned, unsigned>>& free_cells,
			std::vector<int>& index_map,
			const std::shared_ptr<SnakePart>& lower_part):
		Active(img, x_cell, y_cell, layer, free_cells, index_map),
		snake_controller_(snake_controller),
		lower_part_(lower_part)
	{}

	virtual void move_update() {};

	virtual void update_direction() {
		set_direction(next_direction_);
	}
	void recursive_direction_update() {
		if (lower_part_) {
			lower_part_->set_next_direction(get_direction());
			lower_part_->recursive_direction_update();
		}
		update_direction();
	}

	bool basic_part_update();

	std::shared_ptr<SnakePart> get_lower_part() const {
		return lower_part_;
	}

	void set_lower_part(const std::shared_ptr<SnakePart> lower_part) {
		lower_part_ = lower_part;
	}

	void set_next_direction(int v) {
		next_direction_ = v;
	}

	int get_next_direction() const {
		return next_direction_;
	}
protected:
	std::shared_ptr<SnakeController> snake_controller_;
private:
	std::shared_ptr<SnakePart> lower_part_;
	int next_direction_ = 0;
};
