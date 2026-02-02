#include <iostream>

using namespace std;

int gcd(int a, int b) {
    int c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    
    return c;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int count;
    cin >> count;

    for (int index = 0; index < count; index++) {
        int M, N, x, y;
        cin >> M >> N >> x >> y;

        int limit = lcm(M, N);
        int ans = -1;

        for (int i = x; i <= limit; i += M) {
            int ny = (i - 1) % N + 1;
            
            if (ny == y) {
                ans = i;
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
