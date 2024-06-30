#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//Struct for the four values supplied by CSV file
struct Process {
    int processID; //Column 0
    int arrivalTime;  //Column 1
    int burstDuration; //Column 2
    int burstModified;
    int priority; //Column 3
};

//Function that reads provided CSV file and converts it into a vector
//Vector is full of Process structs
vector<Process> fileToVector (const string& file) {
    vector<Process> processes;
    ifstream inputFile(file);

    string line;

    //Read lines until end of file
    while (getline(inputFile, line)) {
        Process prx;
        size_t commaPosition;
        
        commaPosition = line.find(',');
        string firstNumber = line.substr(0, commaPosition);
        prx.processID = stoi(firstNumber);
        line.erase(0, commaPosition + 1);

        commaPosition = line.find(',');
        string secondNumber = line.substr(0, commaPosition);
        prx.arrivalTime = stoi(secondNumber);
        line.erase(0, commaPosition + 1);

        commaPosition = line.find(',');
        string thirdNumber = line.substr(0, commaPosition);
        prx.burstDuration = stoi(thirdNumber);
        prx.burstModified = stoi(thirdNumber);
        line.erase(0, commaPosition + 1);

        prx.priority = stoi(line);

        processes.push_back(prx);
    }
    inputFile.close();

    return processes;
}

//Output helper function
void output(double TT, double WT, double TP) {
    cout << "Average Turnaround Time: " << fixed << setprecision(3) << TT << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(3) << WT << endl;
    cout << "Throughput: " << fixed << setprecision(3) << TP << endl;
}

//Calculate total time to run all processes
int totalBurst(vector<Process> processes) {
    int totalTime = 0;
    for (const auto& process: processes) {
        totalTime += process.burstDuration;
    }
    return totalTime;
}

//Helper function for sorting by arrival time
bool byArrivalTime(const Process& a, Process& b) {
    if (a.arrivalTime == b.arrivalTime) {
        return a.processID < b.processID;
    }
    
    return a.arrivalTime < b.arrivalTime;
}

//Helper function for sorting by arrival time reverse
bool byArrivalTimeReverse(const Process& a, Process& b) {
    if (a.arrivalTime == b.arrivalTime) {
        return a.processID > b.processID;
    }
    
    return a.arrivalTime > b.arrivalTime;
}

//Comparator for priority queue
struct compareArrivalTime{
    bool operator()(const Process& a, Process& b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.processID > b.processID;
        }
    
        return a.arrivalTime > b.arrivalTime;
    }
};

//Comparator for SJFP queue
struct compareBurstDuration{
    bool operator()(const Process& a, Process& b) {
        if (a.burstDuration == b.burstDuration) {
            return a.processID > b.processID;
        }
    
        return a.burstDuration > b.burstDuration;
    }
};

//Comparator for priority queue
struct comparePriority{
    bool operator()(const Process& a, Process& b) {
        if (a.priority == b.priority) {
            return a.processID > b.processID;
        }
    
        return a.priority > b.priority;
    }
};

//First Come First Serve Scheduling Algorithm
//Return nothing, output findings within process
void FCFS(vector<Process> processes) {
    int waitingTime = 0;
    int totalTime = 0;
    int turnaroundTime = 0;
    vector<Process> processesTemp = processes;
    
    //sort by arrival time
    sort(processesTemp.begin(), processesTemp.end(), byArrivalTime);

    //Calculate waiting time, totaltime and turnaroundtime
    for (unsigned int i = 0; i < processesTemp.size(); i++) {
        if (totalTime < processesTemp[i].arrivalTime) {
            totalTime = processesTemp[i].arrivalTime;
        }
        
        waitingTime += totalTime - processesTemp[i].arrivalTime;
        totalTime += processesTemp[i].burstDuration;
        turnaroundTime += totalTime - processesTemp[i].arrivalTime;
    }

    //calculate average waiting time
    double avgWaitingTime = static_cast<double> (waitingTime) / processesTemp.size();
    //calculate throughput
    double throughput = processesTemp.size() / static_cast<double> (totalTime);
    //calculate average turnaround time
    double avgTurnaroundTime = static_cast<double> (turnaroundTime) / processesTemp.size();

    //create output for FCFS algorithm
    output(avgTurnaroundTime, avgWaitingTime, throughput);
}

//Shortest Job First
//Pre-emptive.
void SJFP(vector<Process> processes) {
    int waitingTime = 0;
    int totalTime = 0;
    int turnaroundTime = 0;
    vector<Process> processesTemp = processes;

    //Prio Qs to hold processes while they havent started and when they are waiting to run
    priority_queue<Process, vector<Process>, compareArrivalTime> arrivalQueue;
    priority_queue<Process, vector<Process>, compareBurstDuration> waitingQueue;
    
    //sort by arrival time
    sort(processesTemp.begin(), processesTemp.end(), byArrivalTime);

    //push vector elements to queue sorted by arrival time
    for (auto& process : processes) {
        arrivalQueue.push(process);
    }

    //loop for as long as computations are being made
    while (totalTime < totalBurst(processesTemp)) {
        //if Arrival Q is not empty then add top element to waiting Q if totalTime = arrivalTime. Repeat for multiple elements if necessary
        if (!arrivalQueue.empty()) {
            Process nextProcess = arrivalQueue.top();
            
            if (nextProcess.arrivalTime == totalTime) {
                arrivalQueue.pop();
                waitingQueue.push(nextProcess);

                while (!arrivalQueue.empty() && arrivalQueue.top().arrivalTime == totalTime) {
                    nextProcess = arrivalQueue.top();
                    arrivalQueue.pop();
                    waitingQueue.push(nextProcess);
                }
            }
        }

        //remove 1 burst from the item with the least burst left in waiting queue. 
        //if no bursts left calculate waiting time and add to total
        if(!waitingQueue.empty()) {
            Process removeBurst = waitingQueue.top();

            removeBurst.burstModified -= 1;
            waitingQueue.pop();
            if (removeBurst.burstModified != 0) {
                waitingQueue.push(removeBurst);
            }
            else {
                waitingTime += totalTime - removeBurst.arrivalTime - removeBurst.burstDuration + 1;
            }

        }
        totalTime++;
    }
    turnaroundTime = waitingTime + totalTime;
    //calculate average waiting time
    double avgWaitingTime = static_cast<double> (waitingTime) / processesTemp.size();
    //calculate throughput
    double throughput = processesTemp.size() / static_cast<double> (totalBurst(processesTemp));
    //calculate average turnaround time
    double avgTurnaroundTime = static_cast<double> (turnaroundTime) / processesTemp.size();

    //create output for FCFS algorithm
    output(avgTurnaroundTime, avgWaitingTime, throughput);
}

//Priority
//Pre-emptive.
void Priority(vector<Process> processes) {
    int waitingTime = 0;
    int totalTime = 0;
    int turnaroundTime = 0;
    vector<Process> processesTemp = processes;

    //Prio Qs to hold processes while they havent started and when they are waiting to run
    priority_queue<Process, vector<Process>, compareArrivalTime> arrivalQueue;
    priority_queue<Process, vector<Process>, comparePriority> waitingQueue;
    
    //sort by arrival time
    sort(processesTemp.begin(), processesTemp.end(), byArrivalTime);

    //push vector elements to queue sorted by arrival time
    for (auto& process : processes) {
        arrivalQueue.push(process);
    }

    //loop for as long as computations are being made
    while (totalTime < totalBurst(processesTemp)) {
        //if Arrival Q is not empty then add top element to waiting Q if totalTime = arrivalTime. Repeat for multiple elements if necessary
        if (!arrivalQueue.empty()) {
            Process nextProcess = arrivalQueue.top();
            
            if (nextProcess.arrivalTime == totalTime) {
                arrivalQueue.pop();
                waitingQueue.push(nextProcess);

                while (!arrivalQueue.empty() && arrivalQueue.top().arrivalTime == totalTime) {
                    nextProcess = arrivalQueue.top();
                    arrivalQueue.pop();
                    waitingQueue.push(nextProcess);
                }
            }
        }

        //remove 1 burst from the item with the highest priority left in waiting queue. 
        //if no bursts left calculate waiting time and add to total
        if(!waitingQueue.empty()) {
            Process removeBurst = waitingQueue.top();

            removeBurst.burstModified -= 1;
            waitingQueue.pop();
            if (removeBurst.burstModified != 0) {
                waitingQueue.push(removeBurst);
            }
            else {
                waitingTime += totalTime - removeBurst.arrivalTime - removeBurst.burstDuration + 1;
            }

        }
        totalTime++;
    }
    turnaroundTime = waitingTime + totalTime;
    //calculate average waiting time
    double avgWaitingTime = static_cast<double> (waitingTime) / processesTemp.size();
    //calculate throughput
    double throughput = processesTemp.size() / static_cast<double> (totalBurst(processesTemp));
    //calculate average turnaround time
    double avgTurnaroundTime = static_cast<double> (turnaroundTime) / processesTemp.size();

    //create output for FCFS algorithm
    output(avgTurnaroundTime, avgWaitingTime, throughput);
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Missing file!" << endl;
        return 1;
    }

    //Create vector with all the different processes included
    vector<Process> processes = fileToVector(argv[1]);

    //Run all three scheduling algorithms
    //FCFS Scheduling algo:
    cout << "--- FCFS ---" << endl;
    FCFS(processes);

    //SJFP Scheduling algo:
    cout << "--- SJFP ---" << endl;
    SJFP(processes);

    //Priority Scheduling algo:
    cout << "--- Priority ---" << endl;
    Priority(processes);

    return 0;
}