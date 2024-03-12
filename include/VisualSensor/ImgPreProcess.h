//
// Created by pigoil on 23-10-20.
//

#ifndef TOSTART_IMGPREPROCESS_H
#define TOSTART_IMGPREPROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Thirdparty/Orbbec/Orbbec/ObSensor.hpp"

class ImgPreProcess {
public:
    ImgPreProcess();

    ob::Pipeline pipeline;

    std::shared_ptr<ob::Config> config = std::make_shared<ob::Config>();

    void GeminiInit();

    bool ExtracteFromGemini();

    void GetRGBDImgs(cv::Mat &color, cv::Mat &depth);

    void SaveDepth(cv::Mat depthImg, unsigned long creatTime);

    void SaveColor(cv::Mat colorImg, unsigned long time);

private:
    cv::Mat colorImg;

    cv::Mat depthImg;

    ob::FormatConvertFilter formatConverFilter;

};


#endif //TOSTART_IMGPREPROCESS_H
