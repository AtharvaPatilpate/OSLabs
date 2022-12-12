#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Process
{
public:
    int ID;
    int AT = 0;
    int BT = 0;
    int CT = 0;
    int TAT = 0;
    int WT = 0;
};

void Gantt(vector<Process> p, int n)
{
    int i, j;
    printf(" ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].BT; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].BT - 1; j++)
            printf(" ");
        printf("P%d", p[i].ID);
        for (j = 0; j < p[i].BT - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].BT; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p[i].BT; j++)
            printf("  ");
        if (p[i].TAT > 9)
            printf("\b");
        printf("%d", p[i].CT);
    }
    printf("\n");
}

int main()
{
    int n;
    cout << "Enter the number of processes to run: ";
    cin >> n;

    vector<Process> P(n);

    for (int i = 0; i < n; i++)
    {
        int at, bt;
        cout << "Enter the AT of the P" << i << " process: ";
        cin >> at;
        cout << "Enter the BT of the P" << i << " process: ";
        cin >> bt;

        P[i].ID = i;
        P[i].AT = at;
        P[i].BT = bt;
    }

    sort(P.begin(), P.end(), [](const Process &lhs, const Process &rhs)
         { return lhs.AT < rhs.AT; });

    P[0].CT = P[0].AT + P[0].BT;

    for (int i = 1; i < n; i++)
    {
        P[i].CT = (P[i - 1].CT >= P[i].AT) ? P[i - 1].CT + P[i].BT : P[i].AT + P[i].BT;
    }

    for (int i = 0; i < n; i++)
    {
        P[i].TAT = P[i].CT - P[i].AT;
        P[i].WT = P[i].TAT - P[i].BT;
    }

    cout << "The process sequence will be: ";
    for (int i = 0; i < n - 1; i++)
    {
        cout << P[i].ID << " -> ";
    }
    cout << P[n - 1].ID << endl
         << endl;

    Gantt(P, n);
    cout << "\n\nThe table of the processes: " << endl;

    cout << "Process\tAT\tBT\tCT\tTAT\tWT" << endl;

    sort(P.begin(), P.end(), [](const Process &lhs, const Process &rhs)
         { return lhs.ID < rhs.ID; });

    for (int i = 0; i < n; i++)
    {
        cout << "P" << P[i].ID << " -> "
             << "\t" << P[i].AT << "\t" << P[i].BT << "\t" << P[i].CT << "\t" << P[i].TAT << "\t" << P[i].WT << endl;
    }

    return 0;
}