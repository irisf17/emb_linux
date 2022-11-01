#include <iostream>
#include <unistd.h> //for sleep function
#include <stdlib.h> //library for atoi()
using namespace std;


int main(int argc, char *argv[]) {
    // Write C++ code here
    int i;
    int multiply;
    multiply = atoi(argv[1]);
    cout << "The multiplier value chosen is: " << multiply << "\n";

    while(1){
        // sleep(0.5);
        cin >> i;
        cout << "The counter value is " << i;
        cout << " and its multiplied value is " << i*multiply << ".\n";
    }
    

    return 0;
}