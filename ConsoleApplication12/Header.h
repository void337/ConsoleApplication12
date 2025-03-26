#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <windows.h>
#include <string>
#include <math.h>
#include <random>
#include <iomanip>
#include <chrono>

using namespace std;

struct Stats {
    long iterations;
    long comparisons;
    long swaps;
};

void clean();
int random_int(int min, int max);
Stats inclusionSort(vector<int>& num, int size);
Stats selectionSort(vector<int>& num, int size);
Stats bubbleSort(vector<int>& num, int size);
Stats quickSort(vector<int>& arr, int low, int high);
int partition(vector<int>& arr, int low, int high, Stats& stat);
void init(vector<int>& numbers, int size, int percent);
void comparison_z1();
void comparison_z2(int num);
void selectionSortDescending(vector<int>& arr, int size);
void variant(int size);

#endif