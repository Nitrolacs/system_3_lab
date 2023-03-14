#ifndef SF_VM_EXCHANGE_FUNCTIONS_H
#define SF_VM_EXCHANGE_FUNCTIONS_H

//
// Created by stud on 13.03.23.
//
#include "structure.h"

void PrintMenu(void);

void PrintChangingMenu(void);

int CheckingInput(int lowerBound, int count);

char* StringInput(void);

float FloatInput();

Node *CreateNode(Enterprise data);

void AddNode(Node **head, Enterprise data);

void UpdateNode(Node* head, int countEnterprises);

void DeleteNode(Node **head, int* countEnterprises);

void PrintNode(Node* head, int countEnterprises);

void PrintList(Node* head, int countEnterprises);

void find_best_ratio(Node *head);

void find_price_range(Node *head);

void free_list(Node **head);

#endif //SF_VM_EXCHANGE_FUNCTIONS_H
