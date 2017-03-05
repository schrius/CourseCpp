#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ArrSize = 500;

template <class T>
int choosePivot(T* arr, int start, int end, int& NumSwap, int& PivotChoic)
{
    switch(PivotChoic)
    {
        case 0:return start;
        case 1:return start+(rand()%(end-start));
        case 2:if(end-start>3){
            if((arr[start]>=arr[start+1]||arr[start]>=arr[start+2])&&(arr[start]<=arr[start+1]||arr[start]<=arr[start+2]))return start;
            else if((arr[start+1]>=arr[start]||arr[start+1]>=arr[start+2])&&(arr[start+1]<=arr[start]||arr[start+1]<=arr[start+2]))return start+1;
            else return start+2;
            }
            else return start;
        case 3:if(end-start>5)
            {
            T median[5];
            bool SWAP = true;
            for(int i = 0; i<5; i++)
                {
                median[i] = arr[start+i];
                }
            while(SWAP){
                SWAP = false;
                for(int i = 0; i<4; i++)
                    {
                    if(median[i]>median[i+1])
                        {
                        SWAP = true;
                        T temp = median[i];
                        median[i] = median[i+1];
                        median[i+1] = temp;
                        }
                    }
                }
                for(int i = 0; i<5; i++)
                 if(median[2]==arr[start+i])return start+i;
            }
            else return start;
    }
}

template <class T>
int partition (T* arr, int start, int end, int& NumSwap, int& PivotChoic)
{
  int pidx = choosePivot(arr, start, end, NumSwap, PivotChoic);
  T pivot = arr[pidx];
  swap(arr[pidx], arr[end-1]);
     NumSwap++;
  int i = start - 1;
  for (int j = start; j < end; j++) {
    if (arr[j] < pivot)
    {
      swap(arr[++i], arr[j]);
            NumSwap++;
    }
  }
  swap(arr[++i], arr[end-1]);
     NumSwap++;
  return i;
}

template <class T>
void quicksort (T* arr, int begin, int end, int& NumSwap, int& PivotChoic)
{
  if (end - begin<=1) return;
  int pivot = partition(arr, begin, end, NumSwap, PivotChoic);
  quicksort(arr, begin, pivot, NumSwap, PivotChoic);
  quicksort(arr, pivot+1, end, NumSwap, PivotChoic);
}

int main()
{
    srand(time(0));
    int arr[4][ArrSize];
    int NumSwap[4] = {0, 0, 0, 0}, value;

    for(int i =0; i<ArrSize; i++)
        {
        value = rand()% ArrSize+1;
        for(int j =0; j<4; j++)
        arr[j][i] = value;
        }

    for(int i = 0; i<4; i++)
    quicksort(arr[i], 0, ArrSize, NumSwap[i], i);

    cout<<"\nSorting by first element : [" <<NumSwap[0]<<"] swaps"<<endl;
    cout<<"Sorting by random element : [" <<NumSwap[1]<<"] swaps"<<endl;
    cout<<"Sorting by median of first three elements : [" <<NumSwap[2]<<"] swaps"<<endl;
    cout<<"Sorting by median of first five elements : [" <<NumSwap[3]<<"] swaps"<<endl;
}
