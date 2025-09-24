#include <vector>
#include <memory>

#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include "types.hpp"

class Guardian;
class Triumph;


/*
    Notatki:
    Przeciążony operator== sprawdza czy nazwa się zgadza i wyrzuca błąd, jeśli jednocześnie nie zgadza się lista Triumfów
    Obiekt tworzony jest przez dowolny Triumph na podstawie wartości typu ActivityType (do zmiany?)
    Konstruktor pobiera opis z dedykowanemu dokumentu na podstawie ActivityType
    Obiekt przestaje istnieć, gdy żaden Triumf się do niego nie odnosi
*/


/**
 * @class Activity
 * @brief Stores all Triumphs related to this activity.
 * 
 * @details This class is the base for objects stored by the Catalogue class and defines basic methods and storage functionality.
 * Its purpose is to enable unambiguous recognition of Triumphs by storing weak pointers for each of them.
 * An object of this class depends on the Triumphs that point to it - it is created with the first reference to it and is destroyed when all references are eliminated.
 * Allows you to create a Triumph and bind at least one Guardian to it at a time.
 */
class Activity
{

    std::vector<std::weak_ptr<Triumph>> triumphs;

    // const std::shared_ptr<Triumph> createTriumph(const std::shared_ptr<Guardian> ptrGuardian, const TriumphType& triumph);
    // const std::shared_ptr<Triumph> createTriumph(const std::vector<std::shared_ptr<Guardian>> ptrGuardians, const TriumphType& triumph);

    std::weak_ptr<Triumph> findTriumph (const TriumphType& triumphType) const;

    void removeExpiredPointers();

public:

    Activity(const Activity&) = delete;
    template <typename ActivityType>
    Activity(const ActivityType& activity);

    const void connectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph);
    const void connectTriumph(std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumph);

    std::vector<std::weak_ptr<Triumph>>::iterator begin() {return triumphs.begin();}
    std::vector<std::weak_ptr<Triumph>>::iterator end() {return triumphs.end();}
    std::vector<std::weak_ptr<Triumph>>::const_iterator begin() const {return triumphs.begin();}
    std::vector<std::weak_ptr<Triumph>>::const_iterator end() const {return triumphs.end();}

    Activity& operator=(const Activity&) = delete;

};

#endif
