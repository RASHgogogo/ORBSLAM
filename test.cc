#include <iostream>

#include "ImgPreProcess.h"
#include "System.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cerr << endl << "Usage: ./rgbd_tum path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Retrieve paths to images

    vector<double> vTimestamps;


    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::RGBD,true);


    // Main loop
    cv::Mat imRGB, imD;


    // Pass the image to the SLAM system
    //SLAM.TrackRGBD(imRGB,imD,tframe);

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveTrajectoryTUM("CameraTrajectory.txt");
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");   

    return 0;
}