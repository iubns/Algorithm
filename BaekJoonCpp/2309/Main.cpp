#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> answer;
int tall[9];

int findSum(int depth, int index, int sum){
    if(depth > 7){
        return 0;
    }

    if(depth == 7 && sum == 100){
        return 1;
    }

    for(int i = index; i < 9; i++){
        if(findSum(depth + 1, i + 1, sum + tall[i])){
            answer.push_back(tall[i]);
            return 1;
        }
    }
        
    return 0;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    for(int i = 0; i < 9; i++){
        std::cin >> tall[i];
    }
    findSum(0, 0, 0);
    std::sort(answer.begin(), answer.end());
    auto iter = answer.begin();
    while(iter != answer.end()){
        std::cout << *iter++ << std::endl;
    }

    return 0;
}
