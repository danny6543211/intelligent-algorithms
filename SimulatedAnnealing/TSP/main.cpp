#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

// 坐标结构体
struct coordinate{
    double x;
    double y;
};

// 城市坐标表
unordered_map<int, coordinate> city_table = {
    {1, {0.4, 0.4439}},
    {2, {0.2439, 0.1463}},
    {3, {0.1707, 0.2293}},
    {4, {0.2293, 0.761}},
    {5, {0.5171, 0.9414}},
    {6, {0.8732, 0.6536}},
    {7, {0.6878, 0.5219}},
    {8, {0.8488, 0.3609}},
    {9, {0.6683, 0.2536}},
    {10, {0.6195, 0.2634}},
};

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

// 计算两城市距离
double calculate_city_distance(int city1, int city2) {
    double x_difference = fabs(city_table[city1].x - city_table[city2].x);
    double y_difference = fabs(city_table[city1].y - city_table[city2].y);
    double distance = sqrt( pow(x_difference, 2) + pow(y_difference, 2) );
    return distance;
}

// 计算总长度
double calculate_value(vector<int> ans) {
    double sum = 0;
    for (int i = 0; i < 10-1; i++) {
        sum += calculate_city_distance(ans[i], ans[i+1]);   
    }
    // 最后一个和第一个的距离
    sum += calculate_city_distance(ans[10], ans[0]);
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

int main() 
{   
    srand(time(NULL));
    fstream file;
    file.open("result.txt", ios::out);
    // 初始温度
    double T = 1000;
    // 降温系数
    double a = 0.99;
    // 最小温度
    double e = 0.01;
    // 随机初始解
    vector<int> ans;
    random_init_ans(ans);
    
    while (1) {
        vector<int> temp_ans = ans;
        random_neighborhood_search(temp_ans);
        // 如果解更好就直接用
        double old_value = calculate_value(ans);
        double new_value = calculate_value(temp_ans);
        if (new_value < old_value) {
            ans = temp_ans;
            continue;
        } 
        // 如果值更差以一定概率接受
        else if (exp(-(new_value-old_value)/T) > (double)rand()/RAND_MAX) {
            ans = temp_ans;
            continue;
        }
        // 降温
        T *= a;
        if (T < e) 
            break;
        // print
        for (int i = 0; i < 10; i++) {
            file << ans[i] << " ";
        }
        file << "    " << calculate_value(ans) << endl;    
    }
    file.close();
    
    return 0;
}