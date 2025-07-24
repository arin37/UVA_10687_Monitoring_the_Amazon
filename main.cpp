#include <iostream>

using namespace std;
#define SIZE 1005

int numOfStations, x, y, sX[SIZE], sY[SIZE], graphLink[SIZE][SIZE], dist[SIZE][SIZE], visited[SIZE], ans;

void init() {
    ans = 1;
    for(int i = 0; i < SIZE; i++) {
        visited[i] = 0;
        for(int j = 0; j < SIZE; j++) {
            graphLink[i][j] = 0;
            dist[i][j] = 0;
        }
    }
}

void read() {
    for(int i = 0; i < numOfStations; i++) {
        cin >> sX[i] >> sY[i];
    }
}

int calculateDistance(int sA, int sB) {
    int d = (((sX[sA]-sX[sB])*(sX[sA]-sX[sB])) + ((sY[sA]-sY[sB])*(sY[sA]-sY[sB])));
    return d;
}

void findLink(int parent) {
    int minDist, minStation;
    for(int m = 0; m < 2; m++) {
        minDist = 999999;
        for(int i = 0; i < numOfStations; i++) {
            if(i == parent) {
                continue;
            }
            if(dist[parent][i] < minDist) {
                minDist = dist[parent][i];
                minStation = i;
            }
            else if(dist[parent][i] == minDist) {
                if(sX[i] < sX[minStation]) {
                    minDist = dist[parent][i];
                    minStation = i;
                }
                else if(sX[i] == sX[minStation]) {
                    if(sY[i] < sY[minStation]) {
                        minDist = dist[parent][i];
                        minStation = i;
                    }
                }
            }
        }
        graphLink[parent][minStation] = 1;
        dist[parent][minStation] = 9999999;
    }
}

void dfs(int root) {
    for(int i = 0; i < numOfStations; i++) {
        if(graphLink[root][i] && !visited[i]) {
            visited[i] = 1;
            dfs(i);
        }
    }
}

void solveCase() {
    for(int i = 0; i < numOfStations; i++) {
        for(int j = i+1; j < numOfStations; j++) {
            dist[i][j] = dist[j][i] = calculateDistance(i, j);
        }
       findLink(i);
    }

    visited[0] = 1;
    dfs(0);

    for(int i = 0; i < numOfStations; i++) {
        if(!visited[i]) {
            ans = 0;
        }
    }
}

void print() {
    if(ans) {
        cout << "All stations are reachable." << endl;
    }
    else {
        cout << "There are stations that are unreachable." << endl;
    }
}

int main()
{
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    while((cin >> numOfStations) && (numOfStations)) {
        init();
        read();
        solveCase();
        print();
    }
    return 0;
}
