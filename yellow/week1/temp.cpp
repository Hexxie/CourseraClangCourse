#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main()
{
    int nr_elements, element;
    int64_t sum = 0, average = 0;
    vector<int> daily_temp;
    vector<int> above_avg;

    cin >> nr_elements;
    for (size_t i = 0; i < nr_elements; ++i)
    {
        cin >> element;
        sum += element;
        daily_temp.push_back(element);
    }

    average = sum / nr_elements;

    for (size_t i = 0; i < nr_elements; ++i)
    {
        if(daily_temp[i] > average)
        {
            above_avg.push_back(i);
        }
    }

    cout<<above_avg.size()<<endl;
    for(int i = 0; i < above_avg.size(); i++)
    {
        cout<<above_avg[i]<<" ";
    }
    cout<<endl;

    return 0;
}