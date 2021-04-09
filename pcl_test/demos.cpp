#include "demos.h"




//https://blog.csdn.net/Suo_ivy/article/details/79867568
//深度图例子
void range_image_creation()
{
    pcl::PointCloud<pcl::PointXYZ> pointCloud;

    // 循环产生点云的数据
    //y范围1，精度0.01，101个点，z，101个点
    //x是2-y，1.5~2.5，和y线性，z固定
    //画一个直线段，加上z的迭代，是个矩形！
    for (float y = -0.5f; y <= 0.5f; y += 0.01f) {
        for (float z = -0.5f; z <= 0.5f; z += 0.01f) {
            pcl::PointXYZ point;
            point.x = 2.0f - y;
            point.y = y;
            point.z = z;
            pointCloud.points.push_back(point);
        }
    }

    pointCloud.width = (uint32_t)pointCloud.points.size();
    pointCloud.height = 1;

    //实现一个呈矩形形状的点云
    float angularResolution = (float)(1.0f*(M_PI / 180.0f));//angular_resolution为模拟的深度传感器的角度分辨率，即深度图像中一个像素对应的角度大小
    float maxAngleWidth = (float)(360.0f*(M_PI / 180.0f));//max_angle_width为模拟的深度传感器的水平最大采样角度，
    float maxAngleHeight = (float)(180.0f*(M_PI / 180.0f));//max_angle_height为模拟传感器的垂直方向最大采样角度  都转为弧度

    Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);//传感器的采集位置

    pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;//深度图像遵循坐标系统
    float noiseLevel = 0.00;//noise_level获取深度图像深度时，近邻点对查询点距离值的影响水平
    float minRange = 0.0f;//min_range设置最小的获取距离，小于最小获取距离的位置为传感器的盲区，可以尝试对点云可视化，然后调整这个距离看效果
    int borderSize = 1;//border_size获得深度图像的边缘的宽度

    pcl::RangeImage rangeImage;
    rangeImage.createFromPointCloud(pointCloud, angularResolution, maxAngleWidth, maxAngleHeight, sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);
    std::cout << rangeImage << std::endl;


    system("pause");
}



typedef pcl::PointXYZ PointType;
//参数 全局
float angular_resolution_x = 0.5f, //角分辨率（单位弧度）
angular_resolution_y = angular_resolution_x;
pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME; //坐标帧（相机帧）
bool live_update = true; //是否根据选择的视角更新深度图像
                         // 打印帮助信息
void printUsage(const char* progName)
{
    std::cout << "\n\nUsage: " << progName << " [options] <scene.pcd>\n\n"
        << "Options:\n"
        << "-------------------------------------------\n"
        << "-rx <float>  angular resolution in degrees (default " << angular_resolution_x << ")\n"
        << "-ry <float>  angular resolution in degrees (default " << angular_resolution_y << ")\n"
        << "-c <int>     coordinate frame (default " << (int)coordinate_frame << ")\n"
        << "-l           live update - update the range image according to the selected view in the 3D viewer.\n"
        << "-h           this help\n"
        << "\n\n";
}
//https://blog.csdn.net/xuezhisdc/article/details/51019461?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&dist_request_id=1328679.63658.16164855374635915&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control
//本来是命令行和main的，改了。

void range_image_visualization() {
    //解析命令行参数
//     if (pcl::console::find_argument(argc, argv, "-h") >= 0)
//     {
//         printUsage(argv[0]);
//         return 0;
//     }
//     if (pcl::console::find_argument(argc, argv, "-l") >= 0)
//     {
//         live_update = true;
//         std::cout << "Live update is on.\n";
//     }
//     if (pcl::console::parse(argc, argv, "-rx", angular_resolution_x) >= 0)
//         std::cout << "Setting angular resolution in x-direction to " << angular_resolution_x << "deg.\n";
//     if (pcl::console::parse(argc, argv, "-ry", angular_resolution_y) >= 0)
//         std::cout << "Setting angular resolution in y-direction to " << angular_resolution_y << "deg.\n";
//     int tmp_coordinate_frame;
//     if (pcl::console::parse(argc, argv, "-c", tmp_coordinate_frame) >= 0)
//     {
//         coordinate_frame = pcl::RangeImage::CoordinateFrame(tmp_coordinate_frame);
//         std::cout << "Using coordinate frame " << (int)coordinate_frame << ".\n";
//     }
    angular_resolution_x = pcl::deg2rad(angular_resolution_x);
    angular_resolution_y = pcl::deg2rad(angular_resolution_y);

    //读取pcd文件。如果没有指定文件，则创建样本云点
    pcl::PointCloud<PointType>::Ptr point_cloud_ptr(new pcl::PointCloud<PointType>);
    pcl::PointCloud<PointType>& point_cloud = *point_cloud_ptr;
    Eigen::Affine3f scene_sensor_pose(Eigen::Affine3f::Identity());
    std::vector<int> pcd_filename_indices;// = pcl::console::parse_file_extension_argument(argc, argv, "pcd");
    if (!pcd_filename_indices.empty())
    {
//         std::string filename = argv[pcd_filename_indices[0]];
//         if (pcl::io::loadPCDFile(filename, point_cloud) == -1)
//         {
//             std::cout << "Was not able to open file \"" << filename << "\".\n";
//             printUsage(argv[0]);
//             return 0;
//         }
//         scene_sensor_pose = Eigen::Affine3f(Eigen::Translation3f(point_cloud.sensor_origin_[0],
//             point_cloud.sensor_origin_[1],
//             point_cloud.sensor_origin_[2])) *
//             Eigen::Affine3f(point_cloud.sensor_orientation_);
    }
    else
    {
        std::cout << "\nNo *.pcd file given => Genarating example point cloud.\n\n";
        for (float x = -0.5f; x <= 0.5f; x += 0.01f)
        {
            for (float y = -0.5f; y <= 0.5f; y += 0.01f)
            {
                PointType point;  point.x = x;  point.y = y;  point.z = 2.0f - y;
                point_cloud.points.push_back(point);
            }
        }
        point_cloud.width = (int)point_cloud.points.size();  point_cloud.height = 1;
    }

    //从点云创建出深度图
    float noise_level = 0.0;
    float min_range = 0.0f;
    int border_size = 1;
    boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage); //深度图指针
    pcl::RangeImage& range_image = *range_image_ptr;   //引用
    range_image.createFromPointCloud(point_cloud, angular_resolution_x, angular_resolution_y,
        pcl::deg2rad(360.0f), pcl::deg2rad(180.0f),
        scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size); //从点云创建出深度图

                                                                                   //打开一个3D图形窗口，并添加点云数据
    pcl::visualization::PCLVisualizer viewer("3D Viewer");
    viewer.setBackgroundColor(1, 1, 1); //背景
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> range_image_color_handler(range_image_ptr, 0, 0, 0);
    viewer.addPointCloud(range_image_ptr, range_image_color_handler, "range image");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "range image");
    //viewer.addCoordinateSystem (1.0f, "global");
    //PointCloudColorHandlerCustom<PointType> point_cloud_color_handler (point_cloud_ptr, 150, 150, 150);
    //viewer.addPointCloud (point_cloud_ptr, point_cloud_color_handler, "original point cloud");
    viewer.initCameraParameters();
    //setViewerPose(viewer, range_image.getTransformationToWorldSystem ()); //PCL 1.6 出错

    //以图像的形式显示深度图像，深度值作为颜色显示
    pcl::visualization::RangeImageVisualizer range_image_widget("Range image");
    range_image_widget.showRangeImage(range_image);


    //主循环
    while (!viewer.wasStopped())
    {
        range_image_widget.spinOnce();
        viewer.spinOnce();
        pcl_sleep(10);//window下为毫秒
        //Sleep(10);

        if (live_update) //根据3D显示，实时更新2D图像
        {
            scene_sensor_pose = viewer.getViewerPose(); //获取观测姿势
            range_image.createFromPointCloud(point_cloud, angular_resolution_x, angular_resolution_y,
                pcl::deg2rad(360.0f), pcl::deg2rad(180.0f),
                scene_sensor_pose, pcl::RangeImage::LASER_FRAME, noise_level, min_range, border_size); //重新生成新的深度图
            range_image_widget.showRangeImage(range_image); //重新显示
        }
    }


}











