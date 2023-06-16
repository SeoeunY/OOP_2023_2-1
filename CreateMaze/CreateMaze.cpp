#include <iostream>
#include <Windows.h>    // COORD
#include <time.h>       // time()
using namespace std;

struct Point {
    int x;
    int y;
};

void shuffleArray(int array[], int size)
{
    int i, r, temp;

    for (i = 0; i < (size - 1); ++i)
    {
        r = i + (rand() % (size - i));
        temp = array[i];
        array[i] = array[r];
        array[r] = temp;
    }
}

void generateMap(int y, int x, int map[61][61], int row, int col)
{
    int i, nx, ny;
    int directions[4] = { 0,1,2,3 };//방위
    int DIR[4][2] = { {0, -2},{0, 2},{-2, 0},{2, 0} };//좌표 이동

    map[y][x] = 1;


    shuffleArray(directions, 4);//방위 무작위

    for (i = 0; i < 4; i++)
    {
        // 다음 위치를 구한다.
        nx = x + DIR[directions[i]][0];//무작위 방위 순서에 맞게 좌표 이동
        ny = y + DIR[directions[i]][1];

        bool range = (ny < 2 * row && ny > 0) && (nx < 2 * col && nx > 0);//범위 확인

        if (range && map[ny][nx] == 0)
        {
            // 세로 축 이동인 경우
            if (ny != y)
                map[(ny + y) / 2][x] = 1;//벽 뚫어
            // 가로 축 이동인 경우
            else
                map[y][(x + nx) / 2] = 1;
            map[ny][nx] = 1;//현재 좌표 길 표시
            generateMap(ny, nx, map, row, col);
        }
    }
}

bool isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && x <= 2 * cols + 1 && y >= 0 && y <= 2 * rows + 1);
}

bool isDestination(Point curr, Point dest) {
    return (curr.x == dest.x && curr.y == dest.y);
}

void BFS(int map_bfs[61][61], Point start, Point end, int rows, int cols) {
    Point q[3600];
    int front = -1;
    int rear = -1;

    bool visited[61][61] = { false, };
    Point parent[61][61]{};
    visited[start.y][start.x] = true;
    front = rear = 0;
    q[rear] = start;
    parent[start.y][start.x] = start;

    while (front<=rear) {
        Point curr = q[front];
        front++;

        if (isDestination(curr, end)) {
            // 도착점에 도달했으므로 경로 출력
            int row = end.y;
            int col = end.x;

            while (!(parent[row][col].y == row && parent[row][col].x == col)) {
                int tempRow = parent[row][col].y;
                int tempCol = parent[row][col].x;
                map_bfs[row][col] = 3;
                row = tempRow;
                col = tempCol;
            }
            map_bfs[start.y][start.x] = 3;

            return;
        }

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (isValid(ny, nx, rows, cols) && !visited[ny][nx] && map_bfs[ny][nx] != 0) {
                visited[ny][nx] = true;
                rear++;
                q[rear] = { nx,ny };
                parent[ny][nx] = curr;
                map_bfs[ny][nx] = 2;
            }
        }
    }
}

void DFS_2(int map_dfs[61][61], Point start, Point end, int rows, int cols) {
    Point stack[900]{};
    int top = -1;

    bool visited_dfs[61][61] = { false, };
    Point parent_dfs[61][61]{};
    parent_dfs[start.y][start.x] = start;
    visited_dfs[start.y][start.x] = true;

    top++;
    stack[top] = start;

    while (top != -1) {
        Point cur = stack[top];
        int x = cur.x;
        int y = cur.y;

        if (cur.x == end.x && cur.y == end.y) {
            //도착

            map_dfs[stack[top].y][stack[top].x] = 2;
            
            int row = end.y;
            int col = end.x;

            while (!(parent_dfs[row][col].y == row && parent_dfs[row][col].x == col)) {
                int tempRow = parent_dfs[row][col].y;
                int tempCol = parent_dfs[row][col].x;
                map_dfs[row][col] = 3;
                row = tempRow;
                col = tempCol;
            }
            map_dfs[start.y][start.x] = 3;

            //출력
            return;
        }

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        int i;
        for (i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (isValid(ny, nx, rows, cols) && !visited_dfs[ny][nx] && map_dfs[ny][nx] != 0) {
                visited_dfs[ny][nx] = true;
                top++;
                stack[top] = { nx,ny };
                parent_dfs[ny][nx] = cur;
                map_dfs[ny][nx] = 2;
                break;
            }
        }
        if (i == 4) {//막다른 길
            map_dfs[stack[top].y][stack[top].x] = 2;
            top--;
        }
    }
}

int main()
{
    int map[61][61] = { 0, };

    int row, col;
    cin >> row >> col;//미로 크기 입력

    int x = 1 + rand() % (col - 1);//시작 지점 무작위
    int y = 1 + rand() % (row - 1);
    if (x % 2 == 0)
        x--;
    if (y % 2 == 0)
        y--;

    srand((unsigned int)time(NULL));

    generateMap(y, x, map, row, col);//생성 함수 호출


    int map_bfs[61][61] = { 0, };
    int map_dfs[61][61] = { 0, };
    
    for (int i = 0; i < 61; i++) {
        for (int j = 0; j < 61; j++) {
            map_dfs[i][j] = map[i][j];
            map_bfs[i][j] = map[i][j];
        }
    }

    int a, b;
    Point start;
    cout << "Start Point";
    cin >> a >> b;//미로 좌표
    start.x = a * 2 - 1;//배열 좌표
    start.y = b * 2 - 1;

    Point end;
    cout << "End Point";
    cin >> a >> b;
    end.x = a * 2 - 1;
    end.y = b * 2 - 1;
    

    BFS(map_bfs, start, end, row, col);
   
    for (int i = 0; i < 2 * row + 1; i++) {
        for (int j = 0; j < 2 * col + 1; j++) {
            cout << map_bfs[i][j];
        }
        cout << endl;
    }

    DFS_2(map_dfs, start, end, row, col);

    return 0;
}