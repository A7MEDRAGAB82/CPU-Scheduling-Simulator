#pragma once

#include "Process.h"
#include <vector>

void FCFS(std::vector<Process>& processes);
void SJF_NonPreemptive(std::vector<Process>& processes);
void Priority_NonPreemptive(std::vector<Process>& processes);
void RoundRobin(std::vector<Process>& processes ,  int timeQuantum);
void SJF_Preemptive(std::vector<Process>& processes);
void Priority_Preemptive(std::vector<Process>& processes);
void MultiLevelQueue(std::vector<Process>& processes);


