#include "GameManager.h"
#include "SnakeHead.h"
#include "SnakeTail.h"
#include "SnakeBody.h"
#include <iostream>

std::shared_ptr<Fruit> GameManager::create_fruit() {
	std::pair<unsigned, unsigned> fruit_location = free_cells_[rand() % free_cells_.size()];
	std::shared_ptr<Fruit> f = std::make_shared<Fruit>(texture_collection_->fruit_img, 
			fruit_location.first,
			fruit_location.second,
			1,
			free_cells_,
			index_map_);
	world_entities_.insert(f);
	renderer_->add(f);
	return f;
}

std::shared_ptr<SnakeBody> GameManager::create_part(unsigned x_cell, 
		unsigned y_cell, 
		const std::shared_ptr<SnakeController>& snake_controller,
		const std::shared_ptr<SnakePart>& lower_part) {
	std::shared_ptr<SnakeBody> part = std::make_shared<SnakeBody>(texture_collection_->body_img, 
			x_cell, 
			y_cell, 
			2,
			snake_controller,
			free_cells_,
			index_map_,
			lower_part);
	renderer_->add(part);
	return part;
}	

void GameManager::init_world(const uint8_t *&current_key_states) {
	std::shared_ptr<Entity> bg = std::make_shared<Entity>(texture_collection_->bg_img, 0, 0, 0);
	world_entities_.insert(bg);
	renderer_->add(bg);

	std::shared_ptr<SnakeController> snake_controller = 
		std::make_shared<SnakeController>(current_key_states);


	std::shared_ptr<SnakeTail> t = std::make_shared<SnakeTail>(texture_collection_->body_img, 
			0, 
			0, 
			2, 
			snake_controller, 
			free_cells_,
			index_map_,
			nullptr);		
	renderer_->add(t);
	actions_.insert(make_action<SnakeTail>(t, &SnakeTail::new_part_update, ActionType::NEW_PART_UPDATE));

	std::shared_ptr<SnakePart> prev = t;

	for (int i = 1; i != 2; ++i) {
		prev = create_part(i, 0, snake_controller, prev);
		if (i == 1) t->set_upper_part(prev);
	}

	std::shared_ptr<SnakeHead> h = std::make_shared<SnakeHead>(texture_collection_->head_img, 
			2, 
			0, 
			2, 
			snake_controller, 
			free_cells_,
			index_map_,
			prev,
			t);		
	world_entities_.insert(h);
	renderer_->add(h);
	actions_.insert(make_action<SnakeHead>(h, &SnakeHead::update, ActionType::HEAD_UPDATE));
	actions_.insert(make_action<SnakeHead>(h, &SnakeHead::collision_update, ActionType::HEAD_COLLISION_UPDATE));


	snake_controller->set_fruit(create_fruit());
}

bool GameManager::manage() {
	for (std::set<std::unique_ptr<ActionBase>, ActionComparator>::iterator it = actions_.begin();
			it != actions_.end();) {
		std::unique_ptr<Event> event;
		switch((*it)->handle(event)) {
		case ActionStatus::FRUIT_EATEN: {
			std::shared_ptr<Fruit> fruit = static_cast<FruitEvent*>(event.get())->
				snake_controller->get_fruit();
			FruitEvent *fruit_event = static_cast<FruitEvent*>(event.get());
			renderer_->remove(fruit);
			world_entities_.erase(fruit);
			if (free_cells_.size() == 0) {
				std::cout << "You won!" << std::endl;
				std::cout << "Your score is " << fruit_event->snake_controller->get_score() <<'!' << std::endl;
				return true;
			}

			fruit = create_fruit();
			fruit_event->snake_controller->set_fruit(fruit);
			fruit_event->snake_controller->add_score();
			break;
		}
		case ActionStatus::NEW_PART: {
			PartEvent *part_event = static_cast<PartEvent*>(event.get());
			std::shared_ptr<SnakeBody> body = create_part(part_event->x_cell, 
					part_event->y_cell,
					part_event->snake_controller,
					part_event->tail);
			body->set_direction(part_event->tail->get_direction());
			part_event->tail->get_upper_part()->set_lower_part(body);
			part_event->tail->set_upper_part(body);
			break;
		}
		case ActionStatus::GAME_OVER: {
				
			std::cout << "Game over!" << std::endl;
			std::cout << "Your score is " << 
				static_cast<GameOverEvent*>(event.get())->snake_controller->get_score() <<
				'!' << std::endl;
			return true;
		}
		default: {
			break;
		}
		}		
		++it;
	}
	return false;
}
