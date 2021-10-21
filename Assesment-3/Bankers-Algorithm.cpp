// 20BCE2044 Aditya Mitra

#include <iostream>
using namespace std;

// Structure to store the data
struct Bankers
{
    int m, n;
    int *res_available, **res_max, **res_allocation, **res_need;
};

//Function to flag wether it is a safe zone or not
bool safety(Bankers a)
{
    int i, j, k, x, cnt = 0;
    int *work = new int[a.m];
    int  *safe_sequence = new int[a.n];

    bool *p_complete = new bool[a.n];

    for (i = 0; i < a.n; i++)
    {
        p_complete[i] = false;
    }

    for (i = 0; i < a.m; i++)
    {
        work[i] = a.res_available[i];
    }

    for (k = 0; k < a.n; k++)
    {
        bool f;
        for (i = 0; i < a.n; i++)
        {
            if (p_complete[i] == false)
            {
                f = false;
                for (j = 0; j < a.m; j++)
                {
                    if (a.res_need[i][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == a.m)
                {
                    for (x = 0; x < a.m; x++)
                    {
                        work[x] += a.res_allocation[i][x];
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
            cout << "System is in Unsafe State." << endl;
            return false;
        }
    }

    cout << "System is in Safe State." << endl;
    cout << "Safe Sequence: ";
    for (i = 0; i < a.n; i++)
    {
        cout << safe_sequence[i] << " ";
    }
    cout << endl;
    return true;
}

// Function to create a request
void request(Bankers a)
{
    int i, p_num;
    int *res_request = new int[a.m];

    cout << "Enter Process Number: ";
    cin >> p_num;

    cout << "Enter the Request: ";
    for (i = 0; i < a.m; i++)
    {
        cin >> res_request[i];
    }

    for (i = 0; i < a.m; i++)
    {
        if (res_request[i] <= a.res_need[p_num][i])
        {
            if (res_request[i] <= a.res_available[i])
            {
                a.res_available[i] -= res_request[i];
                a.res_allocation[p_num][i] += res_request[i];
                a.res_need[p_num][i] -= res_request[i];
            }
        }
    }

    safety(a);
}

// main function to drive the program
int main()
{
    // Process Name: P0....
    // n: Number of processes
    // m: Number of resources

    int i, j;

    Bankers a;

    cout << "Enter no. of Processes: ";
    cin >> a.n;

    cout << "Enter no. of Resources: ";
    cin >> a.m;

    cout << endl;

    a.res_max = new int *[a.n];
    a.res_allocation = new int *[a.n];

    cout << "Enter the Max and Allocation for each process: " << endl;
    for (i = 0; i < a.n; i++)
    {
        a.res_max[i] = new int[a.m];
        a.res_allocation[i] = new int[a.m];

        cout << "P" << i << ":" << endl;

        cout << "Allocation: ";
        for (j = 0; j < a.m; j++)
        {
            cin >> a.res_allocation[i][j];
        }

        cout << "Max: ";

        for (j = 0; j < a.m; j++)
        {
            cin >> a.res_max[i][j];
        }

        cout << endl;
    }

    a.res_available = new int[a.m];

    cout << "Enter Available Resources: ";
    for (i = 0; i < a.m; i++)
    {
        cin >> a.res_available[i];
    }
    cout << endl;

    a.res_need = new int *[a.n];

    for (i = 0; i < a.n; i++)
    {
        a.res_need[i] = new int[a.m];
        for (j = 0; j < a.m; j++)
        {
            a.res_need[i][j] = (a.res_max[i][j] - a.res_allocation[i][j]);
            cout << a.res_need[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    safety(a);
    cout << endl;
    request(a);
    cout << endl;

    cout << "Another request" << endl;
    request(a);

    return 0;
}