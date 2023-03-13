//
// Created by stud on 13.03.23.
//

#ifndef SF_VM_EXCHANGE_STRUCTURE_H
#define SF_VM_EXCHANGE_STRUCTURE_H

// Определение структуры данных
struct product {
    char *company; // предприятие-изготовитель
    char *type; // тип
    double price; // цена
    double performance; // производительность
};

// Определение списка, содержащего элементы структуры данных
struct node {
    struct product data; // данные
    struct node *next; // указатель на следующий элемент
};

#endif //SF_VM_EXCHANGE_STRUCTURE_H
