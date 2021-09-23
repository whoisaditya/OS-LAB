#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    // Initializing the necessary variables
    int n, bt[20], wt[20], tat[20], t_wt = 0, t_tat = 0, i, j;
    float avg_wt, avg_tat;

    // Accepting User Input
    cout << "Enter total number of processes(maximum 20): ";
    cin >> n;
    cout << "\nEnter Process Burst Time\n";

    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: ";
        cin >> bt[i];
    }
    wt[0] = 0;

    // Calculation
    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
        {
            wt[i] += bt[j];
        }
    }

    // Printing the output table
    cout << "\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time";
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        t_wt += wt[i];
        t_tat += tat[i];
        cout << "\nP[" << i + 1 << "]" << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    }

    avg_wt = (t_wt*1.0) / n;
    avg_tat= (t_tat*1.0) / n;

    // Printing the result
    cout << "\n\nAverage Waiting Time: " << setprecision(2) << avg_wt;
    cout << "\nAverage Turnaround Time: " << setprecision(2) << avg_tat;

    return 0;
}