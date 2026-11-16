#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cmath>
using namespace std;

const float PI = 3.14;

int height = 50;
int width = 30;

struct cell {
    bool active = true;
    char symbol = '*';
    cell() {
        bool active = true;
        char symbol = '*';
    }
};

cell* screen = new cell[height*width];

void gotoxy(int x = 0, int y = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    COORD coord;
    coord.X = x;    
    coord.Y = y;    
    SetConsoleCursorPosition(hConsole, coord);
}

struct point {
    int x = 0;
    int y = 0;
    int value = 0;
    point(int x = 0, int y = 0, int value = 0) {
        this->x = x;
        this->y = y;
        this->value = value;
    }
};

struct figure {
    point center;
    int len = 12;
    int r = len;
    float u = 0;
    char symbol = '*';
    figure() {
        center.x = width/2;
        center.y = height/2 + 10;
    }
    figure(int x, int y, char symbol = '*') {
        this->r = r;
        this->u = u;
        this->symbol = symbol;
        center.y = y;
        center.x = x;
    }
    void set_xy(int x, int y) {
        center.x = x;
        center.y = y;
    }
    void set_len(int r) {
        this->len = len;
    }
    void set_symbol(char symbol) {
        this->symbol = symbol;
    }
    point to_decart() {
        point a(center.x+r*cos(u), center.y+r*sin(u), 1);
        return a;
    }
};

void print() {
    string buffer;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (screen[i*width + j].active) buffer += screen[i*width + j].symbol;
            else buffer += " ";

            buffer += " ";
        }
        buffer += "\n";
    }
    cout << buffer;
    buffer = "";
    gotoxy();
}

void clear_screen() {
    for (int i = 0; i < height*width; i++) {
        screen[i].active = false;
    }
}

void animate_figure(figure fig, float angle = 0, int k = 5) {
    while (fig.u <= PI) {
        fig.u += PI/180;
        fig.r = (fig.len * cos(k*fig.u + angle));
        point fig_decart = fig.to_decart();
        if (fig_decart.y < height && fig_decart.y > 0 && fig_decart.x < width && fig_decart.x > 0) {
            screen[fig_decart.y * width + fig_decart.x].active = true;
            screen[fig_decart.y * width + fig_decart.x].symbol = fig.symbol;
        }
    }
}

int main() {
    srand(time(0));
    char syms[] = {'*', '#', '?', '@'};
    const int n = 4;
    figure figs[n];
    for (int i = 0; i < n; i++) {
        figs[i].set_xy(rand()%width, rand()%height);
        figs[i].set_len(6 + rand()%4);
        figs[i].set_symbol(syms[i]);
    }
    int step = 0;
    while (true) {
        for (int i = 0; i < n; i++) {
            animate_figure(figs[i], step*PI/10);
        }
        print();
        clear_screen();
        step++;
        if (step == 20) step = 0;
        Sleep(32);
    }
    delete[] screen;
    system("pause");
}
