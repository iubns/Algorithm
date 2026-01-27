#include <iostream>

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int E, S, M;

    std::cin >> E >> S >> M;

    int countE = 1, countS = 1, countM = 1, year = 1;
    while (true)
    {
        if(E == countE && S == countS && M == countM){
            std::cout << year << std::endl;
            return 0;
        }

        countE = (countE % 15) + 1;
        countS = (countS % 28) + 1;
        countM = (countM % 19) + 1;
        year++;
    }
    
    return 0;
}
