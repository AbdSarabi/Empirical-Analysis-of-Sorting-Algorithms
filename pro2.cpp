#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace chrono;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void copyArray(vector<int> &source, vector<int> &destination) {
    for (int i = 0; i < source.size(); ++i) {
        destination[i] = source[i];
    }
}

void generateTestData(vector<int> &arr, int size, string type) {
    arr.clear();
    random_device rd;
    mt19937 gen(rd());

    if (type == "random") {
        uniform_int_distribution<int> dis(0, size * 10);
        for (int i = 0; i < size; ++i) {
            arr.push_back(dis(gen));
        }
    } else if (type == "partially_sorted") {
        uniform_int_distribution<int> dis(0, size * 10);
        for (int i = 0; i < size / 2; ++i) {
            arr.push_back(dis(gen));
        }
        sort(arr.begin(), arr.end());
        for (int i = size / 2; i < size; ++i) {
            arr.push_back(dis(gen));
        }
    } else if (type == "reverse_order") {
        uniform_int_distribution<int> dis(0, size * 10);
        for (int i = 0; i < size; ++i) {
            arr.push_back(dis(gen));
        }
        sort(arr.rbegin(), arr.rend());
    }
}

void bubbleSort(vector<int> &arr) {
    int flag = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                flag = 1;
            }
        }

        if (flag == 0) {
            break;
        }
    }
}

void selectionSort(vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        swap(arr[min_index], arr[i]);
    }
}

vector<int> merge(vector<int> &left, vector<int> &right) {
    vector<int> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i++]);
        } else {
            result.push_back(right[j++]);
        }
    }

    while (i < left.size()) {
        result.push_back(left[i++]);
    }

    while (j < right.size()) {
        result.push_back(right[j++]);
    }

    return result;
}

void mergeSort(vector<int> &arr) {
    if (arr.size() <= 1) {
        return;
    }

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    mergeSort(left);
    mergeSort(right);

    arr = merge(left, right);
}

int partition(vector<int> &array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            ++i;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[high]);
    return i + 1;
}

void quickSort(vector<int> &array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main() {
    vector<int> arr;

    // Generate and Test Data for Bubble Sort
    generateTestData(arr, 1000, "random");
    auto start_time_bubble_random = high_resolution_clock::now();
    bubbleSort(arr);
    auto stop_time_bubble_random = high_resolution_clock::now();
    auto duration_bubble_random = duration_cast<nanoseconds>(stop_time_bubble_random - start_time_bubble_random);
    cout << "Execution Time BUBBLE SORT (Random): " << duration_bubble_random.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "partially_sorted");
    auto start_time_bubble_partially_sorted = high_resolution_clock::now();
    bubbleSort(arr);
    auto stop_time_bubble_partially_sorted = high_resolution_clock::now();
    auto duration_bubble_partially_sorted = duration_cast<nanoseconds>(stop_time_bubble_partially_sorted - start_time_bubble_partially_sorted);
    cout << "Execution Time BUBBLE SORT (Partially Sorted): " << duration_bubble_partially_sorted.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "reverse_order");
    auto start_time_bubble_reverse_order = high_resolution_clock::now();
    bubbleSort(arr);
    auto stop_time_bubble_reverse_order = high_resolution_clock::now();
    auto duration_bubble_reverse_order = duration_cast<nanoseconds>(stop_time_bubble_reverse_order - start_time_bubble_reverse_order);
    cout << "Execution Time BUBBLE SORT (Reverse Order): " << duration_bubble_reverse_order.count() << " nanoseconds" << endl;

    // Generate and Test Data for Selection Sort
    generateTestData(arr, 1000, "random");
    auto start_time_selection_random = high_resolution_clock::now();
    selectionSort(arr);
    auto stop_time_selection_random = high_resolution_clock::now();
    auto duration_selection_random = duration_cast<nanoseconds>(stop_time_selection_random - start_time_selection_random);
    cout << "Execution Time SELECTION SORT (Random): " << duration_selection_random.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "partially_sorted");
    auto start_time_selection_partially_sorted = high_resolution_clock::now();
    selectionSort(arr);
    auto stop_time_selection_partially_sorted = high_resolution_clock::now();
    auto duration_selection_partially_sorted = duration_cast<nanoseconds>(stop_time_selection_partially_sorted - start_time_selection_partially_sorted);
    cout << "Execution Time SELECTION SORT (Partially Sorted): " << duration_selection_partially_sorted.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "reverse_order");
    auto start_time_selection_reverse_order = high_resolution_clock::now();
    selectionSort(arr);
    auto stop_time_selection_reverse_order = high_resolution_clock::now();
    auto duration_selection_reverse_order = duration_cast<nanoseconds>(stop_time_selection_reverse_order - start_time_selection_reverse_order);
    cout << "Execution Time SELECTION SORT (Reverse Order): " << duration_selection_reverse_order.count() << " nanoseconds" << endl;

    // Generate and Test Data for Merge Sort
    generateTestData(arr, 1000, "random");
    auto start_time_merge_random = high_resolution_clock::now();
    mergeSort(arr);
    auto stop_time_merge_random = high_resolution_clock::now();
    auto duration_merge_random = duration_cast<nanoseconds>(stop_time_merge_random - start_time_merge_random);
    cout << "Execution Time MERGE SORT (Random): " << duration_merge_random.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "partially_sorted");
    auto start_time_merge_partially_sorted = high_resolution_clock::now();
    mergeSort(arr);
    auto stop_time_merge_partially_sorted = high_resolution_clock::now();
    auto duration_merge_partially_sorted = duration_cast<nanoseconds>(stop_time_merge_partially_sorted - start_time_merge_partially_sorted);
    cout << "Execution Time MERGE SORT (Partially Sorted): " << duration_merge_partially_sorted.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "reverse_order");
    auto start_time_merge_reverse_order = high_resolution_clock::now();
    mergeSort(arr);
    auto stop_time_merge_reverse_order = high_resolution_clock::now();
    auto duration_merge_reverse_order = duration_cast<nanoseconds>(stop_time_merge_reverse_order - start_time_merge_reverse_order);
    cout << "Execution Time MERGE SORT (Reverse Order): " << duration_merge_reverse_order.count() << " nanoseconds" << endl;

    // Generate and Test Data for Quick Sort
    generateTestData(arr, 1000, "random");
    auto start_time_quick_random = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto stop_time_quick_random = high_resolution_clock::now();
    auto duration_quick_random = duration_cast<nanoseconds>(stop_time_quick_random - start_time_quick_random);
    cout << "Execution Time QUICK SORT (Random): " << duration_quick_random.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "partially_sorted");
    auto start_time_quick_partially_sorted = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto stop_time_quick_partially_sorted = high_resolution_clock::now();
    auto duration_quick_partially_sorted = duration_cast<nanoseconds>(stop_time_quick_partially_sorted - start_time_quick_partially_sorted);
    cout << "Execution Time QUICK SORT (Partially Sorted): " << duration_quick_partially_sorted.count() << " nanoseconds" << endl;

    generateTestData(arr, 1000, "reverse_order");
    auto start_time_quick_reverse_order = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto stop_time_quick_reverse_order = high_resolution_clock::now();
    auto duration_quick_reverse_order = duration_cast<nanoseconds>(stop_time_quick_reverse_order - start_time_quick_reverse_order);
    cout << "Execution Time QUICK SORT (Reverse Order): " << duration_quick_reverse_order.count() << " nanoseconds" << endl;

    return 0;
}
