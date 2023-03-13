#include <stdio.h>

#include "structure.h"
#include "functions.c"

#define ADDING_ENTERPRISE 1
#define CHANGING_ENTERPRISE 2
#define DELETING_ENTERPRISE 3
#define PRINTING_ONE_ENTERPRISE 4
#define PRINTING_ALL_ENTERPRISES 5
#define ENTERPRISES_WITH_BEST_VALUE 6
#define PRICE_RANGE 7
#define EXIT 8

// Тестирование программы
int main() {
    printf("----------------------------------------------\n");
    printf("| Программа для работы со структурами данных |\n");
    printf("----------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice;
    int countEnterprises = 0;

    Node* enterprises = NULL; // создание пустого списка

    do
    {
        PrintMenu(); // выводим меню на экран
        int menuItemsCount = 8; // кол-во пунктов меню
        // нижняя граница допустимых значений
        int lowerBound = 1;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
        // суммарное количество батареек

        switch (userChoice)
        {
            case ADDING_ENTERPRISE:
                printf("--------------------------\n");
                printf("| Добавление предприятия |\n");
                printf("--------------------------\n");

                Enterprise tmpEnterprise = {NULL, NULL, 0, 0};

                printf("Введите название предприятия-изготовителя: ");
                tmpEnterprise.company = StringInput();
                printf("Введите тип предприятия: ");
                tmpEnterprise.type = StringInput();
                char secondMessage[] = "Введите цену: ";
                tmpEnterprise.price = FloatInput(secondMessage);
                char thirdMessage[] = "Введите производительность: ";
                tmpEnterprise.performance = FloatInput(thirdMessage);
                add_node(&enterprises, tmpEnterprise);
                countEnterprises++;
                break;

            case CHANGING_ENTERPRISE:
                if (enterprises == NULL)
                {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }

                break;

            case DELETING_ENTERPRISE:
                if (enterprises == NULL)
                {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }
                //DeletingBattery(&batteries, &countBatteries, mode);
                break;

            case PRINTING_ONE_ENTERPRISE:
                if (enterprises == NULL) {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }
                PrintNode(enterprises, countEnterprises);
                break;

            case PRINTING_ALL_ENTERPRISES:
                if (enterprises == NULL)
                {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }

                break;

            case ENTERPRISES_WITH_BEST_VALUE:
                if (enterprises == NULL)
                {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }

                break;

            case PRICE_RANGE:
                if (enterprises == NULL)
                {
                    printf("Предприятия ещё не добавлены.\n");
                    break;
                }

                break;

            default:
                free_list(&enterprises);
                printf("Выход...\n");
        }
    } while (userChoice != EXIT);

    return 0;
}