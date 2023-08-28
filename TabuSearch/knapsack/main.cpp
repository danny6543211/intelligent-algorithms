#include <iostream>
#include <vector>
#include "TS.h"
using namespace std;

int main() 
{
    // Q1 背包问题
    // ans =  1  0  1  0  1  0  1
    //  Pi = 30 60 25  8 10 40 60
    //  Wi = 40 40 30  5 15 35 30
    cout << "Q1:" << endl;
    TS Q1;
    Q1.init_ans( {1, 0, 1, 0, 1, 0, 1} );
    Q1.init_value( {30, 60, 25, 8, 10, 40, 60} );
    Q1.init_weight( {40, 40, 30, 5, 15, 35, 30} );
    Q1.best_value = Q1.Q1_calculate_value();
    // 五次迭代
    for (int i = 0; i < 5; i++) {
        Q1.Q1_find_next_value();
        cout << "ans: ";
        Q1.print_ans();
        cout << "   ";
        cout << "value: ";
        Q1.print_value();
        cout << endl;
    }
    cout << endl << "after 5 times" << endl;
    cout << "best ans:" << endl;
    Q1.print_ans();
    cout << endl;
    cout << "best value:" << endl;
    cout << Q1.best_value;
    cout << endl << endl;

    cout << endl;
    cout << endl;

    // Q2 建厂问题
    // ans =  1 2 3 4
    //  Ri =  9 8 4 5
    //  Pi =  3 2 4 1
    cout << "Q2:" << endl;
    TS Q2;
    Q2.init_ans( {1, 2, 3, 4} );
    Q2.init_area( {9, 8, 4, 5} );
    Q2.init_price( {3, 2, 4, 1} );
    Q2.best_value = Q2.Q2_calculate_value();
    // 三次迭代
    for (int i = 0; i < 3; i++) {
        Q2.Q2_find_next_value();
        cout << "   ans: ";
        Q2.print_ans();
        cout << "   ";
        cout << "value: ";
        Q2.print_value();
        cout << endl;
    }
    cout << endl << "after 3 times" << endl;
    cout << "best ans:" << endl;
    Q2.print_ans();
    cout << endl;
    cout << "best value:" << endl;
    cout << Q2.best_value;
    cout << endl;

    return 0;
}