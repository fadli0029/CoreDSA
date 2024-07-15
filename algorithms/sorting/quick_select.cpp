#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

int partition(vector<int>& arr) {
  int n = arr.size();
  int lp = 0, rp = n - 1;

  while (lp!=rp) {
    if (arr[rp] >= arr[lp]) {
      rp--;
    }

    else if (arr[lp+1] <= arr[lp]) {
      swap(arr[lp+1], arr[lp]);
      lp++;
    }

    else {
      swap(arr[lp+1], arr[rp]);
    }
  }
  return lp; // pivot index
}

int quick_select(vector<int>& arr, int k) {
  // Find the pivot by placing the first element
  // in the correct position
  int pivot = partition(arr);

  if (k==pivot) {
    return arr[pivot];
  }

  else if (k < pivot) {
    vector<int> left(arr.begin(), arr.begin()+pivot);
    return quick_select(left, k);
  }

  else {
    vector<int> right(arr.begin()+pivot+1, arr.end());
    return quick_select(right, k-(pivot+1));
  }
}

TEST_CASE("Partition function", "[partition]") {
    vector<int> arr = {3, 2, 1, 5, 4};
    int pivot = partition(arr);

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
        int result = quick_select(arr, k);
        vector<int> sorted_arr = arr;
        std::nth_element(sorted_arr.begin(), sorted_arr.begin() + k, sorted_arr.end());
        REQUIRE(result == sorted_arr[k]);
    }

    SECTION("Edge cases for quick select") {
        REQUIRE(quick_select(arr, 0) == *min_element(arr.begin(), arr.end()));
        REQUIRE(quick_select(arr, arr.size() - 1) == *max_element(arr.begin(), arr.end()));
    }
}
