#include <unordered_map>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>

#ifndef TYPES_HPP
#define TYPES_HPP


class Activity;
using TypeId = std::uint8_t;


/*
RAID:
    - Name
    - Number of encounters
*/
#define FOREACH_RAID(RAID) \
    RAID(LastWish) \
    RAID(GardenOfSalvation) \
    RAID(DeepStoneCrypt) \
    RAID(VaultOfGlass) \
    RAID(VowOfTheDisciple) \
    RAID(KingsFall) \
    RAID(RootOfNightmares) \
    RAID(CrotasEnd) \
    RAID(SalvationsEdge) \
    RAID(DessertPerpetual)

/*
DUNGEON:
    - Name
    - Number of encounters
*/
#define FOREACH_DUNGEON(DUNGEON) \
    DUNGEON(ShatteredThrone) \
    DUNGEON(PitOfHeresy) \
    DUNGEON(Prophecy) \
    DUNGEON(Duality) \
    DUNGEON(SpireOfTheWatcher) \
    DUNGEON(GhostsOfTheDeep) \
    DUNGEON(WarlordsRuin) \
    DUNGEON(VespersHost) \
    DUNGEON(SunderedDoctrine)

/*
TRIUMPH:
    - Name
    - Min. number of encounters required
*/
#define FOREACH_TRIUMPH(TRIUMPH) \
    TRIUMPH(flawless) \
    TRIUMPH(fullSolar) \
    TRIUMPH(fullVoid) \
    TRIUMPH(fullArc) \
    TRIUMPH(fullStatis) \
    TRIUMPH(fullStrand) \
    TRIUMPH(fullPrismatic) \
    TRIUMPH(triumphEnc1) \
    TRIUMPH(triumphEnc2) \
    TRIUMPH(triumphEnc3) \
    TRIUMPH(triumphEnc4) \
    TRIUMPH(triumphEnc5) \
    TRIUMPH(triumphEnc6) \
    TRIUMPH(masterChallangeEnc1) \
    TRIUMPH(masterChallangeEnc2) \
    TRIUMPH(masterChallangeEnc3) \
    TRIUMPH(masterChallangeEnc4) \
    TRIUMPH(masterChallangeEnc5) \
    TRIUMPH(masterChallangeEnc6)


/**
 * @struct ActivityTypeWrapper
 * @brief Stores Activity's enumerated types and creates an interface that manages them.
 * 
 * @details This struct is a helper object for the Activity class.
 * Its enumerated types are used by a Catalogue and a Triumph classes to create a new Activity.
 * Depending on which type of enumeration is given, a different constructor the Activity will use.
 * The struct also holds weak pointers to each unique A declared (only one such can exist).
 */
struct ActivityTypeWrapper
{

    enum class RaidType : TypeId
    {   
        START = 0,
        #define GENERATE_ENUM(ENUM) ENUM,
        FOREACH_RAID(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };
    // using enum RaidType;

    static constexpr std::array raidEnums
    {
        #define GENERATE_ARRAY(name) RaidType::name,
        FOREACH_RAID(GENERATE_ARRAY)
        #undef GENERATE_ARRAY
    };

    enum class DungeonType : TypeId
    {
        START = static_cast<int>(RaidType::START) + raidEnums.size() + 1,
        #define GENERATE_ENUM(ENUM) ENUM,
        FOREACH_DUNGEON(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };
    // using enum DungeonType;
    
    static constexpr std::array dungeonEnums
    {
        #define GENERATE_ARRAY(name) DungeonType::name,
        FOREACH_DUNGEON(GENERATE_ARRAY)
        #undef GENERATE_ARRAY
    };

    static std::string toString(const RaidType& raidType);
    static std::string toString(const DungeonType& dungeonType);

    inline static const std::weak_ptr<Activity> getActivity(const RaidType& raidType)
        {return activityMap[static_cast<std::uint8_t>(raidType)];}
    inline static const std::weak_ptr<Activity> getActivity(const DungeonType& dungeonType)
        {return activityMap[static_cast<std::uint8_t>(dungeonType)];}

    inline static void setActivity(const RaidType& raidType, std::weak_ptr<Activity> ptrRaid)
        {activityMap[static_cast<std::uint8_t>(raidType)] = ptrRaid;}
    inline static void setActivity(const DungeonType& dungeonType, std::weak_ptr<Activity> ptrDungeon)
        {activityMap[static_cast<std::uint8_t>(dungeonType)] = ptrDungeon;}

private:

    static std::unordered_map<TypeId, std::weak_ptr<Activity>> activityMap;
    // static std::unordered_map<TypeId, int> propertiesMap;

};

using RaidType = ActivityTypeWrapper::RaidType;
using DungeonType = ActivityTypeWrapper::DungeonType;

std::ostream& operator<<(std::ostream& os, const RaidType& raidType);
std::ostream& operator<<(std::ostream& os, const DungeonType& dungeonType);

#undef FOREACH_RAID
#undef FOREACH_DUNGEON


/**
 * @struct TriumphTypeWrapper
 * @brief Stores Triumph's enumerated type and creates an interface that manage them.
 * 
 * @details This struct is a helper object for the Triumph class.
 * Its enumerated type is used by a Catalogue class to create a new Triumph.
 * The struct stores requirements for an ActivityType to be assigned to given Triumph.
 */
struct TriumphTypeWrapper
{
    enum class TriumphType : TypeId
    {
        #define GENERATE_ENUM(ENUM) ENUM,
        FOREACH_TRIUMPH(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };

    static std::string toString(const TriumphType& triumphType);

    // static void incrementOccurences(const TriumphType& triumphType);
    // static void decrementOccurences(const TriumphType& triumphType);
    // static const int getOccurences(const TriumphType& triumphType);
    // static const int getOccurences();
    
private:

    // static std::unordered_map<TypeId, int> occurenceCounter;
    // static std::unordered_map<TypeId, int> requirementsMap;

};

using TriumphType = TriumphTypeWrapper::TriumphType;

std::ostream& operator<<(std::ostream& os, const TriumphType& triumphType);

#undef FOREACH_TRIUMPH
#endif
