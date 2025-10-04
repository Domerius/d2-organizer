#ifndef ENTITY_CONTAINER_CPP
#define ENTITY_CONTAINER_CPP

#include "../../include/entity/observer.hpp"


template <typename T, typename TDescription>
const bool EntityObserverBase<T,TDescription>::connectEntity(const T& entity)
{
    if (findEntity(entity) == observedEntities.end())
    {
        observedEntities.emplace_back(entity);
        return true;
    }
    return false;
}

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::connectEntity(const std::vector<const T>& entities)
{
    bool allUniqueFlag = true;
    if(entities.empty())
    {
        for (auto entity : entities)
        {
            if (!EntityObserver<T>::connectEntity(entity)) allUniqueFlag = false;
        }
    }
    else throw std::invalid_argument("Received empty vector of T");
    return allUniqueFlag;
}

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::disconectEntity(const TDescription& description)
{   
    std::vector<std::shared_ptr<T>>::iterator itEntity = findEntity(description);
    if (itEntity != observedEntities.end())
    {
        observedEntities.erase(itEntity);
        return true;
    }
    return false;
}

template <typename T, typename TDescription>
const bool EntityObserverBase<T, TDescription>::disconectEntity(const std::vector<const TDescription>& descriptions)
{
    bool allUniqueFlag = true;
    if(entities.empty())
    {
        for (auto description : descriptions)
        {
            if (!EntityObserver<std::shared_ptr<T>>::disconectEntity(description)) allUniqueFlag = false;
        }
    }
    else throw std::invalid_argument("Received empty vector of TDescription");
    return allUniqueFlag;
}

#endif
