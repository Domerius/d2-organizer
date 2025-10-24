#ifndef ENTITY_OBSERVER_HPP
#define ENTITY_OBSERVER_HPP

#include "base.hpp"
#include "observer_base.hpp"

#include <vector>
#include <type_traits>
#include <cstdint>
#include <memory>
#include <algorithm>


/**
 * 
 */
template <typename T>
class EntityObserver : public EntityObserverBase<T, typename T::DescriptionType>
{
public:

    EntityObserver() = default;
    inline EntityObserver(const T ptrEntity)
        : EntityObserverBase<T, typename T::DescriptionType>(ptrEntity) {}
    inline EntityObserver(std::vector<const T> ptrEntities)
        : EntityObserverBase<T, typename T::DescriptionType>(ptrEntities) {}

    virtual ~EntityObserver() = default;

    using EntityDescription = typename T::DescriptionType;
    static_assert(std::is_base_of_v<EntityBase<EntityDescription>, T>,
        "T must derive from EntityBase.");

protected:

    typename std::vector<const T>::iterator& findEntity(const T entity) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [entity](const std::vector<T>::iterator& itObservedEntity){return entity == *itObservedEntity;});}

    typename std::vector<const T>::iterator& findEntity(const EntityDescription& description) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [description](const std::vector<T>::iterator& itObservedEntity){return description == (*itObservedEntity)->getDescription();});}

};

template <typename T>
class EntityObserver<std::shared_ptr<T>> : public EntityObserverBase<std::shared_ptr<T>, typename T::DescriptionType>
{
public:

    EntityObserver() = default;
    inline EntityObserver(const std::shared_ptr<T> ptrEntity)
        : EntityObserverBase<std::shared_ptr<T>, typename T::DescriptionType>(ptrEntity) {}
    inline EntityObserver(std::vector<const std::shared_ptr<T>> ptrEntities)
        : EntityObserverBase<std::shared_ptr<T>, typename T::DescriptionType>(ptrEntities) {}

    virtual ~EntityObserver() = default;

    using EntityDescription = typename T::DescriptionType;
    static_assert(std::is_base_of_v<EntityBase<EntityDescription>, T>,
        "T must derive from EntityBase.");

protected:

    typename std::vector<const std::shared_ptr<T>>::iterator& findEntity(const std::shared_ptr<T> entity) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [entity](const std::vector<std::shared_ptr<T>>::iterator& itObservedEntity){return entity == *itObservedEntity;});}

    typename std::vector<const std::shared_ptr<T>>::iterator& findEntity(const EntityDescription& description) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [description](const std::vector<std::shared_ptr<T>>::iterator& itObservedEntity){return description == (*itObservedEntity)->getDescription();});}

};

template <typename T>
class EntityObserver<std::weak_ptr<T>> : public EntityObserverBase<std::weak_ptr<T>, typename T::DescriptionType>
{
public:

    EntityObserver() = default;
    inline EntityObserver(const std::shared_ptr<T> ptrEntity) {observedEntities.emplace_back(std::weak_ptr(ptrEntity));}
    inline EntityObserver(std::vector<const std::shared_ptr<T>> ptrEntities) {connectEntity(ptrEntities);};

    virtual ~EntityObserver() = default;

    using EntityDescription = typename EntityBase<T>::DescriptionType;
    static_assert(std::is_base_of_v<EntityBase<EntityDescription>, T>,
        "T must derive from EntityBase.");
    
    const bool connectEntity(const std::weak_ptr<T> entity) = delete;
    const bool connectEntity(const std::vector<const std::weak_ptr<T>> entities) = delete;

    const bool connectEntity(const std::shared_ptr<T>& entity);
    const bool connectEntity(const std::vector<const std::shared_ptr<T>>& entities);

protected:

    typename std::vector<std::weak_ptr<T>>::iterator& findEntity(const std::shared_ptr<T> entity) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(),
            [entity](const std::vector<std::weak_ptr<T>>::iterator& itObservedEntity){return entity == itObservedEntity->lock();});}

    typename std::vector<std::weak_ptr<T>>::iterator& findEntity(const EntityDescription& description) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(),
            [description](const std::vector<std::weak_ptr<T>>::iterator& itObservedEntity){return description == (*itObservedEntity)->getDescription();});}

};

#endif
