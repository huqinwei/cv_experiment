#pragma once
#pragma warning(disable:4996)
#include <pcl/range_image/range_image.h>

#include <iostream> //标准输入/输出
#include <boost/thread/thread.hpp> //多线程
#include <pcl/common/common_headers.h>
#include <pcl/range_image/range_image.h> //深度图有关头文件
#include <pcl/io/pcd_io.h> //pcd文件输入/输出
#include <pcl/visualization/range_image_visualizer.h> //深度图可视化
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h> //命令行参数解析
#include <pcl/pcl_macros.h>
#include <windows.h>
void range_image_creation();

void range_image_visualization();
