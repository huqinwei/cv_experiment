#pragma once

//���˲��Ͷ�Ӧλ�ã�https://blog.csdn.net/huqinweI987/article/details/115538917

#include <pcl/point_types.h>
/*#include "point_types"*/

//ѧ�����߿γ̣�https://www.xuetangx.com/learn/THU08091000327/THU08091000327/5883587/video/9215695

//in-triangle test������toleft�����棬����in triangle�ˣ������������α����أ�


//Ϊ��ͳһ��ʹ���Զ���ṹ��
struct Point {
    double x, y;
    bool extreme;
};


bool in_triangle(Point p, Point q, Point r, Point s);





//���
int ToLeft_Demo();



bool ToLeft(Point p, Point q, Point s);


/*
*�����������ʽ����ʽ�����׹�ʽ��
2*S=|p.x    p.y 1|
|q.x    q.y 1|
|s.x    s.y 1|
*/

int Area2(Point p, Point q, Point s);
double Area2double(Point p, Point q, Point s);



//�����˼·��չ���˼���
//https://www.xuetangx.com/learn/THU08091000327/THU08091000327/5883587/video/9215702
//���ߵı������ж�


void markEE(Point S[], int n);


void checkEdge(Point S[], int n, int p, int q);//�����pq��һ�ε���ֻ�ж�pq������pqk��һ���ԣ����ж��Ƿ����Ҷ��е�



