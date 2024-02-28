#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
};

vector<symboltable> ST(20);
vector<literaltable> LT(10);
vector<int> PT(10, 0);
vector<intercode> IC(50);

vector<MOTtable> MOT{
    {"STOP", 1, "00"},
    {"ADD", 1, "01"},
    {"SUB", 1, "02"},
    {"MULT", 1, "03"},
    {"MOVER", 1, "04"},
    {"MOVEM", 1, "05"},
    {"COMP", 1, "06"},
    {"BC", 1, "07"},
    {"DIV", 1, "08"},
    {"READ", 1, "09"},
    {"PRINT", 1, "10"},
    {"START", 3, "01"},
    {"END", 3, "02"},
    {"ORIGIN", 3, "03"},
    {"EQU", 3, "04"},
    {"LTORG", 3, "05"},
    {"DC", 2, "01"},
    {"DS", 2, "02"},
    {"AREG", 4, "01"},
    {"BREG", 4, "02"},
    {"CREG", 4, "03"},
    {"DREG", 4, "04"},
    {"LT", 5, "01"},
    {"LE", 5, "02"},
    {"EQ", 5, "03"},
    {"GT", 5, "04"},
    {"GE", 5, "05"},
    {"ANY", 5, "06"},
    {"NE", 5, "07"}};

int LC = 0;  // location counter
int iPT = 0; // index of entery in pool table
int iLT = 0; // index of entery in Literal table
int iST = 0; // index of entery in symbol table
int iIC = 0; // index of entery in intermediate code table

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
int searchST(string symbol)
{
    vector<symboltable>::iterator it;
    it = find_if(ST.begin(), ST.end(), [&](const symboltable &entry)
                 { return entry.Symbol == symbol; });
    if (it != ST.end())
        return it - ST.begin();
    else
        return -1;
}
int insertST(string symbol, int address)
{
    ST[iST].Symbol = symbol;
    ST[iST].Address = address;
    iST++;
    return iST - 1;
}

void imperative();
void declarative();
void directive();
void print_symbol();
void print_literal();
void print_pool();
void intermediate();
void LTORG();
void DC();
void DS();
void EQU(string);
void START();
void ORIGIN(string);
void END();
int tokencount;

string s1, s2, s3, label;

int main()
{
    ifstream fin;
    ///////////////////////////////////////////////////////////////////////////////////////////////
    fin.open("input3.txt");
    if (fin.fail())
    {
        cout << "Error in opeining file" << endl;
        return 1;
    }
    string line, word;
    int code1 = 0;
    // while (code1 != 16)
    while (!fin.eof())
    {
        code1++;
        // Resetting tokencount and label with symbols
        tokencount = 0;
        label.clear(), s1.clear(), s2.clear(), s3.clear();

        getline(fin, line);
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
        iss >> label >> s1 >> s2 >> s3;

        if (label == "END")
        {
            END();
            break;
        }
        if (!label.empty() and searchMOT(label) != -1)
        {
            s3 = s2;
            s2 = s1;
            s1 = label;
            label.clear();
        }
        else if (searchMOT(label) == -1)
        {
            int index = searchST(label);

            if (index == -1)
                insertST(label, LC);
            else
                ST[index].Address = LC;

            tokencount--;
        }
        if (tokencount == 0)
            continue;
        int index = searchMOT(s1);

        if (index == -1)
        {
            cout << "wrong opcode " << label << "At line " << code1 << endl;
            return 1;
        }
        switch (MOT[index].Class)
        {
        case 1:
            imperative();
            break;
        case 2:
            declarative();
            break;
        case 3:
            // directive();
            {
                if (s1 == "START")
                    START();
                else if (s1 == "ORIGIN")
                    ORIGIN(line);
                else if (s1 == "EQU")
                    EQU(line);
                else if (s1 == "LTORG")
                    LTORG();
            }
            break;
        default:
            cout << "Wrong Opcode " << s1 << endl;
            break;
        }
    }
    LTORG();
    print_symbol();
    print_pool();
    print_literal();
    intermediate();
    cout << "\nEnd of program" << endl;
    return 0;
}
void imperative()
{
    int index = searchMOT(s1);

    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = LC;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;
    LC++;
    if (tokencount > 1)
    {
        index = searchMOT(s2);
        if (index != -1)
        {
            IC[iIC].Code2 = index;
            IC[iIC].Type2 = MOT[index].Class;
        }
        else
        {
            // it is variable
            index = searchST(s2);
            if (index == -1)
                index = insertST(s2, 0);
            IC[iIC].Code2 = index;
            IC[iIC].Type2 = 7;
            // val 7 for variable
        }
    }
    if (tokencount > 2)
    {
        if (s3[0] == '=')
        {
            // LT[iLT].Literal = stoi(s3.substr(1, 1));
            int pos = s3.find('\n', 1);
            LT[iLT].Literal = stoi(s3.substr(1, pos));
            IC[iIC].Code3 = iLT;
            IC[iIC].Type3 = 8;
            // val 8 for literal
            iLT++;
        }
        else
        {
            index = searchST(s3);
            if (index == -1)
                index = insertST(s3, 0);
            IC[iIC].Code3 = index;
            IC[iIC].Type3 = 7;
        }
    }
    iIC++;
}
void declarative()
{
    if (s1 == "DC")
    {
        DC();
        return;
    }
    if (s1 == "DS")
        DS();
}
void directive()
{
}

void DC()
{
    int index = searchMOT(s1);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = LC;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;
    IC[iIC].Type2 = 6; // 6 for constants

    int pos = s2.find("'", 1);
    // check for '50'
    IC[iIC].Code2 = stoi(s2.substr(1, pos));

    index = searchST(label);
    if (index == -1)
        index = insertST(label, 0);
    ST[index].Address = LC;
    LC++;
    iIC++;
}

void DS()
{
    int index = searchMOT(s1);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = LC;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;
    IC[iIC].Type2 = 6; // 6 for constants

    IC[iIC].Code2 = stoi(s2);

    index = searchST(label);
    if (index == -1)
        index = insertST(label, 0);
    ST[index].Address = LC;
    LC = LC + stoi(s2);
    iIC++;
}

void LTORG()
{
    int index;
    for (int i = PT[iPT]; i < iLT; i++)
    {
        LT[i].Address = LC;
        index = searchMOT("DC");
        IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

        IC[iIC].LC = LC;
        IC[iIC].Code1 = index;
        IC[iIC].Type1 = MOT[index].Class;
        IC[iIC].Type2 = 6; // 6 for constants
        IC[iIC].Code2 = LT[i].Literal;
        LC++;
        iIC++;
    }
    iPT++;
    PT[iPT] = iLT;
}

void START()
{
    int index = searchMOT(s1);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = 0;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;
    IC[iIC].Type2 = 6; // 6 for constants
    IC[iIC].Code2 = stoi(s2);
    LC = stoi(s2);
    iIC++;
}

void ORIGIN(string line)
{
    int index = searchMOT(s1);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;
    IC[iIC].Code4 = "";

    IC[iIC].LC = 0;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;

    stringstream st(s2);
    string op1, op2;

    if (line.find('+') != string::npos)
    {
        getline(st, op1, '+');
        getline(st, op2, '\n');
        index = searchST(op1);

        LC = ST[index].Address + stoi(op2);
        IC[iIC].Type2 = 7; // 7 for variable
        IC[iIC].Code2 = index;
        IC[iIC].Code4 = '+' + op2;
    }
    else if (line.find('-') != string::npos)
    {
        getline(st, op1, '-');
        getline(st, op2, '\n');
        index = searchST(op1);

        LC = ST[index].Address - stoi(op2);
        IC[iIC].Type2 = 7; // 7 for variable
        IC[iIC].Code2 = index;
        IC[iIC].Code4 = '-' + op2;
    }
    else
    {
        int number;
        if (st >> number)
        {
            // It is a number
            IC[iIC].Type2 = 6; // 6 for constants
            IC[iIC].Code2 = number;
            LC = number;
        }
        else
        {
            st.str(s2);
            st.clear();
            // It is a symbol
            st >> op1;
            index = searchST(op1);
            LC = ST[index].Address;
            IC[iIC].Type2 = 7; // 7 for variable
            IC[iIC].Code2 = index;
        }
    }
    iIC++;
}

void EQU(string line)
{
    int index = searchMOT(s1);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = 0;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;

    stringstream st(s2);
    string op1, op2;
    int index_label = searchST(label);

    if (line.find('+') != string::npos)
    {
        getline(st, op1, '+');
        getline(st, op2, '\n');
        index = searchST(op1);

        ST[index_label].Address = ST[index].Address + stoi(op2);
        IC[iIC].Type2 = 7; // 7 for variable
        IC[iIC].Code2 = index;
        IC[iIC].Code4 = '+' + op2;
    }
    else if (line.find('-') != string::npos)
    {
        getline(st, op1, '-');
        getline(st, op2, '\n');
        index = searchST(op1);

        ST[index_label].Address = ST[index].Address - stoi(op2);
        IC[iIC].Type2 = 7; // 7 for variable
        IC[iIC].Code2 = index;
        IC[iIC].Code4 = '-' + op2;
    }
    else
    {
        int number;
        if (st >> number)
        {
            // It is a number
            IC[iIC].Type2 = 6; // 6 for constants
            IC[iIC].Code2 = number;
            ST[index_label].Address = number;
        }
        else
        {
            st.str(s2);
            st.clear();
            // It is a symbol
            st >> op1;
            index = searchST(op1);
            ST[index_label].Address = ST[index].Address;
            IC[iIC].Type2 = 7; // 7 for variable
            IC[iIC].Code2 = index_label;
        }
    }
    iIC++;
}

void END()
{
    int index = searchMOT(label);
    IC[iIC].Type1 = IC[iIC].Type2 = IC[iIC].Type3 = 0;

    IC[iIC].LC = 0;
    IC[iIC].Code1 = index;
    IC[iIC].Type1 = MOT[index].Class;
    if (s1 != "")
    {
        // cout << "NULL symbol" << endl;
        index = searchST(s1);
        IC[iIC].Code2 = index;
        IC[iIC].Type2 = 7; // 7 for variable
    }
    iIC++;
}

void intermediate()
{
    ofstream fout("IC.txt");
    char decode[9][3] = {"", "IS", "DL", "AD", "RG", "CC", "C", "S", "L"};
    cout << "\n\nGenerating Intermediate code" << endl;

    for (int i = 0; i < iIC; i++)
    {
        if (IC[i].LC != 0)
            fout << IC[i].LC << "\t";
        else
            fout << "\t";

        fout << "(" << decode[IC[i].Type1] << ","
             << MOT[IC[i].Code1].Opcode << ")\t";

        if (IC[i].Type2 != 0)
        {
            if (IC[i].Type2 < 6)
                fout << "(" << decode[IC[i].Type2] << ","
                     << MOT[IC[i].Code2].Opcode << ")";
            else
                fout << "(" << decode[IC[i].Type2] << ","
                     << IC[i].Code2 << ")";
        }
        if (IC[i].Code4 != "")
        {
            fout << IC[i].Code4;
        }
        if (IC[i].Type3 != 0)
        {
            fout << "\t(" << decode[IC[i].Type3] << ","
                 << IC[i].Code3 << ")";
        }
        fout << endl;
    }
    fout.close();
}

void print_symbol()
{
    ofstream fout("Symbol Table.txt");
    cout << "\n\nGenerating Symbol table" << endl;
    for (int i = 0; i < iST; i++)
    {
        fout << ST[i].Symbol << "\t" << ST[i].Address << endl;
    }
    fout.close();
}
void print_literal()
{
    ofstream fout("Literal Table.txt");
    cout << "\n\nGenerating Literal table" << endl;
    if (iLT == 0)
    {
        cout << "\nNULL Literal table as no literals in file" << endl;
        return;
    }
    for (int i = 0; i < iLT; i++)
    {
        fout << LT[i].Literal << "\t" << LT[i].Address << endl;
    }
    fout.close();
}
void print_pool()
{
    ofstream fout("Pool Table.txt");
    cout << "\n\nGenerating Pool table" << endl;
    if (PT[1] == 0)
    {
        cout << "\nNULL Pool table as no literals in file" << endl;
        return;
    }
    for (int i = 0; i < iPT; i++)
    {
        fout << PT[i] << endl;
    }
    fout.close();
}