#include <iostream>
#include <vector>
#include <algorithm>

char map[50][50];

void swap(std::vector<int> a, std::vector<int> b){
    char temp = map[a[0]][a[1]];
    map[a[0]][a[1]] = map[b[0]][b[1]];
    map[b[0]][b[1]] = temp;   
}

int getMaxLine(int mapSize){
    int max = 0;
    int count = 1;
    for(int rowIndex = 0; rowIndex < mapSize; rowIndex++){
        count = 1;
        for(int colIndex = 0; colIndex < mapSize; colIndex++){
            if(colIndex < mapSize - 1){
                if(map[rowIndex][colIndex] == map[rowIndex][colIndex + 1]){
                    count++;
                }else{
                    count = 1;
                }
                max = std::max(count, max);
            }
        }
    }

    for(int colIndex = 0; colIndex < mapSize; colIndex++){
        count = 1;
        for(int rowIndex = 0; rowIndex < mapSize; rowIndex++){
            if(rowIndex < mapSize - 1){
                if(map[rowIndex][colIndex] == map[rowIndex + 1][colIndex]){
                    count++;
                }else{
                    count = 1;
                }
                max = std::max(count, max);
            }
        }
    }
    return max;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);


    int mapSize;
    std::cin >> mapSize;
    for(int rowIndex = 0; rowIndex < mapSize; rowIndex++){
        for(int colIndex = 0; colIndex < mapSize; colIndex++){
            std::cin >> map[rowIndex][colIndex];
        }
    }

    int answer = 0;

    for(int rowIndex = 0; rowIndex < mapSize; rowIndex++){
        for(int colIndex = 0; colIndex < mapSize; colIndex++){
            if(colIndex < mapSize - 1){
                if(map[rowIndex][colIndex] != map[rowIndex][colIndex + 1]){
                    swap({rowIndex, colIndex}, {rowIndex, colIndex + 1});
                    answer = std::max(answer, getMaxLine(mapSize));
                    swap({rowIndex, colIndex + 1}, {rowIndex, colIndex});
                }
            }

            if(rowIndex < mapSize - 1){
                if(map[rowIndex][colIndex] != map[rowIndex + 1][colIndex]){
                    swap({rowIndex, colIndex}, {rowIndex + 1, colIndex});
                    answer = std::max(answer, getMaxLine(mapSize));
                    swap({rowIndex + 1, colIndex}, {rowIndex, colIndex});
                }
            }
        }
    }

    std::cout << answer << std::endl;

    return 0;
}
