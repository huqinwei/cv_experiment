#pragma once
#pragma warning(disable:4996)
#include <pcl/range_image/range_image.h>

#include <iostream> //��׼����/���
#include <boost/thread/thread.hpp> //���߳�
#include <pcl/common/common_headers.h>
#include <pcl/range_image/range_image.h> //���ͼ�й�ͷ�ļ�
#include <pcl/io/pcd_io.h> //pcd�ļ�����/���
#include <pcl/visualization/range_image_visualizer.h> //���ͼ���ӻ�
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h> //�����в�������
#include <pcl/pcl_macros.h>
#include <windows.h>
void range_image_creation();

void range_image_visualization();
