#include "TS.h"
#include <iostream>
#define MAX_WEIGHT 120
#define MAX_MONEY 70
using namespace std;

TS::TS() {

}

void TS::init_ans(vector<int> init_ans) {
    this->ans = init_ans;
    best_ans = init_ans;
}

void TS::init_value(vector<int> init_value) {
    this->value = init_value;
}

void TS::init_weight(vector<int> init_weight) {
    this->weight = init_weight;
}

void TS::init_area(vector<int> init_area) {
    this->area = init_area;
}

void TS::init_price(vector<int> init_price) {
    this->price = init_price;
}

int TS::Q1_calculate_value() {
    int sum = 0;
    int total_weight = 0;
    int ans_size = ans.size();
    for (int i = 0; i < ans_size; i++) {
        if (ans[i] == 1) {
            sum += this->value[i];
            total_weight += this->weight[i];
        }
    }
    if (total_weight > MAX_WEIGHT)
        return 0;
    return sum;
}

int TS::Q2_calculate_value() {
    int sum = 0;
    int ans_size = ans.size();
    for (int i = 0; i < ans_size; i++) {
        sum += area[ans[i]-1] * price[i];
    }
    return sum;
}

void TS::Q1_find_next_value() {
    vector<int>::iterator it = ans.begin();
    int ans_size = ans.size();
    int index = 0;
    int max_value = 0;
    for (int i = 0; i < ans_size; i++) {
        if (it[i] == 1)
            it[i] = 0;
        else 
            it[i] = 1;

        if (this->Q1_calculate_value() > max_value && this->not_in_tabu_table()) {
            max_value = this->Q1_calculate_value();
            index = i;
        }
        
        if (it[i] == 1)
            it[i] = 0;
        else 
            it[i] = 1;        
    }

    if (it[index] == 1)
        it[index] = 0;
    else 
        it[index] = 1;
    this->tabu_table.push_back(ans);
    if (tabu_table.size() > 3) {
        vector<vector<int>>::iterator it = tabu_table.begin();
        tabu_table.erase(it);
    }
    current_value = Q1_calculate_value();
    if (current_value > best_value) {
        best_value = current_value;
        best_ans = ans;
    }
}

void TS::Q2_find_next_value() {
    // 邻域搜索为左右互换
    vector<int>::iterator it = ans.begin();
    int ans_size = ans.size();
    int index = 0;
    int max_value = 0;
    for (int i = 0; i < ans_size-1; i++) {
        int temp = it[i];
        it[i] = it[i+1];
        it[i+1] = temp;

        if (this->Q2_calculate_value() > max_value && this->not_in_tabu_table()) {
            max_value = this->Q2_calculate_value();
            index = i;
        }

        temp = it[i];
        it[i] = it[i+1];
        it[i+1] = temp;
    }

    int temp = it[index];
    it[index] = it[index+1];
    it[index+1] = temp;

    this->tabu_table.push_back(ans);
    if (tabu_table.size() > 3) {
        vector<vector<int>>::iterator it = tabu_table.begin();
        tabu_table.erase(it);
    }
    current_value = Q2_calculate_value();
    if (current_value > best_value) {
        best_value = current_value;
        best_ans = ans;
    }
}

bool TS::not_in_tabu_table() {
    int tabu_table_size = this->tabu_table.size();
    for (int i = 0; i < tabu_table_size; i++) {
        if (tabu_table[i] == ans) 
            return 0;
    }
    return 1;
}

void TS::print_ans() {
    vector<int>::iterator it = ans.begin();
    while (it != ans.end()) {
        cout << *it << " ";
        it++;
    }
}

void TS::print_value() {
    cout << current_value;
}