#pragma once

#include "conf.h"
#include "components/Component.h"
#include "managers/ResourceManager.h"

class SpriteRenderer : public Component {
public:
	SpriteRenderer(GameObject *parent, resource_map *resources);
	~SpriteRenderer();

	void load() override;
	void start() override;
	void render(sf::RenderTarget& canvas) override;
private:
	std::string sprite_file_;
	sf::Sprite sprite_;
};