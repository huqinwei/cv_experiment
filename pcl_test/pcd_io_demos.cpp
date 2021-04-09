#pragma warning(disable:4996)
#include "pcd_io_demos.h"
#include "pcl/io/pcd_io.h"
#include "pcl/point_types.h"




int read_pcd()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); // �������ƣ�ָ�룩

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("G:/github_project/pcl/test/bunny.pcd", *cloud) == -1) //* ����PCD��ʽ���ļ�������ļ������ڣ�����-1
    {
        PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //�ļ�������ʱ�����ش�����ֹ����
        return (-1);
    }
    std::cout << "Loaded "
        << cloud->width * cloud->height
        << " data points from test_file.pcd with the following fields: "
        << std::endl;
    //for (size_t i = 0; i < cloud->points.size (); ++i) //��ʾ���еĵ�
    for (size_t i = 0; i < 5; ++i) // Ϊ�˷���۲죬ֻ��ʾǰ5����
        std::cout << "    " << cloud->points[i].x
        << " " << cloud->points[i].y
        << " " << cloud->points[i].z << std::endl;



}



int write_pcd()
{
    pcl::PointCloud<pcl::PointXYZ> cloud; // �������ƣ�����ָ�룩

                                          //����������
    cloud.width = 5; //���õ��ƿ��
    cloud.height = 1; //���õ��Ƹ߶�
    cloud.is_dense = false; //���ܼ���
    cloud.points.resize(cloud.width * cloud.height); //���Σ�����
                                                     //������Щ�������
    for (size_t i = 0; i < cloud.points.size(); ++i)
    {
        cloud.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }
    //���浽PCD�ļ�
    pcl::io::savePCDFileASCII("test_pcd.pcd", cloud); //�����Ʊ��浽PCD�ļ���
    std::cerr << "Saved " << cloud.points.size() << " data points to test_pcd.pcd." << std::endl;
    //��ʾ��������
    for (size_t i = 0; i < cloud.points.size(); ++i)
        std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;

    return (0);

}