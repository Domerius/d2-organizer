#ifndef GUARDIAN_HPP
#define GUARDIAN_HPP

#include "types.hpp"
#include "triumph.hpp"
#include "activity.hpp"

#include <string>
#include <vector>
#include <utility>
#include <memory>


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
    std::vector<std::pair<std::shared_ptr<Triumph>, EncId>> ptrTriumphs;

    template <typename ActivityType>
    std::weak_ptr<Triumph> findTriumph (const ActivityType& activityType, const TriumphType& triumphType) const;
    std::weak_ptr<Triumph> findTriumph (const std::shared_ptr<Activity>& activity, const TriumphType& triumphType) const;

public:

    inline Guardian(const std::string guardianId)
        : id(guardianId) {}
    inline Guardian(const std::string guardianId, const std::shared_ptr<Triumph>& ptrRelatedTriumph, const EncId& encId)
        : id(guardianId) {ptrTriumphs.emplace_back(std::make_pair(std::weak_ptr<Triumph>(ptrRelatedTriumph), encId));}
    Guardian(const std::string guardianId, std::vector<const std::pair<std::shared_ptr<Triumph>, EncId>>& ptrRelatedPairs);

    // When the Catalogue adds Triumphs to multiple Guardians, only the first creates it, the rest gets only pointer to copy 
    const void connectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph, const EncId& encId);
    const void connectTriumph(const std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>& ptrRelatedPairs);

    // When the Catalogue removes Triumphs to multiple Guardians, only the first creates it, the rest gets only pointer to copy 
    const void disconnectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph);
    const void disconnectTriumph(std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumphs);

    std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>::iterator begin() {return ptrTriumphs.begin();}
    std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>::iterator end() {return ptrTriumphs.end();}
    std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>::const_iterator begin() const {return ptrTriumphs.begin();}
    std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>::const_iterator end() const {return ptrTriumphs.end();}
    
    inline const bool operator==(const std::string otherId) const {return otherId==id;}
    const bool operator==(const Guardian other) const;

    inline const std::string getId() const {return id;}
    inline const std::vector<std::pair<std::shared_ptr<Triumph>, EncId>>& getTriumphs() const {return ptrTriumphs;}
    template <typename ActivityType>
    const std::shared_ptr<Triumph>& getTriumph(const TriumphType& triumph, const ActivityType& activity) const;

};

#endif
