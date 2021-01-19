#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include "pcl/point_types.h"
#include <pcl/point_types.h>

#include<pcl/filters/bilateral.h>

#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>


#include "pointcloud_demo.h"

using namespace std;

void pcl_ptr_test()
{
#if 0

    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::SACSegmentation<pcl::PointXYZ>seg;
    seg.setInputCloud(cloud->makeShared());
#elif 0

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_Ptr(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ> cloud;

    cloud = *cloud_Ptr;
    cloud_Ptr = cloud.makeShared();
#elif 0
    pcl::PointCloud<pcl::PointXYZ> cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::SACSegmentation<pcl::PointXYZ>seg;
    seg.setInputCloud(cloud);

#endif
}

void strcpy1(char* dst, char* src)
{
    int n = sizeof(dst);
    cout << n << endl;
    // 	for (int i = 0; i < n; ++i)
    // 	{
    // 
    // 	}
}

int main()
{


    char str[] = "hello";
    cout << sizeof(str) << endl;
    cout << strlen(str) << endl;


    connect_pointcloud_ptr_save();
    connect_pointcloud_ptr();


    //create_4points();
    connect_pointcloud2();

    //connect_pointcloud();
    //pcl_ptr_test();


    srand(time(NULL));
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 1000;
    cloud->height = 1;

    cloud->points.resize(cloud->width*cloud->height);
    for (size_t i = 0; i < cloud->size(); ++i)
    {
        cloud->points[i].x = 1024.0f*rand() / (RAND_MAX + 1.0f);
        cloud->points[i].y = 1024.0f*rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 1024.0f*rand() / (RAND_MAX + 1.0f);

    }

    pcl::KdTreeFLANN<pcl::PointXYZ>kdtree;
    kdtree.setInputCloud(cloud);

    pcl::PointXYZ searchPoint;
    searchPoint.x = 1024.0f*rand() / (RAND_MAX + 1.0f);
    searchPoint.y = 1024.0f*rand() / (RAND_MAX + 1.0f);
    searchPoint.z = 1024.0f*rand() / (RAND_MAX + 1.0f);

    int K = 10;
    std::vector<int>pointIdxNKNSearch(K);
    std::vector<float>pointNKNSquaredDistance(K);
    std::cout << "K nearest neighbor search at (" << searchPoint.x << " " << searchPoint.y << " " << searchPoint.z << ")with K= " << K << std::endl;









    system("pause");

    return 0;
}










