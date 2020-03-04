//
//  MyQueue.hpp
//  process_queue
//
//

#ifndef myqueue_hpp
#define myqueue_hpp

#include <iostream>
#include <stdio.h>
#include "Process.hpp"
#include <vector>
#include <queue>
#include <sstream>

//Class definition for my queue, uses the Process class

class MyQueue {
private:
    std::unique_ptr<std::vector<std::shared_ptr<Process>>> heads;
    std::shared_ptr<Process> current=nullptr;
    std::shared_ptr<Process> next=nullptr;
    std::queue<std::shared_ptr<Process>> incoming_processes;
    int total_processes, current_burst_time, total_burst_time, quantum{}, incoming, round_robin_time{}, in_queue{};
    void set_current(std::shared_ptr<Process> task);
    void set_next();
    std::stringstream outstring = std::stringstream();
public:
    MyQueue();
    MyQueue(std::shared_ptr<Process> task);
    MyQueue(int total, int quantum, std::queue<std::shared_ptr<Process>> tasks);
    int start_queue();
    int run_current();
    int check_incoming();
    bool check_precedence();
    bool add_process();
    std::shared_ptr<Process> current_process();
    std::shared_ptr<Process> next_process();
    std::string print_report();
};

#endif /*  myqueue_hpp */
