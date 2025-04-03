#include <iostream>
#include <fstream>

int main() {
    std::cout << "Standard Output Test" << std::endl;
    std::cerr << "Standard Error Test" << std::endl;
    
    std::ofstream outFile("debug_test.txt");
    if (outFile.is_open()) {
        outFile << "File writing test successful" << std::endl;
        outFile.close();
        std::cout << "Successfully wrote to debug_test.txt" << std::endl;
    } else {
        std::cerr << "Failed to open file for writing" << std::endl;
    }
    
    return 0;
}
