#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <random>
#include "GA.h"
#include "GENE.h"
#include "global.h"

int main() {
    srand(time(NULL));

    GA test;
    cout << "initial        gene                                     adaptive_value" << endl;
    // 創建初始種群
    test.create_init_population();
    test.print_all_gene();
    // 限定最大迭帶次數
    int iterations;
    for (iterations = 0; iterations < MAX_ITERATIONS; iterations++) {
        // 選擇
        test.roulette_choice();
        // 交叉運算
        test.cross();
        // 尋找最好基因並保護
        test.find_the_best();
        // 變異運算
        test.genetic_variation();
        // 更新適應值
        test.update_adaptive_value();
        // 是否停止
        if (test.is_stop())
            break;
    }
    cout << "initial       gene                                     adaptive_value" << endl;
    test.print_all_gene();

    cout << endl << "after" << iterations << "times" << endl;
    cout << "the best value is " << test.best_one_value << endl;
    
    return 0;
}