#include <string>
#include <vector>
#include <cstdint>

#ifndef TRIUMPH_HPP
#define TRIUMPH_HPP

// #include "activity.hpp"
class Guardian;
class Activity;


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
    Kompozycja względem klas pochodnych klasy Activity
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
    const Activity* ptrSuperior;
    std::vector<Guardian *const> ptrGuardians;

public:

    // Zainicjuj obiekt z poziomu obiektu nadrzędnego
    inline TriumphToken(const TriumphType triumph, const Activity* activity, Guardian *const guardian)
        : description(triumph), ptrSuperior(activity) {ptrGuardians.emplace_back(guardian);}
    TriumphToken(const TriumphType triumph, const Activity* activity, std::vector<Guardian *const> guardians);

    // Usuń wskaźnik do tego triumfu zewsząd przed unicestwieniem obiektu
    ~TriumphToken();

    // Jeśli nie jest duplikatem, dodaj guardiana do kontenera
    const bool addGuardian(Guardian *const guardian);
    const bool addGuardian(std::vector<Guardian *const> &guardians);

    // Znajdź i usuń zarówno wzmiankę o sobię u tego Guardiana jak i jego ze swojej listy
    const bool removeGuardian(Guardian *const guardian);
    const bool removeGuardian(std::vector<Guardian *const>& guardians);
    const bool removeGuardian(const std::string& guardiansName);
    const bool removeGuardian(std::vector<const std::string>& guardiansNames);

    // Sprawdź czy Triumf jest pusty/niepotrzebny
    inline const bool empty() {return ptrGuardians.empty();}

    // Przeciążony operator porównania
    const bool operator==(TriumphToken& other);

    typename std::vector<Guardian *const>::iterator begin() {return ptrGuardians.begin();}
    typename std::vector<Guardian *const>::iterator end() {return ptrGuardians.end();}
    typename std::vector<Guardian *const>::const_iterator begin() const {return ptrGuardians.begin();}
    typename std::vector<Guardian *const>::const_iterator end() const {return ptrGuardians.end();}

    // Wskaż wszystkich powiązanych Guardianów
    inline const std::vector<Guardian *const> getGuardians() {return ptrGuardians;}

    // Wskaż konkretną aktywność, na potrzebę której powstała instancja tego obiektu
    inline const Activity* getActivity() {return ptrSuperior;}

};

#endif
