#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
struct MacroName
{
    string mname;
    int PP = 0, KP = 0, MDTP = 0, KPDTABP = 0;
};
struct keyword
{
    string kname;
    string value;
};
struct MacroDefination
{
    string opcode;
    int Class1 = 0, Code1;
    int Class2 = 0, Code2;
};

vector<MacroName> MNT;
vector<keyword> KPDTAB, APTAB;
vector<string> PNTAB;
vector<MacroDefination> MDT;
int searchMNT(string symbol)
{
    vector<MacroName>::iterator it;
    it = find_if(MNT.begin(), MNT.end(), [&](const MacroName &entry)
                 { return entry.mname == symbol; });
    if (it != MNT.end())
        return it - MNT.begin();
    else
        return -1;
}
void addMNT()
{
    ifstream fin("MNT.txt");
    string line, word;
    string name;
    int pp, kp, mdtp, kdptabp;
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> name >> pp >> kp >> mdtp >> kdptabp;
        MNT.push_back({name, pp, kp, kdptabp, mdtp});
    }
    fin.close();
}
int getcode(string word)
{
    if (word == "P")
        return 1;
    if (word == "RG")
        return 2;
    if (word == "L")
        return 3;
    if (word == "C")
        return 4;
    return 0;
}
void addMDT()
{
    ifstream fin("MDT.txt");
    string line, word;
    string op;
    while (getline(fin, line))
    {
    int code1 = 0, code2 = 0, cls1 = 0, cls2 = 0;
    string class1 = "", class2 = "";
        stringstream iss(line);
        iss >> op >> class1 >> code1 >> class2 >> code2;
        cls1 = getcode(class1);
        cls2 = getcode(class2);
        MDT.push_back({op, cls1, code1, cls2, code2});
    }
    fin.close();
    char decode[5][3] = {"", "P", "RG", "L", "C"};

}
void addKDP()
{
    ifstream fin("KPDTAB.txt");
    string line, word;
    string name, val;
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> name >> val;
        KPDTAB.push_back({name, val});

        // vector<keyword>::iterator it;

        // it = find(APTAB.begin(), APTAB.end(), name);

        // if (it != APTAB.end())
        //     APTAB[it - APTAB.begin()].value = val;
    }
    fin.close();
}
void addPNT()
{
    ifstream fin("PNTAB.txt");
    string line, word;
    string name;
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> name;
        PNTAB.push_back(name);
        APTAB.push_back({name});
    }
    fin.close();
}
void getMC()
{
    ofstream fout("MC.txt");
    ifstream fin("IC.txt");
    string line, word;
    while (getline(fin, line))
    {
        stringstream iss(line);
        iss >> word;
        int index = searchMNT(word);
        int imdt = MNT[index].MDTP;
        cout << index << "  " << imdt << endl;

        // fout << imdt << endl;
        // int ikpdt = MNT[index].KPDTABP;

        // vector<string> tokens;
        // vector<keyword>::iterator it;
        // it = find(APTAB.begin(), APTAB.end(), MNT[index].mname);
        // int iapt = it - APTAB.begin();
        // while (!iss.eof())
        // {
        //     iss >> word;
        //     tokens.push_back(word);
        // }
        // for (string stg : tokens)
        // {
        //     if (stg.find("=") != string::npos)
        //     {
        //         int index = stg.find("=");
        //         it = find(APTAB.begin(), APTAB.end(), stg.substr(0, index));
        //         APTAB[it - APTAB.begin()].value = stg.substr(index + 1);
        //     }
        //     else
        //     {
        //         APTAB[++iapt].value = stg;
        //     }
        // }
        char decode[5][3] = {"", "P", "RG", "L", "C"};
        while (MDT[imdt].opcode != "MEND")
        {
            fout << MDT[imdt].opcode << "  "
                 << decode[MDT[imdt].Class1] << "  " << MDT[imdt].Code1 << "  "
                 << decode[MDT[imdt].Class2] << "  " << MDT[imdt++].Code2 << endl;
        }
    }
    fout.close();
    fin.close();
}
int main()
{
    addMNT();
    addMDT();
    addPNT();
    addKDP();
    getMC();
    return 0;
}