
#if 0
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
#if 0
    create_pointcloud_and_save();
    load_and_save_point_cloud();
#endif

    create_4points();
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

#endif




#if 0
#pragma warning(disable:4996)

#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <pcl/filters/filter.h>





int user_data;

void
viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere(o, 0.25, "sphere", 0);
    std::cout << "i only run once" << std::endl;
}
void
viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape("text", 0);
    viewer.addText(ss.str(), 200, 300, "text", 0);
    //FIXME: possible race condition here:
    user_data++;
}
int
main()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile("test_cloud.pcd", *cloud);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);

    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer

    //This will only get called once
    viewer.runOnVisualizationThreadOnce(viewerOneOff);

    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread(viewerPsycho);

    while (!viewer.wasStopped())
    {
        std::cout << cloud->width << endl;
        std::cout << cloud->height << endl;
        //you can also do cool processing here
        //FIXME: Note that this is running in a separate thread from viewerPsycho
        //and you should guard against race conditions yourself...
        user_data++;
    }
    return 0;
}
#endif 
#pragma warning(disable:4996)

// #include "vtkAutoInit.h" 
// VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
// VTK_MODULE_INIT(vtkInteractionStyle);

#include <iostream>  
#include <pcl/io/pcd_io.h>  
#include <pcl/point_types.h>  
#include <pcl/ModelCoefficients.h>  
#include <pcl/filters/project_inliers.h>  


#if 0//���������õ�����
int main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_projected(new pcl::PointCloud<pcl::PointXYZ>);

    // Fill in the cloud data  
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        cloud->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    std::cerr << "Cloud before projection: " << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
        std::cerr << "    " << cloud->points[i].x << " "
        << cloud->points[i].y << " "
        << cloud->points[i].z << std::endl;

    // Create a set of planar coefficients with X=Y=0,Z=1  
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
    coefficients->values.resize(4);
    coefficients->values[0] = coefficients->values[1] = 0;
    coefficients->values[2] = 1.0;
    coefficients->values[3] = 0;

    // Create the filtering object  
    pcl::ProjectInliers<pcl::PointXYZ> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    proj.setInputCloud(cloud);
    proj.setModelCoefficients(coefficients);
    proj.filter(*cloud_projected);

    std::cerr << "Cloud after projection: " << std::endl;
    for (size_t i = 0; i < cloud_projected->points.size(); ++i)
        std::cerr << "    " << cloud_projected->points[i].x << " "
        << cloud_projected->points[i].y << " "
        << cloud_projected->points[i].z << std::endl;

    system("pause");
    return (0);
}

#endif 

#if 0 //�����е���һ�����ӣ���ʾ���ӣ�bunny.pcd�������ҿ���������
#include<pcl/visualization/cloud_viewer.h>
#include<iostream>
#include<pcl/io/io.h>
#include<pcl/io/pcd_io.h>
#include<pcl/io/ply_io.h>
#include<pcl/point_types.h>
int user_data;
using std::cout;


void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);
}

int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    //char strfilepath[256] = "G:/github_project/pcl/test/bunny.pcd";
    char strfilepath[256] = "D:/CC_proj/neimeng300-osgb-test/Productions/osgb_7block/Data/Tile_+002_+003/Tile_+002_+003_L23_0002020.obj";
    if (-1 == pcl::io::loadPCDFile(strfilepath, *cloud)) {
        cout << "error input!" << endl;
        return -1;
    }

    cout << cloud->points.size() << endl;
    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    viewer.showCloud(cloud);
    viewer.runOnVisualizationThreadOnce(viewerOneOff);
    system("pause");
    return 0;
}

#endif

#if 0//��ʾ��
#include <iostream>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/console/parse.h>


int main(int argc, char **argv) {
    std::cout << "Test PCL !!!" << std::endl;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
    uint8_t r(255), g(15), b(15);
    for (float z(-1.0); z <= 1.0; z += 0.05)
    {
        for (float angle(0.0); angle <= 360.0; angle += 5.0)
        {
            pcl::PointXYZRGB point;
            point.x = 0.5 * cosf(pcl::deg2rad(angle));
            point.y = sinf(pcl::deg2rad(angle));
            point.z = z;
            uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
                static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
            point.rgb = *reinterpret_cast<float*>(&rgb);
            point_cloud_ptr->points.push_back(point);
        }
        if (z < 0.0)
        {
            r -= 12;
            g += 12;
        }
        else
        {
            g -= 12;
            b += 12;
        }
    }
    point_cloud_ptr->width = (int)point_cloud_ptr->points.size();
    point_cloud_ptr->height = 1;

    pcl::visualization::CloudViewer viewer("test");
    viewer.showCloud(point_cloud_ptr);
    while (!viewer.wasStopped()) {};
    return 0;
}
#endif



#if 0//ȱ��IO���̣��Ȼ�������
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/console/parse.h>  //pcl����̨����

int main(int argc, char **argv) {
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;  //����ICP��ʵ����
    icp.setInputSource(cloud_sources);
    icp.setInputTarget(cloud_target);
    icp.setMaxCorrespondenceDistance(100);//���ö�Ӧ���֮��������루��ֵ����׼���Ӱ��ϴ󣩡�
    icp.setTransformationEpsilon(1e-10);//�������α仯����֮��Ĳ�ֵ��һ������Ϊ1e - 10���ɣ���
    icp.setEuclideanFitnessEpsilon(0.001);//�������������Ǿ�������С����ֵ�� ֹͣ������
    icp.setMaximumIterations(100);//������������icp��һ�������ķ�������������Щ�Σ�����Ͽ��ӻ��������ʾ���ɽ���������Ϊ1����
    icp.align(final);

    //////////////////////////////////���Ϊ�˸�������˽�ICP�ļ�����̣���������ĵڶ���Ŀ�ģ�����������´��룺////////////////////////////////////////////////////////////

    boost::shared_ptr<pcl::visualization::PCLVisualizer> view(new pcl::visualization::PCLVisualizer("icp test"));  //���崰�ڹ���ָ��
    int v1; //������������v1��v2������v1������ʾ��ʼλ�ã�v2������ʾ��׼����
    int v2;
    view->createViewPort(0.0, 0.0, 0.5, 1.0, v1);  //�ĸ����ڲ����ֱ��Ӧx_min,y_min,x_max.y_max.
    view->createViewPort(0.5, 0.0, 1.0, 1.0, v2);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> sources_cloud_color(cloud_in, 250, 0, 0); //����Դ���Ƶ���ɫΪ��ɫ
    view->addPointCloud(cloud_in, sources_cloud_color, "sources_cloud_v1", v1);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_cloud_color(cloud_target, 0, 250, 0);  //Ŀ�����Ϊ��ɫ
    view->addPointCloud(cloud_target, target_cloud_color, "target_cloud_v1", v1); //��������ӵ�v1����

    view->setBackgroundColor(0.0, 0.05, 0.05, v1); //�����������ڵı���ɫ
    view->setBackgroundColor(0.05, 0.05, 0.05, v2);

    view->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "sources_cloud_v1");  //������ʾ��Ĵ�С
    view->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target_cloud_v1");

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>aligend_cloud_color(Final, 255, 255, 255);  //������׼���Ϊ��ɫ
    view->addPointCloud(Final, aligend_cloud_color, "aligend_cloud_v2", v2);
    view->addPointCloud(cloud_target, target_cloud_color, "target_cloud_v2", v2);

    view->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "aligend_cloud_v2");
    view->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "target_cloud_v2");

    view->registerKeyboardCallback(&keyboardEvent, (void*)NULL);  //���ü��̻ص�����
    int iterations = 0; //��������
    while (!view->wasStopped())
    {
        view->spinOnce();  //������ͼ
        if (next_iteration)
        {
            icp.align(*Final);  //icp����
            cout << "has conveged:" << icp.hasConverged() << "score:" << icp.getFitnessScore() << endl;
            cout << "matrix:\n" << icp.getFinalTransformation() << endl;
            cout << "iteration = " << ++iterations;
            /*... ���icp.hasConverged=1,��˵��������׼�ɹ���icp.getFinalTransformation()������任����   ...*/
            if (iterations == 1000)  //��������������
                return 0;
            view->updatePointCloud(Final, aligend_cloud_color, "aligend_cloud_v2");

        }
        next_iteration = false;  //���ε����������ȴ�����

    }


    /////////////////////////////////�����Ҫ�������¼��̻ص����������Կ��Ƶ������̣�///////////////////////////////////////
    bool next_iteration = false;
    //���ü��̽�������
    void keyboardEvent(const pcl::visualization::KeyboardEvent &event, void *nothing)
    {
        if (event.getKeySym() == "space" && event.keyDown())
            next_iteration = true;
    }
    /*... ����������ʾ�����̿ո������ʱ���ſ�ִ��ICP���� ... */


    
    return 0;
}
#endif

#include "demos.h"
#include "pcd_io_demos.h"

#include "ToLeft.h"

int main() {

    ToLeft_Demo();
    return 0;
    write_pcd();
    return 0;
    read_pcd();
    return 0;


    range_image_visualization();
    return 0;
    range_image_creation();
}
