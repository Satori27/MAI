#include "lib.h"

int main() {
    int number;
    cin >> number;
    pair < int, int > answer = closest_pair_tonum(number);

    if (answer.first == 0) {
        cout << "Very big number or not valuable input" << "\n";
        return 0;
    }

    cout << answer.first << " " << answer.second << "\n";
}