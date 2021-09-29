#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
    char pid;
    int bt; // Burst Time
    int at; // Arrival Time
    int priority; // Priority
    int restime = 0; // Rest Time
    int ct = 0; // Completion Time
    int wt = 0; // Waiting Time
} a[1000], b[1000], c[1000];

void insert(int n, bool A)
{
    int i;
    for (i = 0; i < n; i++)
    {
        cout << "Process Name: ";
        cin >> a[i].pid;
        cout << "Priority: ";
        cin >> a[i].priority;
        if(A)
        {cout << "Arrival Time: ";
        cin >> a[i].at;}
        else
        {a[i].at = 0;}
        cout << "Burst Time: ";
        cin >> a[i].bt;
        a[i].wt = -a[i].at + 1;
        cout << endl;
    }
}

bool btSort(node a, node b)
{
    return a.bt < b.bt;
}

bool atSort(node a, node b)
{
    return a.at < b.at;
}

bool prioritySort(node a, node b)
{
    return a.priority < b.priority;
}

int k = 0, f = 0, r = 0;
void disp(int nop, int qt)
{
    int n = nop, q;
    sort(a, a + n, atSort);
    int ttime = 0, i;
    int j, tArray[20];
    int alltime = 0;
    bool moveLast = false;

    for (i = 0; i < n; i++)
    {
        alltime += a[i].bt;
    }
    alltime += a[0].at;

    for (i = 0; ttime <= alltime;)
    {
        j = i;
        while (a[j].at <= ttime && j != n)
        {
            b[r] = a[j];
            j++;
            r++;
        }
        if (r == f)
        {
            c[k].pid = 'i';
            c[k].bt = a[j].at - ttime;
            c[k].at = ttime;
            ttime += c[k].bt;
            k++;
            continue;
        }
        i = j;
        if (moveLast == true)
        {
            sort(b + f, b + r, prioritySort);
            b[r] = b[f];
            f++;
            r++;
        }
        j = f;
        if (b[j].bt > qt)
        {
            c[k] = b[j];
            c[k].bt = qt;
            k++;
            b[j].bt = b[j].bt - qt;
            ttime += qt;
            moveLast = true;
            for (q = 0; q < n; q++)
            {
                if (b[j].pid != a[q].pid)
                {
                    a[q].wt += qt;
                }
            }
        }
        else
        {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].bt;
            moveLast = false;
            for (q = 0; q < n; q++)
            {
                if (b[j].pid != a[q].pid)
                {
                    a[q].wt += b[j].bt;
                }
            }
        }
        if (f == r && i >= n)
        {
            break;
        }
    }
    tArray[i] = ttime;
    ttime += a[i].bt;
    for (i = 0; i < k - 1; i++)
    {
        if (c[i].pid == c[i + 1].pid)
        {
            c[i].bt += c[i + 1].bt;
            for (j = i + 1; j < k - 1; j++)
            {
                c[j] = c[j + 1];
            }
            k--;
            i--;
        }
    }
    int rtime = 0;
    for (j = 0; j < n; j++)
    {
        rtime = 0;
        for (i = 0; i < k; i++)
        {
            if (c[i].pid == a[j].pid)
            {
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].bt;
        }
    }
    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout << "\n";
    cout << "\n";
    cout << "P.Name Priority AT\tBT\tCT\tTAT\tWT\tRT\n";
    for (i = 0; i < nop && a[i].pid != 'i'; i++)
    {
        if (a[i].pid == '\0')
        {
            break;
        }
        cout << 'P' << a[i].pid << "\t";
        cout << a[i].priority << "\t";
        cout << a[i].at << "\t";
        cout << a[i].bt << "\t";
        cout << a[i].ct << "\t";
        cout << a[i].wt + a[i].ct - rtime + a[i].bt << "\t";
        averageTAT += a[i].wt + a[i].ct - rtime + a[i].bt;
        cout << a[i].wt + a[i].ct - rtime << "\t";
        averageWaitingTime += a[i].wt + a[i].ct - rtime;
        cout << a[i].restime - a[i].at << "\t";
        averageResponseTime += a[i].restime - a[i].at;
        cout << "\n";
    }
    cout << "Average Response time: " << (float)averageResponseTime / (float)n << endl;
    cout << "Average Waiting time: " << (float)averageWaitingTime / (float)n << endl;
    cout << "Average TA time: " << (float)averageTAT / (float)n << endl;
}

int main()
{
    int nop, choice, i, qt;
    bool A;

    cout << "Menu for Priority" << endl;
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

    cout << "Enter number of processes\n";
    cin >> nop;

    cout << "Enter Process Details\n";
    insert(nop, A);

    disp(nop, 1);
    return 0;
}