#pragma once
#include<iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;
//#define PI acos(-1.0)
#define PI 3.14159265358979323846
struct PT
{
	int x;
	int y;
};
struct LINE
{
	Point pStart;
	Point pEnd;
};

struct Point4Pos 
{
	Point2d topleft;
	Point2d topright;
	Point2d bottomleft;
	Point2d bottomright;
};

class CRoteImage
{
public:
	CRoteImage();
	~CRoteImage();

	Mat getRotedImage(Mat img, double fAngle);
	//��������ľ�γ�ȣ���ת�Ƕȣ�����õ�ʵ�ʾ��룬������һ���㡣
	Point2d computerThatLonLat(double lon, double lat, double brng, double dist);

	//����ͼ�����ĵ�posλ����Ϣ���ɻ����и߶ȣ����࣬�����ȣ�������ȣ�����ͼ��������λ��
	Point4Pos compute4Position(Point2d center, double flyHeight, double focus=4.3, double imgWidth=3.42, double imgHeight=4.59);
private:
	Mat m_img;

};

