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
void playerMove(string **, int, int, int);
bool checkWinner(string **, int, int);
void flushGrid(string **, int);

const string playerChars[] = {"+", "x"};

enum PLAYERS {
    PLUS = 0,
    CROSS = 1,
};

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
            cout << p_p_grid[j][i] << " ";
        }
        cout << endl;
    }
}

void flushGrid(string ** p_p_grid, int h) {
    for(int i = 0; i < h; i++) {
        delete [] p_p_grid[i];
    }
    delete [] p_p_grid;
}

void playerMove(string ** p_p_grid, int height, int player) {
    while (true) {
        int c = 0;
        cout << "Player " << player + 1 <<  " move!" << endl;
        cout << "Column: ";
        cin >> c;
        cout << endl;
        string * p_cell = 0;
        for (int i = 0; i < height && (p_p_grid[c][i] == "_"); i++) {
            p_cell =  &p_p_grid[c][i];
        }
        if (p_cell != NULL) {
            *p_cell = playerChars[player];
            break;
        } else cout << "Do step again!" << endl;
    }

}

bool checkWinner(string ** p_p_grid, int height, int width) {
    for (int player = 0; player < 2; player++) {
        string chart = playerChars[player];

        //обход по строкам
        int horisontal_res = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (p_p_grid[i][j] == chart) {
                    horisontal_res++;
                } else {
                    horisontal_res = 0;
                }
                if (horisontal_res >= 4) {
                    cout << "Player " << player + 1 << " won!" << endl;
                    return true;
                }
            }
        }
        //обход по столбцам
        int vertical_res = 0;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (p_p_grid[j][i] == chart) {
                    vertical_res++;
                } else {
                    vertical_res = 0;
                }
                if (vertical_res >= 4) {
                    cout << "Player " << player + 1 << " won!" << endl;
                    return true;
                }
            }
        }
        //обход по обратным правым диагоналям
        int rdiagonal_res = 0;
        for (int r = 0; r < height + width - 1; r++)
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    if (i + j == r) {
                        if (p_p_grid[j][i] == chart) {
                            rdiagonal_res++;
                        } else {
                            rdiagonal_res = 0;
                        }
                        if (rdiagonal_res >= 4) {
                            cout << "Player " << player + 1 << " won!" << endl;
                            return true;
                        }

        }
        //обход по обратным левым диагоналям
        int ldiagonal_res = 0;
        for (int r = 0; r < height + width - 1; r++)
            for (int i = 0; i < height; i++)
                for (int j = width - 1; j >=1 ; j--)
                    if (i + j == r) {
                        if (p_p_grid[j][i] == chart) {
                            ldiagonal_res++;
                        } else {
                            ldiagonal_res = 0;
                        }
                        if (rdiagonal_res >= 4) {
                            cout << "Player " << player + 1 << " won!" << endl;
                            return true;
                        }

                    }
    }
    return false;
}

int main() {
    int h = 0, w = 0;
    startGame(h, w);

    bool isGameContinue = true;
    //init pointer to array
    auto ** p_p_Grid = new string * [h];
    for (int i = 0; i < h; i++) {
        p_p_Grid[i] = new string [w];
    }
    initGrid(p_p_Grid, h, w);
    printGrid(p_p_Grid, h, w);

    while (isGameContinue) {
        for (int i = PLUS; i <= CROSS; i++) {
            playerMove(p_p_Grid, h, i);
            printGrid(p_p_Grid, h, w);
            isGameContinue = !checkWinner(p_p_Grid, h, w);
            if (!isGameContinue) {
                break;
            }
        }
    }
    flushGrid(p_p_Grid, h);
    cout << "END GAME!";
    return 0;
}