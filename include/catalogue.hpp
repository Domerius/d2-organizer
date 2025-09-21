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
    Dodawanie i usuwanie Triumphów poprzez zarówno Guardian i Activity
    Sprawdzanie czy Activity i Guardian istnieje (bezpośrednio) oraz czy Triumph istnieje (poprzez Activity)
    Upcasting klas Raid i Dungeon do klasy Activity
    guardianList - posiadanie przez smart pointer, aby umożliwić wskazywanie na obiekty Guardian przez Triumph
    Metoda dodająca Triumph jest szablonem, zależnym od ActivityType - od tego też zależy czy Raid czy Dungeon
    Katalog tworzy Guardian. Za pomocą Guardian tworzę Triumph (przy inicjalizacji tworzę lub przypinam Rajd lub Dungeon)
    Każdy Raid lub Dungeon podpięte są przez upcasting do Katalogu - nie mogą istnieć puste, stąd jedyna opcja to tworzyć przez Triumph.
    Stworzyć klasę Archivizer?
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

    // Check if any activity expired
    // Call every Activity and Triumph to check if any pointers expired
    
    // Check if a Triumph exists by an ActivityType and a TriumphType
    // Check if an Activity exists by an ActivityType
    // Check if a Guardian exists by a GuardianID

    // Pass a request of adding (creating or just connecting) a Triumph to the Guardian

public:

    // Constructor reads history files and reconstructs the database
    // Destructor cleans the classes up and updates history files

    /*
    template <typename ActivityType>
    std::weak_ptr<TriumphType> addTriumph(std::string guardianId, ActivityType activityType, TriumphType triumphType)
        Calls: Check if Guardian exists.
            (if not) Calls: Create such one.
        Calls: Check if Activity exists.
            (if yes) Calls: Check if such Triumph exists.
                (if yes) Return a pointer to existing Triumph.
                (if no) A pointer to the Activity class is passed to the Guardian and the Triumph is created. Return a pointer to created Triumph.
            (if no) Pass both activityType and triumphType to the Guardian, create a Triumph (it will create a new Activity). Return a pointer to created Triumph.
    Overloaded by:
    std::weak_ptr<TriumphType> addTriumph(Guardian guardian, ActivityType activityType, TriumphType triumphType) (?)
    std::weak_ptr<TriumphType> addTriumph(std::vector<std::string> guardianIds, ActivityType activityType, TriumphType triumphType)
    std::vector<std::weak_ptr<TriumphType>> addTriumph(std::string guardianId, ActivityType activityType, std::vector<TriumphType> triumphTypes)
    etc.
    */
    
    /*
    template <typename ActivityType>
    void removeTriumph(std::string guardianId, ActivityType activityType, TriumphType triumphType)
        Calls Guardian: Check if Triumph in relation with such activity exists.
            (if no) Raise an error - this shouldn't be possible.
        Call Guardian: Remove a pointer to a Triumph that matches description. (if it was the last Guardian standing, the Triumph gets destroyed automatically)
    Overloaded by:
    void removeTriumph(Guardian guardian, ActivityType activityType, TriumphType triumphType) (?)
    void removeTriumph(std::vector<std::string> guardianId, ActivityType activityType, TriumphType triumphType)
    void removeTriumph(std::string guardianId, ActivityType activityType, std::vector<TriumphType> triumphTypes)
    */

    // addGuardian(std::string guardianId)
    // addGuardian(std::vector<std::string> guardianIds)
    // removeGuardian(std::string guardianId)
    // removeGuardian(std::vector<std::string> guardianIds)

    // void printReportByGuardians();
    // void printReportByGuardians(std::string guardianId);
    // void printReportByActivity();
    // template <typename ActivityType>
    // void printReportByActivity(ActivityType activityType);

};

#endif
