#include "ToLeft.h"


bool ToLeft(Point p, Point q, Point s) {
    return Area2double(p, q, s) > 0;
}


/*
*三角形面积公式行列式（海伦公式）
2*S=|p.x    p.y    1|
    |q.x    q.y    1|
    |s.x    s.y    1|
    */
int Area2(Point p, Point q, Point s) {
    return p.x*q.y + q.x*s.y + s.x*p.y
        - p.x*s.y - q.x*p.y - s.x*q.y;
}

double Area2double(Point p, Point q, Point s) {
    return p.x*q.y + q.x*s.y + s.x*p.y
        - p.x*s.y - q.x*p.y - s.x*q.y;
}


bool in_triangle(Point p, Point q, Point r, Point s) {
    bool b1 = ToLeft(p, q, s);
    bool b2 = ToLeft(q, r, s);
    bool b3 = ToLeft(r, p, s);


    return ToLeft(p, q, s) && ToLeft(q, r, s) && ToLeft(r, p, s);


}


int ToLeft_Demo()
{


#if 0
    Point S[5];
    S[0].x = 0;
    S[0].y = 0;

    S[1].x = 2;
    S[1].y = 0;

    S[2].x = 2;
    S[2].y = 2;

    S[3].x = 0;
    S[3].y = 2;

    S[4].x = 1;
    S[4].y = 0.5;




    markEE(S, 5);
    return 0;
#endif

    
    Point S[100];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            S[i * 10 + j].x = i;
            S[i * 10 + j].y = j;
        }

    for (int i = 0; i < 100; i++)
        std::cout << "S[" << i << "]:" << S[i].x << " " << S[i].y << std::endl;

    markEE(S, 100);

    return 0;

    Point p, q, s,r, q_prime;//假设PQS为逆时针，海伦公式正方向
    p.x = 1;
    p.y = 1;

    q.x = 3;
    q.y = 3;

    s.x = 2;
    s.y = 2.1;//2.1 false?面积不能太小？因为Area2返回int？所以视频示例错误


    r.x = 2;
    r.y = 4;

    q_prime.x = 5;//替代s，三点一线，看结果
    q_prime.y = 5;



    bool is_in_triangle = in_triangle(p,q,r,s);




    int ret1 = ToLeft(p, q, s);//逆时针
    int ret2 = ToLeft(q, s, p);//换起点逆时针
    int ret3 = ToLeft(s, q, p);//顺时针
    int ret4 = ToLeft(p, q, q_prime);//替代s，三点一线，看结果

    std::cout << "in_triangle" << std::endl;
    std::cout << "ret1:" << ret1 << std::endl;
    std::cout << "ret2:" << ret2 << std::endl;
    std::cout << "ret3:" << ret3 << std::endl;
    std::cout << "ret4:" << ret4 << std::endl;



    ret1 = Area2(p, q, s);
    ret2 = Area2(q, s, p);
    ret3 = Area2(s, q, p);
    ret4 = Area2(p, q, q_prime);//替代s，三点一线，看结果

    std::cout << "area2" << std::endl;
    std::cout << "ret1:" << ret1 << std::endl;
    std::cout << "ret2:" << ret2 << std::endl;
    std::cout << "ret3:" << ret3 << std::endl;
    std::cout << "ret4:" << ret4 << std::endl;



    return 0;

}



void markEE(Point S[], int n) {
    for (int k = 0; k < n; k++) {
        S[k].extreme = false;
    }

    for (int p = 0; p < n; p++) {
        for (int q = p + 1; q < n; q++) {
            checkEdge(S, n, p, q);
        }
    }

}
void checkEdge(Point S[], int n, int p, int q) {//传入边pq，一次调用只判断pq，保持pqk的一致性，能判断是否左右都有点
    bool LEmpty = true, REmpty = true;
    for (int k = 0; k < n && (LEmpty || REmpty); k++) {
        if (k != p &&k != q) {//全遍历了，只要加个不等判断就好
            if (ToLeft(S[p], S[q], S[k]))//这个代码对吗？在中间呢？在中间也是极线
                LEmpty = false;
            else
                REmpty = false;
        }
    }
    if (LEmpty || REmpty)
        S[p].extreme = S[q].extreme = true;
}