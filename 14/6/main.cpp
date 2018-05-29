//
// Created by a.shibaev on 28.05.2018.
//
/*
 * Напишите программу, которая создаёт лабиринт с шириной и высотой, заданными пользователем.
 * Лабиринт должен всегда содержать путь к выходу. После генерации выведите лабиринт на экран
 */

#include <iostream>
#include <ctime>
#include <stack>
#include <vector>

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
void printArray(Cell **, int, int);

void initArray(Cell ** p_p_mass, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            p_p_mass[i][j].x = j;
            p_p_mass[i][j].y = i;
            p_p_mass[i][j].Visited = false;
        }
    }
}

void printArray(Cell ** p_p_mass, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << (1 ? p_p_mass[i][j].Visited : 0) << " ";
        }
        cout << endl;
    }
    cout << endl;
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

    cout << "Start point is x: " << p_startPoint->x << " y:" << p_startPoint->y << endl;
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

    Cell * p_startPoint = NULL;

    p_startPoint = selectStart(p_p_Array, h, w);

    //инициализируем стек
    stack <Cell> path;
    //добавляем стартовую ячейку
    path.push(*p_startPoint);

    while(!path.empty()) {
        Cell _cell = path.top();

        vector <Cell> nextstep;

        //ход влево
        if (_cell.x > 0 && p_p_Array[_cell.x - 1][_cell.y].Visited == false ) {
            nextstep.push_back(p_p_Array[_cell.x - 1][_cell.y]);
        }
        //ход вправо
        if (_cell.x < (w - 1) && p_p_Array[_cell.x + 1][_cell.y].Visited == false) {
            nextstep.push_back(p_p_Array[_cell.x + 1][_cell.y]);
        }
        //ход вверх
        if (_cell.y > 0 && p_p_Array[_cell.x][_cell.y + 1].Visited == false) {
            nextstep.push_back(p_p_Array[_cell.x][_cell.y + 1]);
        }
        //ход вниз
        if (_cell.y < (h - 1) && p_p_Array[_cell.x][_cell.y - 1].Visited == false ) {
            nextstep.push_back(p_p_Array[_cell.x][_cell.y - 1]);
        }

        if (!nextstep.empty()) {
            srand(time(NULL));

            Cell next = nextstep[rand() % nextstep.size()];

            //Открываем сторону, в которую пошли на ячейках
            if (next.x != _cell.x)
            {
                if (_cell.x - next.x > 0)
                {
                    p_p_Array[_cell.x][_cell.y].Left = Open;
                    p_p_Array[next.x][next.y].Right = Open;
                }
                else
                {
                    p_p_Array[_cell.x][_cell.y].Right = Open;
                    p_p_Array[next.x][next.y].Left = Open;
                }
            }
            if (next.y != _cell.y)
            {
                if (_cell.y - next.y > 0)
                {
                    p_p_Array[_cell.x][_cell.y].Top = Open;
                    p_p_Array[next.x][next.y].Bottom = Open;
                }
                else
                {
                    p_p_Array[_cell.x][_cell.y].Bottom = Open;
                    p_p_Array[next.x][next.y].Top = Open;
                }
            }

            p_p_Array[next.x][next.y].Visited = true;
            path.push(next);

        }
        else
        {
            //если пойти никуда нельзя, возвращаемся к предыдущему узлу
            path.pop();
        }
        //printArray(p_p_Array, h, w);
    }

    //очистка памяти
    cleanMemory(p_p_Array, h);
    return 0;
}