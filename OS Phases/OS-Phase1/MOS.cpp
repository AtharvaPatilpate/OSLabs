#include <iostream>
#include <fstream>
using namespace std;

class OS
{
    char M[100][4], IR[4], R[4], buffer[40];
    int IC, SI;
    bool C;

public:
    void INIT();
    void LOAD();
    void STARTEXECUTION();
    void EXECUTEUSERPROGRAM();
    void MOS();
    void READ();
    void WRITE();
    void TERMINATE();
    fstream Input;
    fstream Output;
};

void OS::INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = '\0';
        }
    }
    IR[4] = {'\0'};
    R[4] = {'\0'};
    C = false;
}

void OS::LOAD()
{

    int x = 0;
    do
    {
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }

        Input.getline(buffer, 40);

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            INIT();
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            STARTEXECUTION();
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int k = 0;

            for (; x < 100; x++)
            {
                for (int j = 0; j < 4; j++)
                {

                    M[x][j] = buffer[k];
                    k++;
                    cout << "M[" << x << "]"
                         << "[" << j << "]: " << M[x][j] << endl;
                }
                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    break;
                }
            }
        }

    } while (!Input.eof());
}

void OS::STARTEXECUTION()
{
    IC = 00;
    EXECUTEUSERPROGRAM();
}

void OS::EXECUTEUSERPROGRAM()
{
    while (true)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        int i = IR[2] - 48;

        i = i * 10 + (IR[3] - 48);

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {

            for (int j = 0; j <= 3; j++)
                R[j] = M[i][j];
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {

            for (int j = 0; j <= 3; j++)
                M[i][j] = R[j];
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {

            if (M[i][0] == R[0] && M[i][1] == R[1] && M[i][2] == R[2] && M[i][3] == R[3])
            {
                C = true;
            }
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
            {
                IC = i;
            }
        }
    }
}

void OS::MOS()
{

    switch (SI)
    {
    case 1:
        READ();
        break;
    case 2:
        WRITE();
        break;
    case 3:
        TERMINATE();
        break;
    }
}

void OS::READ()
{
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    Input.getline(buffer, 40);

    int k = 0;
    int i = IR[2] - 48;
    i = i * 10 + (IR[3] - 48);

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = buffer[k];
            k++;
        }
        if (k == 40)
        {
            break;
        }
        i++;
    }

    SI = 0;
}

void OS::WRITE()
{
    for (int i = 0; i < 40; i++)
    {
        buffer[i] = '\0';
    }

    int k = 0;
    int i = IR[2] - 48;
    i = i * 10;

    for (int l = 0; l < 10; l++)
    {
        for (int j = 0; j < 4; j++)
        {
            buffer[k] = M[i][j];
            Output << buffer[k];

            k++;
        }
        if (k == 40)
        {
            break;
        }
        i++;
    }

    Output << "\n";
    SI = 0;
}

void OS::TERMINATE()
{
    Output << "\n";
    Output << "\n";
    SI = 0;
}

int main()
{
    OS os;

    os.Input.open("input.txt", ios::in);
    os.Output.open("output.txt", ios::out);
    os.LOAD();

    return 0;
}