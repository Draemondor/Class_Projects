//
//  main.cpp
//  process_queue
//
//

#include <iostream>
#include "Scheduler.hpp"

int main(int argc, const char * argv[]) {
    
//    char* input[];
    std::string infile, outfile;
    int quantum{};
    
    if (argc > 1) {
        for(int i = 0; i <= argc; i++) {
            if (std::string(argv[i]).compare("input-")) {
                infile = std::string(argv[i+1]);
            } else if (std::string(argv[i]).compare("output-")){
                outfile = std::string(argv[i+1]);
            }else if (std::string(argv[i]).compare("quantum-")) {
                quantum = atoi(argv[i+1]);
            }
        }
    } else {
        std::cout << "Welcome to the Process Scheduler\n";
        std::cout << "Please enter a filename for input: ";
        std::cin >> infile;
//        infile = std::string(input);
        std::cout << "\nPlease enter a filename for output: ";
        std::cin >> outfile;
//        outfile = std::string(input);
        std::cout << "\nIf desired, enter in a quantum number: ";
        std::cin >> quantum;
    }
    
    
        auto scheduler = std::make_unique<Scheduler>(infile, outfile, quantum);
        if (scheduler) {
            std::cout << "\nSuccess";
        }
        scheduler->run();
    
    
    
    
    return 0;
}
