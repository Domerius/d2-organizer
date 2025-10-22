#ifndef ENTITY_OBSERVER_CPP
#define ENTITY_OBSERVER_CPP

#include "../../include/entity/observer.hpp"


template <typename T>
const bool EntityObserver<std::weak_ptr<T>>::connectEntity(const std::shared_ptr<T>& entity)
{
    if (findEntity(entity) == observedEntities.end())
    {
        observedEntities.emplace_back(std::weak_ptr(entity));
        return true;
    }
    return false;
}

template <typename T>
const bool EntityObserver<std::weak_ptr<T>>::connectEntity(const std::vector<const std::shared_ptr<T>>& entities)
{
    bool allUniqueFlag = true;
    if(entities.empty())
    {
        for (auto entity : entities)
        {
            if (!connectEntity(entity)) allUniqueFlag = false;
        }
    }
    else throw std::invalid_argument("Received empty vector of T");
    return allUniqueFlag;
}

#endif
