#include "ToLeft.h"


bool ToLeft(Point p, Point q, Point s) {
    return Area2double(p, q, s) > 0;
}


/*
*�����������ʽ����ʽ�����׹�ʽ��
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

    Point p, q, s,r, q_prime;//����PQSΪ��ʱ�룬���׹�ʽ������
    p.x = 1;
    p.y = 1;

    q.x = 3;
    q.y = 3;

    s.x = 2;
    s.y = 2.1;//2.1 false?�������̫С����ΪArea2����int��������Ƶʾ������


    r.x = 2;
    r.y = 4;

    q_prime.x = 5;//���s������һ�ߣ������
    q_prime.y = 5;



    bool is_in_triangle = in_triangle(p,q,r,s);




    int ret1 = ToLeft(p, q, s);//��ʱ��
    int ret2 = ToLeft(q, s, p);//�������ʱ��
    int ret3 = ToLeft(s, q, p);//˳ʱ��
    int ret4 = ToLeft(p, q, q_prime);//���s������һ�ߣ������

    std::cout << "in_triangle" << std::endl;
    std::cout << "ret1:" << ret1 << std::endl;
    std::cout << "ret2:" << ret2 << std::endl;
    std::cout << "ret3:" << ret3 << std::endl;
    std::cout << "ret4:" << ret4 << std::endl;



    ret1 = Area2(p, q, s);
    ret2 = Area2(q, s, p);
    ret3 = Area2(s, q, p);
    ret4 = Area2(p, q, q_prime);//���s������һ�ߣ������

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
void checkEdge(Point S[], int n, int p, int q) {//�����pq��һ�ε���ֻ�ж�pq������pqk��һ���ԣ����ж��Ƿ����Ҷ��е�
    bool LEmpty = true, REmpty = true;
    for (int k = 0; k < n && (LEmpty || REmpty); k++) {
        if (k != p &&k != q) {//ȫ�����ˣ�ֻҪ�Ӹ������жϾͺ�
            if (ToLeft(S[p], S[q], S[k]))//�������������м��أ����м�Ҳ�Ǽ���
                LEmpty = false;
            else
                REmpty = false;
        }
    }
    if (LEmpty || REmpty)
        S[p].extreme = S[q].extreme = true;
}