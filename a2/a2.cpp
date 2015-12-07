/*  
    ##
    ## A2P3 r_rise QUESTION
    ## Mark Luo: 20509972
    ##
*/
#include <iostream>
#include <vector>
//#define DEBUG

using namespace std;

// Vector of integer, denoted as ivec
typedef vector<int> ivec;

// Forward declared functions
ivec get_max_r_rise_array(ivec, int, float);
ivec find_longest_r_rise_array(ivec, ivec, float);
void print_return_statement(ivec, ivec);
int get_first_r_rise_index(ivec, ivec);

// DEBUG HELPER
template <class T> ostream& operator<<(ostream &os, const vector<T> &vec);

// Main function:
// O(nlog_2 n)
int main(int argc, char const *argv[])
{

    int n;
    ivec r_rise_array;
    float r;

    // Get n
    cin >> n;

    // Get all value for array
    for (int i = 0; i < n; i++) {
        int tempVal;
        cin >> tempVal;
        // Populate array
        r_rise_array.push_back(tempVal);
    }

    // Get r
    cin >> r;

    // Get array of the longest r_rise array from the given array
    // O(nlog_2 n)
    ivec return_array = get_max_r_rise_array(r_rise_array, n, r);

    // Return statement
    // O(n)

#ifdef DEBUG
    cout << "r = " << r << endl;
    cout << "Original Array: " << r_rise_array <<endl;
    cout << "Derived Array:  " << return_array << endl;
#endif

    print_return_statement(return_array, r_rise_array);
    return 0;
}


// get_max_r_rise_array
// Vector<int>, int, float
//
// Using Divide and Conquer method, divide the given array in half
// Find longest r_rise for each half, and then find the longest
// possible r_rise from the last element of A_L to the end of A_R
//
// Runtime for get_max_r_rise_array:
// O(log_2 n) recursive calls
// Each recursive iteration calls method find_longest_r_rise_array
// See find_longest_r_rise_array for runtime details
ivec get_max_r_rise_array(ivec current_array, int n, float r) {

    ivec return_array;

    // Base case of Divide and Conquer
    if (n == 1) {
        return_array = current_array;
    } else {
        
        // Get index for 1,...,n / 2 and n / 2 + 1,...,n
        int n_L, n_R;;
        n_L = n_R = n / 2;

        // Get left and Right sub array from given array
        ivec A_L(current_array.begin(), current_array.begin() + n_L);
        ivec A_R(current_array.begin() + n_R, current_array.end());
        
        // Find the max_r_rise array from Left and Right
        // Recursive call here:
        // n -> n/2
        ivec left_array_r_rise = get_max_r_rise_array(A_L, n_L, r);
        ivec right_array_r_rise = get_max_r_rise_array(A_R, n - n_R, r);

        // Find the max_r_rise from Left and Right
        // GIVEN ALGORITHM: Screen from index n / 2 to 0 for A_L
        //                  Screen from n / 2 + 1 to n for A_R
        ivec combined_array_r_rise = find_longest_r_rise_array(A_L, A_R, r);

        // Conditional deduction to find the largest r_rise from the three
        // derived r_rises
        return_array = left_array_r_rise;
        if (return_array.size() < combined_array_r_rise.size()) {
            return_array = combined_array_r_rise;
        }
        if (return_array.size() < right_array_r_rise.size()){
            return_array = right_array_r_rise;
        }
    }

    return return_array;
}

// find_longest_r_rise_array
// vector<int>, vector<int>, float
//
// Aim to find the longest chain of r_rise from both A_L and A_R array
//
// Runtime of find_longest_r_rise_array:
// Traverse through both at most n/2 array: O(n)
//
ivec find_longest_r_rise_array(ivec left_array, ivec right_array, float r) {
    
    ivec return_array;
    
    // Reverse traversing through left_array
    for (int i = left_array.size()-1; i >= 0; i--) {
        // Initial population of return_array
        // Give return_array the last value of left_array
        if (return_array.size()) {
            if (return_array[0] <= left_array[i] * r) {
                break;
            }
        }
        return_array.insert(return_array.begin(),left_array[i]);
    }

    // Forawrd traversing through right_array
    for (int i = 0; i < right_array.size(); i++) {
        // Check if more chains of consecutive r_rise is possible from A_R
        if (right_array[i] > return_array[return_array.size() - 1] * r) {
            return_array.push_back(right_array[i]);
        } else {
            break;
        }
    }

    return return_array;
}

// print_return_statement
// vector<int>, vector<int>
//
// Print the index and the numerical value of the longest_r_rise
//
// Runtime of print_return_statement:
// O(1) + Runtime of get_first_r_rise_index = O(n)
//
void print_return_statement(ivec derived_array, ivec original_array) {
    int index = get_first_r_rise_index(derived_array, original_array);
    cout << index << " " << derived_array[0] << endl;
}

// get_first_r_rise_index
// vector<int>, vector<int>
//
// Find the index of the given key from an array
// Using rolling radix search, we only traverse the array once
//
// Runtime of get_first_r_rise_index:
// O(n)
//
int get_first_r_rise_index(ivec key, ivec array) {
    int return_value;

    bool found_leading_index = false;
    for (int i = 0; i < array.size(); i++) {
        // Matching key array pattern with array
        // Since r is strictly > 1
        // We are guaranteed that key array contains all distincted keys
        for (int j = 0; j < key.size(); j++) {
            if (array[i] == key[j]) {
                i++;
                if (j == key.size()-1){
                    found_leading_index = true;
                }
            } else {
                break;
            }
        }
        if (found_leading_index) {
            return_value = i - key.size();
            break;
        }
    }

    return return_value;
}

// DEBUG HELPER
template <class T> ostream& operator<<(ostream &os, const vector<T>&vec) {
    for (int i = 0; i < vec.size(); i++){os<<vec[i]<<" ";}
    return os;
}
