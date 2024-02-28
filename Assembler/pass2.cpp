#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct MOTtable
{
    string Mnemonic;
    int Class;
    string Opcode;
};
struct symboltable
{
    string Symbol;
    int Address;
};

struct literaltable
{
    int Literal;
    int Address;
};

struct intercode
{
    int LC;
    int Code1, Type1;
    int Code2, Type2;
    int Code3, Type3;
    string Code4;
    // intercode()
    // {
    // Code4 = "";
    // }
};

vector<symboltable> ST(20);
vector<literaltable> LT(10);
vector<int> PT(10, 0);
// vector<intercode> IC;
vector<string> IC;

int LC = 0;  // location counter
int iPT = 0; // index of entery in pool table
int iLT = 0; // index of entery in Literal table
int iST = 0; // index of entery in symbol table
int iIC = 0; // index of entery in intermediate code table

string LCounter, op1, op2, op3;

void getSymbols()
{
    ifstream fin("Symbol Table.txt");
    string line;
    if (fin.fail())
    {
        cout << "Symbol table opening failed." << endl;
        return;
    }
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> ST[iST].Symbol >> ST[iST++].Address;
    }
    fin.close();
}
void getliterals()
{
    ifstream fin("Literal Table.txt");
    string line;
    if (fin.fail())
    {
        cout << "Literal table opening failed." << endl;
        return;
    }
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> LT[iLT].Literal >> LT[iLT++].Address;
    }
    fin.close();
}
void getPools()
{
    ifstream fin("Pool Table.txt");
    string line;
    if (fin.fail())
    {
        cout << "Pool table opening failed." << endl;
        return;
    }
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> PT[iPT++];
    }
    fin.close();
}
void getIC()
{
    ifstream fin("IC.txt");
    ofstream fout("MC.txt");
    string line, word;
    int Loc, tokencount;
    if (fin.fail())
    {
        cout << "IC file opening failed" << endl;
        return;
    }
    while (getline(fin, line))
    {
        tokencount = 0;
        LCounter.clear(), op1.clear(), op2.clear(), op3.clear();
        stringstream iss(line);
        while (!iss.eof())
        {
            iss >> word;
            if (!iss.fail())
            {
                tokencount++;
            }
        }
        // Reinitialize iss with line
        iss.str(line);

        // Clear any error flags
        iss.clear();

        bool result = false;
        iss >> LCounter >> op1 >> op2 >> op3;
        try
        {
            Loc = stoi(LCounter);
            result = true;
            tokencount--;
        }
        catch (...)
        {
        }
        if (!result)
        {
            op3 = op2;
            op2 = op1;
            op1 = LCounter;
            Loc = 0;
        }
        if (Loc == 0)
        {
            fout << "\n";
            continue;
        }
        fout << Loc << ")  ";

        string Class, code;
        getline(stringstream(op1), Class, ',');
        getline(stringstream(op1.substr(op1.find(',') + 1)), code, ')');
        // if (Class == "(DL" and code == "02")
        if (Class == "(DL")
        {
            fout << "0   ";
        }
        else
            fout << code << "  ";

        getline(stringstream(op2), Class, ',');
        getline(stringstream(op2.substr(op2.find(',') + 1)), code, ')');

        fout << code << "  ";
        if (op3 != "")
        {
            getline(stringstream(op3), Class, ',');
            getline(stringstream(op3.substr(op3.find(',') + 1)), code, ')');
            if (Class == "(L")
                fout << LT[stoi(code)].Address;
            else if (Class == "(S")
                fout << ST[stoi(code)].Address;
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}

int main()
{
    getSymbols();
    getliterals();
    getPools();
    getIC();
    // for (int i = 0; i < iST; i++)
    // {
    //     cout << ST[i].Symbol << "\t" << ST[i].Address << endl;
    // }
    // for (int i = 0; i < iLT; i++)
    // {
    //     cout << LT[i].Literal << "\t" << LT[i].Address << endl;
    // }
    // for (int i = 0; i < iPT; i++)
    // {
    //     cout << PT[i] << endl;
    // }
    return 0;
}