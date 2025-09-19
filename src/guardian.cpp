#include <stdexcept>
#include <algorithm>


#include "../include/guardian.hpp"

#include "../include/triumph.hpp"


Guardian::Guardian(const std::string guardianId, std::vector<const std::shared_ptr<TriumphToken>>& ptrTriumphs)
    : id(guardianId)
{
    if (!ptrTriumphs.empty())
    {
        for (auto ptrTriumph : ptrTriumphs)
        {
            if (std::find_if(ptrRelatedTriumphs.begin(), ptrRelatedTriumphs.end(),
                [ptrTriumph](std::vector<std::weak_ptr<TriumphToken>>::iterator itPtrRelatedTriumph){return ptrTriumph == itPtrRelatedTriumph->lock();}) == ptrRelatedTriumphs.end())
            {
                ptrRelatedTriumphs.emplace_back(std::weak_ptr<TriumphToken>(ptrTriumph));
            }
        }
    }
    else throw std::invalid_argument("Received empty Triumph list of pairs.");
    return;
}

const bool Guardian::addRelatedTriumph(const std::shared_ptr<TriumphToken>& ptrTriumph)
{   
    if(std::find_if(ptrRelatedTriumphs.begin(), ptrRelatedTriumphs.end(),
        [ptrTriumph](std::vector<const std::weak_ptr<TriumphToken>>::iterator itPtrRelatedGuardian){return ptrTriumph == itPtrRelatedGuardian->lock();}) == ptrRelatedTriumphs.end())
    {
        ptrRelatedTriumphs.emplace_back(std::weak_ptr<TriumphToken>(ptrTriumph));
        return true;
    }
    return false;
}

const bool Guardian::operator==(const Guardian other) const
{
    if (other.id==id)
    {
        if (other.getTriumphs() != ptrRelatedTriumphs)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
