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
    int PP, KP, KPDTABP = 0, MDTP = 0;
};
struct keyword
{
    string kname;
    string value;
};
struct MacroDefination
{
    string opcode;
    int Type1 = 0, Code1;
    int Type2 = 0, Code2;
};
struct MOTtable
{
    string Mnemonic;
    string Opcode;
};
vector<MacroName> MNT(10);
vector<keyword> KPDTAB(15);
vector<string> PNTAB(20);
vector<MacroDefination> MDT(50);
vector<MOTtable> MOT{
    {"STOP", "00"},
    {"ADD", "01"},
    {"SUB", "02"},
    {"MULT", "03"},
    {"MOVER", "04"},
    {"MOVEM", "05"},
    {"COMP", "06"},
    {"BC", "07"},
    {"DIV", "08"},
    {"READ", "09"},
    {"PRINT", "10"},
    {"START", "01"},
    {"END", "02"},
    {"ORIGIN", "03"},
    {"EQU", "04"},
    {"LTORG", "05"},
    {"DC", "01"},
    {"DS", "02"},
    {"AREG", "01"},
    {"BREG", "02"},
    {"CREG", "03"},
    {"DREG", "04"},
    {"LT", "01"},
    {"LE", "02"},
    {"EQ", "03"},
    {"GT", "04"},
    {"GE", "05"},
    {"ANY", "06"},
    {"NE", "07"}};

class PASS1
{
private:
    string op, s1, s2, line, word;
    vector<string> tokens;
    ifstream fin;
    ofstream fout1;
    int iMNT = 0, code1 = 0;
    int iMDT = 0;
    int iKPDTAB = 0;
    int iPNTAB = 0;

public:
    PASS1(string name)
    {
        fout1.open("PNTAB.txt", ios::out);
        fin.open(name);
        while (fin.fail())
        {
            cout << "File not found!!" << endl;
            cout << "Enter the file name: ";
            cin >> name;
            fin.open(name);
        }
    }
    ~PASS1()
    {
        fout1.close();
    }
    int searchMOT(string symbol)
    {
        vector<MOTtable>::iterator it;
        it = find_if(MOT.begin(), MOT.end(), [&](const MOTtable &entry)
                     { return entry.Mnemonic == symbol; });
        if (it != MOT.end())
            return it - MOT.begin();
        else
            return -1;
    }
    int searchPNT(string symbol)
    {
        vector<string>::iterator it;
        // it = find_if(PNTAB.begin(), PNTAB.end(), [&](const string &entry)
        //  { return entry == symbol; });
        it = find(PNTAB.begin(), PNTAB.end(), symbol);

        if (it != PNTAB.end())
            return it - PNTAB.begin();
        else
            return -1;
    }
    void print_MDT()
    {
        // cout << "\n\nMDT\n";
        ofstream fout("MDT.txt");
        char decode[5][3] = {"", "P", "RG", "L", "C"};
        for (int i = 0; i < iMDT; i++)
        {
            fout << left << setw(8) << setfill(' ') << MDT[i].opcode;
            if (MDT[i].Type1 != 0)
                fout << decode[MDT[i].Type1] << ' ' << MDT[i].Code1 << " ";
            if (MDT[i].Type2 != 0)
                fout << decode[MDT[i].Type2] << ' ' << MDT[i].Code2 << "  ";
            fout << endl;
        }
        fout.close();
    }
    void print_MNT()
    {
        ofstream fout("MNT.txt");
        for (int i = 0; i < iMNT; i++)
        {
            fout << MNT[i].mname << "  "
                 << MNT[i].PP << "  "
                 << MNT[i].KP << "  "
                 << MNT[i].KPDTABP << "  "
                 << MNT[i].MDTP << endl;
        }
        fout.close();
    }
    void print_KPDTAB()
    {
        // cout << "\n\nKPDTAB\n";
        // cout << "kname" << setw(10) << "value" << endl;
        ofstream fout("KPDTAB.txt");
        for (int i = 0; i < iKPDTAB; i++)
        {
            fout << left << setw(10) << setfill(' ') << KPDTAB[i].kname << setw(10) << KPDTAB[i].value << endl;
        }
        fout.close();
    }
    void print_PNTAB()
    {
        // cout << "\n\nPNTAB\n";

        for (int i = 0; i < iPNTAB; i++)
        {
            fout1 << PNTAB[i] << endl;
        }
    }
    void process()
    {
        while (getline(fin, line))
        {
            code1++;
            if (line == "START")
            {
                ofstream fout("IC.txt");
                getline(fin, line);
                while (line != "END")
                {
                    fout << line << endl;
                    getline(fin, line);
                }
                fout.close();
                break;
            }
            stringstream iss(line);
            s1.clear(), s2.clear(), op.clear();
            if (line == "MEND")
            {
                MDT[iMDT++].opcode = line;
                continue;
            }

            else if (line == "MACRO")
            {
                // vector<string>
                iPNTAB = 0;
                MNT[iMNT].MDTP = iMDT;
                MNT[iMNT].KPDTABP = iKPDTAB;
                MNT[iMNT].PP = -1;
                MNT[iMNT].KP = 0;
                tokens.clear();
                getline(fin, line);

                iss.str(line);
                iss.clear();

                // iss >> word;
                // MNT[iMNT].mname = word;

                while (!iss.eof())
                {
                    iss >> word;
                    tokens.push_back(word);
                }

                MNT[iMNT].mname = tokens[0];

                for (string stg : tokens)
                {
                    if (stg.find("=") != string::npos)
                    {
                        int index = stg.find("=");
                        MNT[iMNT].KP++;
                        PNTAB[iPNTAB++] = stg.substr(0, index);
                        KPDTAB[iKPDTAB].kname = stg.substr(0, index);
                        KPDTAB[iKPDTAB++].value = stg.substr(index + 1);
                    }
                    else
                    {
                        MNT[iMNT].PP++;
                        PNTAB[iPNTAB++] = stg;
                    }
                }
                iMNT++;
                print_PNTAB();
                continue;
            }

            iss >> op >> s1 >> s2;
            if (s1 == "")
                continue;
            int index = searchMOT(op);
            if (index != -1)
                MDT[iMDT].opcode = MOT[index].Mnemonic;
            else
                cout << "Wrong opcode at " << code1 << endl;
            index = searchMOT(s1);
            if (index != -1)
            {
                MDT[iMDT].Type1 = 2;
                MDT[iMDT].Code1 = stoi(MOT[index].Opcode);
            }
            else
            {
                index = searchPNT(s1);
                MDT[iMDT].Type1 = 1;
                MDT[iMDT].Code1 = index + 1;
            }
            index = searchPNT(s2);
            if (index != -1)
            {
                MDT[iMDT].Type2 = 1;
                MDT[iMDT].Code2 = index + 1;
            }
            else
            {
                if (s2.find('=') != string::npos)
                {

                    MDT[iMDT].Type2 = 3;
                    MDT[iMDT].Code2 = stoi(s2.substr(2, s2.find("'", 2)));
                }
                else
                {
                    MDT[iMDT].Type2 = 4;
                    MDT[iMDT].Code2 = stoi(s2);
                }
            }
            iMDT++;
        }

        print_MNT();
        print_KPDTAB();
        print_MDT();
    }
};
int main()
{
    PASS1 obj("input.txt");
    obj.process();
    return 0;
}