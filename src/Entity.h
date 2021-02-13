#pragma once
#include <SDL2/SDL.h>
#include <memory>

class Entity {
public:
	Entity(SDL_Texture *img, double x, double y, int layer):
		img_(img),
		x_(x),
		y_(y),
		layer_(layer)
	{
		SDL_QueryTexture(img_, NULL, NULL, &image_w_, &image_h_);
	}

	virtual ~Entity() = default;
	void render(SDL_Renderer *);

	int get_layer() const {
		return layer_;
	}

	int get_direction() const {
		return direction_;
	}

	void set_direction(int v) {
		direction_ = v;
	}

	double get_x() const {
		return x_;
	}

	double get_y() const {
		return y_;
	}

	void add_x(double v) {
		x_ += v;
	}

	void add_y(double v) {
		y_ += v;
	}

	void set_x(double v) {
		x_ = v;
	}

	void set_y(double v) {
		y_ = v;
	}

private:
	SDL_Texture *img_;
	double x_ = 0;
	double y_ = 0;
	int image_w_ = 0;
	int image_h_ = 0;
	int layer_ = 0;
	int direction_ = 0;
};

class EntityLayerComparator {
public:
	bool operator()(const std::weak_ptr<Entity>& a, const std::weak_ptr<Entity>& b) const {
		return a.lock()->get_layer() < b.lock()->get_layer();
	}
};
