#include <string>
#include <vector>
#include <utility>
#include <memory>

#ifndef GUARDIAN_HPP
#define GUARDIAN_HPP

class Triumph;
class Activity;
enum class TriumphType;
enum class ActivityType;


/*
    Notatki:
    Przeciążony operator == dla innej instancji tego samego obiektu oraz dla samego ID
    Obiekt może istnieć bez przypisanych Triumfów, ale nie na odwrót
*/

/**
 * @class Guardian
 * @brief A representation of a single player.
 * 
 * @details This class stores data about a single Guardian and pointers to its associated Triumphs.
 * Allows the creation of a Triumph and its existence depends on the Catalogue object pointing to it.
 */
class Guardian
{

    const std::string id;
    const std::weak_ptr<Activity> ptrSuperior;
    std::vector<std::shared_ptr<Triumph>> ptrRelatedTriumphs;

public:

    inline Guardian(const std::string guardianId)
        : id(guardianId) {}
    inline Guardian(const std::string guardianId, const std::shared_ptr<Triumph>& ptrTriumph)
        : id(guardianId) {ptrRelatedTriumphs.emplace_back(std::weak_ptr<Triumph>(ptrTriumph));}
    Guardian(const std::string guardianId, std::vector<const std::shared_ptr<Triumph>>& ptrTriumphs);
    Guardian(const std::string guardianId, const TriumphType& triumph, const ActivityType& activity);
    Guardian(const std::string guardianId, const std::vector<std::pair<TriumphType, ActivityType>>& relatedPairs);

    const bool addRelatedTriumph(const std::shared_ptr<Triumph>& ptrTriumph);
    const bool addRelatedTriumph(std::vector<const std::shared_ptr<Triumph>>& ptrTriumph);
    const bool addRelatedTriumph(const TriumphType& triumph, const ActivityType& activity);
    const bool addRelatedTriumph(const std::vector<std::pair<TriumphType, ActivityType>>& relatedPairs);

    const bool removeRelatedTriumph(const std::shared_ptr<Triumph> ptrTriumph);

    std::vector<std::shared_ptr<Triumph>>::iterator begin() {return ptrRelatedTriumphs.begin();}
    std::vector<std::shared_ptr<Triumph>>::iterator end() {return ptrRelatedTriumphs.end();}
    std::vector<std::shared_ptr<Triumph>>::const_iterator begin() const {return ptrRelatedTriumphs.begin();}
    std::vector<std::shared_ptr<Triumph>>::const_iterator end() const {return ptrRelatedTriumphs.end();}
    
    inline const bool operator==(const std::string otherId) const {return otherId==id;}
    const bool operator==(const Guardian other) const;

    inline const std::string getId() const {return id;}
    const std::vector<std::shared_ptr<Triumph>>& getTriumphs() const {return ptrRelatedTriumphs;}

};

#endif
