#include <string>
#include <vector>
#include <utility>

#ifndef GUARDIAN_HPP
#define GUARDIAN_HPP

// #include "activity.hpp"
class Activity;
class TriumphToken;


/*
    Notatki:
    Przeciążony operator == dla innej instancji tego samego obiektu oraz dla samego ID
    Obiekt może istnieć bez przypisanych Triumfów, ale nie na odwrót
*/

/**
 * @class Guardian
 * @brief A representation of a single player.
 */
class Guardian
{

    const std::string id;
    std::vector<const std::pair<Activity*, TriumphToken*>> ptrRelatedTriumphs;

public:

    inline Guardian(const std::string guardianId)
        : id(guardianId) {}
    inline Guardian(const std::string guardianId, const std::pair<Activity*, TriumphToken*>& ptrRelatedPair)
        : id(guardianId) {ptrRelatedTriumphs.emplace_back(ptrRelatedPair);}
    Guardian(const std::string guardianId, std::vector<const std::pair<Activity*, TriumphToken*>> ptrRelatedPairs);

    const bool addRelatedTriumph(const std::pair<Activity*, TriumphToken*>& relatedTriumph);
    const bool addRelatedTriumph(std::vector<const std::pair<Activity*, TriumphToken*>>& relatedTriumph);

    const bool removeRelatedTriumph(const std::pair<const Activity*, const TriumphToken*>& relatedTriumph);
    
    inline const bool operator==(const std::string otherId){return otherId==id;}
    const bool operator==(const Guardian other);

    inline const std::string getId(){return id;}

};

#endif
