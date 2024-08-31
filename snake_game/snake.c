#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#define ROWS 20
#define COLS 20
#define SNAKE_CHAR '0'
#define FOOD_CHAR 'X'
#define EMPTY_CHAR ' '

struct Node{
    int x,y;
    struct Node* next;
};

void initializeGameBoard(char grid[ROWS][COLS]){
    // Initialize the game board
    for(int i=0; i<ROWS; i++){
        for(int j=0;j<COLS; j++){
            if(i == 0 || i == ROWS-1 || j == 0 || j == COLS-1){
                grid[i][j] = '#';
            } else {
                grid[i][j] = EMPTY_CHAR;
            }
        }
    }
}

void drawGameBoard(char grid[ROWS][COLS], int score){
    printf("\x1B[2J");
    for(int i=0; i < ROWS; i++){
        for(int j=0; j < COLS; j++){
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    fflush(stdout);
}

int kbhit(void){

    return 0;
}

int getch(void){
    
    return 0;
}

int main(){
    int score = 0;
    int direction = 0; // 0:up, 1:right, 2:down, 3:left

    char grid[ROWS][COLS];
    struct Node* head = NULL;

    srand(time(NULL));

    initializeGameBoard(grid);

    //initialize the snake
    head = (struct Node*)malloc(sizeof(struct Node));
    head->x = ROWS/2;
    head->y = COLS/2;
    head->next = NULL;
    grid[head->x][head->y] = SNAKE_CHAR;

    //generate initial food
    int foodX, foodY;
    do{
        foodX = rand() % (ROWS - 2) + 1;
        foodY = rand() % (COLS - 2) + 1;
    }while (grid[foodX][foodY] != EMPTY_CHAR);
    grid[foodX][foodY] = FOOD_CHAR;

    //game loop
    while(1){
        //handle user input
        if(kbhit()){
            char ch = getch();
            if(ch == 'w' && direction != 2){
                direction = 0;
            } else if(ch == 'd' && direction != 3){
                direction = 1;
            } else if(ch == 's' && direction != 0){
                direction = 2;
            } else if(ch == 'a' && direction != 1){
                direction = 3;
            }
        }
        //update snake position
        struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
        newHead->next = head;
        switch(direction){
            case 0:
                newHead->x = head->x -1;
                newHead->y = head->y;
                break;
            case 1:
                newHead->x = head->x;
                newHead->y = head->y+1;
                break;
            case 2:
                newHead->x = head->x+1;
                newHead->y = head->y;
                break;
            case 3:
                newHead->x = head->x;
                newHead->y = head->y-1;
                break;
        }
        //check for collisions
        //wall collision
        if(newHead->x < 1 || newHead->x >=ROWS-1 || newHead->y < 1 || newHead->y >= COLS-1){
            printf("Game Over! You hit a wall\n");
            break;
        }
        //self collision
        struct Node* current = head;
        while(current != NULL){
            if(current->x == newHead->x && current->y == newHead->y){
                printf("Game Over! You ran into yourself\n");
                return 0;
            }
            current = current->next;
        }
        //check for food
        if(grid[newHead->x][newHead->y] == FOOD_CHAR){
            score++;
            do{
            foodX = rand() % (ROWS - 2) + 1;
            foodY = rand() % (COLS - 2) + 1;
            } while (grid[foodX][foodY] != EMPTY_CHAR);
            grid[foodX][foodY] = FOOD_CHAR;
        } else {
            // remove tail
            struct Node* temp = head;
            while(temp->next->next != NULL){
                temp = temp->next;
            }
            grid[temp->next->x][temp->next->y] = EMPTY_CHAR;
            free(temp->next);
            temp->next = NULL;
        }

        //update head
        head = newHead;
        grid[head->x][head->y] = SNAKE_CHAR;

        //Draw the game board
        drawGameBoard(grid,score);


        // pause for 50 milliseconds
        struct timespec ts = {0, 50000000};
        nanosleep(&ts, NULL);
    }
    return 0;
}

void initializeGameBoard(char grid[ROWS][COLS]);
void drawGameBoard(char grid[ROWS][COLS], int score);
int kbhit(void);
int getch(void);