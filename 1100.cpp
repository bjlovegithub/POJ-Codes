#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum SybType {Op, Digi, Par};

struct Element
{
    SybType type;
    unsigned int val;
    char syb;
};

void Parse(const string &input, vector<Element> &exp, int &result)
{
    stringstream ss(input);
    ss >> result;
    char c;
    while (ss >> c && c != '=');

    while(ss)
    {
        while (ss >> c && c == ' ');
        if (c >= '0' && c <= '9') /// is digit
        {
            Element e;

            /// Add a operator between two numbers
            SybType t = exp[exp.size()-1].type;
            if (exp.size() >= 1 &&
                (t == Digi || (t == Par && exp[exp.size()-1].syb == ')')))
            {
                e.type = Op;
                e.syb = '_';
                exp.push_back(e);
            }

            e.type = Digi;
            ss.putback(c);
            ss >> e.val;
            exp.push_back(e);
        }
        else /// is parenthesis
        {
            Element e;
            if ('(' == c)
            {
                if (exp.size() >= 1 && exp[exp.size()-1].type == Digi)
                {
                    e.type = Op;
                    e.syb = '_';
                    exp.push_back(e);
                }
            }

            e.type = Par;
            e.syb = c;
            exp.push_back(e);
        }
    }
}

void PrintResult(const vector<Element> &exp, int result)
{
    cout << result << "=";
    for (size_t i = 0; i < exp.size(); ++i)
    {
        if (exp[i].type == Digi)
            cout << exp[i].val;
        else
            cout << exp[i].syb;
    }
    cout << endl;
}

int main(void)
{
    string input;
    int count = 1;
    while (getline(cin, input))
    {
        if (input == "0")
            break;

        printf("Equation #%d:\n", count++);
        
        vector<Element> exp;
        int result;
        Parse(input, exp, result);

        //bool flag = false;
        //Search(exp, flag, '*');

        PrintResult(exp, result);
    }

    return 0;
}

