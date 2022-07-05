#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

string highscore_name[10];
int highscore[10];
int sleep_values[11] = { 0, 400, 350, 300, 250, 200, 150, 100, 50, 20, 0 };

void main_menu(int& select)
{
    system("cls");
    cout << "Use UP and DOWN buttons to scroll, ENTER to select\n\n\n";
    cout << "\n\t\tSnake game\n\n";
    if (select < 1) select = 5;
    if (select > 5) select = 1;
    if (select == 1) cout << "--> ";
    cout << "Start" << endl;
    if (select == 2) cout << "--> ";
    cout << "Instructions" << endl;
    if (select == 3) cout << "--> ";
    cout << "Options" << endl;
    if (select == 4) cout << "--> ";
    cout << "High Scores" << endl;
    if (select == 5) cout << "--> ";
    cout << "Quit" << endl;

}
void options_menu(int& select)
{
    if (select < 1) select = 2;
    if (select > 2) select = 1;
    system("cls");
    if (select == 1) cout << "--> ";
    cout << "Speed" << endl;
    if (select == 2) cout << "--> ";
    cout << "Difficulty Level" << endl;
}
void speed_menu(int& level)
{
    if (level < 1) level = 1;
    if (level > 10) level = 10;
    system("cls");
    cout << "\n  Level " << level << endl << endl;
    cout << " ---------- " << endl;
    cout << "|";
    for (int i = 0; i < level; i++)
        cout << "#";
    for (int i = level; i < 10; i++)
        cout << " ";
    cout << "|\n ---------- " << endl;
}
void difficulty_menu(int& select, bool mushrooms, bool hit_wall, bool walls)
{
    if (select > 3) select = 1;
    if (select < 1) select = 3;
    system("cls");
    if (select == 1) cout << "--> ";
    cout << "mushrooms ";
    if (mushrooms) cout << "ON\n";
    else cout << "OFF\n";
    if (select == 2) cout << "--> ";
    cout << "die when hit a wall ";
    if (hit_wall) cout << "ON\n";
    else cout << "OFF\n";
    if (select == 3) cout << "-->";
    cout << "additional walls ";
    if (walls) cout << "ON\n";
    else cout << "OFF\n";
}
void highscore_menu(int select)
{
    if (select > 4) select = 3;
    if (select < 3) select = 4;
    system("cls");
    if (select == 3) cout << "--> ";
    cout << "See leaderboard\n";
    if (select == 4) cout << "--> ";
    cout << "Clear leaderboard\n";

}
void print_highscores()
{
    system("cls");
    cout << "\n\tHigh scores\n\n";
    for (int i = 0; i < 10; i++)
    {
        if (i == 9)  cout << "10) " << highscore_name[9];
        else cout << i + 1 << ")  " << highscore_name[i];
        for (int j = 0; j < 20 - highscore_name[i].size(); j++)
            cout << " ";
        cout << "      " << highscore[i] << endl << endl;
    }
}
void print_Instructions()
{
    system("cls");
    cout << "\tUse 'w' to change the snake's direction to UP, 'a' for LEFT, 's' for DOWN and 'd' for RIGHT.\n";
    cout << "Press 'P' or Spacebar to pause and resume the game. \n";
    cout << "The purpose is to get the fruits 'F', and to avoid the mushrooms 'M'.\n";
    cout << "\nPress ESC for main menu";
}
void change_highscores(int score)
{
    string name;
    for (int i = 0; i < 10; i++)
        if (score > highscore[i]) {
            cout << "\nYou are in High Scores!\n\nPlease enter your name: ";
            cin >> name;
            for (int j = 10; j > i; j--)
            {
                highscore[j] = highscore[j - 1];
                highscore_name[j] = highscore_name[j - 1];
            }
            highscore[i] = score;
            highscore_name[i] = name;
            break;
        }
}

class snake
{
    const int width=15, height=15;
    bool gameOver, mushroom_break, walls, mushrooms, hit_wall;
    int ntail, mushroom_cnt, mushroom_break_cnt, x, y, fx, fy, mx, my, score;
    int xtail[180], ytail[180], highscore[10];
    string name;
    enum key { STOP = 0, LEFT, RIGHT, UP, DOWN, ESC, PAUSE };
    key KEY, last_key;
public:
    snake()
    {
        mushrooms = true;
        hit_wall = false;
        walls = false;
    }
    void generateFruit();
    void generateMushroom();
    void setup();
    void draw();
    void input();
    void logic();
    void set_mushrooms();
    void set_hit_walls();
    void set_walls();
    bool get_gameOver();
    int get_score();
    bool get_mushrooms();
    bool get_hit_walls();
    bool get_walls();
};
void snake::generateFruit()
{
    fx = (rand() % (width - 2)) + 1;
    fy = (rand() % (height - 2)) + 1;
    for (int i = 0; i < ntail; i++)
        if (fx == xtail[i] && fy == ytail[i]) { generateFruit(); }
    if (walls == true && fy == 9 && fx > 4 && fx < 10)  generateFruit();
}
void snake::generateMushroom()
{
    mx = (rand() % (width - 2)) + 1;
    my = (rand() % (height - 2)) + 1;
    for (int i = 0; i < ntail; i++)
        if (mx == xtail[i] && my == ytail[i]) { generateMushroom(); break; }
    if (walls == true && my == 9 && mx > 4 && mx < 10)  generateMushroom();
    if (mx == fx && my == fy)  generateMushroom();
}
void snake::setup()
{
    x = width / 2;
    y = height / 2;
    generateFruit();
    ntail = 0;
    mushroom_cnt = 0;
    mushroom_break_cnt = 0;
    mushroom_break = true;
    mx = -2;
    my = -2;
    gameOver = false;
    score = 0;
    for (int i = 0; i < 100; i++)
    {
        xtail[i] = -1;
        ytail[i] = -1;
    }
}
void snake::draw()
{
    if (mushrooms)
    {
        if (!mushroom_break) mushroom_cnt++;
        if (mushroom_cnt >= 50) {
            mushroom_break = true;
            mushroom_cnt = 0;
            mx = -2;
            my = -2;

        }
        if (mushroom_break) {
            mushroom_break_cnt++;
            if (mushroom_break_cnt >= 60) {
                mushroom_break_cnt = 0;
                mushroom_break = false;
                generateMushroom();
            }
        }
    }

    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bool printed = false;


            if (i == y && x == j)  cout << "O";
            else if (i == fy && j == fx) cout << "F";
            else if (walls == true && j > 4 && j < 10 && i == 9) cout << "#";
            else if (i == my && j == mx) cout << "M";
            else if (j == 0 || j == height - 1 || i == 0 || i == width - 1) cout << "#";
            else
            {
                for (int k = 0; k < ntail; k++)
                    if (i == ytail[k] && j == xtail[k]) {
                        cout << "o";
                        printed = true;
                    }
                if (!printed) cout << " ";
            }
        }
        cout << endl;
    }
}
void snake::input()
{
    last_key = KEY;
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            KEY = LEFT;
            break;
        case 's':
            KEY = DOWN;
            break;
        case 'd':
            KEY = RIGHT;
            break;
        case 'w':
            KEY = UP;
            break;
        case 27:
            KEY = ESC;
            break;
        case 'p':
            KEY = PAUSE;
            break;
        case 32:
            KEY = PAUSE;
            break;
        }
    }
}
void snake::logic()
{
    int paused_taken = false;;
    int prevx, prevy;
    prevx = x;
    prevy = y;
    switch (KEY)
    {
    case LEFT:
        x--;
        paused_taken = false;
        break;
    case RIGHT:
        x++;
        paused_taken = false;
        break;
    case UP:
        y--;
        paused_taken = false;
        break;
    case DOWN:
        y++;
        paused_taken = false;
        break;
    case ESC:
        gameOver = true;
        break;
    case PAUSE:
        bool paused = true;
    pause:
        while (paused)
        {
            if (_kbhit())
            {
                if (_getch() == 'p' || _getch() == 32) {
                    paused = false;
                    paused_taken = true;
                }
                else goto pause;
            }
        }
        KEY = last_key;
        break;
    }
    if (!paused_taken)
    {
        for (int i = ntail - 1; i > 0; i--)
        {
            xtail[i] = xtail[i - 1];
            ytail[i] = ytail[i - 1];
        }
        xtail[0] = prevx;
        ytail[0] = prevy;
    }

    if (hit_wall)
    {
        if (x >= width - 1 || x <= 0 || y >= height - 1 || y <= 0) {
            gameOver = true; cout << "\nYou hit a wall\n";
        }
    }
    else
    {
        if (x >= width - 1) x = 1;
        if (x <= 0) x = width - 2;
        if (y >= height - 1) y = 1;
        if (y <= 0) y = height - 2;
    }
    for (int i = 0; i < ntail; i++)
        if (x == xtail[i] && y == ytail[i]) {
            cout << "\nYou ate yourself\n";
            gameOver = true;
            break;
        }
    if (walls == true && x > 4 && x < 10 && y == 9) {
        cout << "\nYou hit a wall\n";  gameOver = true;
    }

    if (x == fx && y == fy) {
        generateFruit();
        score++;
        ntail++;
    }
    if (x == mx && y == my) {
        mushroom_break = true;
        mushroom_break_cnt = 0;
        score -= 2;
        ntail -= 2;
        mx = -1;
        my = -1;
    }
}

void snake::set_mushrooms()
{
    mushrooms = !mushrooms;
}

void snake::set_hit_walls()
{
    hit_wall = !hit_wall;
}

void snake::set_walls()
{
    walls = !walls;
}

bool snake::get_gameOver()
{
    return gameOver;
}

int snake::get_score()
{
    return score;
}

bool snake::get_mushrooms()
{
    return mushrooms;
}

bool snake::get_hit_walls()
{
    return hit_wall;
}

bool snake::get_walls()
{
    return walls;
}

int main()
{
    int speed_level = 5;
    snake mysnk;

    fstream highscores;
    highscores.open("highscore.txt", ios::in | ios::binary);
    for (int i = 0; i < 10; i++)
    {
        highscores >> highscore[i];
    }
    for (int i = 0; i < 10; i++)
    {
        highscores >> highscore_name[i];
    }
    highscores.close();

menu:
    bool selected = false;
    int select = 1;
    main_menu(select);
    while (!selected)
    {

        if (_kbhit())
        {
            switch (_getch())
            {
            case 72: select--;
                break;
            case 80: select++;
                break;
            case 13: selected = true;
                break;
            }
            main_menu(select);
        }
    }

    selected = false;
    switch (select)
    {
    case 1:
    play_game:
        mysnk.setup();
        while (mysnk.get_gameOver() == false)
        {
            mysnk.draw();
            mysnk.input();
            mysnk.logic();
            Sleep(sleep_values[speed_level]);
        }

        cout << "\n\nscore: " << mysnk.get_score() << endl << endl;
        select = 0;
        change_highscores(mysnk.get_score());
        print_highscores();
        break;
    case 2:
        print_Instructions();
        select = -1;
        while (!selected)
        {
            if (_kbhit() && _getch() == 27) { system("cls");  goto menu; }
        }
        break;
    case  3:
    options_menu:
        selected = false;
        system("cls");
        options_menu(select);
        while (!selected)
        {

            if (_kbhit())
            {
                switch (_getch())
                {
                case 72: select--;
                    break;
                case 80: select++;
                    break;
                case 13: selected = true;
                    break;
                case 27: goto menu;
                    break;
                }
                options_menu(select);
            }
        }
        break;
    case 4:
    high_scores:
        selected = false;
        select = 3;
        highscore_menu(select);
        while (!selected)
        {

            if (_kbhit())
            {
                switch (_getch())
                {
                case 72: select--;
                    break;
                case 80: select++;
                    break;
                case 13: selected = true;
                    break;
                case 27: goto menu;
                    break;
                }
                highscore_menu(select);
            }
        }
        break;
    }
        selected = false;
        switch (select)
        {
        case 0:
            cout << "Press ENTER to play again\n\n";
            cout << "Press ESC to exit the game\n\n";
            cout << "Press SPACE to change the options\n\n";
            while (!selected)
            {
                if (_kbhit())
                    switch (_getch())
                    {
                    case 13:
                        selected = true;
                        goto play_game;
                        break;
                    case 27:
                        selected = true;
                        break;
                    case 32:
                        selected = true;
                        goto menu;
                    }
            }
            break;
        case 1:
            speed_menu(speed_level);
            while (1)
            {
                if (_kbhit())
                {
                    switch (_getch())
                    {
                    case 75: speed_level--;
                        break;
                    case 77:speed_level++;
                        break;
                    case 27:goto options_menu;
                        break;
                    case 13:goto options_menu;
                        break;
                    }
                    speed_menu(speed_level);
                }
            }
            break;
        case 2:
            select = 1;
            difficulty_menu(select, mysnk.get_mushrooms(), mysnk.get_hit_walls(), mysnk.get_walls());
            while (1)
            {
                if (_kbhit())
                {
                    switch (_getch())
                    {
                    case 72: select--;
                        break;
                    case 80: select++;
                        break;
                    case 13: if (select == 1) mysnk.set_mushrooms();
                           else if (select == 2) mysnk.set_hit_walls();
                           else if (select == 3) mysnk.set_walls();
                        break;
                    case 27:goto options_menu;
                        break;
                    }
                    difficulty_menu(select, mysnk.get_mushrooms(), mysnk.get_hit_walls(), mysnk.get_walls());
                }
            }
            break;
        case 3:
            print_highscores();
            cout << "\nPress ESC to return to main menu\n";
            while (1)
            {
                if (_kbhit() && _getch() == 27) goto menu;
            }
            break;
        case 4:
            system("cls");
            cout << "Are you sure you want to clear the Leaderboard?\n\n";
            cout << "Press ENTER to clear the Leaderboard\n";
            cout << "Press ESC to cancel\n";
            while (!selected)
            {
                if (_kbhit())
                {
                    if (_getch() == 27) goto menu;
                    if (_getch() == 13) {
                        selected = true;

                        for (int i = 0; i < 10; i++)
                        {
                            highscore[i] = 0;
                            highscore_name[i] = '-';
                        }
                    }
                }
            }
            system("cls");
            cout << "Leaderboard cleared succesfully!\n";
            Sleep(1500);
            goto menu;
            break;
        }

        highscores.open("highscore.txt", ios::out | ios::binary);
        for (int i = 0; i < 10; i++)
        {
            highscores << highscore[i] << " ";
        }
        highscores << endl;
        for (int i = 0; i < 10; i++)
        {
            highscores << highscore_name[i] << " ";
        }
        highscores.close();
        return 0;
}