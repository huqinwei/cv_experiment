#include "pointcloud_demo.h"




void create_4points()
{

	pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.push_back(pcl::PointXYZ(1.11, 1.12, 1.13));
    std::cout << "width:" << cloud.width << std::endl;
    cloud.push_back(pcl::PointXYZ(2.11, 2.12, 2.13));
    std::cout << "width:" << cloud.width << std::endl;
    cloud.push_back(pcl::PointXYZ(3.11, 3.12, 3.13));
    std::cout << "width:" << cloud.width << std::endl;
    cloud.push_back(pcl::PointXYZ(4.11, 4.12, 4.13));
    std::cout << "width:" << cloud.width << std::endl;

	std::cout << "cloud:\n" << cloud << std::endl;
	std::cout << "width:" << cloud.width << std::endl;
	std::cout << "height:" << cloud.height << std::endl;

#if 0
	for (int i = 0; i < cloud.size(); ++i)
	{
		std::cout << cloud.at(i) << std::endl;
	}
	for (int i = 0; i < cloud.size(); ++i)
	{
		std::cout << cloud[i] << std::endl;
	}
#endif

	for (int i = 0; i < cloud.size(); ++i)
	{
		std::cout << cloud.at(i).x << std::endl;
		std::cout << cloud.at(i).y << std::endl;
		std::cout << cloud.at(i).z << std::endl;
		//std::cout << cloud.at(i).PointXYZ.data << std::endl;
	}


}














void connect_pointcloud()
{

	//pcl::PointCloud<pcl::PointXYZ> cloud_a;//XYZ�ֶ�
	pcl::PointCloud<pcl::Normal> n_cloud_b;//�����ֶ�
	pcl::PointCloud<pcl::PointNormal> p_n_cloud_c;//���Ӻ���ֶ�

												  //////////////////////////////////��ptr��ʽ��ֱ������/////////////////////////////////////////////////

												  //����resize()����ʵ������ߵ�vector  points   resize�����ⲿ��size�Ƿ�װvector��size�����size��width��heightû��Ȼ��ϵ
												  //inline size_t size () const { return (points.size ()); }
	pcl::PointCloud<pcl::PointXYZ> cloud_a, cloud_b, cloud_c;
	cloud_a.width = 5;
	cloud_a.height = cloud_b.height = n_cloud_b.height = 1;
	if (1)//�ȼ۲���
		cloud_a.points.resize(cloud_a.width*cloud_a.height);
	else
		cloud_a/*.points*/.resize(cloud_a.width*cloud_a.height);
	cloud_b.width = 3;
	cloud_b.points.resize(cloud_b.width*cloud_b.height);

	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		cloud_a.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
	}

	std::cerr << "cloud A:" << std::endl;
	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		std::cerr << " " << cloud_a.points[i].x << " " << cloud_a.points[i].y << " " << cloud_a.points[i].z << std::endl;
	}
	for (size_t i = 0; i < cloud_b.points.size(); ++i)
	{
		cloud_b.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_b.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_b.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
	}
	std::cerr << "cloud B:" << std::endl;
	for (size_t i = 0; i < cloud_b.points.size(); ++i)
	{
		std::cerr << " " << cloud_b.points[i].x << " " << cloud_b.points[i].y << " " << cloud_b.points[i].z << std::endl;
	}

	cloud_c = cloud_a;
	cloud_c += cloud_b;//������ƪ����
	std::cerr << "cloud C:" << std::endl;
	for (size_t i = 0; i < cloud_c.points.size(); ++i)
	{
		std::cerr << " " << cloud_c.points[i].x << " " << cloud_c.points[i].y << " " << cloud_c.points[i].z << std::endl;
	}



}

void connect_pointcloud2()//��ptr��ʽ
{
	//////////////////////////////////�����ֶ�/////////////////////////////////////////////////
	//pcl::PointCloud<pcl::PointXYZ> cloud_a;//XYZ�ֶ�
	pcl::PointCloud<pcl::Normal> n_cloud_b;//�����ֶ�
	pcl::PointCloud<pcl::PointNormal> p_n_cloud_c;//���Ӻ���ֶ�

	pcl::PointCloud<pcl::PointXYZ> cloud_a, cloud_b, cloud_c;
	cloud_a.width = 5;
	cloud_a.height = cloud_b.height = n_cloud_b.height = 1;
	cloud_a.points.resize(cloud_a.width*cloud_a.height);

	n_cloud_b.width = 5;
	n_cloud_b.points.resize(n_cloud_b.width*n_cloud_b.height);

	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		cloud_a.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
	}

	std::cerr << "cloud A:" << std::endl;
	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		std::cerr << " " << cloud_a.points[i].x << " " << cloud_a.points[i].y << " " << cloud_a.points[i].z << std::endl;
	}
	for (size_t i = 0; i < n_cloud_b.size(); ++i)
	{
		n_cloud_b.points[i].normal[0] = 1024 * rand() / (RAND_MAX + 1.0f);
		n_cloud_b.points[i].normal[1] = 1024 * rand() / (RAND_MAX + 1.0f);
		n_cloud_b.points[i].normal[2] = 1024 * rand() / (RAND_MAX + 1.0f);
	}
	std::cerr << "cloud B:" << std::endl;
	for (size_t i = 0; i < n_cloud_b.points.size(); ++i)
	{
		std::cerr << " " << n_cloud_b.points[i].normal[0] << " " << n_cloud_b.points[i].normal[1] << " " << n_cloud_b.points[i].normal[2] << std::endl;
	}



	pcl::concatenateFields(cloud_a, n_cloud_b, p_n_cloud_c);
	std::cerr << "cloud C:" << std::endl;
	for (size_t i = 0; i < p_n_cloud_c.points.size(); ++i)
	{
		std::cerr << " " << p_n_cloud_c.points[i].x << " " << p_n_cloud_c.points[i].y << " " << p_n_cloud_c.points[i].z
			<< " " << p_n_cloud_c.points[i].normal[0] << " " << p_n_cloud_c.points[i].normal[1] << " " << p_n_cloud_c.points[i].normal[2] << std::endl;
	}


}


void create_pointcloud_and_save()//ptr��ʽ
{

	//pcl::PointCloud<pcl::PointXYZ> cloud_a;//XYZ�ֶ�
	pcl::PointCloud<pcl::Normal> n_cloud_b;//�����ֶ�
	pcl::PointCloud<pcl::PointNormal> p_n_cloud_c;//���Ӻ���ֶ�

												  //////////////////////////////////��ptr��ʽ��ֱ������/////////////////////////////////////////////////

												  //����resize()����ʵ������ߵ�vector  points   resize�����ⲿ��size�Ƿ�װvector��size�����size��width��heightû��Ȼ��ϵ
												  //inline size_t size () const { return (points.size ()); }
	pcl::PointCloud<pcl::PointXYZ> cloud_a, cloud_b, cloud_c;
	cloud_a.width = 5;
	cloud_a.height = cloud_b.height = n_cloud_b.height = 1;
	if (1)//�ȼ۲���
		cloud_a.points.resize(cloud_a.width*cloud_a.height);
	else
		cloud_a/*.points*/.resize(cloud_a.width*cloud_a.height);
	cloud_b.width = 3;
	cloud_b.points.resize(cloud_b.width*cloud_b.height);

	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		cloud_a.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_a.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
	}

	std::cerr << "cloud A:" << std::endl;
	for (size_t i = 0; i < cloud_a.points.size(); ++i)
	{
		std::cerr << " " << cloud_a.points[i].x << " " << cloud_a.points[i].y << " " << cloud_a.points[i].z << std::endl;
	}
	for (size_t i = 0; i < cloud_b.points.size(); ++i)
	{
		cloud_b.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_b.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
		cloud_b.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
	}
	std::cerr << "cloud B:" << std::endl;
	for (size_t i = 0; i < cloud_b.points.size(); ++i)
	{
		std::cerr << " " << cloud_b.points[i].x << " " << cloud_b.points[i].y << " " << cloud_b.points[i].z << std::endl;
	}

	pcl::io::savePCDFile("0.pcd", cloud_a);
	pcl::io::savePCDFile("1.pcd", cloud_b);

}
void load_and_save_point_cloud()//ptr��ʽ
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr c1(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr c2(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr c3(new pcl::PointCloud<pcl::PointXYZ>);

	pcl::io::loadPCDFile("0.pcd", *c1);
	pcl::io::loadPCDFile("1.pcd", *c2);

	std::vector<pcl::PointCloud<pcl::PointXYZ>> combine_point;
	combine_point.push_back(*c1);
	combine_point.push_back(*c2);

	for (size_t i = 0; i < combine_point.size(); i++)
	{
		*c3 += combine_point[i];
	}

    //���Զ��üӷ�
    pcl::PointCloud<pcl::PointXYZ> cloud_d;
    cloud_d.width = 2;
    cloud_d.height = cloud_d.height = 1;
    cloud_d.points.resize(cloud_d.width*cloud_d.height);
    for (size_t i = 0; i < cloud_d.points.size(); ++i)
    {
        cloud_d.points[i].x = i;
        cloud_d.points[i].y = i;
        cloud_d.points[i].z = i;
    }
    *c3 += cloud_d;

	pcl::io::savePCDFile("c3.pcd", *c3);

}
