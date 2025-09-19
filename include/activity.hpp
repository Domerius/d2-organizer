#include <vector>
#include <memory>

#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

class TriumphToken;


enum class ActivityType
{

};


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
 */
class Activity
{

    std::vector<std::weak_ptr<TriumphToken>> triumphs;

public:

    std::vector<std::weak_ptr<TriumphToken>>::iterator begin() {return triumphs.begin();}
    std::vector<std::weak_ptr<TriumphToken>>::iterator end() {return triumphs.end();}
    std::vector<std::weak_ptr<TriumphToken>>::const_iterator begin() const {return triumphs.begin();}
    std::vector<std::weak_ptr<TriumphToken>>::const_iterator end() const {return triumphs.end();}

};

#endif
