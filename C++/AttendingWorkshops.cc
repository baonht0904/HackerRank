#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops

#include <stdlib.h>
#define MAX_TIME 3000

struct Workshop {
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    Workshop *arr;
};

Available_Workshops* initialize (int start_time[], int duration[], int n) {
    auto ptr = new Available_Workshops;
    ptr->n = n;
    ptr->arr = new Workshop[n];
    for(auto i = 0; i < n; ++i) {
        ptr->arr[i].start_time = start_time[i];
        ptr->arr[i].duration = duration[i];
        ptr->arr[i].end_time = start_time[i] + duration[i];
    }
    
    return ptr;
}

int CompareWorkshopByDuration(const void* lhs, const void* rhs) {
    return (*(Workshop*)lhs).end_time - (*(Workshop*)rhs).end_time;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    if(ptr->n <= 0)
    {
        return 0;
    }
    qsort(ptr->arr, ptr->n, sizeof(Workshop), CompareWorkshopByDuration);
    int last_end = 0, count = 0;
    for (int i = 0; i < ptr->n; ++i) {
        // Greedy search
        if (ptr->arr[i].start_time >= last_end) {
            last_end = ptr->arr[i].end_time;
            count++;
        }
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
