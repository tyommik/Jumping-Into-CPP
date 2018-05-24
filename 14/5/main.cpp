//
// Created by a.shibaev on 24.05.2018.
//

/*
 * Напишите версию игры Connect Four (четыре в ряд) для двух игроков, в которой пользователь может задать
 * ширину и высоту поля и оба игрока по очереди роняют фишки в ячейки. Отображайте одну
 * сторону поля значками +, другую - значками x, а пустые ячейки помечайте значками _.
 */

#include <iostream>

using namespace std;

void startGame(int &, int &);
void initGrid(string **, int, int);
void printGrid(string **, int, int);

void startGame(int &height, int &width) {
    while (height <= 3 || width <= 3) {
        cout << "Enter the height: ";
        cin >> height;
        cout << "Enter the width: ";
        cin >> width;

        if(height <= 3 || width <= 3) cout << "You need to init height > 3 and width > 3!" << endl;
    }

}

void initGrid(string ** p_p_grid, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            p_p_grid[i][j] = "_";
        }
    }
}

void printGrid(string ** p_p_grid, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << p_p_grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int h = 0, w = 0;
    startGame(h, w);

    //init pointer to array
    string ** p_p_Grid = new string * [h];
    for (int i = 0; i < h; i++) {
        p_p_Grid[i] = new string [w];
    }
    initGrid(p_p_Grid, h, w);
    printGrid(p_p_Grid, h, w);
    return 0;
}