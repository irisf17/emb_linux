#include <iostream>
#include <unistd.h> //for sleep function
using namespace std;

int main() {
    int counter = 0;


    while(1){
        // Write C++ code here
        cout << counter << '\r';
        cout.flush();
        counter++;
        sleep(1);
    }
    
    return 0;
}