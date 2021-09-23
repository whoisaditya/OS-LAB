#include <iostream>
#include <iomanip>

using namespace std;
int main()
{
    // Initializing the necessary variables
    int n, bt[20], wt[20], tat[20], pr[20], t_wt = 0, t_tat = 0, i, j, pos, total = 0, temp, p[20];
    float avg_wt = 0, avg_tat = 0;

    // Accepting User Input
    cout << "Enter total number of processes(maximum 20): ";
    cin >> n;
    cout << "\nEnter Process Burst Time\n";

    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]: " << endl;

        cout << "Burst Time: ";
        cin >> bt[i];

        cout << "Priority: ";
        cin >> pr[i];

        p[i] = i + 1;

        cout << endl;
    }

    // Calculation
    for (i = 0; i < n; i++)
    {
        pos = i;
        for (j = i + 1; j < n; j++)
        {
            if (pr[j] < pr[pos])
            {
                pos = j;
            }
        }
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }
    wt[0] = 0; //waiting time for first process is zero

    // Calculate waiting time
    for (i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (j = 0; j < i; j++)
        {
            wt[i] += bt[j];
        }
    }

    // Printing the output table
    cout << "\nProcess\t\tBurst Time\tPriority\tWaiting Time\tTurnaround Time";
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        t_wt += wt[i];
        t_tat += tat[i];
        cout << "\nP[" << i + 1 << "]"
             << "\t\t" << bt[i] << "\t\t" << pr[i] << "\t\t" << wt[i] << "\t\t" << tat[i];
    }

    avg_wt = (t_wt * 1.0) / n;
    avg_tat = (t_tat * 1.0) / n;

    // Printing the result
    cout << "\n\nAverage Waiting Time: " << setprecision(2) << avg_wt;
    cout << "\nAverage Turnaround Time: " << setprecision(2) << avg_tat;

    return 0;
}