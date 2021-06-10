//
// Created by 剑伊 on 2021/6/9.
//

#ifndef STACKLAB_MAZE_H
#define STACKLAB_MAZE_H

#include <iostream>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define LINE 10
#define COL 10
using namespace std;
typedef struct Node {
    int x;
    int y;
    int direct;
    struct Node *next;
    struct Node *last;
} Node, *LinkNode;

typedef struct {
    LinkNode base;
    LinkNode top;
    int stacksize;
} SqStack, *Stack;

typedef struct {
    int cx;
    int cy;
} Direction;

Direction direct[4] = {{0,  1},
                       {1,  0},
                       {0,  -1},
                       {-1, 0}};

int marix[12][12] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                     {1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1},
                     {1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1},
                     {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                     {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                     {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                     {1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1},
                     {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
                     {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int InitStack(Stack S) {
    LinkNode link = (Node *) malloc(STACK_INIT_SIZE * sizeof(Node));
    S->base = link;
    if (!S->base)
        return 0;
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push(Stack S, Node e) {
    if (S->top - S->base >= S->stacksize) {
        S->base = (Node *) realloc(S->base, (S->stacksize +
                                             STACKINCREMENT) * sizeof(Node));
        if (!S->base)
            return 0;
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return 1;
}

int Pop(Stack S, Node &e) {
    if (S->top == S->base)
        return 0;
    e = *--S->top;
    return 1;
}

int GetTop(Stack S, Node &e) {
    if (S->top == S->base)
        return 0;
    e = *(S->top - 1);
    return 1;
}

void MazeRun() {
    SqStack H, S;
    InitStack(&H);
    InitStack(&S);
    Node a, b, temp;
    temp.x = 1;
    temp.y = 1;
    temp.direct = -1;
    Push(&H, temp);
    int line, col;
    while (GetTop(&H, a) == 1) {
        Pop(&H, temp);
        int x, y, di;
        x = temp.x;
        y = temp.y;
        di = temp.direct + 1;
        while (di < 4) {
            line = x + direct[di].cx;
            col = y + direct[di].cy;
            if (marix[line][col] == 0) {
                temp.x = x;
                temp.y = y;
                temp.direct = di;
                Push(&H, temp);
                x = line;
                y = col;
                marix[x][y] = -1;
                if (x == LINE && y == COL) {
                    while (GetTop(&H, a)==1) {
                        Pop(&H, temp);
                        Push(&S, temp);
                    }
                    while (GetTop(&S, b)==1) {
                        Pop(&S, temp);
                        printf("(%d,%d),direct: %d\n", temp.x, temp.y, temp.direct);
                    }
                } else
                    di = 0;
            } else
                di++;
        }

    }
}


#endif //STACKLAB_MAZE_H
