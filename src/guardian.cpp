#include <stdexcept>
#include <algorithm>


#include "../include/guardian.hpp"

#include "../include/triumph.hpp"


Guardian::Guardian(const std::string guardianId, std::vector<const std::shared_ptr<Triumph>>& ptrRelatedTriumphs)
    : id(guardianId)
{
    if (!ptrRelatedTriumphs.empty())
    {
        for (auto ptrRelatedTriumph : ptrRelatedTriumphs)
        {
            if (std::find_if(ptrTriumphs.begin(), ptrTriumphs.end(),
                [ptrRelatedTriumph](std::vector<std::weak_ptr<Triumph>>::iterator itPtrRelatedTriumph){return ptrRelatedTriumph == itPtrRelatedTriumph->lock();}) == ptrTriumphs.end())
            {
                ptrTriumphs.emplace_back(std::weak_ptr<Triumph>(ptrRelatedTriumph));
            }
        }
    }
    else throw std::invalid_argument("Received empty Triumph list of pairs.");
    return;
}

const bool Guardian::connectTriumph(const std::shared_ptr<Guardian>& guardian, const std::shared_ptr<Triumph>& ptrRelatedTriumph)
{   
    if(std::find_if(ptrTriumphs.begin(), ptrTriumphs.end(),
        [ptrRelatedTriumph](std::vector<const std::weak_ptr<Triumph>>::iterator itPtrRelatedGuardian){return ptrRelatedTriumph == itPtrRelatedGuardian->lock();}) == ptrTriumphs.end())
    {
        ptrRelatedTriumph->addGuardian(guardian);
        ptrTriumphs.emplace_back(std::weak_ptr<Triumph>(ptrRelatedTriumph));
        return true;
    }
    return false;
}

const bool Guardian::operator==(const Guardian other) const
{
    if (other.id==id)
    {
        if (other.getTriumphs() != ptrTriumphs)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
