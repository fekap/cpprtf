#ifndef UNIT_H
#define UNIT_H

//unit class for working with twips in rtf.
class CppRtf_Unit
{
public:
    CppRtf_Unit();

    static const float UNIT_TWIPS = 1;
    static const float UNIT_CM = 567;
    static const float UNIT_MM = 56.692913;
    static const float UNIT_INCH = 1440;
    static const float UNIT_POINT = 14.988078;

    //sets global unit
    static void setGlobalUnit(int unit);

    //gets global unit
    static int getGlobalUnit();

    //gets unit in twips
    static int getUnitInTwips(float value);

    //gets points in twips
    static int getPointsInTwips(float value);

    //converts the value to another unit
    static float convertTo(float value, float unitFrom, float unitTo);

private:
    static int _unit;
};

#endif // UNIT_H
