/*
网格最短路径
输入：起始节点坐标
      终止节点坐标
输出：路径
*/

#include "main.h"


int visited[MAX_VERTEX];
struct step_pre step_pre[MAX_VERTEX];
struct point point[MAX_VERTEX] = {
                                  {0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0},
                                  {0, 1, 0}, {1, 1, 1}, {2, 1, 0}, {3, 1, 0},
                                  {0, 2, 0}, {1, 2, 1}, {2, 2, 0}, {3, 2, 0},
                                  {0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}
                                                                            };
int edge  = (int)sqrt(MAX_VERTEX);


int main(){
    int i, j;
    int startpointx, startpointy, endpointx, endpointy;
    int start, end;
    VerList *p, *q;
    LGraph G;
    list *r;


    //BFS链表初始化
    list *Q = CreatList();
    //用来保存cord2ord函数输出
    list *order = CreatList();

    cord2ord(&point, order);
    LGraphInit(&G, order);
    
    for(i = 0; i < MAX_VERTEX; i++){
        p = &(G.graph[i]);
        for(q = p; q != NULL; q = q->NextVer){
            printf("%d\t", q->VerNum);
        }
        printf("\n");
    }

    printf("输入搜索起点坐标：\n");
    scanf("%d %d", &startpointx, &startpointy);
    start = startpointy * edge + startpointx;
    
    printf("输入搜索终点坐标：\n");
    scanf("%d %d", &endpointx, &endpointy);
    end = endpointy * edge + endpointx;
    
    printf("\n");
    BFS(&G, Q, start);


    for(j = 0; j < MAX_VERTEX; j++)
        printf("%d:%d\n", step_pre[j].step, step_pre[j].pre);
    printf("\n");

    printf("从起点到达终点的长度:%d\n", step_pre[end].step);
    printf("从终点到达起点的路径:");
    //printf("%d-->",end);
    printf("(%d,%d)-->",point[end].x, point[end].y);
    while(step_pre[end].step--){
        //printf("%d%s", step_pre[end].pre, step_pre[end].step != 0 ? "-->" : "");
        printf("(%d,%d)%s", point[step_pre[end].pre].x, point[step_pre[end].pre].y, step_pre[end].step != 0 ? "-->" : "");
        end = step_pre[end].pre;
    }
    printf("\n");
    return 0;
}

//每一个节点都来一次BFS
void TRAVEL_BFS(LGraph *G, list *Q){
    int i;

    for(i = 0; i < MAX_VERTEX; i++)
        visited[i] = 0;
    for(i = 0; i < MAX_VERTEX; i++)
        if(!visited[i])
            BFS(G, Q, i);
}

//从节点V开始广度优先遍历图G
void BFS(LGraph *G, list *Q, int v){
    int w;


    step_pre[v].step = 0;
    step_pre[v].pre = 0;
    visited[v] = TRUE;
    EnQueue(Q, v);
    while(!isEmpty(Q)){
        v = DeQueue(Q);
        for(w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)){
            if(!visited[w]){

                //visit函数-->在BFS里统计节点v到各节点距离，以及路径上的前一个节点
                step_pre[w].step = step_pre[v].step + 1;
                step_pre[w].pre = v;

                visited[w] = TRUE;
                EnQueue(Q, w);
            }
        }
    }
}

//输入相连的节点，以邻接表方式初始化图
void LGraphInit(LGraph *G, list *order){
    int i;
    int v1, v2;
    list *r;

    r = order->next;
    for(i = 0; i < MAX_VERTEX; i++){
        G->graph[i].VerNum = i;
        G->graph[i].NextVer = NULL;
    }

    //printf("输入相连的顶点：\n");
    //这里的输入来自于cord2ord函数的输出链表
    while(/*~scanf("%d %d", &v1, &v2)*/r != NULL){
        /*
            VerList node1;
            VerLise node2;
            这样声明调用完LGLGraphInit()后空间会被回收
        */
        v1 = r->data;
        v2 = r->next->data;

        VerList *node1 = (VerList*)malloc(sizeof(VerList));
        VerList *node2 = (VerList*)malloc(sizeof(VerList));

        node1->VerNum = v2;
        node1->NextVer = G->graph[v1].NextVer;
        G->graph[v1].NextVer = node1;


        node2->VerNum = v1;
        node2->NextVer = G->graph[v2].NextVer;
        G->graph[v2].NextVer = node2;


        r = r->next->next;

    }
}

//返回单链表头节点
list *CreatList(){
    list *temp;
    int data;

    list *p = (list *)malloc(sizeof(list));
    p->data = 0;
    p->next = NULL;
    temp = p;
    /*
    printf("输入链表节点数值：\n");
    while(~scanf("%d", &data)){
       while(temp->next != NULL)
            temp = temp->next;
       list *q = (list *)malloc(sizeof(list));
       q->data = data;
       temp->next = q;
       q->next = NULL;
    }
    */
    return p;
}

//尾插法入队
list *EnQueue(list *p, int data){
    list *temp;

    temp = p;
    while(temp->next != NULL)
        temp = temp->next;
    list *q = (list *)malloc(sizeof(list));
    q->data = data;
    q->next = NULL;
    temp->next = q;

    return p;
}

//出队，返回删除节点数据
int DeQueue(list *p){
    list *temp;
    int data;

    temp = p;
    temp = temp->next;
    data = temp->data;
    p->next = temp->next;
    free(temp);

    return data;
}

//判断列表是否为空
int isEmpty(list *p){
    if(p->next == NULL)
        return TRUE;
    else
        return FALSE;
}

//返回v的一个邻接点，找不到返回-1
int FirstNeighbor(LGraph *G, int v){
    int i;
    VerList *p;

    for(i = 0; i < MAX_VERTEX; i++){
        if(v == G->graph[i].VerNum)
            break;
        if(i == MAX_VERTEX)
            return -1;
    }

    p = &(G->graph[v]);
    if(p->NextVer == NULL)
        return -1;
    else
        return p->NextVer->VerNum;
}

//w是v的邻接点，返回除w之外的下一个邻接点，找不到返回-1
int NextNeighbor(LGraph *G, int v, int w){
    VerList *p;

    p = G->graph[v].NextVer;
    while(p != NULL){
        //w在最后一个位置
        if(p->VerNum == w && p->NextVer == NULL)
            return -1;
        //w不在最后一个位置
        if(p->VerNum == w && p->NextVer != NULL)
            return p->NextVer->VerNum;
        p = p->NextVer;
    }
}

//输入各节点坐标，输出相连的节点序号（保存在list链表）
void cord2ord(struct point *p, list *order){
    int i, j;

    for(i = 0; i < edge; i++){
        for(j = 0; j < edge; j++){
            //输出相连的上顶点
            if(p[j * edge + i].flag == 0 && p[(j + 1) * edge + i].flag == 0  && (j >= 0 && j <= edge - 2)){
                EnQueue(order, j * edge + i);
                EnQueue(order, (j + 1) * edge + i);
                //printf("%d %d\n", j * edge + i, (j + 1) * edge + i);
            }
            //输出相连的右顶点
            if(p[j * edge + i].flag == 0 && p[j * edge + i + 1].flag == 0 && (i >= 0 && i <= edge - 2)){
                EnQueue(order, j * edge + i);
                EnQueue(order, j * edge + i + 1);
                //printf("%d %d\n", j * edge + i, j * edge + i + 1);
            }
        }
    }
}
