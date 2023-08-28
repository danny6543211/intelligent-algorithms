#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

// // 坐标结构体
// struct coordinate{
//     double x;
//     double y;
// };

// 城市坐标表 
// unordered_map<int, coordinate> city_table = {
//     {1, {0.4, 0.4439}},
//     {2, {0.2439, 0.1463}},
//     {3, {0.1707, 0.2293}},
//     {4, {0.2293, 0.761}},
//     {5, {0.5171, 0.9414}},
//     {6, {0.8732, 0.6536}},
//     {7, {0.6878, 0.5219}},
//     {8, {0.8488, 0.3609}},
//     {9, {0.6683, 0.2536}},
//     {10, {0.6195, 0.2634}},
// };

// 工人工作表
unordered_map<int, vector<double>> work_table;
// 文件
fstream file;

// 随机初始化工人工作表 (每个工人完成每个工作的时间)
void random_init_work_table() {
    for (int i = 1; i <= 10; i++) {
        vector<double> temp;
        for (int j = 0; j < 10; j++) {
            // 随机0 ~ 10的数
            temp.push_back((double) 10*rand()/RAND_MAX);
        }
        work_table[i] = temp;
    }
}

// 随机初始解
void random_init_ans(vector<int> &ans) {
    srand(time(NULL));
    int temp_ans[10];
    for (int i = 0; i < 10; i++) {
        temp_ans[i] = rand()%100;
    }
    for (int i = 0; i < 10; i++) {
        int index;
        int max = 0;
        for (int j = 0; j < 10; j++) {
            if (temp_ans[j] > max) {
                max = temp_ans[j];
                index = j;
            }
        }
        ans.push_back(index+1);
        temp_ans[index] = 0;
    }
}

// // 计算两城市距离
// double calculate_city_distance(int city1, int city2) {
//     double x_difference = fabs(city_table[city1].x - city_table[city2].x);
//     double y_difference = fabs(city_table[city1].y - city_table[city2].y);
//     double distance = sqrt( pow(x_difference, 2) + pow(y_difference, 2) );
//     return distance;
// }

// 计算总长度
// double calculate_value(vector<int> ans) {
//     double sum = 0;
//     for (int i = 0; i < 10-1; i++) {
//         sum += calculate_city_distance(ans[i], ans[i+1]);   
//     }
//     // 最后一个和第一个的距离
//     sum += calculate_city_distance(ans[10], ans[0]);
//     return sum;
// }

double calculate_value(vector<int> ans) {
    double sum = 0;
    for (int i = 1; i < 10; i++) {
        // i号工人做 ans[i]号工作
        sum += work_table[i][ans[i]];
    }
    return sum;
}


// 取随机邻域
void random_neighborhood_search(vector<int> &ans) {
    int left;
    int right;
    while (1) {
        left = rand()%10;
        right = rand()%10;
        if (left != right)
            break;
    }
    vector<int>::iterator it = ans.begin();
    int temp = ans[left];
    ans[left] = ans[right];
    ans[right] = temp;
}

// 打印工人的工作表
void print_work_table() {
    for (int i = 1; i <= 10; i++) {
        file << "工人:" << i << " ";
        file << "完成工作所需时间: ";
        for (int j = 1; j <= 10; j++) {
            file <<work_table[i][j] << " ";
        }
        file << endl;
    }
}

int main() 
{   
    srand(time(NULL));
    // 初始温度
    double T = 1000;
    // 文件
    file.open("result.txt", ios::out);
    // 降温系数
    double a = 0.99;
    // 最小温度
    double e = 0.01;
    // 随机初始解
    vector<int> ans;
    random_init_ans(ans);
    random_init_work_table();
    print_work_table();

    // cout << calculate_value(ans);   
    while (1) {
        vector<int> temp_ans = ans;
        // 随机邻域搜索
        // 邻域定义为两个解的元素互换
        random_neighborhood_search(temp_ans);
        double old_value = calculate_value(ans);
        double new_value = calculate_value(temp_ans);
        // 如果解更好就直接用
        if (new_value < old_value) {
            ans = temp_ans;
            continue;
        } 
        // 如果解更差以一定概率接受
        else if (exp(-(new_value-old_value)/T) > (double)rand()/RAND_MAX) {
            ans = temp_ans;
            continue;
        }
        // 降温
        T *= a;
        // 温度小余e停止
        if (T < e) 
            break;
        // 打印数据到文件
        for (int i = 0; i < 10; i++) {
            file << ans[i] << " ";
        }
        file << "    " << calculate_value(ans) << endl;    
    }
    file.close();
    
    return 0;
}