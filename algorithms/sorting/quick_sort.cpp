#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

// int partition(vector<int>& arr, int lp, int rp) {
//   while (lp!=rp) {
//     if (arr[rp] >= arr[lp]) {
//       rp--;
//     }

//     else if (arr[lp+1] <= arr[lp]) {
//       swap(arr[lp+1], arr[lp]);
//       lp++;
//     }

//     else {
//       swap(arr[lp+1], arr[rp]);
//     }
//   }
//   return lp; // pivot index
// }

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

void quick_sort(vector<int>& arr, int lp, int rp) {
  // Base case:
  // 1. partition to sort has only one element (lp == rp)
  // 2. partition to sort has no element (lp > rp)
  if (lp >= rp) return;

  // We choose initial pivot as lp (first element in arr)
  int pivot = partition(arr, lp, rp);

  // Recursively sort left and right partition
  quick_sort(arr, lp, pivot - 1);
  quick_sort(arr, pivot + 1, rp);
}

void sort(vector<int>& arr) {
  int n = arr.size();
  quick_sort(arr, 0, n - 1);
}

TEST_CASE("partition function") {
  vector<int> arr1 = {3, 1, 2, 5, 4};
  int pivot1 = partition(arr1, 0, arr1.size() - 1);
  REQUIRE(pivot1 == 2);
  REQUIRE(is_sorted(arr1.begin(), arr1.begin() + pivot1));
  REQUIRE(!is_sorted(arr1.begin() + pivot1 + 1, arr1.end()));

  vector<int> arr2 = {5, 4, 3, 2, 1};
  int pivot2 = partition(arr2, 0, arr2.size() - 1);
  REQUIRE(pivot2 == 4);
  REQUIRE(!is_sorted(arr2.begin(), arr2.begin() + pivot2));
  REQUIRE(is_sorted(arr2.begin() + pivot2 + 1, arr2.end()));
}

TEST_CASE("quick_sort function") {
  vector<int> arr1 = {3, 1, 2, 5, 4};
  quick_sort(arr1, 0, arr1.size() - 1);
  REQUIRE(is_sorted(arr1.begin(), arr1.end()));

  vector<int> arr2 = {5, 4, 3, 2, 1};
  quick_sort(arr2, 0, arr2.size() - 1);
  REQUIRE(is_sorted(arr2.begin(), arr2.end()));
}

TEST_CASE("sort function") {
  vector<int> arr1 = {3, 1, 2, 5, 4};
  sort(arr1);
  REQUIRE(is_sorted(arr1.begin(), arr1.end()));

  vector<int> arr2 = {5, 4, 3, 2, 1};
  sort(arr2);
  REQUIRE(is_sorted(arr2.begin(), arr2.end()));

  vector<int> arr3 = {};
  sort(arr3);
  REQUIRE(is_sorted(arr3.begin(), arr3.end()));

  vector<int> arr4 = {1};
  sort(arr4);
  REQUIRE(is_sorted(arr4.begin(), arr4.end()));
}

TEST_CASE("sort function with repeated elements") {
  vector<int> arr = {3, 3, 3, 3, 3};
  sort(arr);
  REQUIRE(is_sorted(arr.begin(), arr.end()));
}

TEST_CASE("sort function with negative elements") {
  vector<int> arr = {-1, -3, -2, -5, -4};
  sort(arr);
  REQUIRE(is_sorted(arr.begin(), arr.end()));
}

TEST_CASE("sort function with mixed elements") {
  vector<int> arr = {1, -1, 0, -2, 2};
  sort(arr);
  REQUIRE(is_sorted(arr.begin(), arr.end()));
}
