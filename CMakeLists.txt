cmake_minimum_required(VERSION 3.26)

project(ToStart)


set(CMAKE_CXX_STANDARD 17)

#定位OpenCV库
find_package(OpenCV REQUIRED)

#定位Eigen3库
find_package(Eigen3 REQUIRED)

#定位Pangolin库
find_package(Pangolin REQUIRED)

#计算机本地库头文件
include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        ${Pangolin_INCLUDE_DIRS})

#计算机本地库库文件
link_directories(
        ${OpenCV_LIBRARIES}
        ${EIGEN3_LIBS}
        ${Pangolin_LIBRARIES})

#第三方库库文件
link_directories(
        ${PROJECT_SOURCE_DIR}/Thirdparty/DBoW2/lib
        ${PROJECT_SOURCE_DIR}/Thirdparty/g2o/lib
        ${PROJECT_SOURCE_DIR}/Thirdparty/Orbbec/lib)        

#头文件目录
include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include/ORBSLAM
        ${PROJECT_SOURCE_DIR}/include/VisualSensor)




add_executable(ToStart 
test.cc
src/VisualSensor/ImgPreProcess.cc
src/ORBSLAM/System.cc
src/ORBSLAM/Tracking.cc
src/ORBSLAM/LocalMapping.cc
src/ORBSLAM/LoopClosing.cc
src/ORBSLAM/ORBextractor.cc
src/ORBSLAM/ORBmatcher.cc
src/ORBSLAM/FrameDrawer.cc
src/ORBSLAM/Converter.cc
src/ORBSLAM/MapPoint.cc
src/ORBSLAM/KeyFrame.cc
src/ORBSLAM/Map.cc
src/ORBSLAM/MapDrawer.cc
src/ORBSLAM/Optimizer.cc
src/ORBSLAM/PnPsolver.cc
src/ORBSLAM/Frame.cc
src/ORBSLAM/KeyFrameDatabase.cc
src/ORBSLAM/Sim3Solver.cc
src/ORBSLAM/Initializer.cc
src/ORBSLAM/Viewer.cc
)

target_link_libraries(ToStart 
        OrbbecSDK
        DBoW2
        g2o
        ${OpenCV_LIBRARIES}
        ${Pangolin_LIBRARIES}
        ${EIGEN3_LIBS})





#find_package(PCL REQUIRED)
#include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_LIBRARY_DIRS})
#add_definitions(${PCL_DEFINITIONS})
