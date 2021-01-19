// TestRoteImage.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RoteImage.h"

#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
//#include "opencv2/highgui/highgui.hpp"
#include<opencv2/stitching.hpp>




void testcompute4PosDLL()
{
	//test ���������Ķ�̬���
	Point4Pos imgpos;
  Point2d center(117.406298, 39.558841);//ͼƬ���ĵ�ľ�γ������

	CRoteImage* roteimage = new CRoteImage;
	imgpos = roteimage->compute4Position(center, 100);
	cout <<setiosflags(ios::fixed) << setprecision(7) << imgpos.topleft.x << "  " << imgpos.topleft.y << endl;
	cout << setiosflags(ios::fixed) << setprecision(7) << imgpos.topright.x << "  " << imgpos.topright.y << endl;
	cout << setiosflags(ios::fixed) << setprecision(7) << imgpos.bottomleft.x << "  " << imgpos.bottomleft.y << endl;
	cout << setiosflags(ios::fixed) << setprecision(7) << imgpos.bottomright.x << "  " << imgpos.bottomright.y << endl;
	//test ���������Ķ�̬��

}

int main()
{
//  	Mat img;
//  	img = imread("./1.png");
// 	
// 	if (img.empty())
// 	{
// 		return -1;
// 	}
// 
// 	CRoteImage* roteimage = new CRoteImage;
// 	Mat dst;
// 	dst = roteimage->getRotedImage(img, 30);
// 
// 	imwrite("1_res.png", dst);

	testcompute4PosDLL();


	system("pause");

    return 0;
}

