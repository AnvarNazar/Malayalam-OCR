#include "contourwithdata.h"

bool ContourWithData::checkIfContourIsValid(int area)
{
    if(this->area < area)
        return false;
    return true;
}

bool ContourWithData::sorByBoundingRectXPosition(const ContourWithData &cwdLeft, const ContourWithData &cwdRight)
{
    return (cwdLeft.boundingRect.x < cwdRight.boundingRect.x);
}

ContourWithData::ContourWithData()
{
}


