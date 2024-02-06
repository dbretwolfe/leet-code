#include <vector>
#include <iostream>
#include <set>

using namespace std;

// General purpose example, will handle unsorted inputs.
double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
    if((nums1.size() == 0) && (nums2.size() == 0)) {
        return 0.0;
    }

    multiset<int> sortedNums;

    for (int num : nums1) {
        sortedNums.insert(num);
    }

    for (int num : nums2) {
        sortedNums.insert(num);
    }

    int size = sortedNums.size();
    double median = 0;
    auto it = sortedNums.begin();
    advance(it, size/2);

    if ((size % 2) == 0) {
        median = (static_cast<double>(*it + *(--it)) / 2.0);
    }
    else {
        median = *it;
    }

    return median;
}

// Constrained example for sorted inputs only.
double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
    if((nums1.size() == 0) && (nums2.size() == 0)) {
        return 0.0;
    }

    int index1 = 0;
    int index2 = 0;
    vector<int> sortedNums;

    // Iterate through both source vectors until one of them runs out,
    // sorting them through comparison.
    while ((index1 < nums1.size()) && (index2 < nums2.size())){
        if (nums1[index1] < nums2[index2]) {
            sortedNums.push_back(nums1[index1++]);
        }
        else if (nums1[index1] > nums2[index2]){
            sortedNums.push_back(nums2[index2++]);
        }
        else {
            sortedNums.push_back(nums1[index1++]);
            sortedNums.push_back(nums2[index2++]);
        }
    }

    // If there are still elements left in one of the vectors, put them at the end of the sorted
    // vector.
    while(index1 < nums1.size()) {
        sortedNums.push_back(nums1[index1++]);
    }

    while(index2 < nums2.size()) {
        sortedNums.push_back(nums2[index2++]);
    }

    int size = sortedNums.size();
    double median = 0;
    auto it = sortedNums.begin();
    advance(it, size/2);

    if ((size % 2) == 0) {
        median = (static_cast<double>(*it + *(--it)) / 2.0);
    }
    else {
        median = *it;
    }

    return median;
}

int main() {
    vector<int> nums1 = {1,3};
    vector<int> nums2 = {2};
    cout << findMedianSortedArrays1(nums1, nums2) << endl;
    cout << findMedianSortedArrays2(nums1, nums2) << endl;
}