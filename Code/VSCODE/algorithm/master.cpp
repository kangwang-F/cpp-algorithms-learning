#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>

// 冒泡排序
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

// 插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // 插入 key 到正确的位置
    }
}

// 快速排序的分区函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i = i + 1;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// // 快速排序的分区函数
// int partition(std::vector<int>& arr, int low, int high) {
//     int pivot = arr[high];
//     int i = low - 1;
//     for (int j = low; j < high; ++j) {
//         if (arr[j] <= pivot) {
//             i = i + 1;
//             std::swap(arr[i], arr[j]);
//         }
//     }
//     std::swap(arr[i + 1], arr[high]);
//     return i + 1;
// }

// 快速排�??
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 合并两个子数�??
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序
void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 生成随机数组
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);
    for (int i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
    return arr;
}

// 生成有序数组
std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

// 生成逆序数组
std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

// 测量排序算法时间
template <typename SortFunc>
double measureTime(SortFunc sortFunc, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration / 1000.0; // 转换为毫�??
}

int main() {
    std::vector<int> sizes = {10, 100, 1000, 10000};
    std::vector<std::string> distributionNames = {"随机", "有序", "逆序"};
    std::vector<std::function<void(std::vector<int>&)>> sortFunctions = {bubbleSort, selectionSort, insertionSort, 
                                                                       [](std::vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, 
                                                                       [](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }};
    std::vector<std::string> sortFunctionNames = {"冒泡排序", "选择排序", "插入排序", "快速排�??", "归并排序"};

    for (int size : sizes) {
        std::cout << "数据规模: " << size << std::endl;
        for (const auto& distributionName : distributionNames) {
            std::cout << "分布类型: " << distributionName << std::endl;
            std::vector<int> arr;
            if (distributionName == "随机") {
                arr = generateRandomArray(size);
            }
            else if (distributionName == "有序") {
                arr = generateSortedArray(size);
            }
            else {
                arr = generateReverseSortedArray(size);
            }
            for (size_t i = 0; i < sortFunctions.size(); ++i) {
                std::vector<int> tempArr = arr;
                double time = measureTime(sortFunctions[i], tempArr);
                std::cout << sortFunctionNames[i] << " 时间: " << time << " 毫秒" << std::endl;
            }
        }
    }
    return 0;
}