//
// Created by a.shibaev on 28.05.2018.
//
/*
 * Напишите программу, которая создаёт лабиринт с шириной и высотой, заданными пользователем.
 * Лабиринт должен всегда содержать путь к выходу. После генерации выведите лабиринт на экран
 */

#include <iostream>
#include <ctime>

using namespace std;

enum CellState {Close, Open};

//класс состояния ячейки
class Cell {
public:
    int x;
    int y;
    CellState Left;
    CellState Right;
    CellState Top;
    CellState Bottom;
    bool Visited;
};


void initArray(Cell **, int, int);
void cleanMemory(Cell **, int);
Cell * selectStart (Cell **, int, int);

void initArray(Cell ** p_p_mass, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            p_p_mass[i][j].x = j;
            p_p_mass[i][j].y = i;
            p_p_mass[i][j].Visited = false;
        }
    }
}

Cell * selectStart(Cell ** p_p_Mass, int height, int width) {
    //выбираем ячейку для начала движения
    Cell * p_startPoint = NULL;
    srand(time(NULL));
    // 0 - top, 1 - right, 2 - bottom, 3 - left
    int side = rand() % 4;
    switch (side) {
        case 0:
            p_startPoint = p_p_Mass[0] + (rand() % width);
            break;
        case 1:
            p_startPoint = p_p_Mass[rand() % height] + (width - 1);
            break;
        case 2:
            p_startPoint = p_p_Mass[height - 1] + (rand() % width);
            break;
        case 3:
            p_startPoint = p_p_Mass[rand() % height];
            break;
    }

    cout << "Start point is x: " << p_startPoint->x << " y:" << p_startPoint->y;
    return p_startPoint;

}

void cleanMemory(Cell ** p_p_mass, int h) {
    for (int i = 0; i < h; i++) {
        delete [] p_p_mass[i];
    }
    delete [] p_p_mass;
}

int main() {
    int h, w;
    cout << "Height: ";
    cin >> h;
    cout << "\nWidth: ";
    cin >> w;

    Cell ** p_p_Array = new Cell * [h];
    for (int i = 0; i < h; i++) {
        p_p_Array[i] = new Cell[w];
    }
    initArray(p_p_Array, h, w);


    selectStart(p_p_Array, h, w);
    cleanMemory(p_p_Array, h);
    return 0;
}