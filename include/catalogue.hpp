#include <vector>
#include <memory>

#ifndef CATALOGUE_HPP
#define CATALOGUE_HPP

#include "guardian.hpp"
#include "raid.hpp"
#include "dungeon.hpp"


/*
    Notatki:
    Indywidualna lista                                      Guardian -> std::vector<std::pair<Activity, Triumph>>
    Co trzeba zrobić z danej aktywności i dla ilu osób?     Activity -> std::vector<std::pair<Triumph, std::vector<Guardian>>
    Dodawanie i usuwanie Guardianów
    Dodawanie i usuwanie powiązań Guardian-Triumph
    Upcasting klas Raid i Dungeon do klasy Activity
    guardianList - posiadanie przez smart pointer, aby umożliwić wskazywanie na obiekty Guardian przez Triumph

    Katalog tworzy Guardian. Za pomocą Guardian tworzę Triumph (przy inicjalizacji tworzę lub przypinam Rajd lub Dungeon)
    Każdy Raid lub Dungeon podpięte są przez upcasting do Katalogu - nie mogą istnieć puste, stąd jedyna opcja to tworzyć przez Triumph.
*/


/**
 * @class Catalogue
 * @brief Collect and manage all the Triumphs, Guardians, and the relationships between them.
 */
class Catalogue
{

    std::vector<std::weak_ptr<Activity>> activityList;
    std::vector<std::shared_ptr<Guardian>> guardianList;

public:

    // void printReport();

};

#endif
