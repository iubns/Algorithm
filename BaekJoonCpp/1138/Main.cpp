#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int selected[11] = {0,};
int target[11];

bool check(int n){
    int result[11] = {0,};

    for(int i = 1; i <= n; i++){
        int target = i;
        int count = 0;

        for(int j = 1; j <=n; j++){
            if(target < selected[j]){
                count++;
            }else if(target == selected[j]){
                break;
            }
        }
        result[i] = count;
    }

    for(int i = 1; i <= n; i++){
        if(result[i] != target[i]){
            return false;
        }
    }
    return true;
}

bool select(int step, int n){
    if(step == 0){
        if(!check(n)){
            return false;
        }
        for(int i = 1; i <= n; i++){
            cout << selected[i] << " ";
        }
        cout << "\n";
        return true;
    }

    for(int i = 1; i <= n; i++){
        if(selected[i]){
            continue;
        }

        selected[i] = step;
        if(select(step - 1, n)){
            return true;
        }
        selected[i] = 0;
    }
    return false;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> target[i + 1];
    }

    select(n, n);
    
    return 0;
}
