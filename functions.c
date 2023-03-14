#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

void PrintChangingMenu(void)
{
    printf("--------------\n");
    printf("| Параметры: |\n");
    printf("--------------\n");
    printf("1 - Предприятие-изготовитель\n");
    printf("2 - Тип\n");
    printf("3 - Цена\n");
    printf("4 - Производительность\n");
}

int CheckingInput(int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

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
            printf("Неверный ввод. Попробуйте снова.\nВведите номер: ");
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
            printf("Неверный ввод. Попробуйте снова.\nВведите номер: ");
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    return userInput;
}

char* StringInput(void)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    while(curChar != '\n')
    {
        curChar = getchar();

        int deltaVal = 0; // Определяет, на сколько изменится длина массива
        int lengthDif = 0;

        // Если мы стираем символы, а не пишем их,
        if (curChar == BACKSPACE_KEY)
        {
            deltaVal = -1; // то будем уменьшать длину массива
            lengthDif = 1; // и копировать строку до предпоследнего символа
        }

            // Иначе проверяем, входит ли введённый символ в диапазон печатных
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                deltaVal = 1; // Если да, то будем увеличивать длину на 1
                lengthDif = 2; // Не заполняем последние 2 символа -
                // оставляем место для введённого символа и \0
            }
            else
            {
                continue; // Если это не печатный символ, то пропускаем его
            }
        }

        // Если стирать больше нечего, но пользователь
        // всё равно жмёт Backspace.
        int newSize = curSize + deltaVal;
        if (newSize == 0)
        {
            continue; // то мы переходим на следующую итерацию - ждём '\n'
        }

        char* tmpStr = (char*)malloc(newSize * sizeof(char));
        if (tmpStr) // Проверяем, выделилась ли память
        {
            // Идём до предпоследнего символа, т.к. надо в конец записать '\0'
            for (int i = 0;
                 i < newSize - lengthDif;
                 ++i)
            {
                tmpStr[i] = userStr[i];
            }

            if (curChar != BACKSPACE_KEY) // Если введён печатный символ,
            {
                tmpStr[newSize - 2] = curChar; // Добавляем его в строку
                tmpStr[newSize - 1] = '\0';
            }
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            printf("Не могу выделить память под обновлённую строку!");
            break;
        }
    }

    return userStr;
}

float FloatInput()
{
    float number = 0;
    while (number == 0 || number < 0)
    {
        char* InputValue = StringInput();
        number = strtof(InputValue, NULL);
        if (number == 0 || number < 0)
        {
            printf("Неверный ввод. Попробуйте снова.\nПовторите ввод: ");

        }
    }
    return number;
}

Node* CreateNode(Enterprise data) {
    Node* newNode = malloc(sizeof(Node)); // выделение памяти
    if (newNode == NULL) { // проверка на ошибку
        printf("Не удалось выделить память.\n");
        exit(1);
    }
    newNode->data = data; // копирование данных
    newNode->next = NULL; // инициализация указателя
    return newNode; // возврат нового элемента
}

// Функция для добавления элемента в конец списка
void AddNode(Node** head, Enterprise data)
{
    Node* newNode = CreateNode(data); // создание нового элемента
    if (*head == NULL) // если список пустой
    {
        *head = newNode; // новый элемент становится головой списка
    }
    else // если список не пустой
    {
        Node* temp = *head; // создание временного указателя temp и присвоение ему значения головы списка
        while (temp->next != NULL) // перебор списка до последнего элемента
        {
            temp = temp->next;
        }
        temp->next = newNode; // связывание последнего элемента с новым элементом
    }
}

// Функция для изменения значения всех полей элемента списка
// или только части из них
void UpdateNode(Node* head, int countEnterprises) {
    printf("Всего добавлено %d предприятий.\n", countEnterprises);
    printf("Введите номер предприятия, которое вы хотите изменить: ");
    int index = CheckingInput(1, countEnterprises) - 1;
    int count = 0; // счетчик

    PrintChangingMenu();
    printf("Введите номер пункта: ");
    int userChoice = CheckingInput(1, 4);

    char* newCompany = NULL;
    char* newType = NULL;
    float newPrice = 0;
    float newPerformance = 0;

    if (userChoice == 1)
    {
        printf("Введите новое название предприятия-изготовителя: ");
        newCompany = StringInput();
    }
    if (userChoice == 2)
    {
        printf("Введите новый тип предприятия: ");
        newType = StringInput();
    }
    if (userChoice == 3)
    {
        printf("Введите новую цену: ");
        newPrice = FloatInput();
    }
    if (userChoice == 4)
    {
        printf("Введите новую производительность: ");
        newPerformance = FloatInput();
    }

    while (head != NULL) { // пока не достигнут конец списка
        if (count == index) { // если счетчик совпадает с индексом
            // Проверить, задано ли новое значение для каждого поля
            if (newCompany != NULL) { // если задано новое название предприятия
                head->data.company = newCompany; // заменить название предприятия на новое
            }
            if (newType != NULL) { // если задан новый тип продукта
                head->data.type = newType; // заменить тип продукта на новый
            }
            if (newPrice > 0.0) { // если задана новая цена
                head->data.price = newPrice; // заменить цену на новую
            }
            if (newPerformance > 0.0) { // если задана новая производительность
                head->data.performance = newPerformance; // заменить производительность на новую
            }
            return; // завершить функцию
        }
        count++; // увеличить счетчик
        head = head->next; // перейти к следующему элементу
    }
    printf("Индекс за пределами диапазона.\n"); // сообщить об ошибке
}

// Функция для удаления элемента списка по индексу
void DeleteNode(Node** head, int* countEnterprises) {
    printf("Всего добавлено %d предприятий.\n", *countEnterprises);
    printf("Введите номер предприятия, которое вы хотите удалить: ");
    int index = CheckingInput(1, *countEnterprises) - 1;

    Node* current = *head; // текущий элемент
    Node* prev = NULL; // предыдущий элемент
    int count = 0; // счетчик
    while (current != NULL) { // пока не достигнут конец списка
        if (count == index) { // если индекс совпадает с счетчиком
            if (prev == NULL) { // если удаляем голову списка
                *head = current->next; // обновить голову списка
            } else { // иначе
                prev->next = current->next; // обойти удаляемый элемент
            }
            free(current); // освободить память
            *countEnterprises = *countEnterprises - 1;
            return; // завершить функцию
        }
        count++; // увеличить счетчик
        prev = current; // обновить предыдущий элемент
        current = current->next; // перейти к следующему элементу
    }
    printf("Индекс за пределами диапазона.\n"); // сообщить об ошибке
}

// Функция для чтения элемента списка по индексу
void PrintNode(Node* head, int countEnterprises) {
    printf("Всего добавлено %d предприятий.\n", countEnterprises);

    printf("Введите номер предприятия: ");
    int index = CheckingInput(1, countEnterprises) - 1;

    int count = 0; // счетчик
    bool flag = false;

    while (head != NULL) { // пока не достигнут конец списка
        if (count == index) { // если счетчик совпадает с индексом
            flag = true;
            break;
        }
        count++; // увеличить счетчик
        head = head->next; // перейти к следующему элементу
    }
    if (flag)
    {
        printf("\n");
        printf("Предприятие №%d\n", index + 1);
        printf("Предприятие-изготовитель: %s\n", head->data.company);
        printf("Тип: %s\n", head->data.type);
        printf("Цена: %.2f\n", head->data.price);
        printf("Производительность: %.2f\n", head->data.performance);
        printf("\n");
    }
    else
    {
        printf("Индекс за пределами диапазона.\n"); // сообщить об ошибке
    }
}

// Функция для отображения содержимого всех элементов списка или его части
void PrintList(Node* head, int countEnterprises) {
    printf("Всего добавлено %d предприятий.\n", countEnterprises);

    printf("Введите начальный номер: ");
    int start = CheckingInput(1, countEnterprises) - 1;

    printf("Введите конечный номер: ");
    int end = CheckingInput(start, countEnterprises) - 1;

    int count = 0; // счетчик
    while (head != NULL) { // пока не достигнут конец списка
        if (count >= start && count <= end) { // если счетчик входит в заданный диапазон
            // Вывести данные текущего элемента
            printf("\n");
            printf("Предприятие №%d\n", count + 1);
            printf("Предприятие-изготовитель: %s\n", head->data.company);
            printf("Тип: %s\n", head->data.type);
            printf("Цена: %.2f\n", head->data.price);
            printf("Производительность: %.2f\n", head->data.performance);
            printf("\n");
        }
        count++; // увеличить счетчик
        head = head->next; // перейти к следующему элементу
    }
}

// Функция для нахождения списка предприятий с наилучшим соотношением цена/производительность
void FindBestRatio(Node* head) {
    Node *current = head; // текущий элемент
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
    printf("Лучшее соотношение цена/качество %.2f\n",
           best_ratio); // вывести лучшее соотношение
    printf("Предприятия с таким коэффициентом:\n"); // вывести список предприятий с этим соотношением
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
void find_price_range(Node *head) {
    Node *current = head; // текущий элемент
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
void free_list(Node **head) {
    Node *current = *head; // текущий элемент
    Node *next; // следующий элемент
    while (current != NULL) { // пока список не пуст
        next = current->next; // запомнить следующий элемент
        free(current); // освободить память текущего элемента
        current = next; // перейти к следующему элементу
    }
    *head = NULL; // обнулить голову списка
}
