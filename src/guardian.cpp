#include <stdexcept>
#include <algorithm>


#include "../include/guardian.hpp"

#include "../include/triumph.hpp"


Guardian::Guardian(const std::string guardianId, std::vector<const std::pair<Activity*, TriumphToken*>> ptrRelatedPairs)
    : id(guardianId)
{
    if (!ptrRelatedPairs.empty())
    {
        auto new_end = std::unique(ptrRelatedPairs.begin(), ptrRelatedPairs.end());
        ptrRelatedPairs.erase(new_end, ptrRelatedPairs.end());
        ptrRelatedTriumphs = std::move(ptrRelatedPairs);
    }
    else throw std::invalid_argument("Received empty Raid-Triumph list of pairs.");
    return;
}

const bool Guardian::addRelatedTriumph(const std::pair<Activity*, TriumphToken*>& relatedTriumph)
{
    if (std::find(ptrRelatedTriumphs.begin(), ptrRelatedTriumphs.end(), relatedTriumph) == ptrRelatedTriumphs.end())
    {
        ptrRelatedTriumphs.emplace_back(relatedTriumph);
        return true;
    }
    return false;
}

const bool Guardian::operator==(const Guardian other)
{
    if (other.id==id)
    {
        if (other.ptrRelatedTriumphs!=ptrRelatedTriumphs)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
