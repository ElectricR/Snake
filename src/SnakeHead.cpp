#include "SnakeHead.h"
#include <iostream>

void SnakeHead::swap_with_tail() {
	unsigned head_x_cell = get_x_cell();
	unsigned head_y_cell = get_y_cell();
	double head_x = get_x();
	double head_y = get_y();
	int head_direction = get_direction();

	set_x_cell(tail_->get_x_cell());
	set_y_cell(tail_->get_y_cell());
	set_x(tail_->get_x());
	set_y(tail_->get_y());
	set_direction((tail_->get_direction() + 2) % 4);

	tail_->set_x_cell(head_x_cell);
	tail_->set_y_cell(head_y_cell);
	tail_->set_x(head_x);
	tail_->set_y(head_y);
	tail_->update_prev_cell();
	tail_->set_direction((head_direction + 2) % 4);
}

void SnakeHead::update_direction() {
	int last_key_pressed = snake_controller_->get_last_key_pressed();
	if (get_direction() == 0 || get_direction() == 2) {
		if (last_key_pressed == SDL_SCANCODE_W) {
			set_direction(1);
		}
		else if (last_key_pressed == SDL_SCANCODE_S) { 
			set_direction(3);
		}
	}
	else {
		if (last_key_pressed == SDL_SCANCODE_A) {
			set_direction(2);
		}
		else if (last_key_pressed == SDL_SCANCODE_D) { 
			set_direction(0);
		}
	}
}

void SnakeHead::reverse_snake() {
	std::shared_ptr<SnakePart> second_part = get_lower_part();

	std::shared_ptr<SnakePart> prev = get_lower_part();
	std::shared_ptr<SnakePart> next = prev->get_lower_part();
	while (std::shared_ptr<SnakePart> next_next = next->get_lower_part()) {
		next->set_direction((next->get_direction() + 2) % 4);
		next->set_lower_part(prev);
		next->set_next_direction(prev->get_next_direction());
		prev = next;
		next = next_next;
	}
	second_part->set_lower_part(next);
	second_part->set_direction((second_part->get_direction() + 2) % 4);
	tail_->set_upper_part(get_lower_part());
	set_lower_part(prev);

	swap_with_tail();

	snake_controller_->reset_reverse_requested();
	snake_controller_->change_direction();
}

ActionStatus SnakeHead::update(std::unique_ptr<Event>& event) {
	bool fruit_eaten = false;
	snake_controller_->update();
	int ret = basic_part_update();
	get_lower_part()->move_update();
	
	if (ret) {
		tail_->notify_movement();
		if (snake_controller_->get_fruit_location() == 
				std::pair<unsigned, unsigned>(get_x_cell(), get_y_cell())) {
			fruit_eaten = true;
			tail_->notify_fruit({get_x_cell(), get_y_cell()});
		}

		if (snake_controller_->get_reverse_requested()) {
			if (!fruit_eaten) remove_cell_from_pool(get_x_cell(), get_y_cell());
			reverse_snake();
		}
		else {
			get_lower_part()->set_next_direction(get_direction());
			update_direction();
			get_lower_part()->recursive_direction_update();
			if (!fruit_eaten) remove_cell_from_pool(get_x_cell(), get_y_cell());
		}
		snake_controller_->reset_last_key_pressed();
	}
	snake_controller_->reset_reverse_requested();
	if (fruit_eaten) {
		event = std::make_unique<FruitEvent>(snake_controller_);
		return ActionStatus::FRUIT_EATEN;
	}
	return ActionStatus::NONE;
}

ActionStatus SnakeHead::collision_update(std::unique_ptr<Event>& event) {
	int next_x_cell = get_x_cell();
	int next_y_cell = get_y_cell();
	double distance_from_cell = std::abs(get_x() - get_x_cell() * global::CELL_SIZE + get_y() - get_y_cell() * global::CELL_SIZE);

	if (get_direction() == 0 || get_direction() == 2) {
		next_x_cell += 1 - get_direction();
		if (next_x_cell < 0) {
			next_x_cell = global::CELL_COUNT - 1;
		}
		else if (next_x_cell == global::CELL_COUNT) {
			next_x_cell = 0;
		}
	}
	else {
		next_y_cell += get_direction() - 2;
		if (next_y_cell < 0) {
			next_y_cell = global::CELL_COUNT - 1;
		}
		else if (next_y_cell == global::CELL_COUNT) {
			next_y_cell = 0;
		}
	}


	std::pair<unsigned, unsigned> fruit_location = snake_controller_->get_fruit_location();
	std::pair<unsigned, unsigned> next_location(next_x_cell, next_y_cell);
	if (index_map_[next_x_cell * global::CELL_COUNT + next_y_cell] == -1 and 
			fruit_location != next_location and
			distance_from_cell > static_cast<double>(global::CELL_SIZE) / 1.5 and
			(next_location != tail_->get_location() or
			 (next_location == tail_->get_location() and not tail_->get_can_move()))) {
		event = std::make_unique<GameOverEvent>(snake_controller_);
		return ActionStatus::GAME_OVER;
	}
	return ActionStatus::NONE;
}
