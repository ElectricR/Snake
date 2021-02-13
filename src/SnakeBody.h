#pragma once
#include "SnakePart.h"

class SnakeBody:
	public SnakePart
{
public:
	using SnakePart::SnakePart;

	void move_update() override {
		basic_part_update();
		get_lower_part()->move_update();
	};
};
