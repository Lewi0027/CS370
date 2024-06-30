#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int processID; 
    int arrivalTime; 
    int burstDuration; 
    int priority;
};

int main (int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Missing file!" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    vector<Process> processes;
    string line;

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
        line.erase(0, commaPosition + 1);

        prx.priority = stoi(line);

        processes.push_back(prx);
    }

    inputFile.close(); 

    for (const auto& process : processes) {
        cout << "ProcessID: " << process.processID << ", ";
        cout << "Arrival Time: " << process.arrivalTime << ", ";
        cout << "Burst Duration: " << process.burstDuration << ", ";
        cout << "Priority: " << process.priority << endl;
    }

    return 0;
}