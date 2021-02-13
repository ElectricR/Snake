#pragma once
#include <memory>

class SnakeTail;
class SnakeController;
class Fruit;

class Event {
public:
	virtual ~Event() = default;
};

class FruitEvent:
	public Event
{
public:
	FruitEvent(const std::shared_ptr<SnakeController>& sc):
		snake_controller(sc)
	{}

	std::shared_ptr<SnakeController> snake_controller;
};

class PartEvent:
	public Event
{
public:
	PartEvent(unsigned x_cell, 
			unsigned y_cell, 
			const std::shared_ptr<SnakeController>& sc, 
			const std::shared_ptr<SnakeTail>& tail):
		x_cell(x_cell),
		y_cell(y_cell),
		snake_controller(sc),
		tail(tail)
	{}

	unsigned x_cell;
	unsigned y_cell;
	const std::shared_ptr<SnakeController> snake_controller;
	const std::shared_ptr<SnakeTail> tail;
};

class GameOverEvent:
	public Event 
{
public:
	GameOverEvent(const std::shared_ptr<SnakeController>& sc):
		snake_controller(sc)
	{}
	
	const std::shared_ptr<SnakeController> snake_controller;
};
			
