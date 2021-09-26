#ifndef __MAIN_H
#define __MAIN_H
#include <math.h>
#include <stdio.h >
#include <stdlib.h>
#define MAX_VERTEX 16 //顶点个数
#define TRUE 1
#define FALSE 0


//单链表
typedef struct node{
    int data;
    struct node *next;
}list;

//顶点链表
typedef struct VerNode{
    int VerNum;
    struct VerNode *NextVer;
}VerList;

//无权无向图
typedef struct{
    VerList graph[MAX_VERTEX];
}LGraph;

//step记录到节点长度，pre是广度优先遍历前一个节点
typedef struct step_pre{
    int step;
    int pre;
};

//节点
typedef struct point{
    int x;
    int y;
    int flag;        //障碍物flag = 1，否则flag = 0
};

void LGraphInit(LGraph *G, list *order);
list *CreatList();
list *EnQueue(list *p, int data);
int DeQueue(list *p);
int FirstNeighbor(LGraph *G, int v);
int NextNeighbor(LGraph *G, int v, int w);
void BFS(LGraph *G, list *Q, int v);
void TRAVEL_BFS(LGraph *G, list *Q);
int isEmpty(list *p);
void cord2ord(struct point *p, list *order);


#endif // __MAIN_H
