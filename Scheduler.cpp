//
//  Scheduler.cpp
//  process_queue
//
//

#include "Scheduler.hpp"


Scheduler::Scheduler() {
    
};

Scheduler::Scheduler(std::string filename, int quantum) {
    this->infile = filename;
    this->outfile = infile;
    this->quantum = quantum;
};

//This is the constructor being used currently
Scheduler::Scheduler(std::string input, std::string output, int quantum) {
    this->infile = input;
    this->outfile = output;
    this->quantum = quantum;
};

//Reads in values from the input file, creates a queue object using the processes, creates the process queue and passes the incoming process queue to it.
void Scheduler::read_in() {
    
    //Open input file
    this->input.open(infile);
    std::cout << "\nAttempting to open the file...";
    outstring << "\nAttempting to open the file...";
    
    //If the file opened succesfully go ahead and read in the values
    if(input.is_open()) {
        std::cout << "\nFile is open";
        outstring << "\nFile is open";
        int total_processes{}, arrival, priority, burst;
            std::queue<std::shared_ptr<Process>> incoming;
        
            //Read in the number of processes
            input >> total_processes;
            std::cout << "\nTotal processes: " << total_processes;
            outstring << "\nTotal processes: " << total_processes;
        
        //Read in the processes one at a time, setting pointers to be used later on
        for (int i=0; i < total_processes; i++) {
            input >> arrival >> priority >> burst;
            auto process = std::make_shared<Process>(arrival, priority, burst, process_designation);
            if(process) {
                std::cout << "\nProcess: " << process_designation << "\tArrival Time: " << arrival << "\tPriority: " << priority << "\tCPU Time: " << burst;
                outstring << "\nProcess: " << process_designation++ << "\tArrival Time: " << arrival << "\tPriority: " << priority << "\tCPU Time: " << burst;
            }
            if(i==0) {
                process->set_previous(process);
                process->set_next(process);
            }else {
                process->set_next(nullptr);
                process->set_previous(incoming.back());
                incoming.back()->set_next(process);
            }
            incoming.push(process);
        }
        
        //Create the process queue object, passing in the total number of processes, time quantum to be used in round robin execution if multiple processes have the same priority, and the incoming queue of processes
        this->process_queue = std::make_unique<MyQueue>(total_processes, quantum, incoming);
    }
    input.close();
};

//Prints the program output to our output file
void Scheduler::print_report() {
    std::string report = process_queue->print_report();
    output << report;
    output.close();
};

//Runs the scheduler
void Scheduler::run() {
    outstring << "Student\nCOSC4327-Operating Systems\nAssignment 3 Output\n\n";
    
    //Calls method to read in from input file and create the incoming queue and the process queue
    this->read_in();
    std::string string = outstring.str();
    
    //Open the output file
    output.open(outfile);
    
    //Output the header and information about the incoming processes to the output file
    output << string;
    
    //Run the queue
    process_queue->start_queue();
    
    //Print out the report
    this->print_report();
};
