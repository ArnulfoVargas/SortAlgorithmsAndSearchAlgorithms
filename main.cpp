#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void PrintArray(int* arr, int size){
    for (int i = 0; i < size; i++)
    {
        std::cout << "[" << arr[i] <<"] "; 
    }
    std::cout<<std::endl;
}

int* InitEmptyArray(int size){
    int* arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
    return arr;
}

int ArrayLenght(int* array, int size){
    int max = INT_MIN;

    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return max + 1;
}

void CountingSort(int* array, int arraySize){
    int arrayLenght = ArrayLenght(array, arraySize);
    int* endResult = InitEmptyArray(arraySize);
    int* count = InitEmptyArray(arrayLenght);

    for (int i = 0; i < arraySize; i++)
    {
        count[ array[i] ] += 1;
    }

    for (int i = 1; i < arrayLenght; i++)
    {
        count[i] += count[i-1];
    }

    for (int i = 0; i < arraySize; i++)
    {
        endResult[count[array[i]] - 1] = array[i];
        count[array[i]] -= 1;
    }
    
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = endResult[i];
    }
}

void CountigSortForRadix(int* array, int arraySize, int exponent){
    int* endResult = InitEmptyArray(arraySize);
    int* count = InitEmptyArray(10);

    for (int i = 0; i < arraySize; i++)
    {
        int index = array[i] / exponent;
        count[ index % 10 ] += 1;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i-1];
    }

    for (int i = arraySize -1; i >= 0; i--)
    {
        int index = array[i] / exponent;
        endResult[ count[ index % 10 ] - 1 ] = array[i];
        count[ index % 10 ] -= 1;
    }
    
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = endResult[i];
    }
}

void RadixSort(int* array, int size){
    
    int max = INT_MIN;
    int exp = 1;

    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    
    while (max / exp >= 1){
        CountigSortForRadix(array, size, exp);
        exp *= 10;
    }
}

void ShellSort(int* arr, int size){
    int jumps = size / 2;
    int index = 0, aumentedIndex = jumps;
    int holder = 0;
    bool change = false;

    do{
        change = false;
        index = 0;
        aumentedIndex = jumps;

        while(aumentedIndex < size){

            if (arr[index] > arr[aumentedIndex])
            {
                holder = arr[aumentedIndex];
                arr[aumentedIndex] = arr[index];
                arr[index] = holder;

                change = true;
            }
            index++;
            aumentedIndex = index + jumps;
        }

        if(!change)
            jumps--;
        
    }while(jumps > 0);
}

void SortArraySelection(int* arr, int size){
    std::string response;
    char val;

    std::cout<<"What sorting algorithm you want to use?\n1-Counting Sort\n2-Radix Sort\n3-Shell Sort\n";
    std::cin >> response;

    val = response[0];

    std::cout<<"Before:\n";
    PrintArray(arr, 100);

    switch (val)
    {
    case '1':
        CountingSort(arr, 100);
        break;
    case '2':
        RadixSort(arr, 100);
        break;
    case '3':
        ShellSort(arr, 100);
        break;
    default:
        SortArraySelection(arr, size);
        break;
    }

    std::cout<<"\nAfter:\n";
    PrintArray(arr, 100);
}

void SequentialSearch(int* arr, int size){
    int num = 0;
    int index = 0;
    bool found = false;

    std::cout << "What number are you looking for?\n";
    std::cin >> num;

    for (int i = 0; i < size; i++)
    {
        if(num == arr[i])
        {
            index = i;
            found = true;
            break;
        }
    }

    if (found){
        std::cout << "Number " << num << " found at index: " << index << "\n";
    }
    else{
        std::cout << "Number " << num << " not found\n";
    }
}

void BinarySearch(int* arr, int size){
    int num = 0;
    int index = 0;
    bool found = false;
    int min = 0, max = size, current = size / 2;


    std::cout << "What number are you looking for?\n";
    std::cin >> num;

    while(!found){
        if (num == arr[current])
        {
            found = true;
            index = current;
            break;
        }else{
            if (num > arr[current])
            {
                min = current;
            }
            else{
                max = current;
            }

            if(max - min <= 1 && num != arr[min] && num != arr[max])
                break;
            else
                current = min + ((max - min) / 2);
        }
    }

    if (found){
        std::cout << "Number " << num << " found at index: " << index << "\n";
    }
    else{
        std::cout << "Number " << num << " not found\n";
    }
}


void SearchDigit(int* arr, int size){
    std::string response;
    char val;

    std::cout<<"What search algorithm you want to use?\n1-Sequential Search\n2-Binary Search\n";
    std::cin >> response;
    val = response[0];

    switch (val)
    {
    case '1':
        SequentialSearch(arr, size);
        break;
    case '2':
        BinarySearch(arr, size);
        break;
    default:
        SearchDigit(arr, size);
        break;
    }
}

int main(){
    int* digits = new int[100];
    bool retry = false;

    srand(time(NULL));

    for (int i = 0; i < 100; i++)
    {
        digits[i] = rand() % 256;
    }
    
    do
    {
        system("CLS");

        SortArraySelection(digits, 100);
        SearchDigit(digits, 100);

        std::cout << "Try again?\n0 - No\n1 - Yes\n";
        std::cin >> retry;

    } while (retry);
}