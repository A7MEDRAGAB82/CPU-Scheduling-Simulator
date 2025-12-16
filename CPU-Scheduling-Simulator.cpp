#include <iostream>
#include <vector>
#include "Process.h"

using namespace std;





int main()
{
   vector<Process> processes ;

   cout << "Please enter the number of processes: ";
   int NumOfProcesses = 0;
   cin >> NumOfProcesses;
   for (int i = 0;i<NumOfProcesses;i++)
   {
       int pid, at, bt, prio;
       cout << "Enter ProcessID, arrival time, burst time, and priority for the process : ";
       cin >> pid >> at >> bt >> prio;
        processes.push_back(Process(pid, at, bt, prio));
   }

   for (auto &i : processes)
   {
       cout << "Process ID: " << i.pid << ", Arrival Time: " << i.arrivalTime
            << ", Burst Time: " << i.burstTime << ", Priority: " << i.priority << endl;
   }


    
}
