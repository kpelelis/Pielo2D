#pragma once

#include "components/Component.h"

template<typename T>
Component * create_component(GameObject * parent, resource_map *resources) { return new T(parent, resources); }

class ComponentFactory {
public:
    typedef std::map<std::string, Component*(*)(GameObject *, resource_map *)> ComponentMap;

    ComponentFactory() {
        component_map = new ComponentMap;         
    }

    ~ComponentFactory() {
        delete component_map;         
    }


    Component * create_instance(std::string const& s, GameObject * parent, resource_map *resources) {
        ComponentMap::iterator itt = component_map->find(s);
        if(itt == component_map->end())
            return 0;
        return itt->second(parent, resources);
    }

    template<class T>
    void register_component(const std::string& name) {
        INFO("ComponentFactory", "Registering component ", name)
        component_map->insert(std::make_pair(name, &create_component<T>));
    }

private:
    ComponentMap *component_map;
};