#pragma once

#include "Process.h"
#include <vector>

using namespace std;

void FCFS(vector<Process>& processes);
void SJF_NonPreemptive(vector<Process>& processes);
void Priority_NonPreemptive(vector<Process>& processes);
