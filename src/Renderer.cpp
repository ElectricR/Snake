#include "Renderer.h"

void Renderer::render() {
	SDL_RenderClear(sdl_renderer_);

	for (std::multiset<std::weak_ptr<Entity>, EntityLayerComparator>::iterator 
			it = rend_list_.begin();
			it != rend_list_.end();) {
		std::shared_ptr<Entity> ptr = (*it).lock();
		if (!ptr) {
			it = rend_list_.erase(it);
		}
		else {
			ptr->render(sdl_renderer_);
			++it;
		}
	}

	SDL_RenderPresent(sdl_renderer_);
}
