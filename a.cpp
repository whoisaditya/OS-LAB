#include <iostream>
using namespace std;

// Structure to store the data
struct Process
{
    int m, n;
    int *available, **max, **allocation, **need;
};

bool safety(Process var)
{
    int i, j, k, x, cnt = 0;
    int *work = new int[var.m];
    int  *safe_sequence = new int[var.n];

    bool *p_complete = new bool[var.n];


    for (i = 0; i < var.n; i++)
    {
        p_complete[i] = false;
    }

    for (i = 0; i < var.m; i++)
    {
        work[i] = var.available[i];
    }

    for (k = 0; k < var.n; k++)
    {
        bool f;
        for (i = 0; i < var.n; i++)
        {
            if (p_complete[i] == false)
            {
                f = false;
                for (j = 0; j < var.m; j++)
                {
                    if (var.need[i][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == var.m)
                {
                    for (x = 0; x < var.m; x++)
                    {
                        work[x] += var.allocation[i][x];
                    }

                    p_complete[i] = true;
                    safe_sequence[cnt] = i;
                    cnt++;
                    f = true;
                }
            }
        }

        if (f == false)
        {
            cout << "No" << endl;
            return false;
        }
    }

    cout << "Yes" << endl;
    cout << "Safe Sequence"<<endl;
    for (i = 0; i < var.n; i++)
    {
        cout << safe_sequence[i] << endl;
    }
    cout << endl;
    return true;
}

void request(Process var)
{
    int i, p_num;
    int *res_request = new int[var.m];
    
    cout << "Which Process has request"<<endl;
    cin >> p_num;

    cout << "Request Vector"<<endl;
    for (i = 0; i < var.m; i++)
    {
        cin >> res_request[i];
    }

    for (i = 0; i < var.m; i++)
    {
        if (res_request[i] <= var.need[p_num][i])
        {
            if (res_request[i] <= var.available[i])
            {
                var.available[i] -= res_request[i];
                var.allocation[p_num][i] += res_request[i];
                var.need[p_num][i] -= res_request[i];
            }
        }
    }

    safety(var);
}

int main()
{
    int i,j;
    
    Process var;
    
    cout << "Enter the number of processes:\n";
    cin >> var.n;
    
    cout << "Enter the number of resource types:\n";
    cin >> var.m;
    
    var.available = new int[var.m];
    
    cout << "Enter the available vector:\n";
    for (i = 0; i < var.m; i++)
    {
        cin >> var.available[i];
    }
    
    var.allocation = new int *[var.n];
    cout << "Enter the allocation matrix:\n";
    
    for (i = 0; i < var.n; i++)
    {
        var.allocation[i] = new int[var.m];
        cout << "Allocation for process " << i+1 << endl;
        for (j = 0; j < var.m; j++)
        {
            cin >> var.allocation[i][j];
            
        }
    }
    
    var.max = new int *[var.n];
    for (i = 0; i < var.n; i++)
    {
        var.max[i] = new int[var.m];
        cout << "Max for process " << i+1 << endl;
        for (j = 0; j < var.m; j++)
        {
            cin >> var.max[i][j];
        }
    }
    
    request(var);
    return 0;
    
    
}