#include <vector>

#include "guardian.hpp"
#include "raid.hpp"
#include "dungeon.hpp"


/*
    Notatki:
    Indywidualna lista                      Guardian -> std::vector<Triumph> (sortowanie względem wypadkowego rankingu)
    Ilu osobom brakuje osiągnięcia?         Activity -> Triumph -> Guardian (sortowanie wg liczby chętnych)
    Co trzeba zrobić z danej aktywności?    Activity -> std::vector<Triumph>
    Dodawanie i usuwanie Guardianów
    Dodawanie i usuwanie powiązań Guardian-Triumph
    Upcasting klas Raid i Dungeon do klasy Activity
*/


/**
 * @class Catalogue
 * @brief Collect and manage all the Triumphs, Guardians, and the relationships between them.
 */
class Catalogue
{

    // std::vector<Activity> activityList;
    // std::vector<Guardian<Activity>> guardianList;

public:

    // void printReport();

};
