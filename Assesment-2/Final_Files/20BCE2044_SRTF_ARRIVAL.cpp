#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
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

// Function To Implement SRTF Scheduling
int main()
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
    int br[100]; // Burst Remaining
    int is_completed[100];

    memset(is_completed, 0, sizeof(is_completed));

    cout << setprecision(2) << fixed;
    
    // Accepting User Input
    cout << "STRF" << endl;
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]" << endl;

        cout << "Arrival Time: ";
        cin >> p[i].at;

        cout << "Burst time: ";
        cin >> p[i].bt;
        
        p[i].pid = i + 1;
        br[i] = p[i].bt;
        cout << endl;
    }

    // Calculation
    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && is_completed[i] == 0)
            {
                if (br[i] < mn)
                {
                    mn = br[i];
                    idx = i;
                }
                if (br[i] == mn)
                {
                    if (p[i].at < p[idx].at)
                    {
                        mn = br[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (br[idx] == p[idx].bt)
            {
                p[idx].st = current_time;
                total_idle_time += p[idx].st - prev;
            }
            br[idx] -= 1;
            current_time++;
            prev = current_time;

            if (br[idx] == 0)
            {
                p[idx].ct = current_time;
                p[idx].tt = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tt - p[idx].bt;
                p[idx].rt = p[idx].st - p[idx].at;

                total_tt += p[idx].tt;
                total_wt += p[idx].wt;
                total_rt += p[idx].rt;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    int min_at = 10000000;
    int max_ct = -1;
    for (int i = 0; i < n; i++)
    {
        min_at = min(min_at, p[i].at);
        max_ct = max(max_ct, p[i].ct);
    }

    avg_tt = (float)total_tt / n;
    avg_wt = (float)total_wt / n;
    avg_rt = (float)total_rt / n;

    cout << endl
         << endl;

    // Printing the Output
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
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].st << "\t" << p[i].ct << "\t" << p[i].tt << "\t" << p[i].wt << "\t" << p[i].rt << "\t"
             << endl;
    }
    cout << "\nAverage Turnaround Time = " << avg_tt << endl;
    cout << "Average Waiting Time = " << avg_wt << endl;
    cout << "Average Response Time = " << avg_rt << endl;
}
