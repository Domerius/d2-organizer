#include "../include/triumph.hpp"

#include "../include/guardian.hpp"
#include "../include/activity.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <stdexcept>


const bool Triumph::connectGuardian(const std::shared_ptr<Guardian>& guardian)
{
    if(std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
        [guardian](std::vector<const std::weak_ptr<Triumph>>::iterator itPtrGuardian){return guardian == itPtrGuardian->lock();}) == ptrGuardians.end())
    {
        ptrGuardians.emplace_back(std::weak_ptr<Guardian>(guardian));
        return true;
    }
    return false;
}

const bool Triumph::connectGuardian(std::vector<const std::shared_ptr<Guardian>>& guardians)
{
    if (!guardians.empty())
    {
        for (auto itGuardian = guardians.begin(); itGuardian < guardians.end(); )
        {
            if (std::find_if(ptrGuardians.begin(), ptrGuardians.end(),
                [itGuardian](std::vector<std::weak_ptr<Triumph>>::iterator itPtrGuardian){return *itGuardian == itPtrGuardian->lock();}) == ptrGuardians.end())
            {
                ptrGuardians.emplace_back(std::weak_ptr(*itGuardian));
                guardians.erase(itGuardian);
            }
            else ++itGuardian;
        }
    }
    else throw std::invalid_argument("Received empty Guardians list.");
    
    if (guardians.empty()) return true;
    return false;
}

const bool Triumph::disconectGuardian(const std::string& guardiansName)
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

const bool Triumph::disconectGuardian(std::vector<const std::string>& guardiansNames)
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

const bool Triumph::operator==(Triumph& other) const
{
    if (other.getDescription()==description && other.getActivity().lock()==ptrActivity)
    {
        if (other.ptrGuardians!=ptrGuardians)
        {
            throw std::invalid_argument("There are two TriumphTokens with matching unique properties and different Guardian pointers.");
        }
        return true;
    }
    return false;
}
