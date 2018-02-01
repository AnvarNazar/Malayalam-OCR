#ifndef CONTOURWITHDATA_H
#define CONTOURWITHDATA_H
#include <vector>
#include <opencv2/core.hpp>


class ContourWithData
{
public:
    std::vector<cv::Point> ptContour;
    cv::Rect boundingRect;
    float area;

    bool checkIfContourIsValid(int area);

    static bool sorByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight);
    ContourWithData();
};

#endif // CONTOURWITHDATA_H
