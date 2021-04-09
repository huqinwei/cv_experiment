#pragma once

//个人博客对应位置：https://blog.csdn.net/huqinweI987/article/details/115538917

#include <pcl/point_types.h>
/*#include "point_types"*/

//学堂在线课程：https://www.xuetangx.com/learn/THU08091000327/THU08091000327/5883587/video/9215695

//in-triangle test，三个toleft都是真，就是in triangle了，但是在三角形边上呢？


//为了统一，使用自定义结构体
struct Point {
    double x, y;
    bool extreme;
};


bool in_triangle(Point p, Point q, Point r, Point s);





//起点
int ToLeft_Demo();



bool ToLeft(Point p, Point q, Point s);


/*
*三角形面积公式行列式（海伦公式）
2*S=|p.x    p.y 1|
|q.x    q.y 1|
|s.x    s.y 1|
*/

int Area2(Point p, Point q, Point s);
double Area2double(Point p, Point q, Point s);



//极点的思路扩展到了极边
//https://www.xuetangx.com/learn/THU08091000327/THU08091000327/5883587/video/9215702
//极边的遍历和判断


void markEE(Point S[], int n);


void checkEdge(Point S[], int n, int p, int q);//传入边pq，一次调用只判断pq，保持pqk的一致性，能判断是否左右都有点



