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

int main() {
    figure a1(4, 0);
    while (true) {
        a1.u += PI/180;
        a1.r = 5 + 4*cos(a1.u);
        point a1_decart = a1.to_decart();
        screen[a1_decart.y * width + a1_decart.x] = 1;
        print();
        // screen[a1_decart.y * width + a1_decart.x] = 0;
        Sleep(32);
    }
    delete[] screen;
    system("pause");
}
