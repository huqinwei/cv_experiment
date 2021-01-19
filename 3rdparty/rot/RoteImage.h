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
	//根据输入的经纬度，旋转角度，距离该点实际距离，计算另一个点。
	Point2d computerThatLonLat(double lon, double lat, double brng, double dist);

	//根据图像中心点pos位置信息，飞机飞行高度，焦距，像幅宽度，像幅长度，计算图像四至点位置
	Point4Pos compute4Position(Point2d center, double flyHeight, double focus=4.3, double imgWidth=3.42, double imgHeight=4.59);
private:
	Mat m_img;

};

