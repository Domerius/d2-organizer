#ifndef TYPES_HPP
#define TYPES_HPP

#include "activity.hpp"

#include <unordered_map>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>


using TypeId = std::uint8_t;

/*
RAID:
    - Name
    - std::string representation
    - Number of encounters
*/
#define FOREACH_RAID(RAID) \
    RAID(LastWish, "Last Wish", 6) \
    RAID(GardenOfSalvation, "Garden of Salvation", 4) \
    RAID(DeepStoneCrypt, "Deep Stone Crypt", 4) \
    RAID(VaultOfGlass, "Vault of Glass", 5) \
    RAID(VowOfTheDisciple, "Vow of the Disciple", 4) \
    RAID(KingsFall, "King's Fall", 6) \
    RAID(RootOfNightmares, "Root of Nightmares", 4) \
    RAID(CrotasEnd, "Crota's End", 4) \
    RAID(SalvationsEdge, "Salvation's Edge", 5) \
    RAID(DessertPerpetual, "Dessert Perpetual", 4)

/*
DUNGEON:
    - Name
    - std::string representation
    - Number of encounters (constant: 3)
*/
#define FOREACH_DUNGEON(DUNGEON) \
    DUNGEON(ShatteredThrone, "Shattered Throne", 3) \
    DUNGEON(PitOfHeresy, "Pit of Heresy", 3) \
    DUNGEON(Prophecy, "Prophecy", 3) \
    DUNGEON(Duality, "Duality", 3) \
    DUNGEON(SpireOfTheWatcher, "Spire of the Watcher", 3) \
    DUNGEON(GhostsOfTheDeep, "Ghosts of the Deep", 3) \
    DUNGEON(WarlordsRuin, "Warlord's Ruin", 3) \
    DUNGEON(VespersHost, "Vesper's Host", 3) \
    DUNGEON(SunderedDoctrine, "Sundered Doctrine", 3)

/*
TRIUMPH:
    - Name
    - std::string representation
*/
#define FOREACH_TRIUMPH(TRIUMPH) \
    TRIUMPH(flawless, "Flawless") \
    TRIUMPH(fullSolar, "Full fireteam - Solar") \
    TRIUMPH(fullVoid, "Full fireteam - Void") \
    TRIUMPH(fullArc, "Full fireteam - Arc") \
    TRIUMPH(fullStatis, "Full fireteam - Stasis") \
    TRIUMPH(fullStrand, "Full fireteam - Strand") \
    TRIUMPH(fullPrismatic, "Full fireteam - Prismatic") \
    TRIUMPH(encounterTriumph, "Encounter Triumph") \
    TRIUMPH(masterChallange, "Master Challange")


static const TypeId RAID_TYPE_START_ID = 100;
static const TypeId DUNGEON_TYPE_START_ID = 150;

/**
 * @struct ActivityHelper
 * @brief Stores Activity's enumerated types and creates an interface that manages them.
 * 
 * @details This struct is a helper object for the Activity class.
 * Its enumerated types are used by a Catalogue and a Triumph classes to create a new Activity.
 * Depending on which type of enumeration is given, a different constructor the Activity will use.
 * The struct also holds weak pointers to each unique A declared (only one such can exist).
 */
struct ActivityHelper
{

    enum class RaidType : TypeId
    {   
        START = RAID_TYPE_START_ID,
        #define GENERATE_ENUM(ENUM, NAME, NR) ENUM,
        FOREACH_RAID(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };

    enum class DungeonType : TypeId
    {
        START = DUNGEON_TYPE_START_ID,
        #define GENERATE_ENUM(ENUM, NAME, NR) ENUM,
        FOREACH_DUNGEON(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };

    inline const std::vector<RaidType> getRaidTypes() const
        {return raidEnums;}
    inline const std::vector<DungeonType> getDungeonTypes() const
        {return dungeonEnums;}

    inline const std::weak_ptr<Activity> getActivity(const RaidType& raidType) const
        {return activityMap.at(static_cast<TypeId>(raidType));}
    inline const std::weak_ptr<Activity> getActivity(const DungeonType& dungeonType) const
        {return activityMap.at(static_cast<TypeId>(dungeonType));}

    inline void setActivity(const RaidType& raidType, std::weak_ptr<Activity> ptrRaid)
        {activityMap[static_cast<TypeId>(raidType)] = ptrRaid;}
    inline void setActivity(const DungeonType& dungeonType, std::weak_ptr<Activity> ptrDungeon)
        {activityMap[static_cast<TypeId>(dungeonType)] = ptrDungeon;}

    static const std::string& toString(const RaidType& raidType)
    {
        switch (raidType)
        {
        #define GENERATE_CASES(ENUM, NAME, NR) case RaidType::ENUM: return std::string(NAME);
        FOREACH_RAID(GENERATE_CASES)
        #undef GENERATE_CASES
        default: throw std::invalid_argument("Given type doesn't match any of RaidType enumeration");
        }
    };

    static const std::string& toString(const DungeonType& dungeonType)
    {
        switch (dungeonType)
        {
        #define GENERATE_CASES(ENUM, NAME, NR) case DungeonType::ENUM: return std::string(NAME);
        FOREACH_DUNGEON(GENERATE_CASES)
        #undef GENERATE_CASES
        default: throw std::invalid_argument("Given type doesn't match any of DungeonType enumeration");
        }
    };

    static const std::string& toString(const TypeId& typeId)
    {
        if (typeId > RAID_TYPE_START_ID && typeId < DUNGEON_TYPE_START_ID) return toString(static_cast<RaidType>(typeId));
        else if (typeId > DUNGEON_TYPE_START_ID) return toString(static_cast<RaidType>(typeId));
        else throw std::invalid_argument("Given encounter ID has invalid value");
    }

    const int& getNrOfEncounters(const RaidType& raidType)
    {
        switch (raidType)
        {
        #define GENERATE_CASES(ENUM, NAME, NR) case RaidType::ENUM: return static_cast<int>(NR);
        FOREACH_RAID(GENERATE_CASES)
        #undef GENERATE_CASES
        default: throw std::invalid_argument("Given type doesn't match any of RaidType enumeration");
        }
    };

    const int& getNrOfEncounters(const DungeonType& dungeonType)
    {
        switch (dungeonType)
        {
        #define GENERATE_CASES(ENUM, NAME, NR) case DungeonType::ENUM: return static_cast<int>(NR);
        FOREACH_DUNGEON(GENERATE_CASES)
        #undef GENERATE_CASES
        default: throw std::invalid_argument("Given type doesn't match any of DungeonType enumeration");
        }
    };

private:

    std::unordered_map<TypeId, std::weak_ptr<Activity>> activityMap;

    const std::vector<RaidType> raidEnums
    {
        #define GENERATE_ARRAY(ENUM, NAME, NR) RaidType::ENUM,
        FOREACH_RAID(GENERATE_ARRAY)
        #undef GENERATE_ARRAY
    };

    const std::vector<DungeonType> dungeonEnums
    {
        #define GENERATE_ARRAY(ENUM, NAME, NR) DungeonType::ENUM,
        FOREACH_DUNGEON(GENERATE_ARRAY)
        #undef GENERATE_ARRAY
    };

};

using RaidType = ActivityHelper::RaidType;
using DungeonType = ActivityHelper::DungeonType;

std::ostream& operator<<(std::ostream& os, const RaidType& raidType)
    {return os << ActivityHelper::toString(raidType);}
std::ostream& operator<<(std::ostream& os, const DungeonType& dungeonType)
    {return os << ActivityHelper::toString(dungeonType);}

#undef FOREACH_RAID
#undef FOREACH_DUNGEON


static const TypeId TRIUMPH_TYPE_START_ID = 200;
using EncId = std::uint8_t;

/**
 * @struct TriumphHelper
 * @brief Stores Triumph's enumerated type and creates an interface that manages them.
 * 
 * @details This struct is a helper object for Catalogue and Triumph class.
 * Its enumerated type is used by a Catalogue class to create a new Triumph.
 * the struct stores helper-functions for encid which is held by guardians to highlight encounters targeted to complete in relation with an associated triumph.
 */
struct TriumphHelper
{
    
    enum class TriumphType : TypeId
    {
        #define GENERATE_ENUM(ENUM, NAME) ENUM,
        FOREACH_TRIUMPH(GENERATE_ENUM)
        #undef GENERATE_ENUM
    };

    inline const std::vector<TriumphType>& getTriumphTypes() const
        {return triumphEnums;}

    static const std::string& toString(const TriumphType& triumphType)
    {
        switch (triumphType)
        {
        #define GENERATE_CASES(ENUM, NAME) case TriumphType::ENUM: return std::string(NAME);
        FOREACH_TRIUMPH(GENERATE_CASES)
        #undef GENERATE_CASES
        default: throw std::invalid_argument("Given type doesn't match any of TriumphType enumeration");
        }
    }; 

    static const std::string& toString(const TypeId& typeId)
        {return toString(static_cast<TriumphType>(typeId));}

    const std::vector<int>& enc2Vec(EncId encId)
    {
        EncId mask = 0x00000001;
        std::vector<int> outVec;
        for (int counter = 1; counter < 8; ++counter)
        {
            if (encId & mask) outVec.emplace_back(counter);
            mask = mask << 1;
        }
        return outVec;
    }

    const EncId& vec2Enc(std::vector<int> vec)
    {
        EncId outEnc = 0x00000000;
        for (auto offset : vec)
        {
            outEnc += 0x00000001 << (offset - 1);
        }
        return outEnc;
    }
    
private:

    const std::vector<TriumphType> triumphEnums
    {
        #define GENERATE_MAP(ENUM, NAME) TriumphType::ENUM,
        FOREACH_TRIUMPH(GENERATE_MAP)
        #undef GENERATE_MAP
    };

};

using TriumphType = TriumphHelper::TriumphType;

std::ostream& operator<<(std::ostream& os, const TriumphType& triumphType)
    {return os << TriumphHelper::toString(triumphType);}

#undef FOREACH_TRIUMPH
#endif
