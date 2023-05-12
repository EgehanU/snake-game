#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <vector>

struct Point {
    int x;
    int y;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// initialize the game
void initializeGame();

// generate a new food item
void generateFood();

// update the game state
void updateGame();

// handle user input
void handleInput();

// draw the game on the screen
void drawGame();

// check if the snake has collided with itself
bool hasCollided();

// check if the snake has collided with the food
bool hasEatenFood();

// exit the game
void exitGame();


const int GAME_WIDTH = 40;
const int GAME_HEIGHT = 20;
const char SNAKE_HEAD = '@';
const char SNAKE_BODY = '*';
const char FOOD = 'X';


std::vector<Point> snake;
Point food;
Direction direction;
bool gameover;

int main() {
    initializeGame();

    // Game loop
    while (!gameover) {
        handleInput();
        updateGame();
        drawGame();

        Sleep(100); 
    }

    exitGame();
    return 0;
}



void initializeGame() {
    srand(static_cast<unsigned>(time(0)));

    // Initialize snake
    snake.push_back({GAME_WIDTH / 2, GAME_HEIGHT / 2});
    snake.push_back({GAME_WIDTH / 2 - 1, GAME_HEIGHT / 2});
    snake.push_back({GAME_WIDTH / 2 - 2, GAME_HEIGHT / 2});

    generateFood();
    
    direction = RIGHT;
    gameover = false;
}

void generateFood() {
    food.x = rand() % (GAME_WIDTH - 2) + 1;
    food.y = rand() % (GAME_HEIGHT - 2) + 1;
}


void updateGame() {

    Point newHead = snake.front();

    switch (direction) {
        case UP:
            newHead.y--;
            break;
        case DOWN:
            newHead.y++;
            break;
        case LEFT:
            newHead.x--;
            break;
        case RIGHT:
            newHead.x++;
            break;
    }

    // Check if the snake has collided with itself or the game boundaries
    if (newHead.x < 0 || newHead.x >= GAME_WIDTH || newHead.y < 0 || newHead.y >= GAME_HEIGHT || hasCollided()) {
        gameover = true;
        return;
    }

    // Check if the snake has eaten the food
    if (newHead.x == food.x && newHead.y == food.y) {
        // Generate the meal
        generateFood();
        snake.push_back(newHead);
    } else {
        // remove the tail
        snake.pop_back();
        snake.insert(snake.begin(), newHead);
    }
}

void handleInput() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 'w' || key == 'W') {
            if (direction != DOWN) {
                direction = UP;
            }
        } else if (key == 's' || key == 'S') {
            if (direction != UP) {
                direction = DOWN;
            }
        } else if (key == 'a' || key == 'A') {
            if (direction != RIGHT) {
                direction = LEFT;
            }
        } else if (key == 'd' || key == 'D') {
            if (direction != LEFT) {
                direction = RIGHT;
            }
        } else if (key == 27) { 
            gameover = true;
        }
    }
}

void drawGame() {
    system("cls");

    // Draw game border
    for (int i = 0; i < GAME_WIDTH; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    // Draw snake and food
    for (int y = 0; y < GAME_HEIGHT; y++) {
        for (int x = 0; x < GAME_WIDTH; x++) {
            if (x == 0 || x == GAME_WIDTH - 1) {
                std::cout << "#";
            } else if (x == food.x && y == food.y) {
                std::cout << FOOD;
            } else {
                bool isSnakeBody = false;
                for (const Point& p : snake) {
                    if (p.x == x && p.y == y) {
                        std::cout << (p.x == snake.front().x && p.y == snake.front().y ? SNAKE_HEAD : SNAKE_BODY);
                        isSnakeBody = true;
                        break;
                    }
                }
                if (!isSnakeBody) {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    // Draw game border
    for (int i = 0; i < GAME_WIDTH; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
}


bool hasCollided() {
    Point head = snake.front();
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].x == head.x && snake[i].y == head.y) {
            return true;
        }
    }
    return false;
}

bool hasEatenFood() {
    Point head = snake.front();
    return (head.x == food.x && head.y == food.y);
}

void exitGame() {
    system("cls");
    if (snake.size() < 20)
        std::cout << "\nGame over beta cuck! Your score: " << snake.size() << std::endl;
    else if (snake.size() >= 20)
        std::cout << "Game over champ! Your score: " << snake.size() << std::endl;
}


       

