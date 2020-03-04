//
//  Process.cpp
//  process_queue
//
//

#include "Process.hpp"

Process::Process(){

};

Process::Process(int arrival_time){
    this->arrival = arrival_time;
};

Process::Process(int arrival_time, int priority, int CPU_time, char& designation){
    this->arrival = arrival_time;
    this->priority.push_back(priority);
    this->CPU_time.push_back(CPU_time);
    this->remaining_time.push_back(CPU_time);
    this->designation = designation;
};

Process::Process(int arrival_time, std::vector<int> priority, std::vector<int> CPU_time, char& designation){
    this->arrival = arrival_time;
    this->priority = priority;
    this->CPU_time = CPU_time;
    this->remaining_time = CPU_time;
    this->designation = designation;
};

std::shared_ptr<Process> Process::get_next(){
    return this->next;
};

std::shared_ptr<Process> Process::get_previous(){
    return this->previous;
};

void Process::set_next(std::shared_ptr<Process> next){
    this->next = next;
};

void Process::set_previous(std::shared_ptr<Process> previous){
    this->previous = previous;
};

int Process::get_remaining_time(){
    return this->remaining_time[current_task];
};

int Process::get_arrival_time(){
    return this->arrival;
};

int Process::get_current_task(){
    return this->current_task;
};

int Process::get_priority(){
    return this->priority[current_task];
};

int Process::get_CPU_time(){
    return this->CPU_time[current_task];
};

void Process::add_task(int priority, int CPU_time){
    this->priority.push_back(priority);
    this->CPU_time.push_back(CPU_time);
};

int Process::run_current() {
    this->remaining_time[current_task]--;
    return this->remaining_time[current_task];
}

char Process::get_designation() {
    return this->designation;
}
