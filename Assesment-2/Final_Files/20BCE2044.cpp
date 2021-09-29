#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;

struct process {
    int priority;
    int pid;// Process ID
    int at; // Arrival Time
    int bt; // Burst Time
    int st; // Start Time
    int ct; // Completion Time
    int tt; // Turnaround Time
    int wt; // Waiting Time
    int rt; // Response Time
};

// Function to implement Priority Scheduling
void Priority(bool A) {

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
    
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
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
        
        cout<<"Priority: ";
        cin>>p[i].priority;

        p[i].pid = i+1;
        cout<<endl;
    }

    // Calculation

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].at < p[idx].at) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].st = current_time;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tt = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tt - p[idx].bt;
            p[idx].rt = p[idx].st - p[idx].at;
            
            total_tt += p[idx].tt;
            total_wt += p[idx].wt;
            total_rt += p[idx].rt;
            total_idle_time += p[idx].st - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].ct;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

    int min_at = 10000000;
    int max_ct = -1;
    for(int i = 0; i < n; i++) {
        min_at = min(min_at,p[i].at);
        max_ct = max(max_ct,p[i].ct);
    }

    avg_tt = (float) total_tt / n;
    avg_wt = (float) total_wt / n;
    avg_rt = (float) total_rt / n;

    cout<<endl<<endl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].priority<<"\t"<<p[i].st<<"\t"<<p[i].ct<<"\t"<<p[i].tt<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<"\t"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avg_tt<<endl;
    cout<<"Average Waiting Time = "<<avg_wt<<endl;
    cout<<"Average Response Time = "<<avg_rt<<endl;
    


}

// Driver Function
int main()
{
    bool A = true;
    int choice;

    // Menu
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

    // Calling the Priority Function with the relevant pacrameter
    Priority(A);

    return 0;
}