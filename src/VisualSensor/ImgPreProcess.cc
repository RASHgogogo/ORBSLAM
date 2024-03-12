//
// Created by pigoil on 23-10-20.
//

#include "ImgPreProcess.h"

ImgPreProcess::ImgPreProcess(){
    
    GeminiInit();

}
void ImgPreProcess::GeminiInit(){
    try{
        auto colorProfiles = pipeline.getStreamProfileList(OB_SENSOR_COLOR);
        std::shared_ptr<ob::VideoStreamProfile> colorProfile  = nullptr;
        if(colorProfiles) {
            colorProfile = colorProfiles->getVideoStreamProfile(640, 480, OB_FORMAT_MJPG, 30);
        }
        config->enableStream(colorProfile);
    }
    catch(ob::Error &e) {
        std::cerr << "Current device is not support color sensor!" << std::endl;
    }

    //加载深度空间图像配置
    try{
        auto depthProfiles = pipeline.getStreamProfileList(OB_SENSOR_DEPTH);
        std::shared_ptr<ob::VideoStreamProfile> depthProfile  = nullptr;
        if(depthProfiles) {
            depthProfile = depthProfiles->getVideoStreamProfile(640, 400, OB_FORMAT_UNKNOWN, 30);
        }
        config->enableStream(depthProfile);
    }
    catch(ob::Error &e) {
        std::cerr << "Current device is not support depth sensor!" << std::endl;
    }
    pipeline.getDevice()->setBoolProperty(OB_PROP_DEPTH_MIRROR_BOOL  , false);
    pipeline.getDevice()->setBoolProperty(OB_PROP_DEPTH_ALIGN_HARDWARE_BOOL , true);

    pipeline.start(config);
}

bool ImgPreProcess::ExtracteFromGemini(){
    auto frameset = pipeline.waitForFrames(100);

    if (frameset == nullptr) {
        std::cout << "The frameset is null!" << std::endl;
        return false;
    }
    auto colorFrame = frameset->colorFrame();
    auto depthFrame = frameset->depthFrame();

    if (colorFrame == nullptr || depthFrame == nullptr) {
        return false;
    }
    auto Framsettime = colorFrame->systemTimeStamp();
    formatConverFilter.setFormatConvertType(FORMAT_MJPG_TO_RGB888);
    colorFrame = formatConverFilter.process(colorFrame)->as<ob::ColorFrame>();
    formatConverFilter.setFormatConvertType(FORMAT_RGB888_TO_BGR);
    colorFrame = formatConverFilter.process(colorFrame)->as<ob::ColorFrame>();

    colorImg = cv::Mat(colorFrame->height(), colorFrame->width(), CV_8UC3, colorFrame->data());
    colorImg = colorImg(cv::Range(0, 399), cv::Range(0, 639)).clone();


    depthImg = cv::Mat(depthFrame->height(), depthFrame->width(), CV_16UC1, depthFrame->data());
    return true;
}
// 保存深度图为png格式
void ImgPreProcess::SaveDepth(cv::Mat depthImg, unsigned long creatTime) {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);
    std::string depthName = "Depth_" + std::to_string(creatTime) + ".png";
    cv::imwrite(depthName, depthImg, compression_params);
    std::cout << "Depth saved:" << depthName << std::endl;
}

// 保存彩色图为png格式
void ImgPreProcess::SaveColor(cv::Mat colorImg, unsigned long time) {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
    compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);
    std::string colorName = "Color_" + std::to_string(time) + ".png";
    cv::imwrite(colorName, colorImg, compression_params);
    std::cout << "Color saved:" << colorName << std::endl;
}

void ImgPreProcess::GetRGBDImgs(cv::Mat &color, cv::Mat &depth){
    while(!ExtracteFromGemini());
    color = colorImg;
    depth = depthImg;
}