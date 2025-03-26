#include <iostream>
#include "Header.h"

void clean() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

int random_int(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

Stats inclusionSort(vector<int>& num, int size)
{
    Stats stat;
    stat.iterations = 0, stat.comparisons = 0, stat.swaps = 0;
    for (int i = 1; i < size; i++)
    {
        stat.iterations++; stat.comparisons++;
        int value = num[i];
        int index = i;
        while ((index > 0) && (num[index - 1] > value))
        {
            stat.swaps++;
            num[index] = num[index - 1];
            index--;
        }
        num[index] = value; 
    }
    return stat;
}

void selectionSortDescending(vector<int>& arr, int size) {
    int max_index; 
    for (int i = 0; i < size - 1; i++) {
        max_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] > arr[max_index]) max_index = j; }
        if (max_index != i) swap(arr[i], arr[max_index]);     
    }
}

Stats selectionSort(vector<int>& num, int size)
{
    Stats stat;
    stat.iterations = 0, stat.comparisons = 0, stat.swaps = 0;
    int min_index;
    for (int i = 0; i < size - 1; i++) {
        stat.iterations++;
        min_index = i;
        for (int j = i + 1; j < size; j++) {
            stat.iterations++;
            stat.comparisons++;
            if (num[j] < num[min_index]) min_index = j;
        }
        if (min_index == i) continue;
        swap(num[i], num[min_index]);
        stat.swaps++;
    }
    return stat;
}

Stats bubbleSort(vector<int>& num, int size)
{
    Stats stat;
    stat.iterations = 0, stat.comparisons = 0, stat.swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        stat.iterations++;
        for (int j = (size - 1); j > i; j--) {
            stat.iterations++;
            stat.comparisons++;
            if (num[j - 1] > num[j]) {
                stat.swaps++;
                swap(num[j - 1], num[j]);
            }
        }
    }
    return stat;
}


int partition(vector<int>& arr, int low, int high, Stats& stat) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        stat.iterations++;
        stat.comparisons++;
        if (arr[j] < pivot) {
            i++;
            if (i != j) { swap(arr[i], arr[j]); stat.swaps++;}
        }
    }
    swap(arr[i + 1], arr[high]);
    stat.swaps++;
    return i + 1;
}

void init(vector<int>& numbers, int size, int percent)
{
    for (int i = 0; i < size; i++) numbers.push_back(random_int(-100, 100));
    if (percent == 0 || percent == -1) {
        if (percent == -1) reverse(numbers.begin(), numbers.end());
    }
    else {
        float p = percent / 100;
        Stats s = quickSort(numbers, 0, round(size * p));
    }
}

void comparison_z1()
{
    Stats stats;
    int sizes[] = { 20, 500, 1000, 3000, 5000, 10000 };
    vector<vector<int>> vectors, vectors_copy;
    for (int i = 0; i < 6; i++) {
        vector<int> n;
        init(n, sizes[i], 0);
        vectors.push_back(n);
        vectors_copy.push_back(n);
    }

    cout << "\nСортировка с помощью прямого включения\n";

    cout << left << setw(10) << "Размер";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < 6; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = inclusionSort(vectors_copy[i], sizes[i]);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(10) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nСортировка с помощью прямого выбора\n";

    cout << left << setw(10) << "Размер";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < 6; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = selectionSort(vectors_copy[i], sizes[i]);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(10) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nСортировка с помощью прямого обмена\n";

    cout << left << setw(10) << "Размер";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < 6; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = bubbleSort(vectors_copy[i], sizes[i]);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(10) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nМетод быстрой сортировки\n";

    cout << left << setw(10) << "Размер";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < 6; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = quickSort(vectors_copy[i], 0, sizes[i] - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(10) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);
}

Stats quickSort(vector<int>& arr, int low, int high) {
    Stats stat;
    stat.iterations = 0, stat.comparisons = 0, stat.swaps = 0;
    if (low < high) {
        int p = partition(arr, low, high, stat);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
    return stat;
}

void comparison_z2(int num) {
    Stats stats;
    vector<vector<int>> vectors, vectors_copy;
    vector<int> n;
    init(n, num, 0);
    vectors.push_back(n);
    init(n, num, -1);
    vectors.push_back(n);
    init(n, num, 25);
    vectors.push_back(n);
    init(n, num, 50);
    vectors.push_back(n);
    init(n, num, 75);
    vectors.push_back(n);
    for (auto e : vectors) vectors_copy.push_back(e);
    string sizes[] = { "обычный массив", "в обратную сторону", "25%", "50%", "75%" };

    cout << "\n\nВсе массивы размера " << num << endl;
    cout << "\nСортировка с помощью прямого включения\n";

    cout << left << setw(30) << "Степень сортировки";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = inclusionSort(vectors_copy[i], num);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(30) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nСортировка с помощью прямого выбора\n";

    cout << left << setw(30) << "Степень сортировки";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = selectionSort(vectors_copy[i], num);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(30) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nСортировка с помощью прямого обмена\n";

    cout << left << setw(30) << "Степень сортировки";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = bubbleSort(vectors_copy[i], num);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(30) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

    cout << "\nМетод быстрой сортировки\n";

    cout << left << setw(30) << "Степень сортировки";
    cout << setw(15) << "Итерации";
    cout << setw(15) << "Сравнения";
    cout << setw(15) << "Обмены";
    cout << setw(15) << "Время (мкс)" << endl;
    cout << string(85, '-') << endl;

    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        stats = quickSort(vectors_copy[i], 0, num - 1);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << setw(30) << sizes[i];
        cout << setw(15) << stats.iterations;
        cout << setw(15) << stats.comparisons;
        cout << setw(15) << stats.swaps;
        cout << setw(15) << duration.count() << endl;
    }

    vectors_copy.clear();
    for (auto e : vectors) vectors_copy.push_back(e);

}

void variant(int size) {
    vector<int> numbers;
    vector<int> n;
    int q;

    cout << "\n\nСписок:\n";
    for (int i = 0; i < size; i++) {
        numbers.push_back(random_int(10, 500));
        cout << numbers[i] << " ";
    }
    cout << "\nНовый список:\n";
    for (int i = 0; i < size; i++) {
        if (numbers[i] >= 10 && numbers[i] <= 99) 
            q = numbers[i] / 10 - numbers[i] % 10;
        else 
            q = numbers[i] / 100 - numbers[i] % 10 - numbers[i] / 10 % 10;
        n.push_back(q);
        cout << n[i] << " ";
    }
    selectionSortDescending(n, size);
    cout << "\nОтсортированный список:\n"; 
    for(auto e : n) 
        cout << e << " ";
}





