#include "DistanceTable.h"
#include <algorithm>

static DistanceRow DISTANCES[] =
{
    { L"Тула", L"Москва", 184 },
    { L"Москва", L"Санкт-Петербург", 635 },
    { L"Тула", L"Санкт-Петербург", 800 },
    { L"Москва", L"Казань", 815 },
    { L"Москва", L"Нижний Новгород", 420 },
    { L"Москва", L"Воронеж", 515 },
    { L"Москва", L"Ростов-на-Дону", 1080 }
};

static const int DIST_COUNT = sizeof(DISTANCES) / sizeof(DistanceRow);

static std::wstring Normalize(const std::wstring& s)
{
    std::wstring r = s;
    std::transform(r.begin(), r.end(), r.begin(), towlower);
    return r;
}

int GetDistanceKm(const std::wstring& from, const std::wstring& to)
{
    std::wstring f = Normalize(from);
    std::wstring t = Normalize(to);

    if (f == t) return 0;

    for (int i = 0; i < DIST_COUNT; i++)
    {
        std::wstring a = Normalize(DISTANCES[i].from);
        std::wstring b = Normalize(DISTANCES[i].to);

        if ((a == f && b == t) || (a == t && b == f))
            return DISTANCES[i].km;
    }
    return 500;
}
