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
#include <random>

using namespace std;

enum CellState {Close, Open};

//класс состояния ячейки
class Cell {
public:
    int x;
    int y;
    CellState Left = Close;
    CellState Right = Close;
    CellState Top = Close;
    CellState Bottom = Close;
    bool Visited;
};


void initArray(Cell **, int, int);
void cleanMemory(Cell **, int);
Cell * selectStart (Cell **, int, int);
void printArray(Cell **, int, int);
void printMaze(Cell **, int, int);

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
            cout << (p_p_mass[i][j].Visited ? 1 : 0) << " ";
            //cout << p_p_mass[i][j].y <<" ";
        }
        cout << endl;
    }
    cout << endl;
}

void printMaze(Cell ** p_p_mass, int h, int w) {
    int maze_height = h * 2 + 1;
    int maze_width = w * 2 + 1;
    string ** p_p_maze_mass = new string * [maze_height];
    for (int p = 0; p < maze_height; p++ ) {
        p_p_maze_mass[p] = new string [maze_width];
    }

    //инициализация пробелами
    for (int i = 0; i < maze_height; i++) {
        for (int j = 0; j < maze_width; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                p_p_maze_mass[i][j] = "*";
            }

            else p_p_maze_mass[i][j] = " ";
        }
    }

    //печать путей
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
//            cout << "x: " << j << " y: " << i << endl;
//            cout << "Top: " << (p_p_mass[i][j].Top ? "Open" : " Close") << endl;
//            cout << "Right: " << (p_p_mass[i][j].Right ? "Open" : " Close") << endl;
//            cout << "Left: " << (p_p_mass[i][j].Left ? "Open" : " Close") << endl;
//            cout << "Bottom: " << (p_p_mass[i][j].Bottom ? "Open" : " Close") << endl;
            if (p_p_mass[i][j].Top == Close) {
                p_p_maze_mass[i * 2][j * 2 + 1] = "*";
            }
            if (p_p_mass[i][j].Right == Close) {
                p_p_maze_mass[i * 2 + 1][j * 2 + 2] = "*";
            }
            if (p_p_mass[i][j].Left == Close) {
                p_p_maze_mass[i * 2 + 1][j * 2] = "*";
            }
            if (p_p_mass[i][j].Bottom == Close) {
                p_p_maze_mass[i * 2 + 2][j * 2 + 1] = "*";
            }
        }
    }

    //печать
    for (int i = 0; i < maze_height; i++) {
        for (int j = 0; j < maze_width; j++) {
            cout << p_p_maze_mass[i][j];
            //cout << p_p_mass[i][j].y <<" ";
        }
        cout << endl;
    }
    cout << endl;
    //заполнение ходов


    //освобождение памяти
    for (int p = 0; p < maze_height; p++ ) {
        delete [] p_p_maze_mass[p];
    }
    delete [] p_p_maze_mass;
}

Cell * selectStart(Cell ** p_p_Mass, int height, int width) {
    //выбираем ячейку для начала движения
    Cell * p_startPoint = nullptr;
    srand(time(nullptr));
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
        default:
            p_startPoint = p_p_Mass[0] + (rand() % width);
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
    std::random_device rd;
    std::mt19937 mt(rd());

    int h, w;
    cout << "Height: ";
    cin >> h;
    cout << "\nWidth: ";
    cin >> w;

    auto ** p_p_Array = new Cell * [h];
    for (int i = 0; i < h; i++) {
        p_p_Array[i] = new Cell[w];
    }
    initArray(p_p_Array, h, w);
    printArray(p_p_Array, h, w);
    Cell * p_startPoint = nullptr;

    p_startPoint = selectStart(p_p_Array, h, w);

    //инициализируем стек
    stack <Cell> path;
    //добавляем стартовую ячейку
    p_startPoint->Visited = true;
    path.push(*p_startPoint);

    while(!path.empty()) {
        Cell _cell = path.top();

        vector <Cell> nextstep;

        //ход влево
        if (_cell.x > 0 && !p_p_Array[_cell.y][_cell.x - 1].Visited) {
            //cout << "Allow left" << endl;
            //cout << "pos: " << p_p_Array[_cell.y][_cell.x - 1].x << " " << p_p_Array[_cell.y][_cell.x - 1].y << endl;
            nextstep.push_back(p_p_Array[_cell.y][_cell.x - 1]);
        }
        //ход вправо
        if (_cell.x < (w - 1) && !p_p_Array[_cell.y][_cell.x + 1].Visited) {
            //cout << "Allow right" << endl;
            //cout << "pos: " << p_p_Array[_cell.y][_cell.x + 1].x << " " << p_p_Array[_cell.y][_cell.x + 1].y<< endl;;
            nextstep.push_back(p_p_Array[_cell.y][_cell.x + 1]);
        }
        //ход вверх
        if (_cell.y > 0 && !p_p_Array[_cell.y - 1][_cell.x].Visited) {
            //cout << "Allow top" << endl;
            //cout << "pos: " << p_p_Array[_cell.y - 1][_cell.x].x << " " << p_p_Array[_cell.y - 1][_cell.x].y<< endl;;
            nextstep.push_back(p_p_Array[_cell.y - 1][_cell.x]);
        }
        //ход вниз
        if (_cell.y < (h - 1) && !p_p_Array[_cell.y + 1][_cell.x].Visited) {
            //cout << "Allow bottom" << endl;
            //cout << "pos: " << p_p_Array[_cell.y + 1][_cell.x].x << " " << p_p_Array[_cell.y + 1][_cell.x].y<< endl;;
            nextstep.push_back(p_p_Array[_cell.y + 1][_cell.x]);
        }

        if (!nextstep.empty()) {
            std::uniform_int_distribution<int> dist(0, nextstep.size() - 1);

            int tmp_rand = dist(mt);
            //cout << "Size is: " << nextstep.size() << endl;
            //cout << "The next step in direction " << tmp_rand << endl;
            Cell next = nextstep[tmp_rand];

            //Открываем сторону, в которую пошли на ячейках
            if (next.x != _cell.x)
            {
                if (_cell.x - next.x > 0)
                {
                    p_p_Array[_cell.y][_cell.x].Left = Open;
                    p_p_Array[next.y][next.x].Right = Open;
                }
                else
                {
                    p_p_Array[_cell.y][_cell.x].Right = Open;
                    p_p_Array[next.y][next.x].Left = Open;
                }
            }
            if (next.y != _cell.y)
            {
                if (_cell.y - next.y > 0)
                {
                    p_p_Array[_cell.y][_cell.x].Top = Open;
                    p_p_Array[next.y][next.x].Bottom = Open;
                }
                else
                {
                    p_p_Array[_cell.y][_cell.x].Bottom = Open;
                    p_p_Array[next.y][next.x].Top = Open;
                }
            }

            p_p_Array[next.y][next.x].Visited = true;
            path.push(next);

        }
        else
        {
            //если пойти никуда нельзя, возвращаемся к предыдущему узлу
            //cout << "Back step" << endl;
            path.pop();
        }
        //printArray(p_p_Array, h, w);
    }

    //печать лабиринта
    printMaze(p_p_Array, h, w);

    //очистка памяти
    cleanMemory(p_p_Array, h);
    return 0;
}