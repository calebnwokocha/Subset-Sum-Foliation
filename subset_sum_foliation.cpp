#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Function to dynamically choose modulus m
int chooseModulus(int n, int T) {
    // Heuristic: choose m as a value larger than the maximum possible sum
    // but less than a large number to avoid excessive space usage.
    return min(T + 1, n * 100);  // Example heuristic for choosing m dynamically
}

// Function to find if any subset has a sum that equals T
bool subsetSumFoliation(const vector<int>& arr, int T) {
    int n = arr.size();
    int m = chooseModulus(n, T);  // Dynamically set modulus m based on input size and target

    // Layered representation: map (subset size -> {sum modulo m -> count})
    vector<unordered_map<int, int>> layers(n + 1);  // Now we track all subset sizes up to n
    layers[0][0] = 1;  // Base case: sum 0 with subset size 0

    for (int num : arr) {
        // Update layers from largest subset size down to avoid overwriting
        for (int i = n; i > 0; --i) {
            for (auto& [modSum, count] : layers[i - 1]) {
                int newModSum = (modSum + num) % m;
                layers[i][newModSum] += count;
            }
        }
    }

    // Check if any subset of any size achieves T % m
    int targetMod = T % m;
    for (int i = 0; i <= n; ++i) {
        if (layers[i].find(targetMod) != layers[i].end()) {
            return true;  // A subset of some size has the desired sum
        }
    }
    return false;
}

// Example Usage
int main() {
    vector<int> arr = {-5, -1, -4, 2, 15, -62, -7, -8, -9, -10};
    int T = -10; // Target sum

    if (subsetSumFoliation(arr, T)) {
        cout << "Subset with sum " << T << " exists." << endl;
    } else {
        cout << "No such subset exists." << endl;
    }

    return 0;
}