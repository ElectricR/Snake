#include "SnakePart.h"
#include <cmath>
#include "globals.h"

bool SnakePart::basic_part_update() {
	constexpr double shift = global::CELL_SIZE * 1000 / global::SNAKE_SLOWNESS / global::TARGET_FPS;

	if (get_direction() == 0) {
		add_x(shift);
		if (std::abs(get_x() - (get_x_cell() + 1) * global::CELL_SIZE) < shift / 2) {
			if (get_x_cell() == global::CELL_COUNT - 1) set_x_cell(0);
			else add_x_cell(1);
			set_x(get_x_cell() * global::CELL_SIZE);
			return true;
		}
	}
	else if (get_direction() == 2) {
		add_x(-shift);
		if (std::abs(get_x_cell() * global::CELL_SIZE - get_x() - global::CELL_SIZE) < shift / 2) {
			if (get_x_cell() == 0) set_x_cell(global::CELL_COUNT - 1);
			else add_x_cell(-1);
			set_x(get_x_cell() * global::CELL_SIZE);
			return true;
		}
	}
	else if (get_direction() == 1) {
		add_y(-shift);
		if (std::abs(get_y_cell() * global::CELL_SIZE - get_y() - global::CELL_SIZE) < shift / 2) {
			if (get_y_cell() == 0) set_y_cell(global::CELL_COUNT - 1);
			else add_y_cell(-1);
			set_y(get_y_cell() * global::CELL_SIZE);
			return true;
		}
	}
	else if (get_direction() == 3) {
		add_y(shift);
		if (std::abs(get_y() - get_y_cell() * global::CELL_SIZE - global::CELL_SIZE) < shift / 2) {
			if (get_y_cell() == global::CELL_COUNT - 1) set_y_cell(0);
			else add_y_cell(1);
			set_y(get_y_cell() * global::CELL_SIZE);
			return true;
		}
	}
	return false;
}
