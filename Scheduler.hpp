//
//  Scheduler.hpp
//  process_queue
//
//

#ifndef Scheduler_hpp
#define Scheduler_hpp

#include <stdio.h>
#include <iostream>
#include "MyQueue.hpp"
#include <fstream>
#include <string>
#include <sstream>


class Scheduler {
private:
    std::unique_ptr<MyQueue> process_queue;
    std::ifstream input;
    std::ofstream output;
    std::string infile, outfile;
    int quantum{};
    char process_designation = 'A';
    std::stringstream outstring = std::stringstream();
    
public:
    Scheduler();
    Scheduler(std::string filename, int quantum = 2);
    Scheduler(std::string input, std::string output, int quantum = 2);
    
    void read_in();
    void print_report();
    void run();
};

#endif /* Scheduler_hpp */
