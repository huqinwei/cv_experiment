#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <chrono>
#include <windows.h>
//#include "LLog.h"

using namespace std;
using namespace cv;
using namespace std::chrono;



//ʵ����ۣ�//Խ��Խģ��
//ê��û�ģ�-1�������ģ�������ô�����ģ����Ҿ�ֵ�ⲻ�������ĵ�
void blur_test()
{
#if 0
    char im1_path[512];
    //D:\experiment_data\pictures_other
    sprintf(im1_path, "D:\\experiment_data\\pictures_other\\dota1.jpg");
    cv::Mat im1 = imread(im1_path, cv::IMREAD_UNCHANGED);//IMREAD_UNCHANGED

    cv::Mat im2, im3, im4, im5;
    blur(im1, im2, cv::Size(1, 1), cv::Point(-1, -1));
    blur(im1, im3, cv::Size(3, 3), cv::Point(-1, -1));
    blur(im1, im4, cv::Size(5, 5), cv::Point(-1, -1));
    blur(im1, im5, cv::Size(19, 19), cv::Point(-1, -1));
    imshow("before", im1);
    imshow("after:2", im2);
    imshow("after:3", im3);
    imshow("after:4", im4);
    imshow("after:5", im5);
    waitKey();
#endif
    cv::Mat im;
    //todo:����mat���Լ�����matԪ�أ�Ȼ���˲����

}




void gaussian_blur_test()
{
#if 1
    char im1_path[512];
    //D:\experiment_data\pictures_other
    sprintf_s(im1_path, "D:\\experiment_data\\pictures_other\\dota1.jpg");
    cv::Mat im1 = imread(im1_path, cv::IMREAD_UNCHANGED);//IMREAD_UNCHANGED

    cv::Mat im2, im3, im4, im5;
    GaussianBlur(im1, im2, cv::Size(1, 1), 11, 11);
    GaussianBlur(im1, im3, cv::Size(3, 3), 11, 11);//��׼��͸�˹�ֲ��йصĲ����ɣ�3*3�вο�����11��11
    GaussianBlur(im1, im4, cv::Size(5, 5), 11, 11);
    GaussianBlur(im1, im5, cv::Size(19, 19), 11, 11);
    imshow("before", im1);
    imshow("after:2", im2);
    imshow("after:3", im3);
    imshow("after:4", im4);
    imshow("after:5", im5);
    waitKey();
#endif
    cv::Mat im;
    //todo:����mat���Լ�����matԪ�أ�Ȼ���˲����

}

int main()
{

    gaussian_blur_test();
}