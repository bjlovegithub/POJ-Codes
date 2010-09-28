#include <iostream>
#include <fstream>
using namespace std;

int main(void)
{
    //ifstream cin("in");

    int varNum;
    char terminals[256];
    int inputVar[10];
    int caseCount = 1;
    while (cin >> varNum)
    {
        if (!varNum)
            break;
        cout << "S-Tree #" << caseCount++ << ":\n";
        for (int i = 1; i <= varNum; ++i)
        {
            char c;
            cin >> c;
            cin >> inputVar[i];
        }

        const int TerminalNum = 1 << varNum;
        for (int i = 0; i < TerminalNum; ++i)
        {
            cin >> terminals[i];
            //cout << terminals[i];
        }
        
        int testNum;
        cin >> testNum;
        for (int i = 0; i < testNum; ++i)
        {
            char input[10];
            for (int j = 1; j <= varNum; ++j)
                cin >> input[j];
            int start = 0, end = TerminalNum-1;
            for (int j = 1; j <= varNum; ++j)
            {
                char branchVal = input[inputVar[j]];
                //cout << inputVar[j] << endl;
                //cout << branchVal << endl;
                int tmp = (start+end)/2;
                if (branchVal == '0')
                    end = tmp;
                else
                    start = tmp+1;
                //cout << start << " " << end << endl;
            }
            //cout << start << endl;
            cout << terminals[start];
        }
        cout << endl << endl;
    }
    return 0;
}
