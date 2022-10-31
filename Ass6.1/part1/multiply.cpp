#include <iostream>
using namespace std;
#include <unistd.h> //for sleep function


int main() {
    // Write C++ code here
    int i;
    // extern counter;
    while(1){
        // sleep(0.5);
        // cout << "Please enter an integer value: ";
        cin >> i;
        cout << "The counter value is " << i;
        cout << " and its multiplied value is " << i*i << ".\n";
    }
    

    return 0;
}