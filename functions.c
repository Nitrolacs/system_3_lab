#include <stdlib.h>
#include <stdio.h>

#include "structure.h"

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Добавление предприятия\n");
    printf("2 - Изменение предприятия\n");
    printf("3 - Удаление предприятия\n");
    printf("4 - Вывод предприятия (по индексу)\n");
    printf("5 - Отображение всех предприятий\n");
    printf("6 - Cписок предприятий с наилучшим соотношением "
           "цена/производительность\n");
    printf("7 - Диапазон цен\n");
    printf("8 - Выход\n");
}

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);

    if (count)
    {
        while (input != CORRECT_INPUT || inputChar != END_STRING
               || userInput < lowerBound || userInput > count)
        {
            if (userInput >= lowerBound && userInput <= count)
            {
                while ((inputChar = getchar()) != '\n');
            }
            userInput = 1;
            printf("Неверный ввод. Попробуйте снова.\n%s", message);
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    else
    {
        while (input != CORRECT_INPUT || inputChar != END_STRING
               || userInput <= lowerBound)
        {
            if (userInput > lowerBound)
            {
                while ((inputChar = getchar()) != '\n');
            }
            userInput = 1;
            printf("Неверный ввод. Попробуйте снова.\n%s", message);
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    return userInput;
}

struct node *create_node(struct product data) {
    struct node *new_node = malloc(sizeof(struct node)); // выделение памяти
    if (new_node == NULL) { // проверка на ошибку
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data; // копирование данных
    new_node->next = NULL; // инициализация указателя
    return new_node; // возврат нового элемента
}

// Функция для добавления элемента в начало списка
void add_node(struct node **head, struct product data) {
    struct node *new_node = create_node(data); // создание нового элемента
    new_node->next = *head; // связывание нового элемента с головой списка
    *head = new_node; // обновление головы списка
}

// Функция для модификации элемента списка по индексу
void modify_node(struct node* head, int index, struct product new_data) {
    struct node* current = head; // текущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count == index) { // если счетчик совпадает с индексом
            current->data = new_data; // заменить данные текущего элемента на новые
            return; // завершить функцию
        }
        count++; // увеличить счетчик
        current = current->next; // перейти к следующему элементу
    }
    printf("Index out of range.\n"); // сообщить об ошибке
}

// Функция для изменения значения всех полей элемента списка или только части из них
void update_node(struct node* head, int index, char* new_company, char* new_type, double new_price, double new_performance) {
    struct node* current = head; // текущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count == index) { // если счетчик совпадает с индексом
            // Проверить, задано ли новое значение для каждого поля
            if (new_company != NULL) { // если задано новое название предприятия
                current->data.company = new_company; // заменить название предприятия на новое
            }
            if (new_type != NULL) { // если задан новый тип продукта
                current->data.type = new_type; // заменить тип продукта на новый
            }
            if (new_price >= 0.0) { // если задана новая цена
                current->data.price = new_price; // заменить цену на новую
            }
            if (new_performance >= 0.0) { // если задана новая производительность
                current->data.performance = new_performance; // заменить производительность на новую
            }
            return; // завершить функцию
        }
        count++; // увеличить счетчик
        current = current->next; // перейти к следующему элементу
    }
    printf("Index out of range.\n"); // сообщить об ошибке
}

// Функция для удаления элемента списка по индексу
void delete_node(struct node **head, int index) {
    struct node *current = *head; // текущий элемент
    struct node *prev = NULL; // предыдущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count == index) { // если индекс совпадает с счетчиком
            if (prev == NULL) { // если удаляем голову списка
                *head = current->next; // обновить голову списка
            } else { // иначе
                prev->next = current->next; // обойти удаляемый элемент
            }
            free(current); // освободить память
            return; // завершить функцию
        }
        count++; // увеличить счетчик
        prev = current; // обновить предыдущий элемент
        current = current->next; // перейти к следующему элементу
    }
    printf("Index out of range.\n"); // сообщить об ошибке
}

// Функция для чтения элемента списка по индексу
struct product read_node(struct node* head, int index) {
    struct node* current = head; // текущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count == index) { // если счетчик совпадает с индексом
            return current->data; // вернуть данные текущего элемента
        }
        count++; // увеличить счетчик
        current = current->next; // перейти к следующему элементу
    }
    printf("Index out of range.\n"); // сообщить об ошибке
    struct product empty; // создать пустую структуру данных
    empty.company = NULL; // инициализировать поля
    empty.type = NULL;
    empty.price = 0.0;
    empty.performance = 0.0;
    return empty; // вернуть пустую структуру данных
}

// Функция для отображения содержимого списка
void display_list(struct node *head) {
    struct node *current = head; // текущий элемент
    while (current != NULL) { // пока не достигнут конец списка
        printf("Company: %s\n",
               current->data.company); // вывод данных текущего элемента
        printf("Type: %s\n", current->data.type);
        printf("Price: %.2f\n", current->data.price);
        printf("Performance: %.2f\n", current->data.performance);
        printf("\n");
        current = current->next; // перейти к следующему элементу
    }
}

// Функция для отображения содержимого всех элементов списка или его части
void print_list(struct node* head, int start, int end) {
    struct node* current = head; // текущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count >= start && count <= end) { // если счетчик входит в заданный диапазон
            // Вывести данные текущего элемента
            printf("Company: %s\n", current->data.company);
            printf("Type: %s\n", current->data.type);
            printf("Price: %.2f\n", current->data.price);
            printf("Performance: %.2f\n\n", current->data.performance);
        }
        count++; // увеличить счетчик
        current = current->next; // перейти к следующему элементу
    }
    if (start < 0 || end >= count) { // если диапазон выходит за границы списка
        printf("Invalid range.\n"); // сообщить об ошибке
    }
}

// Функция для нахождения списка предприятий с наилучшим соотношением цена/производительность
void find_best_ratio(struct node *head) {
    struct node *current = head; // текущий элемент
    double best_ratio = 0.0; // лучшее соотношение
    while (current != NULL) { // пока не достигнут конец списка
        double ratio = current->data.price /
                       current->data.performance; // вычислить соотношение для текущего элемента
        if (ratio < best_ratio || best_ratio ==
                                  0.0) { // если соотношение лучше или еще не определено
            best_ratio = ratio; // обновить лучшее соотношение
        }
        current = current->next; // перейти к следующему элементу
    }
    printf("The best price/performance ratio is %.2f\n",
           best_ratio); // вывести лучшее соотношение
    printf("The companies with this ratio are:\n"); // вывести список предприятий с этим соотношением
    current = head; // сбросить текущий элемент
    while (current != NULL) { // пока не достигнут конец списка
        double ratio = current->data.price /
                       current->data.performance; // вычислить соотношение для текущего элемента
        if (ratio == best_ratio) { // если соотношение совпадает с лучшим
            printf("%s\n",
                   current->data.company); // вывести название предприятия
        }
        current = current->next; // перейти к следующему элементу
    }
}

// Функция для нахождения диапазона цен
void find_price_range(struct node *head) {
    struct node *current = head; // текущий элемент
    double min_price = 0.0; // минимальная цена
    double max_price = 0.0; // максимальная цена
    while (current != NULL) { // пока не достигнут конец списка
        double price = current->data.price; // получить цену текущего элемента
        if (price < min_price ||
            min_price == 0.0) { // если цена меньше или еще не определена
            min_price = price; // обновить минимальную цену
        }
        if (price > max_price ||
            max_price == 0.0) { // если цена больше или еще не определена
            max_price = price; // обновить максимальную цену
        }
        current = current->next; // перейти к следующему элементу
    }
    printf("The price range is from %.2f to %.2f\n", min_price,
           max_price); // вывести диапазон цен
}

// Функция для освобождения памяти списка
void free_list(struct node **head) {
    struct node *current = *head; // текущий элемент
    struct node *next; // следующий элемент
    while (current != NULL) { // пока список не пуст
        next = current->next; // запомнить следующий элемент
        free(current); // освободить память текущего элемента
        current = next; // перейти к следующему элементу
    }
    *head = NULL; // обнулить голову списка
}
