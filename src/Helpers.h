/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_HELPERS_H
#define _PLAYERBOT_HELPERS_H

#include "Common.h"

#include <map>
#include <vector>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>

void split(std::vector<std::string>& dest, std::string const str, char const* delim)
{
    char* pTempStr = strdup(str.c_str());
    char* pWord = strtok(pTempStr, delim);

    while (pWord != nullptr)
    {
        dest.push_back(pWord);
        pWord = strtok(nullptr, delim);
    }

    free(pTempStr);
}

std::vector<std::string>& split(std::string const s, char delim, std::vector<std::string>& elems)
{
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}

std::vector<std::string> split(std::string const s, char delim)
{
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

#endif
