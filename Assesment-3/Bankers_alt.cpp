// Banker's Algorithm
#include <iostream>
using namespace std;

int main()
{

    // Process Name: P0, P1, P2, P3, P4
    // n: Number of processes
    // m: Number of resources
    int n, m, i, j, k;

    cout << "No. of Processes: ";
    cin >> n;

    cout << "No. of Resources: ";
    cin >> m;

    int res_allocation[n][m], res_max[n][m];

    cout << "Enter the Max and Allocation for each process: " << endl;
    for (i = 0; i < n; i++)
    {
        cout << "P" << i << ":" << endl;
        cout << "Max: ";

        for (j = 0; j < m; j++)
        {
            cin >> res_max[i][j];
        }

        cout << "Allocation: ";
        for (j = 0; j < m; j++)
        {
            cin >> res_allocation[i][j];
        }
    }

    // Available Resources
    int res_available[m];

    cout << "Enter Available Resources: ";
    for (i = 0; i < m; i++)
    {
        cin >> res_available[i];
    }

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            need[i][j] = res_max[i][j] - res_allocation[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {

                int flag = 0;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > res_available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        res_available[y] += res_allocation[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    cout << "Following is the SAFE Sequence" << endl;
    for (i = 0; i < n - 1; i++)
    {
        cout << " P" << ans[i] << " ->";
    }
    cout << " P" << ans[n - 1] << endl;

    return (0);
}

// This code is contributed by SHUBHAMSINGH10
