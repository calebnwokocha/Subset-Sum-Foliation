#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to find if a subset of size `s` exists with a sum `T`
bool subsetSumFoliation(const vector<int>& arr, int T, int s) {
    int n = arr.size();
    int m = 10007; // Choose a sufficiently large modulus to handle collisions
    
    // Layered representation: map (subset size -> {sum modulo m -> count})
    vector<unordered_map<int, int>> layers(s + 1);
    layers[0][0] = 1; // Base case: sum 0 with subset size 0

    for (int num : arr) {
        // Update layers from largest subset size down to avoid overwriting
        for (int i = s; i > 0; --i) {
            for (auto& [modSum, count] : layers[i - 1]) {
                int newModSum = (modSum + num) % m;
                layers[i][newModSum] += count;
            }
        }
    }

    // Check if any subset of size `s` achieves `T % m`
    int targetMod = T % m;
    return layers[s].find(targetMod) != layers[s].end();
}

// Example Usage
int main() {
    vector<int> arr = {3, 1, 4, 2, 5, 6, 7, 8, 9, 10};
    int T = 10; // Target sum
    int s = 5; // Subset size

    if (subsetSumFoliation(arr, T, s)) {
        cout << "Subset of size " << s << " with sum " << T << " exists." << endl;
    } else {
        cout << "No such subset exists." << endl;
    }

    return 0;
}