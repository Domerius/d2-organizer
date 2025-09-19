#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#ifndef TRIUMPH_HPP
#define TRIUMPH_HPP

class Guardian;
class Activity;
enum class ActivityType;


enum class TriumphType
{
    flawless            = 0,
    fullSolar           = 0,
    fullVoid            = 0,
    fullArc             = 0,
    fullStatis          = 0,
    fullStrand          = 0,
    fullPrismatic       = 0,
    triumphEnc1         = 1,
    triumphEnc2         = 2,
    triumphEnc3         = 3,
    triumphEnc4         = 4,
    triumphEnc5         = 5,
    triumphEnc6         = 6,
    masterChallangeEnc1 = 1,
    masterChallangeEnc2 = 2,
    masterChallangeEnc3 = 3,
    masterChallangeEnc4 = 4,
    masterChallangeEnc5 = 5,
    masterChallangeEnc6 = 6
};


/*
    Notatki:
    Wskazuje na aktywność, dla którego instancja powstała
    Wskazuje na wszystkich guardianów, którym zależy na realizacji
    Zawiera pojedynczy triumf
    Obiekt nie może istnieć jeśli żaden Guardian się do niego nie odnosi (usuwa go jego superior ActivityType)
*/


/**
 * @class TriumphToken
 * @brief Keep a description of the achievement and indicate the associated Guardians and the Activity it is part of.
 */
class TriumphToken
{

    const TriumphType description;
    const std::shared_ptr<Activity> ptrActivity;
    std::vector<std::weak_ptr<Guardian>> ptrGuardians;

public:

    // Zainicjuj obiekt z poziomu obiektu nadrzędnego
    inline TriumphToken::TriumphToken(const TriumphType&& triumph, const std::shared_ptr<Activity>& activity, const std::shared_ptr<Guardian>& guardian)
        : description(triumph), ptrActivity(std::weak_ptr<Activity>(activity)) {ptrGuardians.emplace_back(std::weak_ptr<Guardian>(guardian));}
    TriumphToken(const TriumphType&& triumph, const std::shared_ptr<Activity>& activity, std::vector<const std::shared_ptr<Guardian>>& guardians);
    TriumphToken(const TriumphType&& triumph, const ActivityType&& activity, const std::shared_ptr<Guardian>& guardian);
    TriumphToken(const TriumphType&& triumph, const ActivityType&& activity, std::vector<const std::shared_ptr<Guardian>>& guardians);

    // Jeśli nie jest duplikatem, dodaj guardiana do kontenera
    const bool addGuardian(const std::shared_ptr<Guardian>& guardian);
    const bool addGuardian(std::vector<const std::shared_ptr<Guardian>>& guardians);

    // Znajdź i usuń zarówno wzmiankę o sobię u tego Guardiana jak i jego ze swojej listy
    const bool removeGuardian(std::weak_ptr<Guardian>& guardian);
    const bool removeGuardian(std::vector<std::weak_ptr<Guardian>>& guardians);
    const bool removeGuardian(const std::string& guardiansName);
    const bool removeGuardian(std::vector<const std::string>& guardiansNames);

    // Przeciążony operator porównania
    const bool operator==(TriumphToken& other) const;

    std::vector<std::weak_ptr<Guardian>>::iterator begin() {return ptrGuardians.begin();}
    std::vector<std::weak_ptr<Guardian>>::iterator end() {return ptrGuardians.end();}
    std::vector<std::weak_ptr<Guardian>>::const_iterator begin() const {return ptrGuardians.begin();}
    std::vector<std::weak_ptr<Guardian>>::const_iterator end() const {return ptrGuardians.end();}

    // Sprawdź czy Triumf jest pusty/niepotrzebny
    inline const bool empty() const {return ptrGuardians.empty();}

    inline const TriumphType getDescription() const {return description;}
    inline const std::vector<std::weak_ptr<Guardian>> getGuardians() const {return ptrGuardians;}
    inline const std::shared_ptr<Activity> getActivity() const {return ptrActivity;}

};

#endif
