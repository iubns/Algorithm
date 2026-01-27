#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int targetNum;
    while(std::cin >> targetNum){
        int num = 1;
        int count = 1;
        while (true)
        {
            if((num %= targetNum) == 0){
                std::cout << count << std::endl;
                break;
            }
            num *= 10;
            num += 1;
            count++;
        }
    }
    return 0;
}