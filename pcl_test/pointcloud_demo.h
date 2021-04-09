#pragma once
#pragma warning(disable:4996)
#include "pcl/point_types.h"
#include <pcl/point_types.h>

#include<pcl/filters/bilateral.h>

#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>




void create_4points();//基础点云操作



void connect_pointcloud();
void connect_pointcloud2();

//创建点云，存储文件
void create_pointcloud_and_save();

//读取文件，点云加法
void load_and_save_point_cloud();


