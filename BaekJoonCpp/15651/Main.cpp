#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int selected[9] = {0,};

void next(int step, int n, int length){
    if(step == 0){
        for(int i = 0; i < length; i++){
            printf("%d ", selected[i]);
        }
        printf("\n");
        return;
    }

    for(int i = 1; i <= n; i++){
        selected[length - step] = i;
        next(step - 1, n, length);
        selected[length - step] = 0;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);


    int max, length;
    cin >> max >> length;
    next(length, max, length);
}