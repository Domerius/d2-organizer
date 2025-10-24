#ifndef ENTITY_OBSERVER_BASE_HPP
#define ENTITY_OBSERVER_BASE_HPP

#include <vector>


/**
 * @class EntityObserverBase
 * @brief A base template for classes containing object derived from EntityBase
 * 
 * @details This abstract class serves as a template the EntityObserver class.
 * It holds functionality of a container for an objects of template type T which have a public parameter of type TDescription.
 * The class also defines default methods for filling and emptying given vector alongside with container's iterators and a getter.
 */
template <typename T, typename TDescription>
class EntityObserverBase
{
public:

    inline EntityObserverBase() = default;
    inline EntityObserverBase(const T entity) {observedEntities.emplace_back(entity);}
    inline EntityObserverBase(std::vector<const T> entities) {connectEntity(entities);};

    virtual ~EntityObserverBase() = default;

    virtual const bool connectEntity(const T entity);
    virtual const bool connectEntity(const std::vector<const T> entities);

    virtual const bool disconnectEntity(const TDescription& description);
    virtual const bool disconnectEntity(const std::vector<const TDescription>& descriptions);

    typename std::vector<T>::iterator begin() {return observedEntities.begin();}
    typename std::vector<T>::iterator end() {return observedEntities.end();}
    typename std::vector<T>::const_iterator begin() const {return observedEntities.begin();}
    typename std::vector<T>::const_iterator end() const {return observedEntities.end();}

    inline const std::vector<T>& getObservedEntities() const {return observedEntities;}

protected:

    std::vector<const T> observedEntities;

    virtual typename std::vector<const T>::iterator& findEntity(const T entity) = 0;
    virtual typename std::vector<const T>::iterator& findEntity(const TDescription entity) = 0;

};

#endif
