#include <iostream>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

class Thing {
public:
    int id;
    int thingNum;
    string name;
    Thing(int id = 0);
};

Thing::Thing(int id) {
    this->id = id;
}

// return number from 1 to maxValue inclusive
int random(int maxValue) {
    return rand() % maxValue + 1;
}

// ids will range from 1 to maxId
// thingNum will be ascending order
vector<Thing> makeRandomThings(int count, int maxId)
{
    vector<Thing> things;

    for (int i = 0; i < count; i++) {
        things.push_back(Thing{random(maxId)});
    }

    for (int i = 0; i < count; i++) {
        things[i].thingNum = i+1;
    }

    return things;
}

void printVector(vector<Thing> values)
{
    for (unsigned int i = 0; i < values.size(); i++) {
        cout << values[i].thingNum << ", " << values[i].id << endl;
    }
}

// assuming already sorted
bool isStable(vector<Thing> values){
    for (int i = 0; i < (int)values.size()-1; i++) {
        if (values[i].id == values[i+1].id) {
            if (values[i].thingNum > values[i+1].thingNum) {
                return false;
            }
        }
    }
    return true;
}

bool isSorted(vector<Thing> values) {
    for (unsigned int i = 1; i < values.size(); i++) {
        if (values[i].id < values[i-1].id) {
            return false;
        }
    }
    return true;
}

void Merge(vector<Thing> vec, int low, int high, int middle)
{
    int l, j, k;
    vector<Thing> temp;
    l = low;
    j = middle + 1;

    while (l <= middle && j <= high)
    {
        if (vec[l].id < vec[j].id)
        {
            temp.push_back(vec[l]);
            l++;
        }
        else
        {
            temp.push_back(vec[j]);
            j++;
        }
    }

    while (l <= middle)
    {
        temp.push_back(vec[l]);
        l++;
    }

    while (j <= high)
    {
        temp.push_back(vec[j]);
        j++;
    }

    for (l = low; l <= high; l++)
    {
        vec.clear();
        vec = temp;
    }
}

// A function to split array into two parts.
void MergeSort(vector<Thing> vec, int low, int high)
{
    int middle;
    if (low < high)
    {
        middle=(low+high)/2;
        MergeSort(vec, low, middle);
        MergeSort(vec, middle+1, high);

        Merge(vec, low, high, middle);
    }
}

int main(){
    Thing a = 8;
    Thing b = 2;
    Thing c = 0;
    Thing d = 3;
    Thing e = 5;
    vector<Thing> v{a,b,c,d,e};

    printVector(v);
    MergeSort(v,0,4);
    printVector(v);

    return 0;
}
