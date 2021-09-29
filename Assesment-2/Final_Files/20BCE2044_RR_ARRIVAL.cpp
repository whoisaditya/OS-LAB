#include <iostream>
using namespace std;

struct process
{
    int pid;// Process ID
    int at; // Arrival Time
    int bt; // Burst Time
    int rt; // Response Time
};

void RR(bool A)
{
    int i, j, n, time, remain, flag = 0, time_quantum;
    int wait_time = 0, turnaround_time = 0;

    struct process p[100];

    // Accepting User Input
    cout << "Enter Total Process: ";
    cin >> n;

    remain = n;

    for (i = 0; i < n; i++)
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

        cout << "Burst Time: ";
        cin >> p[i].bt;

        cout << endl;

        p[i].rt = p[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    // Calculation and Printing Output
    cout << "\n\nProcess\t|Arrival Time\t|Turnaround Time|Waiting Time\n\n";
    for (time = 0, i = 0; remain != 0;)
    {
        if (p[i].rt <= time_quantum && p[i].rt > 0)
        {
            time += p[i].rt;
            p[i].rt = 0;
            flag = 1;
        }
        else if (p[i].rt > 0)
        {
            p[i].rt -= time_quantum;
            time += time_quantum;
        }
        if (p[i].rt == 0 && flag == 1)
        {
            remain--;
            cout << "P[" << i + 1 << "]\t|\t" << p[i].at <<"\t|\t" << time - p[i].at << "\t|\t" << time - p[i].at - p[i].bt << endl;

            wait_time += time - p[i].at - p[i].bt;
            turnaround_time += time - p[i].at;
            flag = 0;
        }
        if (i == n - 1)
        {
            i = 0;
        }
        else if (p[i + 1].at <= time)
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

// Driver Function
int main()
{
    bool A = true;
    int choice;

    cout << "Menu for RR" << endl;
    cout << "1. With Variable Arrival Time" << endl;
    cout << "2. With all processes arriving at same time ie at 0" << endl;
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