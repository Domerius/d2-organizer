#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include <string>


/**
 * 
 */
template <typename T>
class EntityBase
{
protected:

    T description;

public:

    inline EntityBase(T description) : description(description) {}
    virtual ~EntityBase() = default;

    using DescriptionType = T;
    
    virtual operator std::string() const {return std::string(description);}

    inline const T getDescription() const {return description;}

};

#endif
