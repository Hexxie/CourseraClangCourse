#include <iostream>
#include "Matrix.h"

using namespace std;

int main()
{
    Matrix m1, m2, m3;
    cout<< "Enter matrix 1. Row, size then elements: ";
    cin >> m1;

    cout << "You've entered the next matrix 1 \n:"<< m1;

    cout<< "Enter matrix 2. Row, size then elements: ";
    cin >> m2;

    cout << "You've entered the next matrix 2 \n:"<< m2;

    cout<< "Calculating the sum... ";
    try {
        m3 = m1 + m2;
        cout << "Calculated matrix m3: \n"<< m3;
    } catch (invalid_argument e)
    {
        cout<<e.what();
    }



}