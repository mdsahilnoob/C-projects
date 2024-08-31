#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#define ROWS 20
#define COLS 60
#define SNAKE_CHAR 'O'
#define FOOD_CHAR 'X'
#define EMPTY_CHAR ' '

struct Node {
    int x, y;
    struct Node* next;
};



int main() {
    int score = 0;
    int direction = 0; // 0:up, 1:right, 2:down, 3:left

    char grid[ROWS][COLS];
    struct Node* head = NULL;

    // Initialize the game board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if(i == 0 || i == ROWS-1 || j == 0 || j == COLS-1){
                grid[i][j] = '#';
            } else {
                grid[i][j] = EMPTY_CHAR;
            }
        }
    }

    // Initialize the snake
    head = (struct Node*)malloc(sizeof(struct Node));
    head->x = ROWS / 2;
    head->y = COLS / 2;
    head->next = NULL;
    grid[head->x][head->y] = SNAKE_CHAR;

    // Generate initial food
    int foodX = rand() % (ROWS-2) + 1;
    int foodY = rand() % (COLS-2) + 1;
    grid[foodX][foodY] = FOOD_CHAR;

    // Game loop
    while (1) {
        // Handle user input
        if (kbhit()) {
            char ch = getch();
            if (ch == 'w' && direction != 2) {
                direction = 0;
            } else if (ch == 'd' && direction != 3) {
                direction = 1;
            } else if (ch == 's' && direction != 0) {
                direction = 2;
            } else if (ch == 'a' && direction != 1) {
                direction = 3;
            }
        }

        // Update snake position
        struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
        newHead->next = head;
        switch (direction) {
            case 0:
                newHead->x = head->x - 1;
                newHead->y = head->y;
                break;
            case 1:
                newHead->x = head->x;
                newHead->y = head->y + 1;
                break;
            case 2:
                newHead->x = head->x + 1;
                newHead->y = head->y;
                break;
            case 3:
                newHead->x = head->x;
                newHead->y = head->y - 1;
                break;
        }

        // Check for collisions
        if (newHead->x <= 0 || newHead->x >= ROWS-1 || newHead->y <= 0 || newHead->y >= COLS-1) {
            printf("Game Over!\n");
            break;
        }

        struct Node* current = head;
        while (current != NULL && current->next != NULL) {
            if (current->next->x == newHead->x && current->next->y == newHead->y) {
                printf("Game Over!\n");
                break;
            }
            current = current->next;
        }

        // Check for food
        if (newHead->x == foodX && newHead->y == foodY) {
            score++;
            grid[foodX][foodY] = EMPTY_CHAR;

            // Generate new food within the main function
            do {
                foodX = rand() % ROWS;
                foodY = rand() % COLS;
            } while (grid[foodX][foodY] != EMPTY_CHAR);

            grid[foodX][foodY] = FOOD_CHAR;
        }

        head = newHead;
        grid[head->x][head->y] = SNAKE_CHAR;

        // Draw the game
        system("cls");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                printf("%c", grid[i][j]);
            }
            printf("\n");
        }

        printf("Score: %d\n", score);
        fflush(stdout);
        usleep(50000000);
    }

    return 0;
}