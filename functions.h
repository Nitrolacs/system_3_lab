#ifndef SF_VM_EXCHANGE_FUNCTIONS_H
#define SF_VM_EXCHANGE_FUNCTIONS_H

//
// Created by stud on 13.03.23.
//
#include "structure.h"



void PrintMenu(void);

int CheckingInput(const char message[], int lowerBound, int count);

char* StringInput(void);

float FloatInput(const char message[]);

Node *create_node(Enterprise data);

void add_node(Node **head, Enterprise data);

void update_node(Node* head, int index, char* new_company, char* new_type,
                 double new_price, double new_performance);

void delete_node(Node **head, int index);

Enterprise PrintNode(Node* head, int index);

void print_list(Node* head, int start, int end);

void find_best_ratio(Node *head);

void find_price_range(Node *head);

void free_list(Node **head);

#endif //SF_VM_EXCHANGE_FUNCTIONS_H
