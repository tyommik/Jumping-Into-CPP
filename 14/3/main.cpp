//
// Created by a.shibaev on 23.05.2018.
//

/*
 * Напишите программу, которая выводит адреса памяти всех элементов двумерного массива. Удостоверьтесь,
 * что понимаете, почему выведенные значения образуют последовательность, структуру которой я объяснял ранее
 */

#include <iostream>

using namespace std;

void buildArray(int **, int, int);
void printArray(int **, int, int);
void delArray(int **, int, int);

void buildArray(int ** p_p_arr, int height, int width) {
    for (int i = 0; i < height; i++) {
        p_p_arr[i] = new int [width];
        for (int j = 0; j < width; j++) {
            p_p_arr[i][j] = 0;
        }
    }
}

void printArray(int ** p_p_arr, int height, int width) {
    for (int i = 0; i < height; i++) {
        p_p_arr[i] = new int [width];
        for (int j = 0; j < width; j++) {
            cout << &p_p_arr[i][j] << " ";
        }
        cout << endl;
    }
}

void delArray(int ** p_p_arr, int height, int width) {
    for (int i = 0; i < height; i++) {
            delete [] p_p_arr[i];
    }
    delete [] p_p_arr;
}

int main() {
    int height = 0, width = 0;
    cout << "Enter height: ";
    cin >> height;
    cout << "\nEnter width: ";
    cin >> width;

    int ** p_p_array = new int * [height];

    buildArray(p_p_array, height, width);
    delArray(p_p_array, height, width);

    return 0;
}