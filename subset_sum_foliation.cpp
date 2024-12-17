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

// Optimized function to find if any subset has a sum that equals T
bool hasSubsetSumFoliation(const vector<int>& arr, int T) {
    int n = arr.size();
    int m = chooseModulus(n, T);  // Dynamically set modulus m

    unordered_map<int, int> current, next;
    current[0] = 1;  // Base case: sum 0 with subset size 0

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, count] : current) {
            int newModSum = (modSum + num) % m;
            next[newModSum] += count;  // Update the new subset sums
        }

        current = move(next);  // Move next to current to save copying overhead
    }

    // Check if the target modulo exists in the current map
    return current.find(T % m) != current.end();
}


// Optimized function to check if a subset of size s has sum T
bool hasSubsetSumFoliation(const vector<int>& arr, int T, int s) {
    int n = arr.size();
    int m = chooseModulus(n, T);  // Dynamically set modulus m

    // Maps: (modSum, subsetSize) -> count
    unordered_map<int, unordered_map<int, int>> current, next;
    current[0][0] = 1; // Base case: subset size 0, sum 0

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, sizeMap] : current) {
            for (auto& [subsetSize, count] : sizeMap) {
                if (subsetSize < s) {  // Only update if subset size is valid
                    int newModSum = (modSum + num) % m;
                    next[newModSum][subsetSize + 1] += count;  // Update subset size and sum
                }
            }
        }

        current = move(next);  // Move next to current to save copying overhead
    }

    // Check if a subset of size s achieves T % m
    int targetMod = T % m;
    return current.find(targetMod) != current.end() && current[targetMod].find(s) != current[targetMod].end();
}


// Function to find if a subset of size s exists with a sum T and modulus m
bool hasSubsetSumFoliation(const vector<int>& arr, int T, int s, int m
                        /*Choose a sufficiently large modulus to handle collisions*/) {
    int n = arr.size();

    // Maps: (modSum, subsetSize) -> count
    unordered_map<int, unordered_map<int, int>> current, next;
    current[0][0] = 1; // Base case: subset size 0, sum 0

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, sizeMap] : current) {
            for (auto& [subsetSize, count] : sizeMap) {
                if (subsetSize < s) {  // Only update if subset size is valid
                    int newModSum = (modSum + num) % m;
                    next[newModSum][subsetSize + 1] += count;  // Update subset size and sum
                }
            }
        }

        current = move(next);  // Move next to current to save copying overhead
    }

    // Check if a subset of size s achieves T % m
    int targetMod = T % m;
    return current.find(targetMod) != current.end() && current[targetMod].find(s) != current[targetMod].end();
}

// Function to find and print subsets of size s whose sum is T
void printSubsetSumFoliation(const vector<int>& arr, int T) {
    int n = arr.size();
    int m = chooseModulus(n, T);  // Dynamically choose modulus

    unordered_map<int, vector<vector<int>>> current, next;
    current[0] = { { } };  // Base case: subset with sum 0 is empty

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, subsets] : current) {
            int newModSum = (modSum + num) % m;

            for (auto& subset : subsets) {
                vector<int> newSubset = subset;
                newSubset.push_back(num);
                next[newModSum].push_back(newSubset);
            }
        }

        current = move(next);  // Update current state
    }

    // Check for subsets with sum T % m
    int targetMod = T % m;
    if (current.find(targetMod) != current.end()) {
        cout << "Subsets with sum " << T << " are:" << endl;
        for (auto& subset : current[targetMod]) {
            cout << "{ ";
            for (int num : subset) {
                cout << num << " ";
            }
            cout << "}" << endl;
        }
    } else {
        cout << "No subsets with sum " << T << " exist." << endl;
    }
}


// Function to find and print subsets of size s whose sum is T
void printSubsetSumFoliation(const vector<int>& arr, int T, int s) {
    int n = arr.size();
    int m = chooseModulus(n, T);  // Dynamically choose modulus

    unordered_map<int, unordered_map<int, vector<vector<int>>>> current, next;
    current[0][0] = { { } };  // Base case: subset size 0, sum 0 is empty

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, sizeMap] : current) {
            for (auto& [subsetSize, subsets] : sizeMap) {
                if (subsetSize < s) {  // Update only if valid subset size
                    int newModSum = (modSum + num) % m;

                    for (auto& subset : subsets) {
                        vector<int> newSubset = subset;
                        newSubset.push_back(num);
                        next[newModSum][subsetSize + 1].push_back(newSubset);
                    }
                }
            }
        }

        current = move(next);  // Update current state
    }

    // Check for subsets of size s with sum T % m
    int targetMod = T % m;
    if (current.find(targetMod) != current.end() && current[targetMod].find(s) != current[targetMod].end()) {
        cout << "Subsets of size " << s << " with sum " << T << " are:" << endl;
        for (auto& subset : current[targetMod][s]) {
            cout << "{ ";
            for (int num : subset) {
                cout << num << " ";
            }
            cout << "}" << endl;
        }
    } else {
        cout << "No subsets of size " << s << " with sum " << T << " exist." << endl;
    }
}

// Function to find and print subsets of size s whose sum is T and modulus is m
void printSubsetSumFoliation(const vector<int>& arr, int T, int s, int m) {
    int n = arr.size();

    unordered_map<int, unordered_map<int, vector<vector<int>>>> current, next;
    current[0][0] = { { } };  // Base case: subset size 0, sum 0 is empty

    for (int num : arr) {
        next = current;  // Copy current state to next

        for (auto& [modSum, sizeMap] : current) {
            for (auto& [subsetSize, subsets] : sizeMap) {
                if (subsetSize < s) {  // Update only if valid subset size
                    int newModSum = (modSum + num) % m;

                    for (auto& subset : subsets) {
                        vector<int> newSubset = subset;
                        newSubset.push_back(num);
                        next[newModSum][subsetSize + 1].push_back(newSubset);
                    }
                }
            }
        }

        current = move(next);  // Update current state
    }

    // Check for subsets of size s with sum T % m
    int targetMod = T % m;
    if (current.find(targetMod) != current.end() && current[targetMod].find(s) != current[targetMod].end()) {
        cout << "Subsets of size " << s << " with sum " << T << " are:" << endl;
        for (auto& subset : current[targetMod][s]) {
            cout << "{ ";
            for (int num : subset) {
                cout << num << " ";
            }
            cout << "}" << endl;
        }
    } else {
        cout << "No subsets of size " << s << " with sum " << T << " exist." << endl;
    }
}

// Example Usage
int main() {
    vector<int> arr = {-625, -5, -1, -4, 2, 74523, 15, -62, -7, -8, -9, 396, -10};
    int T = 74293; // Target sum

	printSubsetSumFoliation(arr, T, 8);

    return 0;
}
