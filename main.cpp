#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std::chrono;
using namespace std;
template<class type>
class Sorter{
public:
    virtual  type sorter(vector<type> &list, int listSize){};
    void Swap(vector<type> &itemsList, int firstItem, int secondItem){
        type temp=itemsList[firstItem];
        itemsList[firstItem]=itemsList[secondItem];
        itemsList[secondItem]=temp;}
};
template<class type>
class SelectionSort:public Sorter<type>{
public:
    int minimum(vector<type> &myList, int firstIndex, int lastIndex ){
        int minLocation=firstIndex;
        for (int i = firstIndex+1; i <=lastIndex ; ++i)
            if (myList[minLocation]>myList[i])
                minLocation=i;
        return minLocation;
    }
    type selectionSort(vector<type> &myList, int size){
        int minLocation;
        for (int i = 0; i < myList.size(); ++i) {
            minLocation=minimum(myList ,i, myList.size()-1);
            Sorter<type>::Swap(myList,i, minLocation);}}
    type sorter(vector<type> theList, int sizeOfList){
        selectionSort(theList, sizeOfList);
    }
    type sorter(vector<type> &list, int size){
        selectionSort(list, size);
    }
    //------------------------------------------------------------------------------------------------------------------
    //REVERSED SELECTION SORT
    int maximum(vector<type> &myList, int firstIndex, int lastIndex ){
        int maxLocation=firstIndex;
        for (int i = firstIndex+1; i <=lastIndex ; ++i)
            if (myList[maxLocation]<myList[i])
                maxLocation=i;
        return maxLocation;
    }
    type reversedSelectionSort(vector<type> &myList, int size){
        int maxLocation;
        for (int i = 0; i < myList.size(); ++i) {
            maxLocation=maximum(myList ,i, myList.size()-1);
            Sorter<type>::Swap(myList,i, maxLocation);}}

};
template<class type>
class QuickSort: public Sorter<type>{
public:
    //partition function
    int Partition(vector<type> &theList, int first, int last){
        int i=first;
        int pivot=theList[first];
        for (int j = first+1; j <= last; ++j) {
            if (theList[j]<pivot){
                i++;
                Sorter<type>::Swap(theList ,j, i);
            }}
        Sorter<type>::Swap(theList, first, i);
        return i;}
    void quickSort(vector<type> &myList,int firstIndex, int lastIndex){
        if(firstIndex<lastIndex){
            int pivotPosition;
            pivotPosition=Partition(myList ,firstIndex,lastIndex);
            quickSort(myList ,firstIndex, pivotPosition-1);
            quickSort(myList ,pivotPosition+1, lastIndex);}
    }
    type sorter(vector<type> &arrayOfItems, int arrLength){
        quickSort(arrayOfItems, 0, arrLength);}
    int Partition0fReversed(vector<type> &myList, int first, int last){
        int i=first;
        int pivot=myList[first];
        for (int j = first+1; j <= last; ++j) {
            if (myList[j]>pivot){
                i++;
                Sorter<type>::Swap(myList, j, i);
            }}
        Sorter<type>::Swap(myList, first, i);
        return i;}
    void reversedQuickSort(vector<type> &list,int firstIndex, int lastIndex){
        if(firstIndex<lastIndex){
            int pivotPosition;
            pivotPosition=Partition0fReversed(list ,firstIndex,lastIndex);
            quickSort(list, firstIndex, pivotPosition-1);
            quickSort(list,pivotPosition+1, lastIndex);}
    }
};
template<class type>
class TestBed:public SelectionSort<type>, public QuickSort<type>{
protected:
    long long sum=0;
    vector<int>randomList;

public:
    TestBed(vector<type> rndmList){
        for (int i = 0; i < rndmList.size(); ++i) {
            randomList.push_back(rndmList[i]);
        }
    }
    void GenerateRandomList(int min, int max, int size){
        for (int i = 0; i < size; ++i)
            randomList.push_back((rand()%max+min));}
    void GenerateReverseOrderedList(int min, int max, int sizeRanList){
        GenerateRandomList(min, max, sizeRanList);
        SelectionSort<type>::reversedSelectionSort(randomList, sizeRanList);
    }
    long long RunOnce(Sorter<type> *sorter, vector<type> &data, int size){
        auto start1= high_resolution_clock::now();
        sorter->sorter(data, size);
        auto stop1= high_resolution_clock::now();
        auto executionTime1= duration_cast<microseconds>(stop1-start1);
        return executionTime1.count();
        }
    long long RunAndAverage(Sorter<type> *sorter, string typeOfData, int min, int max, int size, int sets_num){
        if (typeOfData=="Random") {
            for (int i = 0; i < sets_num; ++i) {
                GenerateRandomList(min, max, size);
                sum+=RunOnce(sorter, randomList, size);;}
            cout<<sum/sets_num<<setw(15)<<size<<endl;
        }
        else{
            for (int i = 0; i < sets_num; ++i) {
                GenerateRandomList(min, max, size);
                auto start=high_resolution_clock::now();
                sorter->sorter(randomList, size);
                for (int j = 0, back=size-1; j < size; ++j, back--) {
                    swap(randomList[j], randomList[back]);}
                auto stop=high_resolution_clock::now();
                auto executionTime=duration_cast<microseconds>(stop-start);
                sum+=executionTime.count();
            }
            cout<<sum/sets_num<<setw(15)<<size<<endl;
        }
    }
    long long RunExperiment(Sorter<type>*sorter, string typeOfData, int min, int max, int minRange, int maxRange, int sets_num, int step) {
        if (typeOfData == "Random") {
            cout<<"{Average}"<<setw(15)<<"{size of each set}\n";
            for (int i = minRange; i <= maxRange; i += step) {
                RunAndAverage(sorter, typeOfData, min, max, i, sets_num);
            }
        }
        else {
            cout << "{Average}" << setw(15) << "{size of each set}\n";
            for (int i = minRange; i <= maxRange; i += step) {
                RunAndAverage(sorter, typeOfData, min, max, i, sets_num);
            }
        }
    }
    void display(){
        for (int i = 0; i < randomList.size(); ++i) {
            cout<<randomList[i]<<" ";
        }
    }
};
int main() {
    vector<int> myVector;
    TestBed<int> test(myVector);
    Sorter<int> *sort=new SelectionSort<int>;
    cout<<"we use selection sort"<<endl<<"----------------------------------------------------------------------------------"<<endl;
    cout<<"{Random Data}"<<endl<<"-------------------------------------------------"<<endl;
    test.RunExperiment(sort, "Random", 100, 100000, 100, 1000, 5, 200);
    cout<<"we use selection sort"<<endl<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<"{Reversed}"<<"---------------------------------------------------------"<<endl;
    test.RunExperiment(sort, "Reversed", 100, 100000, 100, 1000, 5, 200);
    Sorter<int> *sort2=new QuickSort<int>;
    cout<<"we use Quick sort"<<endl<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<"{Random Data}"<<endl<<"-------------------------------------------------"<<endl;
    test.RunExperiment(sort2, "Random", 100, 100000, 100, 1000, 5, 200);
    cout<<"we use Quick sort"<<endl<<"-----------------------------------------------------------------------------------"<<endl;
    cout<<"{Reversed Data}"<<endl<<"-------------------------------------------------"<<endl;
    test.RunExperiment(sort2, "Reversed", 100, 100000, 100, 1000, 25, 200);
    return 0;
}