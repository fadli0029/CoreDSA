#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

int partition(vector<int>& arr, int left, int right) {
    // Uses Lomuto partition scheme
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

int quick_select(vector<int>& arr, int left, int right, int k) {
    int pivot_index = partition(arr, left, right);

    if (k == pivot_index) {
        return arr[k];
    } else if (k < pivot_index) {
        return quick_select(arr, left, pivot_index - 1, k);
    } else {
        return quick_select(arr, pivot_index + 1, right, k);
    }
}

int find_kth_smallest(std::vector<int>& arr, int k) {
  return quick_select(arr, 0, arr.size()-1, k);
}

int find_kth_largest(std::vector<int>& arr, int k) {
  return quick_select(arr, 0, arr.size()-1, arr.size() - k);
}

TEST_CASE("Partition function", "[partition]") {
    vector<int> arr = {3, 2, 1, 5, 4};
    int pivot = partition(arr, 0, arr.size() - 1);

    SECTION("Pivot is within bounds") {
        REQUIRE(pivot >= 0);
        REQUIRE(pivot < arr.size());
    }

    SECTION("Elements to the left of pivot are smaller or equal to arr[pivot]") {
        for (int i = 0; i < pivot; ++i) {
            REQUIRE(arr[i] <= arr[pivot]);
        }
    }

    SECTION("Elements to the right of pivot are greater or equal to arr[pivot]") {
        for (int i = pivot + 1; i < arr.size(); ++i) {
            REQUIRE(arr[i] >= arr[pivot]);
        }
    }
}

TEST_CASE("Quick Select function", "[quick_select]") {
    vector<int> arr = {3, 2, 1, 5, 4};
    int k = 2;

    SECTION("Quick select finds the correct kth smallest element") {
        int result = quick_select(arr, 0, arr.size() - 1, k);
        vector<int> sorted_arr = arr;
        std::nth_element(sorted_arr.begin(), sorted_arr.begin() + k, sorted_arr.end());
        REQUIRE(result == sorted_arr[k]);
    }

    SECTION("Edge cases for quick select") {
        REQUIRE(quick_select(arr, 0, arr.size() - 1, 0) == *min_element(arr.begin(), arr.end()));
        REQUIRE(quick_select(arr, 0, arr.size() - 1, arr.size() - 1) == *max_element(arr.begin(), arr.end()));
    }
}
