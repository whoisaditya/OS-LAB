#include <iostream>
using namespace std;

void RR(bool A)
{
    int i, j, n, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0, at[10], bt[10], rt[10];

    cout << "Enter Total Process: ";
    cin >> n;

    remain = n;

    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]" << endl;

        if (A)
        {
            cout << "Arrival time: ";
            cin >> at[i];
        }
        else
        {
           at[i] = 0;
        }

        cout << "Burst Time: ";
        cin >> bt[i];

        cout << endl;

        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    cout << "\n\nProcess\t|Arrival Time\t|Turnaround Time|Waiting Time\n\n";
    for (time = 0, i = 0; remain != 0;)
    {
        if (rt[i] <= time_quantum && rt[i] > 0)
        {
            time += rt[i];
            rt[i] = 0;
            flag = 1;
        }
        else if (rt[i] > 0)
        {
            rt[i] -= time_quantum;
            time += time_quantum;
        }
        if (rt[i] == 0 && flag == 1)
        {
            remain--;
            cout << "P[" << i + 1 << "]\t|\t" << at[i] <<"\t|\t" << time - at[i] << "\t|\t" << time - at[i] - bt[i] << endl;

            wait_time += time - at[i] - bt[i];
            turnaround_time += time - at[i];
            flag = 0;
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= time)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    cout << "\nAverage Waiting Time = "<< (wait_time * 1.0 / n) << endl;
    cout << "Avg Turnaround Time = " << (turnaround_time * 1.0 / n);
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

    RR(A);

    return 0;
}