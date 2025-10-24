#ifndef ENTITY_OBSERVER_BASE_CPP
#define ENTITY_OBSERVER_BASE_CPP

#include "../../include/entity/observer_base.hpp"

#include <stdexcept>


template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::connectEntity(const T entity)
{
    if (findEntity(entity) == observedEntities.end())
    {   
        observedEntities.emplace_back(entity);
        return true;
    }
    return false;
}

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::connectEntity(const std::vector<const T> entities)
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

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::disconnectEntity(const TDescription& description)
{   
    auto& itEntity = findEntity(description);
    if (itEntity != observedEntities.end())
    {   
        observedEntities.erase(itEntity);
        return true;
    }
    return false;
}

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::disconnectEntity(const std::vector<const TDescription>& descriptions)
{
    bool allUniqueFlag = true;
    if(descriptions.empty())
    {
        for (auto description : descriptions)
        {
            if (!disconectEntity(description)) allUniqueFlag = false;
        }
    }
    else throw std::invalid_argument("Received empty vector of TDescription");
    return allUniqueFlag;
}

#endif
