#include <algorithm>
#include <vector>
#include <utility>
#include <stdexcept>


#include "../include/triumph.hpp"

#include "../include/guardian.hpp"


TriumphToken::TriumphToken(const TriumphType triumph, const Activity* activity, std::vector<Guardian *const> guardians)
    : description(triumph), ptrSuperior(activity)
{
    if (!guardians.empty())
    {
        auto new_end = std::unique(guardians.begin(), guardians.end());
        guardians.erase(new_end, guardians.end());
        ptrGuardians = std::move(guardians);
    }
    else throw std::invalid_argument("Received empty Guardians list.");
}

TriumphToken::~TriumphToken()
{
    if (!ptrGuardians.empty())
    {
        for (std::vector<Guardian* const>::iterator itPtrGuardian = ptrGuardians.begin(); itPtrGuardian != ptrGuardians.end(); )
        {
            std::pair<const Activity*, const TriumphToken*> relatedPair = std::make_pair(ptrSuperior, this);
            (*itPtrGuardian)->removeRelatedTriumph(relatedPair);
        }
    }
    return;
}

const bool TriumphToken::addGuardian(Guardian *const guardian)
{
    
    if (std::find(ptrGuardians.begin(), ptrGuardians.end(), guardian) == ptrGuardians.end())
    {
        ptrGuardians.emplace_back(guardian);
        return true;
    }
    return false;
}

const bool TriumphToken::addGuardian(std::vector<Guardian *const> &guardians)
{
    for (std::vector<Guardian *const>::iterator itPtrGuardian = guardians.begin(); itPtrGuardian != guardians.end(); )
    {
        if (std::find(ptrGuardians.begin(), ptrGuardians.end(), itPtrGuardian) == ptrGuardians.end())
        {
            ptrGuardians.insert(ptrGuardians.end(), *itPtrGuardian);
            guardians.erase(itPtrGuardian);
        } 
        else ++itPtrGuardian;
    }

    if (guardians.empty())
    {
        return true;
    }
    return false;
}

const bool TriumphToken::removeGuardian(Guardian *const guardian)
{   
    std::vector<Guardian *const>::iterator itPtrGuardian = std::find(ptrGuardians.begin(), ptrGuardians.end(), guardian);
    if (itPtrGuardian != ptrGuardians.end())
    {
        ptrGuardians.erase(itPtrGuardian);
        return true;
    }
    return false;
}

const bool TriumphToken::removeGuardian(std::vector<Guardian *const>& guardians)
{
    for (std::vector<Guardian *const>::iterator itPtrGuardian = guardians.begin(); itPtrGuardian != guardians.end(); )
    {
        if (std::find(ptrGuardians.begin(), ptrGuardians.end(), itPtrGuardian) != ptrGuardians.end())
        {
            ptrGuardians.erase(itPtrGuardian);
            guardians.erase(itPtrGuardian);
        } 
        else ++itPtrGuardian;
    }

    if (guardians.empty())
    {
        return true;
    }
    return false;
}

const bool TriumphToken::removeGuardian(const std::string& guardiansName)
{   
    std::vector<Guardian *const>::iterator itPtrGuardian = std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
        [guardiansName](std::vector<Guardian*>::iterator itPtrGuardian){return (*itPtrGuardian)->getId() == guardiansName;});
    if (itPtrGuardian != ptrGuardians.end())
    {
        ptrGuardians.erase(itPtrGuardian);
        return true;
    }
    return false;
}

const bool TriumphToken::removeGuardian(std::vector<const std::string>& guardiansNames)
{
    for (std::vector<const std::string>::iterator itGuardiansName = guardiansNames.begin(); itGuardiansName != guardiansNames.end(); )
    {   
        std::vector<Guardian *const>::iterator itPtrGuardian = std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
            [itGuardiansName](std::vector<Guardian*>::iterator itPtrGuardian){return (*itPtrGuardian)->getId() == *itGuardiansName;});
        if (itPtrGuardian != ptrGuardians.end())
        {
            ptrGuardians.erase(itPtrGuardian);
            guardiansNames.erase(itGuardiansName);
        } 
        else ++itGuardiansName;
    }

    if (guardiansNames.empty())
    {
        return true;
    }
    return false;
}

const bool TriumphToken::operator==(TriumphToken& other)
{
    if (other.description==description && other.ptrSuperior==ptrSuperior)
    {
        if (other.ptrGuardians!=ptrGuardians)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
