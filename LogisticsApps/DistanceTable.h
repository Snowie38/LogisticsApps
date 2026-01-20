#pragma once
#include <string>

struct DistanceRow
{
    const wchar_t* from;
    const wchar_t* to;
    int km;
};


int GetDistanceKm(const std::wstring& from, const std::wstring& to);
