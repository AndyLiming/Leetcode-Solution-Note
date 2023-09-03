#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"
class Tag_sort {
public:
  //quick sort
  void quick_sort_core(vector<int>& nums, int start, int end) {
    if (start >= end) return;
    int pivot = nums[start];
    int i = start, j = end;
    while (i < j) {
      while (i<j && nums[j]>pivot) --j;
      if (i < j) swap(nums[i], nums[j]);
      while (i < j && nums[i] <= pivot) ++i;
      if (i < j) swap(nums[i], nums[j]);
    }
    if (i > start) quick_sort_core(nums, start, i - 1);
    if (i < end) quick_sort_core(nums, i + 1, end);
  }
  void quick_sort(vector<int>& nums) {
    if (nums.size() <= 1) return;
    quick_sort_core(nums, 0, nums.size() - 1);
  }
  //heap sort
  void heapAdjust(vector<int>& nums, int start, int len) {
    int i = start, j = 2 * start + 1, key = nums[start];
    while (j < len) {
      if (j + 1 < len && nums[j + 1] > nums[j])j++;
      if (nums[j] < key) break;
      nums[i] = nums[j];
      i = j;
      j = 2 * i + 1;
    }
    nums[i] = key;
  }
  void heapSort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1) return;
    int len = nums.size();
    for (int i = len / 2 - 1; i >= 0; --i) {
      heapAdjust(nums, i, len);
    }
    for (int i = len - 1; i >= 0; --i) {
      int tmp = nums[i];
      nums[i] = nums[0];
      nums[0] = tmp;
      heapAdjust(nums, 0, i);
    }
  }

  void insertSort(vector<int>& nums) {
    for (int i = 1; i < nums.size(); ++i) {
      for (int j = i; j > 0; --j) {
        if (nums[j] < nums[j - 1]) {
          int tmp = nums[j];
          nums[j] = nums[j - 1];
          nums[j - 1] = tmp;
        }
      }
    }
  }
  /////////////////////////////////////
  void bubbleSort(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = 0; j < nums.size() - i - 1; ++j) {
        if (nums[j] > nums[j + 1]) {
          int tmp = nums[j];
          nums[j] = nums[j + 1];
          nums[j + 1] = tmp;
        }
      }
    }
  }
  void mergeRec(vector<int>& nums, int start, int end, vector<int>& helper) {
    if (start >= end) return;
    int mid = (start + end) / 2;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    mergeRec(nums, start1, end1, helper);
    mergeRec(nums, start2, end2, helper);
    int k = start;
    while (start1 <= end1 && start2 <= end2) {
      helper[k++] = nums[start1] < nums[start2] ? nums[start1++] : nums[start2++];
    }
    while (start1 <= end1) helper[k++] = nums[start1++];
    while (start2 <= end2) helper[k++] = nums[start2++];
    for (k = start; k <= end; ++k) {
      nums[k] = helper[k];
    }
  }
  void mergeSort(vector<int>& nums) {
    vector<int>helper(nums.begin(), nums.end());
    mergeRec(nums, 0, nums.size() - 1, helper);
  }
};