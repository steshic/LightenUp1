#include "helper.h"
#include <QDebug>

Helper::Helper(QObject *parent) : QObject(parent)
{

}

int dfsGeneration(int x, int y, int (*graph)[10], bool (*visited)[10]) {

    visited[x][y] = true;
    int xc[4] = {0, 1, 0, -1};
    int yc[4] = {1, 0, -1, 0};
    int st[4] = {1, 2, 4, 8};
    int k = rand() % 4;
    for (int i = 0; i < 4; i++) {
        k = (k + i) % 4;
        if ((0 <= x + xc[k]) && (x + xc[k] < 10) && (0 <= y + yc[k]) &&
                (y + yc[k] < 10) && (visited[x + xc[k]][y + yc[k]] == false)) {

            graph[x][y] |= st[k];

            graph[x + xc[k]][y + yc[k]] |= st[(k + 2) % 4];
            dfsGeneration(x + xc[k], y + yc[k], graph, visited);
        }
    }
    return 0;
}

QVector <int> Helper::newGame()
{
    int graph[10][10];
    bool visited[10][10];
    QVector <int> bricks;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            graph[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    dfsGeneration(0, 0, graph, visited);


    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            bricks.push_back(graph[i][j]);
        }
    }
    for (int i = 0; i < 100; i++) {
        int k = rand() % 4;
        for (int j = 0; j < k; j++) {
            bricks[i] = (((bricks[i] & 1) << 4) | bricks[i]) >> 1;
        }
    }

    qDebug() << "New Game!";

    return bricks;
}

int dfs(int x, int y, int graph[10][10], bool (*visited)[10]) {
    qDebug() << x << " " << y;
    visited[x][y] = true;
    int xc[4] = {0, 1, 0, -1};
    int yc[4] = {1, 0, -1, 0};
    int st[4] = {1, 2, 4, 8};

    for (int k = 0; k < 4; k++) {
        if ((st[k] & graph[x][y]) && (0 <= x + xc[k]) && (x + xc[k] < 10) && (0 <= y + yc[k]) &&
                (y + yc[k] < 10) && (visited[x + xc[k]][y + yc[k]] == false) && (st[(k + 2) % 4] & graph[x + xc[k]][y + yc[k]])) {
            dfs(x + xc[k], y + yc[k], graph, visited);
        }
    }
    return 0;
}

QVector<bool> Helper::light(QVector<int> bricks)
{
     QVector<bool> lights;

    int graph[10][10];
    bool visited[10][10];

    lights.push_back(true);
    for (int i = 0; i < 100; i++) {
        lights.push_back(false);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            graph[i][j] = bricks[i * 10 + j];
            visited[i][j] = 0;
        }
    }

    dfs(0, 0, graph, visited);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            lights[i * 10 + j] = visited[i][j];
        }
    }

    return lights;
}
