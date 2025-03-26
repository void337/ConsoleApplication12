#include <iostream>
#include "Header.h"

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    comparison_z1();
    cout << "Введите количество элементов в массиве для сравнения\n"; int n; cin >> n;
    while (!cin || cin.peek() != '\n' || n <= 0) {
        clean();
        cout << "\nВведите число > 0" << endl; cin >> n;
    }
    comparison_z2(n);
    cout << "Введите количество элементов для массива из второго задания\n"; int m; cin >> m;
    while (!cin || cin.peek() != '\n' || m <= 0) {
        clean();
        cout << "\nВведите число > 0" << endl; cin >> m;
    }
    variant(m);
}

