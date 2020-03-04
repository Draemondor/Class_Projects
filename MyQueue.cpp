//
//  MyQueue.cpp
//  process_queue
//
//

#include "MyQueue.hpp"

MyQueue::MyQueue(){
    this->quantum = 2;
    this->total_processes = 0;
    this->total_burst_time = 0;
    this->current_burst_time = 0;
    this->incoming = 0;
    this->heads = std::make_unique<std::vector<std::shared_ptr<Process>>>();
    for (int i=0; i<=10; i++) {
        auto list = std::make_shared<Process>();
        list = nullptr;
        heads->push_back(list);
    }
};

MyQueue::MyQueue(std::shared_ptr<Process> task){
    this->total_processes = 1;
    this->quantum = 2;
    this->total_burst_time = 0;
    this->current_burst_time = 0;
    this->incoming = 0;
    this->incoming_processes.push(task);
    this->heads = std::make_unique<std::vector<std::shared_ptr<Process>>>();
    for (int i=0; i<=10; i++) {
        auto list = std::make_shared<Process>();
        list = nullptr;
        heads->push_back(list);
    }
};

//This is the constructor I am actually using, the others are just options that could be implemented in the future to support different forms of input
MyQueue::MyQueue(int total, int quantum, std::queue<std::shared_ptr<Process>> tasks){
    this->total_processes = total;
    this->quantum = quantum;
    this->incoming_processes = tasks;
    this->total_burst_time = 0;
    this->current_burst_time = 0;
    this->incoming = 0;
    this->heads = std::make_unique<std::vector<std::shared_ptr<Process>>>();
    for (int i=0; i<=10; i++) {
        auto list = std::make_shared<Process>();
        list = nullptr;
        heads->push_back(list);
    }
};

//Starts the processing of processes in the queue and returns total CPU time when finished
int MyQueue::start_queue(){
    int processes = total_processes;
    float average_turn_time{};
    //Main execuation loop
    while (total_processes) {
        
        //Check for valid incoming processes in the queue, valid meaning that their arrival time has been reached by the current CPU burst time
        this->incoming = check_incoming();
        
        //If their is at least one valid incoming process, add it to the process queue with the correct precedence
        for (int i = 0; i < incoming; i++) {
            this->add_process();
        }
        
        //Run whichever process is set as the current process for 1 CPU burst time
        auto time_left = run_current();
        
        //Check if anything in the queue now has a higher priority than what was just run, if so pre-empt it and set the higher priority
        check_precedence();
        
        //Increment the current CPU burst time
        current_burst_time++;
        
        //If the CPU time left on the last executed process == 0, remove it from the queue and all references to it
        if (!time_left && this->next_process()!= nullptr) {
            auto remove = this->current_process();
            std::cout << "\nFinished Process: " << remove->get_designation();
            outstring << "\nFinished Process: " << remove->get_designation();
            if (remove->get_next()!=remove) {
                
                heads->at(remove->get_priority()) = remove->get_next();
                heads->at(remove->get_priority())->set_previous(remove->get_previous());
                heads->at(remove->get_priority())->set_next(remove->get_next());
                remove->set_next(nullptr);
                remove->set_previous(nullptr);
                
                
            } else {
                heads->at(remove->get_priority()) = nullptr;
//                std::cout << "\nTurnaround time: " << current_burst_time - remove->get_arrival_time();
//                outstring << "\nTurnaround time: " << current_burst_time - remove->get_arrival_time();
            }
            
            
            std::cout << "\nTurnaround time: " << current_burst_time - remove->get_arrival_time();
            outstring << "\nTurnaround time: " << current_burst_time - remove->get_arrival_time();
            
            average_turn_time+=(current_burst_time - remove->get_arrival_time());
            
            //Set the next process to be executed and make it the current process
            this->set_next();
            this->set_current(this->next_process());
            
            //Decrement the total processes
            total_processes--;
            
            //Set the last reference to the process being removed to nullptr
            remove = nullptr;
        }
        
    }
    
    
    total_burst_time = current_burst_time;
    
    //Calculate the average turnaround time for all the processes
    average_turn_time= average_turn_time / float(processes);
    std::cout << "\nTotal time: " << total_burst_time << "\tAverage Turnaround Time: " << average_turn_time;
    outstring << "\nTotal time: " << total_burst_time << "\tAverage Turnaround Time: " << average_turn_time;
    return this->total_burst_time;
};

//Runs the current process 1 time step and returns the remaining time to complete that task
int MyQueue::run_current(){
    return this->current_process()->run_current();
};

//Checks if a new task or tasks are arriving and returns a number value for how many
int MyQueue::check_incoming(){
    if (!this->incoming_processes.empty()) {
        int arrival = this->incoming_processes.front()->get_arrival_time();
        auto next = this->incoming_processes.front();
        if (next != nullptr) {
        int total = 0;
        while (arrival <= current_burst_time && total <= this->incoming_processes.size() && next!=nullptr) {
            total++;
            next = next->get_next();
            if (next!=nullptr)
            arrival = next->get_arrival_time();
            
        }
        this->incoming = total;
        return total;
        }
    }
    return 0;
};

//Adds the valid incoming processes to the process queue
bool MyQueue::add_process() {
    auto next = this->incoming_processes.front();
    this->incoming_processes.pop();

    int priority = next->get_priority();
    if (this->heads->at(priority)!=nullptr) { //List not empty
        auto tail = this->heads->at(priority)->get_previous();
        next->set_next(this->heads->at(priority));
        next->set_previous(tail);
        tail->set_next(next);
        tail = next;
        this->heads->at(priority)->set_previous(tail);
        if (this->next_process()==nullptr) {
            this->set_next();
        }
        return true;
    } else { //Empty priority list
        this->heads->at(priority) = next;
        next->set_previous(next);
        next->set_next(next);
        if (!in_queue) {
            this->set_current(next);
        }else if (this->next_process()==nullptr) {
            this->set_next();
        }
        in_queue++;
        return true;
    }
    return false;
}

//Checks if any other task has higher precedence, returns true if one is found
bool MyQueue::check_precedence(){
    auto current_priority = this->current_process()->get_priority();
    for (int i=0; i<=10; i++) {
        if (heads->at(i) != nullptr && i < current_priority) {
            //pre-empt
            this->set_current(heads->at(i));
            
        }
        else if (heads->at(i) != nullptr && i == current_priority) {
            if (this->current_process()->get_next() != this->current_process() && round_robin_time > quantum) {
                //round robin
                round_robin_time = 0;
                this->quantum = 0;
                auto send_back = heads->at(i);
                heads->at(i) = send_back->get_next();
                this->set_current(heads->at(i));
            } else {
                round_robin_time++;
            }
        }
    }
    return false;
};

//Sets the current process to be run in the next CPU burst time step
void MyQueue::set_current(std::shared_ptr<Process> task) {
    if (this->current!=task && this->current!=nullptr) {
        std::cout << "\nContext switch to process " << task->get_designation();
        if (this->current->get_remaining_time()) {
            std::cout << "\n CPU time left on " << this->current->get_designation() << ": " << this->current->get_remaining_time();
        }
        outstring << "\nContext switch to process " << task->get_designation();
        if (this->current->get_remaining_time()) {
            outstring << "\n CPU time left on " << this->current->get_designation() << ": " << this->current->get_remaining_time();
        }
    }
    this->current = task;
    if (this->current != task) {
        std::cout << "\nProcessing " << this->current->get_designation();
        outstring << "\nProcessing " << this->current->get_designation();
    };
};

//Sets the next process to be executed based on priority
void MyQueue::set_next() {
    bool stop = false;
    for (int i=0; i <= 10; i++) {
        if (heads->at(i) != nullptr) {
            if(!stop){
                this->next = heads->at(i);
                stop = true;
            }
        }
    }
}

//Returns the current process
std::shared_ptr<Process> MyQueue::current_process(){
    return this->current;
};

//Returns the next process to be executed
std::shared_ptr<Process> MyQueue::next_process(){
    return this->next;
};

//Returns a string for output
std::string MyQueue::print_report() {
    return outstring.str();
}
