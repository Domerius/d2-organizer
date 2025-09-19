#include <string>
#include <vector>
#include <utility>
#include <memory>

#ifndef GUARDIAN_HPP
#define GUARDIAN_HPP

class TriumphToken;
class Activity;
enum class ActivityType;


/*
    Notatki:
    Przeciążony operator == dla innej instancji tego samego obiektu oraz dla samego ID
    Obiekt może istnieć bez przypisanych Triumfów, ale nie na odwrót
    Obiekt 
*/

/**
 * @class Guardian
 * @brief A representation of a single player.
 */
class Guardian
{

    const std::string id;
    const std::weak_ptr<Activity> ptrSuperior;
    std::vector<std::shared_ptr<TriumphToken>> ptrRelatedTriumphs;

public:

    inline Guardian(const std::string guardianId)
        : id(guardianId) {}
    inline Guardian(const std::string guardianId, const std::shared_ptr<TriumphToken>& ptrTriumph)
        : id(guardianId) {ptrRelatedTriumphs.emplace_back(std::weak_ptr<TriumphToken>(ptrTriumph));}
    Guardian(const std::string guardianId, std::vector<const std::shared_ptr<TriumphToken>>& ptrTriumphs);
    Guardian(const std::string guardianId, const TriumphType& triumph, const ActivityType& activity);
    Guardian(const std::string guardianId, const std::vector<std::pair<TriumphType, ActivityType>>& relatedPairs);

    const bool addRelatedTriumph(const std::shared_ptr<TriumphToken>& ptrTriumph);
    const bool addRelatedTriumph(std::vector<const std::shared_ptr<TriumphToken>>& ptrTriumph);
    const bool addRelatedTriumph(const TriumphType& triumph, const ActivityType& activity);
    const bool addRelatedTriumph(const std::vector<std::pair<TriumphType, ActivityType>>& relatedPairs);

    const bool removeRelatedTriumph(const std::shared_ptr<TriumphToken> ptrTriumph);

    std::vector<std::shared_ptr<TriumphToken>>::iterator begin() {return ptrRelatedTriumphs.begin();}
    std::vector<std::shared_ptr<TriumphToken>>::iterator end() {return ptrRelatedTriumphs.end();}
    std::vector<std::shared_ptr<TriumphToken>>::const_iterator begin() const {return ptrRelatedTriumphs.begin();}
    std::vector<std::shared_ptr<TriumphToken>>::const_iterator end() const {return ptrRelatedTriumphs.end();}
    
    inline const bool operator==(const std::string otherId) const {return otherId==id;}
    const bool operator==(const Guardian other) const;

    inline const std::string getId() const {return id;}
    const std::vector<std::shared_ptr<TriumphToken>>& getTriumphs() const {return ptrRelatedTriumphs;}

};

#endif
