#pragma once
#pragma warning(disable:4996)
#include "pcl/point_types.h"
#include <pcl/point_types.h>

#include<pcl/filters/bilateral.h>

#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>




void create_4points();//�������Ʋ���



void connect_pointcloud();
void connect_pointcloud2();

//�������ƣ��洢�ļ�
void create_pointcloud_and_save();

//��ȡ�ļ������Ƽӷ�
void load_and_save_point_cloud();


