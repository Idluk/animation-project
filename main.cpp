#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <cmath>
using namespace std;

const float PI = 3.14;

int height = 50;
int width = 30;

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

int* screen = new int[height*width] {0};

struct figure {
    point center;
    int r = 1;
    float u = 0;
    figure(int r = 1, float u = 0) {
        this->r = r;
        this->u = u;
        center.y = height/2 + 10;
        center.x = width/2;
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
            if (screen[i*width + j] == 1) buffer += "* ";
            else buffer += "  ";
            // buffer += to_string(screen[i*width + j]) + " ";    
        }
        buffer += "\n";
    }
    cout << buffer;
    buffer = "";
    gotoxy();
}

void clear_screen() {
    for (int i = 0; i < height*width; i++) {
        screen[i] = 0;
    }
}

void draw_figure(figure fig, float angle = 0) {
    while (fig.u <= PI) {
        fig.u += PI/180;
        fig.r = 12 * cos(5*fig.u + angle);
        point fig_decart = fig.to_decart();
        screen[fig_decart.y * width + fig_decart.x] = 1;
    }
}

int main() {
    figure fig1(4, 0);
    int i = 0;
    while (true) {
        draw_figure(fig1, i*PI/10);
        print();
        clear_screen();
        i++;
        Sleep(32);
    }
    delete[] screen;
    system("pause");
}
