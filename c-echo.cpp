#include <iostream>

int main(int argv, char** argc) {
    // Skip the first argc index because its the program
    for(int i = 1; i < argv; i++) {
       std::cout << argc[i];
        // Print a whitespace after all but the last iteration
       if(i < argv - 1) {
          std::cout << " ";
       }
    }
std::cout << std::endl;
}
    
