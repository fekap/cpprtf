#include "unit.h"
#include "math.h"

CppRtf_Unit::CppRtf_Unit()
{
}

int CppRtf_Unit::_unit = CppRtf_Unit::UNIT_CM;

void CppRtf_Unit::setGlobalUnit(int unit)
{
    CppRtf_Unit::_unit = unit;
}

int CppRtf_Unit::getGlobalUnit()
{
    return CppRtf_Unit::_unit;
}

int CppRtf_Unit::getUnitInTwips(float value)
{
    return round(value * CppRtf_Unit::getGlobalUnit());
}

int CppRtf_Unit::getPointsInTwips(float value)
{
    return round(value * CppRtf_Unit::UNIT_POINT);
}

float CppRtf_Unit::convertTo(float value, float unitFrom, float unitTo)
{
    if (unitTo == unitFrom) {
        return value;
    }
    return (value * unitFrom) / unitTo;
}
