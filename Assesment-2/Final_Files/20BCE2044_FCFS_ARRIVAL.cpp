#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct process
{
    int pid;// Process ID
    int at; // Arrival Time
    int bt; // Burst Time
    int st; // Start Time
    int ct; // Completion Time
    int tt; // Turnaround Time
    int wt; // Waiting Time
    int rt; // Response Time
};

// Utitlity Functions
bool compareArrival(process p1, process p2)
{
    return p1.at < p2.at;
}

bool compareID(process p1, process p2)
{
    return p1.pid < p2.pid;
}

// Function to implement FCFS
void FCFS(bool A)
{

    // Initializing the necessary variables
    int n;
    struct process p[100];
    float avg_tt; // Average Turnaround Time
    float avg_wt; // Average Waiting Time
    float avg_rt; // Average Respose Time
    int total_tt = 0; // Total Turnaround Time
    int total_wt = 0; // Total Waiting Time
    int total_rt = 0; // Total Response Time
    int total_idle_time = 0;

    cout << setprecision(2) << fixed;

    // Taking User Input
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]" << endl;

        if (A)
        {
            cout << "Arrival time: ";
            cin >> p[i].at;
        }
        else
        {
            p[i].at = 0;
        }
        
        cout << "Burst time: ";
        cin >> p[i].bt;

        p[i].pid = i + 1;
        cout << endl;
    }

    sort(p, p + n, compareArrival);

    for (int i = 0; i < n; i++)
    {
        p[i].st = (i == 0) ? p[i].at : max(p[i - 1].ct, p[i].at);
        p[i].ct = p[i].st + p[i].bt;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].rt = p[i].st - p[i].at;

        total_tt += p[i].tt;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
        total_idle_time += (i == 0) ? (p[i].at) : (p[i].st - p[i - 1].ct);
    }

    avg_tt = (float)total_tt / n;
    avg_wt = (float)total_wt / n;
    avg_rt = (float)total_rt / n;

    sort(p, p + n, compareID);

    // Displaying the Output
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
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].st << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\t" << p[i].rt << "\t" << endl;
    }
    cout << endl;
    cout << "Average Turnaround Time = " << avg_tt << endl;
    cout << "Average Waiting Time = " << avg_wt << endl;
    cout << "Average Response Time = " << avg_rt << endl;
}

// Driver Program
int main()
{
    bool A = true;
    int choice;

    // Menu
    cout << "Menu for FCFS" << endl;
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

    // Calling the FCFS Function
    FCFS(A);

    return 0;
}