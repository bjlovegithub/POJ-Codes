#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

//#define DEBUG

#ifdef DEBUG
#define LOG(content)                            \
    do {                                        \
        stringstream ss;                        \
        ss << content << endl;                  \
        cout << ss.str();                       \
    } while(0);
#define LOG_CALL()  LOG(__FILE__ << ":" << __FUNCTION__)
#else
#define LOG(content)
#define LOG_CALL()
#endif

map<string, bool> FindSet;

string ToString(int num, int arr[10])
{
    stringstream ss;
    sort(arr, arr+num);
    for (int i = 0; i < num; ++i)
        ss << arr[i] << "-";
    return ss.str();
}


int max(int a, int b)
{
    return (a >= b ? a : b);
}

int min(int a, int b)
{
    return (a >= b ? b : a);
}

int GCD(int a, int b)
{
    while(true)
    {
        a = a % b;
		if(a == 0)
			return b;
		b = b % a;
        if(b == 0)
			return a;
    }
}

int Eval(int p, int q, int level, int arr[10])
{
    LOG_CALL();
    LOG(p << "/" << q << ", " << level);
    for (int i = 0; i < level; ++i)
        LOG(arr[i]);

    if (level < 1)
        return 1;
    long tp = arr[0];
    long up = 1;
    for (int i = 1; i < level; ++i)
    {
        int tmp = tp;
        tp = tp*arr[i];
        up = up*arr[i] + tmp;
        int gcd = GCD(max(tp, up), min(tp, up));
        tp /= gcd;
        up /= gcd;
    }

    LOG("up: " << up << ", tp: " << tp);

    if (up == p && tp == q)
        return 0;
    double dest = (double)(p)/q;
    double curr = (double)(up)/tp;
    if (dest < curr)
        return 2;
    return 1;
}

void Search(int p, int q, int a, int n, int &c, int level, int start, int arr[10])
{
    LOG("level: " << level << ", start: " << start);
    int multiResult = 1;
    for (int i = 0; i < level; ++i)
        multiResult *= arr[i];

    LOG("multiResult: " << multiResult);
    for (int i = 0; i < level; ++i)
        LOG(arr[i]);
    
    for (int i = start; ; --i)
    {
        if (multiResult * i > a)
            continue;
        arr[level] = i;
        int flag = Eval(p, q, level+1, arr);
        LOG("Eval ret value: " << flag);
        bool out = false;
        string key;
        switch(flag)
        {
        case 0: /// equal
            key = ToString(level+1, arr);
            if (FindSet.find(key) == FindSet.end())
            {
                ++c;
                FindSet[key] = true;
            }
            out = true;
            break;
        case 1: /// less than p/q
            if (level+1 < n)
                Search(p, q, a, n, c, level+1, a/(multiResult*i)+1, arr);
            break;
        case 2: /// larger than p/q
            out = true;
            break;
        }
        if (out)
            break;
    }
}

int main(void)
{
    ifstream cin("in");

    int p, q, n, a;
    while (cin >> p >> q >> a >> n)
    {
        if (!p && !q && !a && !n)
            break;
        int c = 0;
        int arr[10];
        memset(arr, 0, sizeof(arr));
        Search(p, q, a, n, c, 0, a, arr);
        cout << c << endl;
    }

    return 0;
}
