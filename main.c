#include <stdio.h>

#include "structure.h"
#include "functions.h"

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
    int userChoice = 0;

    struct node* enterprises = NULL; // создание пустого списка

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

                int batteryNumber =
                        CheckingInput("Сколько батареек вы хотите добавить: ",
                                      0, 0);

                for (int i = countBatteries;
                     i < countBatteries + batteryNumber;
                     ++i)
                {
                    battery_t tmpBattery = {NULL, NULL, 0, 0, NULL};
                    printf("---------------\n");
                    printf("| Батарейка №%d|\n", i + 1);
                    printf("---------------\n");
                    printf("Введите модель батарейки: ");
                    tmpBattery.model = StringInput();
                    printf("Введите типоразмер (ААА, АА) батарейки: ");
                    tmpBattery.batterySize = StringInput();
                    tmpBattery.price = CheckingInput("Введите цену батарейки: ",
                                                     0, 0);
                    tmpBattery.voltage = FloatInput();
                    printf("Введите вид батарейки (alkaline, "
                           "salt water и т.д.): ");
                    getchar();
                    tmpBattery.type = StringInput();

                    addBattery2Batteries(&batteries, tmpBattery);
                }

                printf("Сохранить информацию о батарейках в файл?\n");
                printf("(введите цифру)\n");
                printf("1 - Да\n");
                printf("2 - Нет\n");

                menuItemsCount = 2;
                int mode = CheckingInput(firstMessage, lowerBound,
                                         menuItemsCount);
                const int FILE_STORAGE = 1;

                if (mode == FILE_STORAGE)
                {
                    WriteToFile(batteries);
                    printf("Информация о батарейках записана в файл "
                           "batteries.txt\n");
                }

                countBatteries += batteryNumber;
                break;

            case DELETING_BATTERY:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                DeletingBattery(&batteries, &countBatteries, mode);
                break;

            case PRINTING_BATTERIES:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                PrintingBatteries(batteries);
                break;

            case BATTERY_SORTING:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                SortingBatteries(&batteries, mode);
                break;

            case SEARCH:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                SearchByFeature(batteries);
                break;

            default:
                for (int i = 0; i < countBatteries; ++i)
                {
                    free(batteries.b_array[i].type);
                    free(batteries.b_array[i].batterySize);
                    free(batteries.b_array[i].model);
                }
                free(batteries.b_array);
                printf("Выход...");
        }
    } while (userChoice != EXIT);





    // Добавление нескольких элементов в список
    add_node(&head, (struct product) {"Samsung", "Smartphone", 500.0, 80.0});
    add_node(&head, (struct product) {"Apple", "Laptop", 1000.0, 90.0});
    add_node(&head, (struct product) {"Lenovo", "Tablet", 300.0, 70.0});
    add_node(&head, (struct product) {"Dell", "Desktop", 800.0, 100.0});
    // Отображение содержимого списка
    printf("The list contains:\n");
    display_list(head);
    // Модификация элемента списка по индексу
    printf("Modifying the second element:\n");
    modify_node(head, 1,
                (struct product) {"Apple", "Smartphone", 900.0, 85.0});
    // Использование функции update_node
    // Обновление названия предприятия и цены второго элемента списка
    printf("Updating the company name and price of the second element:\n");
    update_node(head, 1, "Microsoft", NULL, 1200.0, -1.0);
    // Отображение содержимого списка
    printf("The list contains:\n");
    display_list(head);
    // Обновление типа продукта и производительности четвертого элемента списка
    printf("Updating the product type and performance of the fourth element:\n");
    update_node(head, 3, NULL, "Monitor", -1.0, 95.0);
    // Отображение содержимого списка
    printf("The list contains:\n");
    display_list(head);
    // Отображение содержимого списка
    printf("The list contains:\n");
    display_list(head);
    // Использование функции print_list
    // Вывод первых двух элементов списка
    printf("Printing the first two elements:\n");
    print_list(head, 0, 1);

    // Вывод последних двух элементов списка
    printf("Printing the last two elements:\n");
    print_list(head, 2, 3);

    // Вывод элементов с индексами 1 и 2
    printf("Printing the elements with indexes 1 and 2:\n");
    print_list(head, 1, 2);

    // Вывод элементов с неверным диапазоном
    printf("Printing the elements with invalid range:\n");
    print_list(head, -1, 4);
    // Удаление элемента списка по индексу
    printf("Deleting the first element:\n");
    delete_node(&head, 0);
    // Отображение содержимого списка
    printf("The list contains:\n");
    display_list(head);
    // Чтение элемента списка по индексу
    printf("Reading the third element:\n");
    struct product p = read_node(head, 2);
    printf("Company: %s\n", p.company);
    printf("Type: %s\n", p.type);
    printf("Price: %.2f\n", p.price);
    printf("Performance: %.2f\n", p.performance);
    printf("\n");

    // Нахождение списка предприятий с наилучшим соотношением цена/производительность
    printf("Finding the best price/performance ratio:\n");
    find_best_ratio(head);
    // Нахождение диапазона цен
    printf("Finding the price range:\n");
    find_price_range(head);

    free_list(&head);
    return 0;
}