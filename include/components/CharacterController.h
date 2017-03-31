#pragma once

#include "conf.h"
#include "components/Component.h"
#include "managers/InputManager.h"

class CharacterController : public Component {
public:
	CharacterController(GameObject *parent, resource_map *resources);
	~CharacterController();

	void update(const double delta_time) override;
	void start() override;
	void exit() override;


private:
	float speed_modifier_ = 2;
};