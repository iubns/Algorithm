#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int brokenNumbers[10] = {0};

bool canIGo(int target){
    if(target == 0){
        return !brokenNumbers[0];
    }
    while(target > 0){
        int num = target % 10;
        if(brokenNumbers[num]){
            return false;
        }
        target /= 10;
    }
    return true;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int target;
    std::cin >> target;

    int breakButonCount;
    std::cin >> breakButonCount;
    for(int index = 0; index < breakButonCount; index++){
        int num;
        std::cin >> num;
        brokenNumbers[num] = 1;
    }

    int result = abs(target - 100);

    for(int i = 0; i < 1'000'000; i++){
        if(canIGo(i)){
            result = min(result, (int)(abs(target - i) + to_string(i).length()));
        }
    }
    cout << result << endl;
    return 0;
}
