#include <algorithm>
#include <vector>
#include <utility>
#include <stdexcept>


#include "../include/triumph.hpp"

#include "../include/guardian.hpp"
#include "../include/activity.hpp"


TriumphToken::TriumphToken(const TriumphType&& triumph, const std::shared_ptr<Activity>& activity, std::vector<const std::shared_ptr<Guardian>>& guardians)
    : description(triumph), ptrActivity(std::weak_ptr<Activity>(activity)) {addGuardian(guardians);}

const bool TriumphToken::addGuardian(const std::shared_ptr<Guardian>& guardian)
{
    if(std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
        [guardian](std::vector<const std::weak_ptr<TriumphToken>>::iterator itPtrGuardian){return guardian == itPtrGuardian->lock();}) == ptrGuardians.end())
    {
        ptrGuardians.emplace_back(std::weak_ptr<Guardian>(guardian));
        return true;
    }
    return false;
}

const bool TriumphToken::addGuardian(std::vector<const std::shared_ptr<Guardian>>& guardians)
{
    if (!guardians.empty())
    {
        for (auto guardian : guardians)
        {
            if (std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
                [guardian](std::vector<std::weak_ptr<TriumphToken>>::iterator itPtrGuardian){return guardian == itPtrGuardian->lock();}) == ptrGuardians.end())
            {
                ptrGuardians.emplace_back(std::weak_ptr(guardian));
            }
        }
    }
    else throw std::invalid_argument("Received empty Guardians list.");
    return true;
}

const bool TriumphToken::removeGuardian(std::weak_ptr<Guardian>& guardian)
{   
    std::vector<std::weak_ptr<Guardian>>::iterator itPtrGuardian = std::find(ptrGuardians.begin(), ptrGuardians.end(), guardian);
    if (itPtrGuardian != ptrGuardians.end())
    {
        ptrGuardians.erase(itPtrGuardian);
        return true;
    }
    return false;
}

const bool TriumphToken::removeGuardian(std::vector<std::weak_ptr<Guardian>>& guardians)
{
    for (std::vector<std::weak_ptr<Guardian>>::iterator itPtrGuardian = guardians.begin(); itPtrGuardian != guardians.end(); )
    {
        if (std::find(ptrGuardians.begin(), ptrGuardians.end(), itPtrGuardian) != ptrGuardians.end())
        {
            ptrGuardians.erase(itPtrGuardian);
        } 
        else ++itPtrGuardian;
    }

}

const bool TriumphToken::removeGuardian(const std::string& guardiansName)
{   
    std::vector<std::weak_ptr<Guardian>>::iterator itPtrGuardian = std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
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
        std::vector<std::weak_ptr<Guardian>>::iterator itPtrGuardian = std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
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

const bool TriumphToken::operator==(TriumphToken& other) const
{
    if (other.getDescription()==description && other.getActivity()==ptrActivity)
    {
        if (other.ptrGuardians!=ptrGuardians)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
