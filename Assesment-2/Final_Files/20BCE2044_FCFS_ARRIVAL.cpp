#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compareArrival(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2)
{
    return p1.pid < p2.pid;
}

void FCFS(bool A)
{

    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]" << endl;

        if (A)
        {
            cout << "Arrival time: ";
            cin >> p[i].arrival_time;
        }
        else
        {
            p[i].arrival_time = 0;
        }
        
        cout << "Burst time: ";
        cin >> p[i].burst_time;

        p[i].pid = i + 1;
        cout << endl;
    }

    sort(p, p + n, compareArrival);

    for (int i = 0; i < n; i++)
    {
        p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0) ? (p[i].arrival_time) : (p[i].start_time - p[i - 1].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    sort(p, p + n, compareID);

    cout << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t"
         << "\n"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << endl;
    }
    cout << endl;
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
}

int main()
{
    bool A = true;
    int choice;

    cout << "Menu" << endl;
    cout << "1. With Variable Arrival Time" << endl;
    cout << "2. With all processes arriving at the same time ie at 0" << endl;
    cout << "Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        A = true;
        break;

    case 2:
        A = false;
        break;
    }

    FCFS(A);

    return 0;
}