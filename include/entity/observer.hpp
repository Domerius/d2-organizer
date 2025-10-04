#ifndef ENTITY_CONTAINER_HPP
#define ENTITY_CONTAINER_HPP

#include "base.hpp"

#include <vector>
#include <type_traits>
#include <memory>


/**
 * 
 */
template <typename T, typename TDescription>
class EntityObserverBase
{

    std::vector<const T> observedEntities;

    virtual std::vector<const T>::iterator& findEntity(const T entity) = 0;
    virtual std::vector<const T>::iterator& findEntity(const TDescription entity) = 0;

public:

    inline EntityObserverBase(const T ptrEntity) {observedEntities.emplace_back(ptrEntity);}
    inline EntityObserverBase(std::vector<const T> ptrEntities) {connectEntity(ptrEntities);};

    virtual ~EntityObserverBase() = default;

    const bool connectEntity(const T& entity);
    const bool connectEntity(const std::vector<const T>& entities);

    const bool disconectEntity(const TDescription& description);
    const bool disconectEntity(const std::vector<const TDescription>& descriptions);

    typename std::vector<T>::iterator begin() {return observedEntities.begin();}
    typename std::vector<T>::iterator end() {return observedEntities.end();}
    typename std::vector<T>::const_iterator begin() const {return observedEntities.begin();}
    typename std::vector<T>::const_iterator end() const {return observedEntities.end();}

    inline const std::vector<T> getObservedEntities() const {return observedEntities;}

};


/**
 * 
 */
template <typename T>
class EntityObserver : public EntityObserverBase<T, T::DescriptionType>;

template <typename T>
class EntityObserver<std::shared_ptr<T>> : public EntityObserverBase<std::shared_ptr<T>, typename T::DescriptionType>
{
protected:

    std::vector<const std::shared_ptr<T>>::iterator& findEntity(const std::shared_ptr<T> entity) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [entity](std::vector<std::shared_ptr<T>>::iterator itObservedEntity){return entity == *itObservedEntity;})}

    std::vector<const std::shared_ptr<T>>::iterator& findEntity(const EntityDescription& description) override
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [description](std::vector<std::shared_ptr<T>>::iterator itObservedEntity){return description == (*itObservedEntity)->getDescription();})}

public:

    inline EntityObserver(const std::shared_ptr<T> ptrEntity) : EntityObserverBase(ptrEntities) {}
    inline EntityObserver(std::vector<const std::shared_ptr<T>> ptrEntities) : EntityObserverBase(ptrEntities) {}

    virtual ~EntityObserver() = default;

    using EntityDescription = T::DescriptionType;
    static_assert(std::is_base_of_v<EntityBase<EntityDescription>, T>,
        "T must derive from EntityBase.");

    const bool connectEntity(const std::shared_ptr<T>& entity);
    const bool connectEntity(const std::vector<const std::shared_ptr<T>>& entities);

    const bool disconectEntity(const EntityDescription& description);
    const bool disconectEntity(const std::vector<const EntityDescription>& descriptions);

    typename std::vector<std::shared_ptr<T>>::iterator begin() {return observedEntities.begin();}
    typename std::vector<std::shared_ptr<T>>::iterator end() {return observedEntities.end();}
    typename std::vector<std::shared_ptr<T>>::const_iterator begin() const {return observedEntities.begin();}
    typename std::vector<std::shared_ptr<T>>::const_iterator end() const {return observedEntities.end();}

    inline const std::vector<std::shared_ptr<T>> getObservedEntities() const {return observedEntities;}

};

template <typename T>
class EntityObserver<std::weak_ptr<T>> : public EntityObserverBase<std::weak_ptr<T>, T::DescriptionType>
{
protected:

    std::vector<std::weak_ptr<T>> observedEntities;

    std::vector<std::weak_ptr<T>>::iterator& findEntity(const std::shared_ptr<T> entity)
        {return std::find_if(observedEntities.begin(), observedEntities.end(),
            [entity](std::vector<std::weak_ptr<T>>::iterator itObservedEntity){return entity == itObservedEntity->lock();})}

    std::vector<std::weak_ptr<T>>::iterator& findEntity(const EntityDescription& description)
        {return std::find_if(observedEntities.begin(), observedEntities.end(), 
            [description](std::vector<std::weak_ptr<T>>::iterator itObservedEntity){return description == (*itObservedEntity)->getDescription();})}

public:

    inline EntityObserver(const std::shared_ptr<T> ptrEntity) {observedEntities.emplace_back(ptrEntity);}
    inline EntityObserver(std::vector<const std::shared_ptr<T>> ptrEntities) {connectEntity(ptrEntities);};

    virtual ~EntityObserver() = default;

    using EntityDescription = typename EntityBase<T>::DescriptionType;
    static_assert(std::is_base_of_v<EntityBase<EntityDescription>, T>,
        "T must derive from EntityBase.");

    const bool connectEntity(const std::shared_ptr<T>& entity);
    const bool connectEntity(const std::vector<const std::shared_ptr<T>>& entities);

    // const bool disconectEntity(const EntityDescription& description);
    // const bool disconectEntity(const std::vector<const EntityDescription>& descriptions);

    // typename std::vector<std::shared_ptr<T>>::iterator begin() {return observedEntities.begin();}
    // typename std::vector<std::shared_ptr<T>>::iterator end() {return observedEntities.end();}
    // typename std::vector<std::shared_ptr<T>>::const_iterator begin() const {return observedEntities.begin();}
    // typename std::vector<std::shared_ptr<T>>::const_iterator end() const {return observedEntities.end();}

    // inline const std::vector<std::shared_ptr<T>> getObservedEntities() const {return observedEntities;}

};

#endif
