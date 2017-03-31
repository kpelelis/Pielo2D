#include "components/Component.h"

Component::Component (GameObject *parent, resource_map * resources) {
	parent_ = parent;
	resources_ = resources;
}