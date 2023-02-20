#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> //memmove

#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7
void finish()
{
    clear();
    refresh();
    endwin();
}
#define APPLE '#'
void init()
{
    initscr();
    noecho();
    timeout(0);
    curs_set(0);
    if(has_colors())
    {
        start_color();
        if (use_default_colors() != ERR) {
            init_pair(COLOR_BLACK, -1, -1);
            init_pair(COLOR_GREEN, COLOR_GREEN, -1);
            init_pair(COLOR_WHITE, COLOR_WHITE, -1);
            init_pair(COLOR_RED, COLOR_RED, -1);
            init_pair(COLOR_CYAN, COLOR_CYAN, -1);
            init_pair(COLOR_MAGENTA, COLOR_MAGENTA, -1);
            init_pair(COLOR_BLUE, COLOR_BLUE, -1);
            init_pair(COLOR_YELLOW, COLOR_YELLOW, -1);
        } else {
            init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
            init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
            init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
            init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
            init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
            init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
            init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
        } 
    }
}

char **board;
#define POINT '*'
void init_board()
{
    int i, j;
    board = (char **)malloc(LINES * sizeof(char *));
    if (!board)
    {
        finish();
    }
    for (i = 0; i < LINES; i++)
    {
        board[i] = (char *)malloc(COLS * sizeof(char));
        if (!board[i])
        {
            finish();
        }
    }

    for (i = 0; i < LINES; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

#define MAX_ZNAKE_LENGHT 100

typedef struct Znake
{
    int row;
    int col;
} Znake;

Znake znake[MAX_ZNAKE_LENGHT];

int tmpZnSize = 1;
int znakeLenght = 5;

void put(int row, int col, char ch)
{
    board[row][col] = ch;
    move(row, col);
    addch(ch);
}

Znake get_random_pos()
{
    Znake rez;
    do
    {
        rez.row = rand() % LINES;
        rez.col = rand() % COLS;
    } while (board[rez.row][rez.col] != ' ');

    return rez;
}

typedef enum Direction
{
    BEGIN,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    STOP
} Direction;

Direction direction = BEGIN;
int keypress;
void change_dir()
{

    if (keypress = wgetch(stdscr)) // т к установлен timeout  то wgetch не блокирующий
    {
        if (keypress == ERR)
        {
            return;
        }
    }
    if (keypress == 'a')
        direction = LEFT;
    else if (keypress == 'd')
        direction = RIGHT;
    else if (keypress == 's')
    {
        direction = DOWN;
    }
    else if (keypress == 'w')
        direction = UP;
    else if (keypress == 'q')
        finish();
}

void new_head()
{
    if (direction == RIGHT)
    {
        znake[0].col++;
    }
    else if (direction == LEFT)
    {
        znake[0].col--;
    }
    else if (direction == UP)
    {
        znake[0].row--;
    }
    else if (direction == DOWN)
    {
        znake[0].row++;
    }
}

int verify_head()
{
    if (znake[0].row < 0 || znake[0].col < 0 || znake[0].row >= LINES || znake[0].col >= COLS)
    {
        return -1;
    }

    if (board[znake[0].row][znake[0].col] != ' ' && board[znake[0].row][znake[0].col] != APPLE)
    {
        return -2;
    }

    return 10;
}

void put_apple()
{
    Znake pos = get_random_pos();
    attron(COLOR_PAIR(COLOR_YELLOW));
    put(pos.row, pos.col, APPLE);
}


int eatApple = 0;
void logic()
{

    memmove(&znake[1], &znake[0], sizeof(Znake) * tmpZnSize);
    new_head(); // новый шаг новая голова
    if (verify_head() < 0)
    {
        direction = STOP;
        return;
    }
    if(board[znake[0].row][znake[0].col] == APPLE)
    {
        eatApple = 1;
    znakeLenght++;
    }
    attron(COLOR_PAIR(COLOR_GREEN));
    put(znake[0].row, znake[0].col, POINT); // вывод на экран одного символа
    if (tmpZnSize < znakeLenght)            // для начала змейки чтобы она из 1 в 5 выросла
        tmpZnSize++;
    else
    {
        put(znake[tmpZnSize].row, znake[tmpZnSize].col, ' '); // удаляем хвост
    }
    if(eatApple == 1)
    {
        eatApple = 0;
        put_apple();
    }
}

int game = 1;

int main(int argv, char *argc[])
{
    srand((unsigned)time(NULL));
    init();
    init_board();
    attron(COLOR_PAIR(COLOR_GREEN));
    znake[0] = get_random_pos();
    put(znake[0].row, znake[0].col, POINT);
    put_apple();
    while (game != 0)
    {
        if (direction != STOP)
        {
            change_dir();
            if (direction != BEGIN)
                logic();
        }
        else
        {
            if (keypress = wgetch(stdscr)) // т к установлен timeout  то wgetch не блокирующий
            {
                if (keypress == ERR)
                {
                }
                else if (keypress == 'q')
                    game = 0;
            }
        }
        napms(100);
    }
    finish();
    printf("end\n");
    return 0;
}