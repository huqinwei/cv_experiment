#pragma warning(disable:4996)
#include "pcd_io_demos.h"
#include "pcl/io/pcd_io.h"
#include "pcl/point_types.h"




int read_pcd()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // 创建点云（指针）

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("G:/github_project/pcl/test/bunny.pcd", *cloud) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
    {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
        return (-1);
    }
    std::cout << "Loaded "
        << cloud->width * cloud->height
        << " data points from test_file.pcd with the following fields: "
        << std::endl;
    //for (size_t i = 0; i < cloud->points.size (); ++i) //显示所有的点
    for (size_t i = 0; i < 5; ++i) // 为了方便观察，只显示前5个点
        std::cout << "    " << cloud->points[i].x
        << " " << cloud->points[i].y
        << " " << cloud->points[i].z << std::endl;



}



int write_pcd()
{
    pcl::PointCloud<pcl::PointXYZ> cloud; // 创建点云（不是指针）

                                          //填充点云数据
    cloud.width = 5; //设置点云宽度
    cloud.height = 1; //设置点云高度
    cloud.is_dense = false; //非密集型
    cloud.points.resize(cloud.width * cloud.height); //变形，无序
                                                     //设置这些点的坐标
    for (size_t i = 0; i < cloud.points.size(); ++i)
    {
        cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }
    //保存到PCD文件
    pcl::io::savePCDFileASCII("test_pcd.pcd", cloud); //将点云保存到PCD文件中
    std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
    //显示点云数据
    for (size_t i = 0; i < cloud.points.size(); ++i)
        std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

    return (0);

}