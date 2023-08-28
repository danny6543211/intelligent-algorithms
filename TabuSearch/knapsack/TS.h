#pragma once
#include <vector>
using namespace std;

class TS {
    public:
        TS();
        void init_ans(vector<int> inint_ans);
        void init_value(vector<int> init_value);
        void init_weight(vector<int> init_weight);
        void init_area(vector<int> init_area);
        void init_price(vector<int> init_price);
        int Q1_calculate_value();
        int Q2_calculate_value();
        void Q1_find_next_value();
        void Q2_find_next_value();
        bool not_in_tabu_table();
        void print_ans();
        void print_value();
    public:
        vector<int> ans;
        vector<int> value;
        vector<int> weight;
        vector<int> area;
        vector<int> price;        
        vector<vector<int>> tabu_table;
        vector<int> best_ans;
        int current_value;
        int best_value;
};