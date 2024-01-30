#include <stdio.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 10

char maze[ROWS][COLS] = {
    "1111111111",
    "1P000000E1",
    "1111111111",
    "1000000001",
    "1111111111"
};

bool visited[ROWS][COLS] = {false};

bool isValid(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != '1' && !visited[x][y]);
}

bool hasPath(int startX, int startY) {
    int stack[ROWS * COLS][2];
    int top = -1;

    stack[++top][0] = startX;
    stack[top][1] = startY;

    while (top >= 0) {
        int x = stack[top][0];
        int y = stack[top][1];
        top--;

        visited[x][y] = true;

        if (maze[x][y] == 'E') {
            return true;
        }

        int moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < 4; i++) {
            int newX = x + moves[i][0];
            int newY = y + moves[i][1];

            if (isValid(newX, newY)) {
                stack[++top][0] = newX;
                stack[top][1] = newY;
            }
        }
    }

    return false;
}

int main() {
    int startX = -1, startY = -1, exitX = -1, exitY = -1;

    // Find the starting position (P) and the exit (E)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 'P') {
                startX = i;
                startY = j;
            } else if (maze[i][j] == 'E') {
                exitX = i;
                exitY = j;
            }
        }
    }

    if (startX == -1) {
        printf("Error: Starting position (P) not found.\n");
        return 0;
    }

    if (exitX == -1) {
        printf("Error: Exit position (E) not found.\n");
        return 0;
    }

    if (hasPath(startX, startY)) {
        printf("There exists a path from the Player to the Exit.\n");
        return 1;
    } else {
        printf("No valid path from the Player to the Exit.\n");
        return 0;
    }
}