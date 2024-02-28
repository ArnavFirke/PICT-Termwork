#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    string s1, s2, op;
    int val1, val2 = 05;
    string line = "L2+ 100 50 k;;k kjku oppp 10", val50 = "05";
    stringstream iss(line);
    cout << val2 << endl;

    // try
    // {
    //     val=stoi(s1);
    // }
    // catch (exception &e)
    // {
    //     cout << "Error" << endl;
    // }

    // cout << val << endl;
    // iss >> s1 >> s2;
    // if (s2 == "")
    // cout << "NULL s2" << endl;
    // if (line.find('+') != string::npos)
    // {
    //     getline(iss, s1, '+');
    //     getline(iss, s2, '\n');
    //     cout << "Line has +" << endl;
    //     op = '+' + s2;
    // }
    // else if (line.find('-') != string::npos)
    // {
    //     getline(iss, s1, '-');
    //     getline(iss, s2, '\n');
    //     cout << "Line has -" << endl;
    //     op = '-' + s2;
    // }
    // else
    // {
    //     // getline(iss, s1);
    //     int num;
    //     if (iss >> num)
    //     {
    //         cout << "Line has number " << num << endl;
    //     }
    //     else
    //         cout << "Line has symbol" << endl;
    // }
    // cout << s1 << endl;
    // cout << "" << op << endl;
    // cout << s2 << endl;

    // iss.str(s1);

    // iss >> s1 >> s >> s2;
    // cout << s1 << endl;
    // cout << s << endl;
    // cout << s2 << endl;
    return 0;
}

bool isNumber(const std::string &s)
{
    try
    {
        size_t pos;
        int num = std::stoi(s, &pos);
        return pos == s.size(); // Ensure the whole string was used for conversion
    }
    catch (const std::exception &)
    {
        return false;
    }
}

// int main()
// {
//     std::string line = "400";

//     if (isNumber(line))
//     {
//         std::cout << "It is a number" << std::endl;
//     }
//     else
//     {
//         std::cout << "It is not a number" << std::endl;
//     }

//     return 0;
// }
