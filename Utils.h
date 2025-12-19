#pragma once
#include <vector>
#include <string>
#include "Process.h"

using namespace std;


void sortByArrivalTime(vector<Process>& processes);

void printResults(const vector<Process>& processes, const string& title);

