#include <iostream>
#include <functional>
#include <vector>
#include "gtest/gtest.h"

using namespace std;

class Thing{
public:
    int num;
    int id;
    Thing(int id);
};

Thing::Thing(int id) {
    this->id = id;
}

bool isSorted(const vector<Thing>& values, function<bool(const Thing& a, const Thing& b)> comp) {
    for (unsigned int i = 1; i < values.size(); i++) {
        if (comp(values[i], values[i-1])) {
            return false;
        }
    }
    return true;
}

void printVector(vector<Thing> things){
    for(unsigned int i = 0; i < things.size(); i++){
        cout << things[i].id << ", " << things[i].num << endl;
    }
}

bool compareThingsById(Thing a, Thing b){
    return a.id <= b.id;
}

void merge(vector<Thing>& values, int low, int high, int mid, function<bool(Thing, Thing)> comp){

    vector<Thing> temp;

    int LIndex = low;
    int MIndex = mid + 1;

    while(LIndex <= mid && MIndex <= high){

        if(comp(values[LIndex], values[MIndex])){
            temp.push_back(values[LIndex]);
            LIndex++;
        }
        else{
            temp.push_back(values[MIndex]);
            MIndex++;
        }
    }

    while(LIndex <= mid){
        temp.push_back(values[LIndex]);
        LIndex++;
    }

    while(MIndex <= high){
        temp.push_back(values[MIndex]);
        MIndex++;
    }

    for (int i = low; i <= high; i++){
        values[i] = temp[i-low];
    }
}

void mergeSortR(vector<Thing>& vec, int LIndex, int HIndex, function<bool(Thing, Thing)> comp){

    int MIndex;

    if(LIndex < HIndex){
        MIndex = (LIndex+HIndex)/2;
        mergeSortR(vec, LIndex, MIndex, comp);
        mergeSortR(vec, MIndex+1, HIndex, comp);
        merge(vec, LIndex, HIndex, MIndex, comp);
    }

}

void mergeSort(vector<Thing>& vec, function<bool(Thing, Thing)> comp){
    int LIndex = 0;
    int HIndex = vec.size()-1;

    mergeSortR(vec, LIndex, HIndex, comp);
}

TEST(SortTest, isVectorSorted) {
    Thing a(1);
    Thing b(5);
    Thing c(7);
    Thing d(2);
    vector<Thing> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    mergeSort(v, compareThingsById);
    ASSERT_TRUE(isSorted(v, compareThingsById));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

