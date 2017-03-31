#include "components/SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject *parent, resource_map *resources) : Component(parent, resources) {
	for(auto resource : *resources) {
		if(std::strcmp(resource.second.second.c_str(), "sprite_file") == 0)
			sprite_file_ = resource.first;
	}
}

SpriteRenderer::~SpriteRenderer() {
	
}

void SpriteRenderer::load() {
	auto *texture = g_ResourceManager->get_texture(sprite_file_);
	sprite_.setTexture(*texture);
	sprite_.setScale(1.f, -1.f);
}

void SpriteRenderer::start() {

}

void SpriteRenderer::render(sf::RenderTarget& canvas) {
	sprite_.setPosition(parent_->get_position());
	canvas.draw(sprite_);
}
