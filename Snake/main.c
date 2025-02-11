#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>


#define WIDTH 30
#define HEIGHT 20
#define INITIAL_LENGTH 3
#define MAX_COUNT_LIVES 3

typedef enum { //цвета для змейки
   RED = 1,
   GREEN,
   YELLOW,
   WHITE,
   BLUE,
} colors_t;


typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[WIDTH * HEIGHT]; //длина змейки максимальная - WIDTH * HEIGHT по идее никто не достигнет границ массива
    int length;
    int direction; // 0: UP, 1: RIGHT, 2: DOWN, 3: LEFT
} Snake;

void init();
void draw(Snake *snake, Point *food);
void input(Snake *snake);
void logic(Snake *snake, Point *food);
void generate_food(Point *food, Snake *snake);
int collision(Snake *snake);
int lives_end = MAX_COUNT_LIVES;
int count_food = 0;
int game_over = 0;
int speed_game = 100000;
int zone_comforta = 10;
colors_t color_snake = WHITE;//устанавливаем цвет по умолчанию белый

int main() {
    Snake snake;
    Point food;


    init();
    snake.length = INITIAL_LENGTH;
    snake.direction = 1; // Начинаем с движения вправо

    // Инициализация тела змейки для движения вправо
    for (int i = 0; i < snake.length; i++) {
        snake.body[i].x = INITIAL_LENGTH - i - 1;
        snake.body[i].y = HEIGHT / 2;
    }

    generate_food(&food, &snake);

    while (game_over < MAX_COUNT_LIVES) {
        draw(&snake, &food); //
        input(&snake);
        logic(&snake, &food);
        if (collision(&snake)) {
            game_over++;
            snake.length = INITIAL_LENGTH;
            color_snake = WHITE;
            snake.direction = 1;
            if(game_over < MAX_COUNT_LIVES) { //чтобы в конце не сбросилось количество очков
                count_food = 0;
            }
            zone_comforta = 10;
            for (int i = 0; i < snake.length; i++) {
                snake.body[i].x = INITIAL_LENGTH - i - 1;
                snake.body[i].y = HEIGHT / 2;
            }
            generate_food(&food, &snake);

        }
        lives_end = MAX_COUNT_LIVES - game_over; //для отображения количества жизней
        if (count_food > zone_comforta) {
            speed_game -= 200; //усложняем игру
            zone_comforta += 10; //переход на следующий уровень комфорта
        }
        usleep(speed_game); // Задержка для управления скоростью игры
    }
    //окончание игры
    endwin();
    printf("Game Over!\nYour score: %d\n", count_food);
    return 0;
}

void init() {
    initscr(); // Инициализация ncurses
    cbreak(); // Отключение буферизации ввода
    noecho(); // Не отображать вводимые символы
    keypad(stdscr, TRUE); // Включение поддержки функциональных клавиш
    curs_set(0); // Скрыть курсор
    srand(time(NULL)); // Инициализация генератора случайных чисел
    timeout(100); // Установка таймера для получения ввода

    start_color(); // Инициализация цветов

    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);

}

void draw(Snake *snake, Point *food) {
    clear(); // Очистка экрана
    mvprintw(0, WIDTH + 4, "Lives: %d", lives_end);
    mvprintw(0, WIDTH + 12, " | ");
    mvprintw(0, WIDTH + 16, "Score: %d", count_food);
    mvprintw(22, 0, "Press the button to exit : F10");
    // Рисуем границы
    for (int i = 0; i < WIDTH + 2; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT + 1, i, "#");
    }
    for (int i = 0; i < HEIGHT + 2; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH + 1, "#");
    }

    // Рисуем змейку, цвет зависит от количества съеденной еды
    switch (count_food) {

        case 2: color_snake = YELLOW; break; //2 еды желтый
        case 4: color_snake = GREEN; break; //4 еды зеленый
        case 8: color_snake = BLUE; break; //8 еды синий
        case 10: color_snake = RED; break; //10 еды красный

    }
    attron(COLOR_PAIR(color_snake)); //применяем цвет
    mvprintw(snake->body[0].y + 1, snake->body[0].x + 1, "@");
    for (int i = 1; i < snake->length; i++) {
        mvprintw(snake->body[i].y + 1, snake->body[i].x + 1, "O");
    }
    attroff(COLOR_PAIR(color_snake));//отключаем цвет, чтобы всё остальное не красилось

    // Рисуем еду
    mvprintw(food->y + 1, food->x + 1, "*");

    refresh(); // Обновление экрана
}

void input(Snake *snake ) {
    int key = getch();
    if(isalpha(key)) { //проверяем, если нажата буквенная клавиша
        key = tolower(key); //преобразуем в нижний регистр
    }
    switch (key) {
        case KEY_UP:
        case 'w':
            if (snake->direction != 2) snake->direction = 0;
            break;
        case KEY_RIGHT:
        case 'd':
            if (snake->direction != 3) snake->direction = 1;
            break;
        case KEY_DOWN:
        case 's':
            if (snake->direction != 0) snake->direction = 2;
            break;
        case KEY_LEFT:
        case 'a':
            if (snake->direction != 1) snake->direction = 3;
            break;
        case KEY_F(10):
            game_over = 3; //выход из игры
            break;
    }
}

void logic(Snake *snake, Point *food) {
    Point new_head = snake->body[0];

    // Обновление координат головы змейки
    switch (snake->direction) {
        case 0: new_head.y--; break; // Вверх
        case 1: new_head.x++; break; // Вправо
        case 2: new_head.y++; break; // Вниз
        case 3: new_head.x--; break; // Влево
    }

    // Сдвиг тела змейки
    for (int i = snake->length; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[0] = new_head;

    // Проверка на поедание еды
    if (new_head.x == food->x && new_head.y == food->y) {

        snake->length++;
        count_food++;
        generate_food(food, snake);
    }
}

void generate_food(Point *food, Snake *snake) {
    int valid_position;
    do {
        valid_position = 1;
        food->x = rand() % WIDTH;
        food->y = rand() % HEIGHT;

        // Проверка, чтобы еда не появлялась на змейке
        for (int i = 0; i < snake->length; i++) {
            if (snake->body[i].x == food->x && snake->body[i].y == food->y) {
                valid_position = 0;
                break;
            }
        }
    } while (!valid_position);
}

int collision(Snake *snake) {
    // Проверка столкновения со стенами
    if (snake->body[0].x < 0 || snake->body[0].x >= WIDTH ||
        snake->body[0].y < 0 || snake->body[0].y >= HEIGHT) {
        return 1; // Опа, Хьюстон у нас проблемы
    }

    // Проверка столкновения с собственным телом
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[0].x == snake->body[i].x &&
            snake->body[0].y == snake->body[i].y) {
            return 1; // Опа, Хьюстон у нас проблемы
        }
    }

    return 0; // Игра продолжается
}

