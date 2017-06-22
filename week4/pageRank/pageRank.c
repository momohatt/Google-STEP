#include<stdio.h>

#define NODE_NUM 6

int adjacencyMatrix[NODE_NUM][NODE_NUM];
int numOfPathOut[NODE_NUM] = {};
double score[NODE_NUM];


void inputAdjacencyMatrix()
{
    printf("グラフの隣接行列を入力：\n");
    int i, j;
    for (i = 0; i < NODE_NUM; ++i){
        for (j = 0; j <NODE_NUM; ++j){
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
    return;
}

void calcNumOfPathOut()
{
    int i, j;
    for (i = 0; i < NODE_NUM; ++i){
        for (j = 0; j <NODE_NUM; ++j){
            if (adjacencyMatrix[i][j] == 1){
                numOfPathOut[i]+=1;
            }
        }

       // printf("%d ", numOfPathOut[i]);
    }
    //printf("\n");
    return;
}

void evalScore(double *score)
{
    double tmpScore[NODE_NUM] = {}; //scoreから計算した新スコアを一時的に保存
    int i, j;

    for (i = 0; i < NODE_NUM; ++i){
        for (j = 0; j < NODE_NUM; ++j){
            if (adjacencyMatrix[i][j] == 1){
                tmpScore[j] += (double) score[i]/numOfPathOut[i];
            }
        }
    }

    int k = 0;
    for (k = 0; k < NODE_NUM; ++k){
        score[k] = tmpScore[k];
    }

    //debug
    //printf("score: %f %f %f %f %f %f\n", score[0], score[1], score[2], score[3], score[4], score[5]);

    return;
}

int main()
{
    inputAdjacencyMatrix();
    calcNumOfPathOut();

    int turn=0;
    
    int i = 0;
    for (i = 0;i < NODE_NUM; ++i){
        score[i] = 100;
    }

    for (turn = 0; turn <= 20; ++turn){
        printf("Step %d: ", turn);
        
        int i=0;
        for (i = 0; i < NODE_NUM; ++i){
            printf("(%c, %f)", 'a' + i,  score[i]);
        }
        printf("\n");

        evalScore(score);
    }

    return 0;
}
