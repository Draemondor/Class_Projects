//
//  Process.hpp
//  process_queue
//
//

#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <vector>
//Definition for my process object

class Process {
private:
    int arrival{}, current_task{};
    std::vector<int> CPU_time, priority, remaining_time;
    std::shared_ptr<Process> next;
    std::shared_ptr<Process> previous;
    char designation{};
public:
    std::shared_ptr<Process> get_next();
    std::shared_ptr<Process> get_previous();
    void set_next(std::shared_ptr<Process> next);
    void set_previous(std::shared_ptr<Process> previous);
    int get_remaining_time();
    int get_arrival_time();
    int get_current_task();
    int get_priority();
    int get_CPU_time();
    void add_task(int priority, int CPU_time);
    int run_current();
    char get_designation();
    Process();
    Process(int arrival_time);
    Process(int arrival_time, int priority, int CPU_time, char& designation);
    Process(int arrival_time, std::vector<int> priority, std::vector<int> CPU_time, char& designation);
};

#endif /* Process_hpp */
