#pragma once
#include "SnakeTail.h"
#include "Events.h"

class SnakeHead:
	public SnakePart
{
public:
	SnakeHead(SDL_Texture *img,
			unsigned x_cell,
			unsigned y_cell,
			int layer,
			const std::shared_ptr<SnakeController>& snake_controller,
			std::vector<std::pair<unsigned, unsigned>>& free_cells,
			std::vector<int>& index_map,
			const std::shared_ptr<SnakePart>& next_part,
			const std::shared_ptr<SnakeTail>& tail):
		SnakePart(img, x_cell, y_cell, layer, snake_controller, free_cells, index_map, next_part),
		tail_(tail)
	{}

	ActionStatus update(std::unique_ptr<Event>& event);

	ActionStatus collision_update(std::unique_ptr<Event>&);

	void update_direction() override;

	void set_tail(const std::shared_ptr<SnakeTail> tail) {
		tail_ = tail;
	}
private:
	void reverse_snake();
	void swap_with_tail();
	std::shared_ptr<SnakeTail> tail_;

};
