// Avantika Suryawanshi, 20BCE2051
#include <iostream>
using namespace std;

int findLRU(int time[], int n)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru(int f, int n, int a[])
{
    int fault = 0, count = 0;
    int frame[f], time[f];
    for (int i = 0; i < n; i++)
    {
        frame[i] = -1;
    }
    int flag1, flag2;

    for (int i = 0; i < n; ++i)
    {
        flag1 = flag2 = 0;

        for (int j = 0; j < f; ++j)
        {
            if (frame[j] == a[i])
            {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0)
        {
            for (int j = 0; j < f; ++j)
            {
                if (frame[j] == -1)
                {
                    count++;
                    fault++;
                    frame[j] = a[i];
                    time[j] = count;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0)
        {
            int pos = findLRU(time, f);
            count++;
            fault++;
            frame[pos] = a[i];
            time[pos] = count;
        }
    }
    cout << fault;
}

int main() 
{
    int n, f;
    
    //cout << "Length of the reference string" << endl;
    cin >> n;

    int a[n];
    //cout << "Reference string" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    //cout << "Size of frame" << endl;
    cin >> f;

    lru(f, n, a);
    return 0;
}