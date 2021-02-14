#pragma once
#include <SDL2/SDL.h>
#include <utility>
#include "Fruit.h"

class SnakeController {
public:
	SnakeController(const uint8_t*& current_key_states):
		current_key_states_(current_key_states)
	{}

	void update();

	void reset_last_key_pressed() {
		last_key_pressed_ = -1;
	}

	void reset_reverse_requested() {
		reverse_requested_ = false;
	}

	bool get_reverse_requested() const {
		return reverse_requested_;
	}

	int get_last_key_pressed() const {
		return last_key_pressed_;
	}

	std::shared_ptr<Fruit> get_fruit() const {
		return fruit_;
	}

	void set_fruit(const std::shared_ptr<Fruit>& v) {
		fruit_ = v;
	}

	std::pair<unsigned, unsigned> get_fruit_location() const {
		return fruit_->get_location();
	}

	void change_direction() {
		direction_ = !direction_;
	}

	bool get_direction() const {
		return direction_;
	}

	void add_score() {
		++score_;
	}

	unsigned get_score() const {
		return score_;
	}
private:
	unsigned score_ = 0;
	const uint8_t *&current_key_states_;
	int last_key_pressed_;
	bool reverse_requested_ = false;
	bool direction_ = false;
	std::shared_ptr<Fruit> fruit_;
};
