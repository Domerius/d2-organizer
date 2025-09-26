#include <stdexcept>
#include <algorithm>


#include "../include/guardian.hpp"

#include "../include/triumph.hpp"


Guardian::Guardian(const std::string guardianId, std::vector<const std::pair<std::shared_ptr<Triumph>, EncId>>& ptrRelatedPairs)
    : id(guardianId)
{
    if (!ptrRelatedPairs.empty())
    {
        for (auto ptrRelatedPair : ptrRelatedPairs)
        {
            if (std::find_if(ptrTriumphs.begin(), ptrTriumphs.end(),
                [ptrRelatedPair](std::vector<std::shared_ptr<Triumph>>::iterator itPtrRelatedTriumph){return ptrRelatedPair.first == *itPtrRelatedTriumph;}) == ptrTriumphs.end())
            {
                ptrTriumphs.emplace_back(ptrRelatedPair);
            }
            else throw std::invalid_argument("Found duplicates in Triumphs given for Guardian");
        };
    }
    else throw std::invalid_argument("Received empty Triumph list of pairs.");
    return;
}

const void Guardian::connectTriumph(const std::shared_ptr<Triumph>& ptrRelatedTriumph, const EncId& encId)
{   
    if(std::find_if(ptrTriumphs.begin(), ptrTriumphs.end(),
        [ptrRelatedTriumph](std::vector<const std::shared_ptr<Triumph>>::iterator itPtrRelatedTriumph){return ptrRelatedTriumph == *itPtrRelatedTriumph;}) == ptrTriumphs.end())
    {
        ptrTriumphs.emplace_back(std::make_pair(ptrRelatedTriumph, encId));
        return;
    }
    else throw std::invalid_argument("A given Triumph was a duplicate for Guardian");
    return;
}

const bool Guardian::operator==(const Guardian other) const
{
    if (other.id==id)
    {
        if (other.getTriumphs() != ptrTriumphs)
        {
            throw std::invalid_argument("There are two Guardians with matching unique properties and different Triumph pointers.");
        }
        return true;
    }
    return false;
}
