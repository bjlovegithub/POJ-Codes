#include <iostream>
using namespace std;

const int MAX = 51;

class Graph
{
public:
    Graph(int len)
        {
            memset(mUsed, 0, sizeof(mUsed));
            mLen = len;
        }

    bool DrawTri(int x, int y, int len)
        {
            
        }

private:
    bool mUsed[MAX][MAX];
    int mRec[MAX][MAX];
    int mLen;
};
