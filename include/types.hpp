#include <map>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>

#ifndef TYPES_HPP
#define TYPES_HPP


class Activity;
using TypeId = std::uint8_t;


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

    static std::map<TypeId, std::weak_ptr<Activity>> activityMap;

    static std::string toString(const RaidType& raidType);
    static std::string toString(const DungeonType& dungeonType);

};

std::ostream& operator<<(std::ostream& os, const RaidType& raidType);
std::ostream& operator<<(std::ostream& os, const DungeonType& dungeonType);

using RaidType = ActivityTypeWrapper::RaidType;
using DungeonType = ActivityTypeWrapper::DungeonType;

#undef FOREACH_RAID
#undef FOREACH_DUNGEON
#endif
