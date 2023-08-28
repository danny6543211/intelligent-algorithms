#define X_MAX 100
#define X_MIN 0
#define Y_MAX 100
#define Y_MIN 0
#define CITY_COUNT 30
#define tabu_table_legth 5
#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

struct coordinate {
    double x;
    double y;
};

class TS {
    public:
        TS();
        // 随机初始化城市的位置
        void random_city_location(int city_count);
        // 随机初始解
        void random_init_ans();
        // 计算两城市距离
        double calculate_city_distance(int city_number1, int city_number2);
        // 打印城市坐标
        void print_city_location();
        // 打印解向量
        void print_ans();
        // 计算全部城市连起来的距离
        double calculate_value(vector<int> ans);
        // 打印解的距离
        void print_value();
        // 禁忌搜索并更新解
        void tabu_search();
        // 判断解是否在禁忌表里
        bool in_tabu_table(vector<int> temp_ans);
        // 交换两个解的位置
        void swap_two_ans_unit(vector<int> &temp_ans, int number_a, int number_b);
        // 打印最优解
        void print_best_ans();
        // 打印最优值
        void print_best_value();
    public:
        unordered_map<int, coordinate> city_table;
        vector<int> ans;
        vector<vector<int>> tabu_table;
        double best_value;
        vector<int> best_ans;
};

TS::TS() {
    best_value = INT_MAX;
}

void TS::random_city_location(int city_count) {
    srand(time(NULL));
    coordinate temp;
    for (int i = 1; i <= city_count; i++) {
        temp.x = rand()%(X_MAX-X_MIN);
        temp.y = rand()%(Y_MAX-Y_MIN);
        city_table[i] = temp;
    }
}

void TS::random_init_ans() {
    srand(time(NULL));
    int temp_ans[CITY_COUNT];
    for (int i = 0; i < CITY_COUNT; i++) {
        temp_ans[i] = rand()%100;
    }
    for (int i = 0; i < CITY_COUNT; i++) {
        int index;
        int max = 0;
        for (int j = 0; j < CITY_COUNT; j++) {
            if (temp_ans[j] > max) {
                max = temp_ans[j];
                index = j;
            }
        }
        ans.push_back(index+1);
        temp_ans[index] = 0;
    }
    best_ans = ans;
}

double TS::calculate_city_distance(int city_number1, int city_number2) {
    double x_difference = fabs(city_table[city_number1].x - city_table[city_number2].x);
    double y_difference = fabs(city_table[city_number1].y - city_table[city_number2].y);
    double distance = sqrt( pow(x_difference, 2) + pow(y_difference, 2) );
    return distance;
}

void TS::print_city_location() {
    for (int i = 1; i <= CITY_COUNT; i++) {
        cout << "city:" << setw(2) << i << "   "; 
        cout << "x:";
        cout << right << setw(2) << city_table[i].x;
        cout << "  " << "y:";
        cout << right << setw(2) << city_table[i].y;
        cout << endl;
    }
}

void TS::print_ans() {
    cout << "ans: ";
    for (int i = 0; i < CITY_COUNT; i++) {
        cout << right << ans[i] << " ";
    }
}

double TS::calculate_value(vector<int> temp_ans) {
    double sum = 0;
    for (int i = 0; i < CITY_COUNT-1; i++) {
        sum += calculate_city_distance(temp_ans[i], temp_ans[i+1]);   
    }
    // 最后一个和第一个的距离
    sum += calculate_city_distance(temp_ans[CITY_COUNT], temp_ans[0]);
    return sum;
}

void TS::print_value() {
    cout << "value: " << calculate_value(ans); 
}

void TS::tabu_search() {
    int min_value = INT_MAX;
    int index_i;
    int index_j;
    for (int i = 0; i < CITY_COUNT-1; i++) {
        for (int j = i+1; j < CITY_COUNT; j++) {
            swap_two_ans_unit(ans, i, j);
            if (calculate_value(ans) < min_value && !in_tabu_table(ans)) {
                min_value = calculate_value(ans);
                index_i = i;
                index_j = j;
            }
            swap_two_ans_unit(ans, i, j);
        }
    }
    swap_two_ans_unit(ans, index_i, index_j);
    if (tabu_table.size() > tabu_table_legth) {
        tabu_table.erase(tabu_table.begin());
    }
    tabu_table.push_back(ans);
    if (calculate_value(ans) < best_value) {
        best_value = calculate_value(ans);
        best_ans = ans;
    }
}

void TS::swap_two_ans_unit(vector<int> &temp_ans, int index_a, int index_b) {
    vector<int>::iterator it = temp_ans.begin();
    int temp = it[index_a];
    it[index_a] = it[index_b];
    it[index_b] = temp;
}

bool TS::in_tabu_table(vector<int> temp_ans) {
    vector<vector<int>>::iterator it = tabu_table.begin();
    while (it != tabu_table.end()) {
        if (*it == temp_ans) {
            return 1;
        }
        it++;
    }
    return 0;
}
    
void TS::print_best_ans() {
    cout << "best ans: ";
    for (int i = 0; i < CITY_COUNT; i++) {
        cout << right << best_ans[i] << " ";
    }
    cout << endl;
}

void TS::print_best_value() {
    cout << "best value: ";
    print_value();
}

int main() {
    // 禁忌搜索
    // 编码方式为到达城市顺序的向量
    // 禁忌对象为解向量
    // 停止准则为运行50次
    // 渴望水平函数为总距离的最小值
    // 邻域搜索采用交换两个解的测略
    TS test;
    // 随机初始化城市的位置
    test.random_city_location(CITY_COUNT);
    // 随机初始化解
    test.random_init_ans();
    // 打印初始信息
    test.print_city_location();
    cout << endl << "initial:" << endl;
    test.print_ans(); cout << endl;
    test.print_value(); cout << endl << endl << endl;
    // 打印搜索过的信息
    cout << "computing 50 times:" << endl << endl;
    for (int i = 0; i < 50; i++) {
        // 禁忌搜索
        test.tabu_search();
        test.print_ans(); cout << "   ";
        test.print_value();
        cout << endl;
    }

    cout << endl;
    test.print_best_ans();
    test.print_best_value();

    return 0;
}
