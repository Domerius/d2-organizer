#include <string>
#include <vector>
#include <utility>
#include <memory>

#ifndef GUARDIAN_HPP
#define GUARDIAN_HPP

class Activity;
class Triumph;
enum class TriumphType;


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
    std::vector<std::shared_ptr<Triumph>> ptrTriumphs;

    // template <typename ActivityType>
    // const std::shared_ptr<Triumph> createTriumph(const TriumphType& triumph, const ActivityType& activity);

    template <typename ActivityType>
    std::weak_ptr<Triumph> findTriumph (const ActivityType& activityType, const TriumphType& triumphType) const;
    std::weak_ptr<Triumph> findTriumph (const std::shared_ptr<Activity>& activity, const TriumphType& triumphType) const;

public:

    inline Guardian(const std::string guardianId)
        : id(guardianId) {}
    inline Guardian(const std::string guardianId, const std::shared_ptr<Triumph>& ptrRelatedTriumph)
        : id(guardianId) {ptrTriumphs.emplace_back(std::weak_ptr<Triumph>(ptrRelatedTriumph));}
    Guardian(const std::string guardianId, std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumphs);

    // When the Catalogue adds Triumphs to multiple Guardians, only the first creates it, the rest gets only pointer to copy 
    const bool connectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph);
    const bool connectTriumph(std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumph);

    // When the Catalogue removes Triumphs to multiple Guardians, only the first creates it, the rest gets only pointer to copy 
    const void disconnectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph);
    const void disconnectTriumph(std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumph);

    std::vector<std::shared_ptr<Triumph>>::iterator begin() {return ptrTriumphs.begin();}
    std::vector<std::shared_ptr<Triumph>>::iterator end() {return ptrTriumphs.end();}
    std::vector<std::shared_ptr<Triumph>>::const_iterator begin() const {return ptrTriumphs.begin();}
    std::vector<std::shared_ptr<Triumph>>::const_iterator end() const {return ptrTriumphs.end();}
    
    inline const bool operator==(const std::string otherId) const {return otherId==id;}
    const bool operator==(const Guardian other) const;

    inline const std::string getId() const {return id;}
    inline const std::vector<std::shared_ptr<Triumph>>& getTriumphs() const {return ptrTriumphs;}
    template <typename ActivityType>
    const std::shared_ptr<Triumph>& getTriumph(const TriumphType& triumph, const ActivityType& activity) const;

};

#endif
