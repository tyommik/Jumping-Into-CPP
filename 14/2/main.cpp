//
// Created by a.shibaev on 23.05.2018.
//
/*
 * Напишите функцию, которая принимает три аргумента, длину, ширину и высоту, динамически выделяет
 * трёхмерный массив с этими размерностями и заполняет его как таблицу умножения. По окончании работы с массивом
 * освободите занимаемую им память.
 */

#include <iostream>

using namespace std;

void buildMatrix(int ***, int, int, int);
void popMatrix(int **, int, int, int);
void printMatrix(int **, int, int, int);

void buildMatrix(int ***p_p_p_Matrix, int length, int width, int height) {
    for (int i = 0; i < length; i++) {
        p_p_p_Matrix[i] = new int * [width];
        for (int j = 0; j < width; j++) {
            p_p_p_Matrix[i][j] = new int [height];
        }
    }
}

void popMatrix(int *** p_p_p_Matrix, int length, int width, int height) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < height; k++) {
                p_p_p_Matrix[i][j][k] = (i + 1) * (j + 1) * (k + 1);
            }
        }
    }
}

void printMatrix(int *** p_p_p_Matrix, int length, int width, int height) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < height; k++) {
                cout << p_p_p_Matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void delMatrix(int *** p_p_p_Matrix, int length, int width, int height) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            delete [] p_p_p_Matrix[i][j];
        }
        delete [] p_p_p_Matrix[i];
    }
    delete [] p_p_p_Matrix;
}

int main() {
    int length = 0,
            width = 0,
            height = 0;

    cout << "Enter length: ";
    cin >> length;
    cout << "Enter width: ";
    cin >> width;
    cout << "Enter height: ";
    cin >> height;

    int *** p_p_p_matrix = new int ** [length];

    buildMatrix(p_p_p_matrix, length, width, height);
    popMatrix(p_p_p_matrix, length, width, height);
    printMatrix(p_p_p_matrix, length, width, height);
    delMatrix(p_p_p_matrix, length, width, height);

    return 0;
}