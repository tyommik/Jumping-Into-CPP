//
// Created by a.shibaev on 31.05.2018.
//

/*
 * 1. Напишите программу, которая удаляет элемент из связного списка. Функция, выполняющая удаление,
 * должна принимать в качестве аргумента только удаляемый элемент. Легко ли написать эту функцию?
 * Будет ли она быстро работать? Можно ли упростить или ускорорить её работу, добавив в список указатель?
 *
 * 2. Напишите программу, которая добавляет элементы в связанный список в порядке его сортировки,
 * а не в начало
 *
 * 3. Напишите программу, которая находит элемент в связанном списке по его имени.
 */

#include <iostream>

void menu ();
void removeBlock();
void addBlock();
void findBlock();
void printBlocks();
void exit();

void removeBlock() {

}

void addBlock() {

}

void findBlock() {

}

void printBlocks() {

}

void exit() {

}

void menu () {
    int item;
    enum menuList {REMOVE = 1, ADD, FIND, PRINT, EXIT};
    do {
        std::cout << "\nPlease choose an option" << std::endl;
        std::cout << "1. Remove person" << std::endl;
        std::cout << "2. Add person" << std::endl;
        std::cout << "3. Find person" << std::endl;
        std::cout << "4. Print full list" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Item: ";
        std::cin >> item;
        std::cout << std::endl;
        switch (item) {
            case REMOVE:
                removeBlock();
                break;
            case ADD:
                addBlock();
                break;
            case FIND:
                findBlock();
                break;
            case PRINT:
                printBlocks();
                break;
            case EXIT:
                exit();
                break;
            default:
                exit();
        }

    } while (item != EXIT);
}

int main () {
    menu();
    return 0;
}