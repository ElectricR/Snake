#pragma once
#include "SnakePart.h"
#include <deque>
#include "Events.h"


class SnakeTail:
	public SnakePart
{
public:
	using SnakePart::SnakePart;
	void move_update() override {
		if (can_move_) {
			if (basic_part_update()) {
				free_cells_.emplace_back(prev_x_cell_, prev_y_cell_);
				index_map_[prev_x_cell_ * global::CELL_COUNT + prev_y_cell_] = free_cells_.size() - 1;
				update_prev_cell();
			}
		}
	}
	
	void update_prev_cell() {
		prev_x_cell_ = get_x_cell();
		prev_y_cell_ = get_y_cell();
	}

	void notify_movement() {
		can_move_ = true;
	}

	void notify_fruit(const std::pair<unsigned, unsigned>& fruit) {
		if (snake_controller_->get_direction()) {
			fruit_locations_.push_back(fruit);
		}
		else {
			fruit_locations_.push_front(fruit);
		}
	}

	ActionStatus new_part_update(std::unique_ptr<Event>& event) {
		if (!fruit_locations_.empty()) {
			bool unhandled_event = false;
			if (snake_controller_->get_direction()) {
				if (fruit_locations_.front() == std::pair<unsigned, unsigned>{get_x_cell(), get_y_cell()}) {
					unhandled_event = true;
				}
			}
			else {	
				if (fruit_locations_.back() == std::pair<unsigned, unsigned>{get_x_cell(), get_y_cell()}) {
					unhandled_event = true;
				}
			}
			if (unhandled_event) {
				can_move_ = false;
				event = std::make_unique<PartEvent>(get_x_cell(), 
						get_y_cell(), 
						snake_controller_, 
						static_pointer_cast<SnakeTail>(upper_part_.lock()->get_lower_part()));
				if (snake_controller_->get_direction()) {
					fruit_locations_.pop_front();
				}
				else {
					fruit_locations_.pop_back();
				}
				return ActionStatus::NEW_PART;
			}
		}
		return ActionStatus::NONE;
	}

	void set_upper_part(const std::shared_ptr<SnakePart>& part) {
		upper_part_ = part;
	}

	std::shared_ptr<SnakePart> get_upper_part() const {
		return upper_part_.lock();
	}

	bool get_can_move() const {
		return can_move_;
	}
private:
	std::weak_ptr<SnakePart> upper_part_;
	unsigned prev_x_cell_ = get_x_cell();
	unsigned prev_y_cell_ = get_y_cell();
	bool can_move_ = true;
	std::deque<std::pair<unsigned, unsigned>> fruit_locations_;
};
