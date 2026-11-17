// Лабораторна робота №4. Структурування програм з використанням функцій
// Виконав: Онищук Тарас Сергійович, група 311
// Варіант: Proc31, Proc21, Integer38
//
// Консольні повідомлення англійською, щоб не залежати від кодування консолі Qt Creator.

#include <iostream>   // cout, cin
#include <iomanip>    // fixed, setprecision
#include <sstream>    // istringstream
#include <string>     // string, getline
#include <cmath>      // fabs, sqrt

using namespace std;

const double G = 9.81;        // прискорення вільного падіння, м/с^2 (Proc21)
const int BUS_CAPACITY = 45;  // вмістимість автобуса, місць (Integer38)

// Прямокутник, заданий координатами двох протилежних вершин (Proc31)
struct Rect
{
    double x1, y1, x2, y2;
};

// ====================== ОГОЛОШЕННЯ ФУНКЦІЙ (до main) ======================

// ---- допоміжна функція введення дійсного числа ----
// Читає рядок, перевіряє що це число і воно лежить у [-100; 100].
// Повертає true, якщо дані НЕкоректні; false, якщо все гаразд.
bool in_real(const string& pName, double& pV);

// ---- Завдання 1, задача Proc31 ----
double RectS(double x1, double y1, double x2, double y2); // площа прямокутника
bool in_rect(int pNum, Rect& pR);                         // введення з перевіркою (true = помилка)
void out_rect(int pNum, double pS);                       // виведення площі
void task_Proc31();                                       // задача Proc31 цілком

// ---- Завдання 1, задача Proc21 ----
void FreeFallTime(double h, double& t);                   // час вільного падіння
bool in_height(int pNum, double& pH);                     // введення висоти 0..100 (true = помилка)
void out_fall(double pH, double pT);                      // виведення часу
void task_Proc21();                                       // задача Proc21 цілком

// ---- Завдання 2, задача Integer38 ----
bool in_N(int& pN);                                       // введення з перевіркою (true = помилка)
void calc_buses(int pN, int& pFull, int& pExtra);         // підрахунок результату
void out_res(int pN, int pFull, int pExtra);              // виведення результату
void task_Int38();                                        // задача Integer38 цілком

// ---- Завдання 3 ----
void menu();                                              // меню вибору завдання

// ================================ main ====================================

int main()
{
    menu();
    return 0;
}

// ====================== ВИЗНАЧЕННЯ ФУНКЦІЙ (після main) ===================

// Меню: користувач обирає одне із завдань, вибір обробляється інструкцією switch
void menu()
{
    string line;
    int choice;

    cout << "=== Laboratory work 4 ===" << endl;
    cout << "1 - Proc31  (area of a rectangle)" << endl;
    cout << "2 - Proc21  (free fall time)" << endl;
    cout << "3 - Integer38 (buses and passengers)" << endl;
    cout << "0 - exit" << endl;
    cout << "Your choice: ";

    getline(cin, line);
    istringstream iss(line);
    if (!(iss >> choice))       // якщо ввели не число
        choice = -1;

    switch (choice)
    {
    case 1:
        task_Proc31();
        break;
    case 2:
        task_Proc21();
        break;
    case 3:
        task_Int38();
        break;
    case 0:
        cout << "Bye!" << endl;
        break;
    default:
        cout << "Wrong menu item!" << endl;
    }
}

// Читає дійсне число з консолі. Повертає true, якщо введено некоректно
bool in_real(const string& pName, double& pV)
{
    string line;
    cout << pName << " = ";
    getline(cin, line);                 // читаємо весь рядок
    istringstream iss(line);

    if (!(iss >> pV))                   // у рядку немає числа
        return true;
    iss >> ws;                          // пропускаємо пробіли після числа
    if (!iss.eof())                     // є зайві символи (наприклад "12abc")
        return true;
    if (pV < -100 || pV > 100)          // поза діапазоном [-100; 100]
        return true;
    return false;                       // дані коректні
}

// ---------------------------- Proc31 ---------------------------------------

// Площа прямокутника зі сторонами, паралельними осям, за двома протилежними вершинами
double RectS(double x1, double y1, double x2, double y2)
{
    return fabs(x2 - x1) * fabs(y2 - y1);   // довжина сторін - модулі різниць координат
}

// Введення координат прямокутника з перевіркою
bool in_rect(int pNum, Rect& pR)
{
    cout << "Rectangle " << pNum << " (opposite vertices):" << endl;
    return in_real("  x1", pR.x1) || in_real("  y1", pR.y1)
        || in_real("  x2", pR.x2) || in_real("  y2", pR.y2);
}

// Виведення площі прямокутника
void out_rect(int pNum, double pS)
{
    cout << "Rectangle " << pNum << ": S = " << fixed << setprecision(3) << pS << endl;
}

// Задача Proc31 цілком: введення, площі трьох прямокутників, виведення
void task_Proc31()
{
    Rect r1, r2, r3;                    // три прямокутники

    cout << "Proc31." << endl;
    // введення; при першій же помилці решта умови не обчислюється
    if (in_rect(1, r1) || in_rect(2, r2) || in_rect(3, r3))
        cout << "Incorrect input! Values must be numbers from -100 to 100." << endl;
    else
    {
        // підрахунок і виведення результатів (без циклів)
        out_rect(1, RectS(r1.x1, r1.y1, r1.x2, r1.y2));
        out_rect(2, RectS(r2.x1, r2.y1, r2.x2, r2.y2));
        out_rect(3, RectS(r3.x1, r3.y1, r3.x2, r3.y2));
    }
}

// ---------------------------- Proc21 ---------------------------------------

// Процедура: час t вільного падіння з висоти h (h - вхідний, t - вихідний параметр)
void FreeFallTime(double h, double& t)
{
    t = sqrt(2 * h / G);                // t = sqrt(2h/g)
}

// Введення висоти з перевіркою: число з діапазону [0; 100]
bool in_height(int pNum, double& pH)
{
    string name = "  h" + to_string(pNum) + " (m)";
    if (in_real(name, pH))              // не число або поза [-100; 100]
        return true;
    return pH < 0;                      // висота не може бути від'ємною
}

// Виведення результату
void out_fall(double pH, double pT)
{
    cout << "h = " << fixed << setprecision(3) << pH
         << " m,  t = " << pT << " s" << endl;
}

// Задача Proc21 цілком: три висоти -> три часи падіння
void task_Proc21()
{
    double h1, h2, h3;                  // висоти
    double t1, t2, t3;                  // часи падіння

    cout << "Proc21." << endl;
    if (in_height(1, h1) || in_height(2, h2) || in_height(3, h3))
        cout << "Incorrect input! Height must be a number from 0 to 100." << endl;
    else
    {
        FreeFallTime(h1, t1);           // виклики процедури (без циклів)
        FreeFallTime(h2, t2);
        FreeFallTime(h3, t3);
        out_fall(h1, t1);
        out_fall(h2, t2);
        out_fall(h3, t3);
    }
}

// ---------------------------- Integer38 ------------------------------------

// Введення кількості пасажирів N з перевіркою. Повертає true, якщо дані некоректні.
// N - ціле число; кількість пасажирів не може бути від'ємною,
// тому допустимий діапазон [0; 100] (перетин з [-100; 100]).
bool in_N(int& pN)
{
    string line;
    cout << "Integer38." << endl;
    cout << "N (passengers) = ";
    getline(cin, line);                 // читаємо весь рядок
    istringstream iss(line);

    if (!(iss >> pN))                   // не ціле число
        return true;
    iss >> ws;
    if (!iss.eof())                     // зайві символи: "12abc", "12.5"
        return true;
    if (pN < 0 || pN > 100)             // поза діапазоном [0; 100]
        return true;
    return false;
}

// Підрахунок: pFull - кількість повних автобусів, pExtra - пасажири "зайвого" автобуса
void calc_buses(int pN, int& pFull, int& pExtra)
{
    pFull = pN / BUS_CAPACITY;          // цілочисельне ділення
    pExtra = pN % BUS_CAPACITY;         // залишок від ділення
}

// Виведення результату
void out_res(int pN, int pFull, int pExtra)
{
    cout << "Passengers: " << pN << endl;
    cout << "Full buses: " << pFull << endl;
    cout << "Passengers in the extra bus: " << pExtra << endl;
}

// Задача Integer38 цілком
void task_Int38()
{
    int N, full, extra;                 // декларація змінних

    if (in_N(N))                        // некоректні дані - розрахунок не виконуємо
        cout << "N must be an integer from 0 to 100!" << endl;
    else
    {
        calc_buses(N, full, extra);     // підрахунок
        out_res(N, full, extra);        // виведення
    }
}
