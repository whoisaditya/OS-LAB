// 20BCE2044 Aditya Mitra

#include <iostream>
using namespace std;

// Structure to store the data
struct Bankers
{
    int m, n;
    int *available, **max, **allocation, **need;
};

//Function to flag wether it is a safe zone or not
bool safety(Bankers var)
{
    int i, j, k, x, cnt = 0, work[var.m], safe_sequence[var.n];
    bool p_complete[var.n];

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
            cout << "System is in Unsafe State." << endl;
            return false;
        }
    }

    cout << "System is in Safe State." << endl;
    cout << "Safe Sequence: ";
    for (i = 0; i < var.n; i++)
    {
        cout << safe_sequence[i] << " ";
    }
    cout << endl;
    return true;
}

// Function to create a request
void request(Bankers var)
{
    int i, p_num, res_request[var.m];

    cout << "Enter Process Number: ";
    cin >> p_num;

    cout << "Enter the Request: ";
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

// main function to drive the program
int main()
{
    // Process Name: P0....
    // n: Number of processes
    // m: Number of resources

    int i, j;

    Bankers var;

    cout << "Enter no. of Processes: ";
    cin >> var.n;

    cout << "Enter no. of Resources: ";
    cin >> var.m;

    cout << endl;

    var.max = new int *[var.n];
    var.allocation = new int *[var.n];

    cout << "Enter the Max and Allocation for each process: " << endl;
    for (i = 0; i < var.n; i++)
    {
        var.max[i] = new int[var.m];
        var.allocation[i] = new int[var.m];

        cout << "P" << i << ":" << endl;

        cout << "Allocation: ";
        for (j = 0; j < var.m; j++)
        {
            cin >> var.allocation[i][j];
        }

        cout << "Max: ";

        for (j = 0; j < var.m; j++)
        {
            cin >> var.max[i][j];
        }

        cout << endl;
    }

    var.available = new int[var.m];

    cout << "Enter availableable Resources: ";
    for (i = 0; i < var.m; i++)
    {
        cin >> var.available[i];
    }
    cout << endl;

    var.need = new int *[var.n];

    for (i = 0; i < var.n; i++)
    {
        var.need[i] = new int[var.m];
        for (j = 0; j < var.m; j++)
        {
            var.need[i][j] = (var.max[i][j] - var.allocation[i][j]);
            cout << var.need[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    safety(var);
    cout << endl;
    request(var);
    cout << endl;

    cout << "Another request" << endl;
    request(var);

    return 0;
}