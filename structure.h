//
// Created by stud on 13.03.23.
//

#ifndef SF_VM_EXCHANGE_STRUCTURE_H
#define SF_VM_EXCHANGE_STRUCTURE_H

// Определение структуры данных
typedef struct Enterprise {
    char* company; // предприятие-изготовитель
    char *type; // тип
    float price; // цена
    float performance; // производительность
} Enterprise;

// Определение списка, содержащего элементы структуры данных
typedef struct Node {
    Enterprise data; // данные
    struct Node *next; // указатель на следующий элемент
} Node;

#endif //SF_VM_EXCHANGE_STRUCTURE_H
