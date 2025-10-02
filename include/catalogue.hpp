#ifndef CATALOGUE_HPP
#define CATALOGUE_HPP

#include "types.hpp"
#include "guardian.hpp"
#include "triumph.hpp"
#include "activity.hpp"

#include <vector>
#include <memory>


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

    std::vector<std::shared_ptr<Guardian>> guardianList;
    ActivityHelper activityHelper;
    TriumphHelper triumphHelper;
    TypeId lastActivityId;

    // Check if any activity expired
    // Call every Activity and Triumph to check if any pointers expired
    void removeExpiredPointers();
    
    template <typename ActivityType>
    std::weak_ptr<Triumph> findTriumph(const ActivityType& activityType, const TriumphType& triumphType) const;
    std::weak_ptr<Triumph> findTriumph(const std::shared_ptr<Activity>& activity, const TriumphType& triumphType) const;
    
    template <typename ActivityType>
    std::weak_ptr<Activity> findActivity (const ActivityType& activityType) const;
    
    std::shared_ptr<Guardian> findGuardian (const std::string& guardianId) const;

    template <typename ActivityType>
    const Triumph& createTriumph(const ActivityType& activityType, const TriumphType& triumphType);
    const Triumph& createTriumph(const std::shared_ptr<Activity>& activity, const TriumphType& triumphType);

public:

    Catalogue();
    ~Catalogue();

    template <typename ActivityType>
    void addTriumph(const std::string& guardianId, const std::vector<int>& relatedEncounters, const ActivityType& activityType, const TriumphType& triumphType);
    /*
        Calls: Check if Activity exists.
            (if yes) Calls: Check if such Triumph exists.
                (if yes) Return a pointer to existing Triumph.
                (if no) Create a Triumph with a pointer to an existing Activity class.
                    Pass a pointer to each Guardian's add-method (or a contructor if such Guardian doesn't exist) and return it along with encounter information.
            (if no) Create a Triumph with both activityType and triumphType.
                Pass a pointer to each Guardian's add-method (or a contructor if such Guardian doesn't exist) and return it along with encounter information.
    Overloaded by:
    std::weak_ptr<TriumphType> addTriumph(std::vector<std::string> guardianIds, const std::vector<int>& relatedEncounters, ActivityType activityType, TriumphType triumphType)
    std::vector<std::weak_ptr<TriumphType>> addTriumph(std::string guardianId, const std::vector<int>& relatedEncounters, ActivityType activityType, std::vector<TriumphType> triumphTypes)
    etc.
    */
    
    template <typename ActivityType>
    void removeTriumph(const std::string& guardianId, const ActivityType& activityType, const TriumphType& triumphType);
    /*
        Calls Guardian: Check if Triumph in relation with such activity exists.
            (if no) Raise an error - this shouldn't be possible.
        Call Guardian: Remove a pointer to a Triumph that matches description. (if it was the last Guardian standing, the Triumph gets destroyed automatically)
    Overloaded by:
    void removeTriumph(const std::string& guardianId, const std::vector<int>& relatedEncounters, ActivityType activityType, TriumphType triumphType)
    void removeTriumph(std::vector<std::string> guardianId, ActivityType activityType, TriumphType triumphType)
    void removeTriumph(std::string guardianId, ActivityType activityType, std::vector<TriumphType> triumphTypes)
    */

    void addGuardian(const std::string& guardianId);
    void addGuardian(const std::vector<std::string>& guardianIds);
    void removeGuardian(const std::string& guardianId);
    void removeGuardian(const std::vector<std::string>& guardianIds);

    void printReportByGuardians();
    void printReportByGuardians(std::string guardianId);
    void printReportByActivity();
    template <typename ActivityType>
    void printReportByActivity(ActivityType activityType);

};

#endif
