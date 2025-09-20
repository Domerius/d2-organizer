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
    Metoda dodająca Triumph jest szablonem, zależnym od ActivityType - od tego też zależy czy Raid czy Dungeon
    Katalog tworzy Guardian. Za pomocą Guardian tworzę Triumph (przy inicjalizacji tworzę lub przypinam Rajd lub Dungeon)
    Każdy Raid lub Dungeon podpięte są przez upcasting do Katalogu - nie mogą istnieć puste, stąd jedyna opcja to tworzyć przez Triumph.
*/


/**
 * @class Catalogue
 * @brief Collect and manage all the activities, Guardians, and all the Triumphs connecting them.
 * 
 * @details This class functions as an interface for the application.
 * It stores pointers to objects of classes derived from the Activity class (to list Triumphs related to the activity) and to objects of the Guardian class (to count the demand for a given Triumph).
 * The class allows to add new Triumphs with their associated activities and Guardians using enumeration class elements, associated with the given activity and achievement description.
 * The key functionalities of the class are managing data archiving between program runs and displaying a report suggesting which Triumph to execute next.
 */
class Catalogue
{

    std::vector<std::weak_ptr<Activity>> activityList;
    std::vector<std::shared_ptr<Guardian>> guardianList;

public:

    
    // void printReport();

};

#endif
