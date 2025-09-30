#ifndef TRIUMPH_HPP
#define TRIUMPH_HPP

#include "types.hpp"
#include "guardian.hpp"
#include "activity.hpp"

#include <string>
#include <vector>
#include <cstdint>
#include <memory>


/**
 * @class Triumph
 * @brief Keep a description of the achievement and indicate the associated Guardians and the Activity it is part of.
 * 
 * @details This class stores the description of the achievement to be obtained and indicates the players who need it and the activity that needs to be completed.
 * An object must be referenced by at least one Guardian to exist, and must reference exactly one associated Activity.
 */
class Triumph
{

    const TriumphType description;
    const std::shared_ptr<Activity> ptrActivity;
    std::vector<std::weak_ptr<Guardian>> ptrGuardians;

    void removeExpiredPointers();

public:

    // Zainicjuj obiekt z poziomu obiektu nadrzędnego
    inline Triumph(const std::shared_ptr<Guardian>& guardian, const std::shared_ptr<Activity>& activity, const TriumphType& triumph)
        : ptrActivity(std::weak_ptr<Activity>(activity)), description(triumph) {ptrGuardians.emplace_back(std::weak_ptr<Guardian>(guardian));}
    inline Triumph(std::vector<const std::shared_ptr<Guardian>>& guardians, const std::shared_ptr<Activity>& activity, const TriumphType& triumph)
        : description(triumph), ptrActivity(std::weak_ptr<Activity>(activity)) {connectGuardian(guardians);}

    // Jeśli nie jest duplikatem, dodaj guardiana do kontenera
    const bool connectGuardian(const std::shared_ptr<Guardian>& ptrGuardian);
    const bool connectGuardian(std::vector<const std::shared_ptr<Guardian>>& ptrGuardians);

    // Znajdź i usuń zarówno wzmiankę o sobię u tego Guardiana jak i jego ze swojej listy
    const bool disconectGuardian(const std::string& guardiansName);
    const bool disconectGuardian(std::vector<const std::string>& guardiansNames);

    // Przeciążony operator porównania
    const bool operator==(Triumph& other) const;

    std::vector<std::weak_ptr<Guardian>>::iterator begin() {return ptrGuardians.begin();}
    std::vector<std::weak_ptr<Guardian>>::iterator end() {return ptrGuardians.end();}
    std::vector<std::weak_ptr<Guardian>>::const_iterator begin() const {return ptrGuardians.begin();}
    std::vector<std::weak_ptr<Guardian>>::const_iterator end() const {return ptrGuardians.end();}

    inline const TriumphType getDescription() const {return description;}
    inline const std::vector<std::weak_ptr<Guardian>> getGuardians() const {return ptrGuardians;}
    inline const std::weak_ptr<Activity> getActivity() const {return ptrActivity;}

};

#endif
