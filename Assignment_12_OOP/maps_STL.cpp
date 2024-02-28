#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

string tolower(string s1)
{
    for (int i = 0; i < s1.length(); i++)
    {
        s1[i] = tolower(s1[i]);
    }
    return s1;
}

class States
{
private:
    map<string, int> population;

public:
    States()
    {
        population.insert(make_pair("Uttar Pradesh", 199812341));
        population.insert(make_pair("Maharashtra", 112374333));
        population.insert(make_pair("Bihar", 104099452));
        population.insert(make_pair("West Bengal", 91276115));
        population.insert(make_pair("Madhya Pradesh", 72626809));
        population.insert(make_pair("Tamil Nadu", 72147030));
    }
    void find()
    {
        string stateName;
        cout << "Enter state Name: ";
        cin.ignore();
        getline(cin, stateName);
        bool found = false;
        for (auto iter = population.begin(); iter != population.end(); iter++)
        {
            auto string1 = iter->first;
            string1 = tolower(string1);
            stateName = tolower(stateName);
            int position = 0;
            int index_str;
            // find function return string::npos if substring is not found
            // if it finds it will return the 1st position
            while ((index_str = string1.find(stateName, position)) != string::npos)
            {
                cout << iter->first << " 's population is " << iter->second << endl;
                found = true;
                position = index_str + 1;
            }
        }
        if (!found)
        {
            cout << "No key found" << endl;
        }
    }
    void display()
    {
        for (auto x : population)
            cout << setw(15) << x.first << ":\t" << x.second << endl;
        cout << endl;
    }
    void insertpair(string state, int pop)
    {
        for (auto iter = population.begin(); iter != population.end(); iter++)
        {
            if (iter->first == state)
            {
                cout << "State Aldready Present in the Map" << endl;
                return;
            }
        }
        population.insert(make_pair(state, pop));
    }
    void update(string state, int pop)
    {
        for (auto iter = population.begin(); iter != population.end(); iter++)
        {
            if (iter->first == state)
            {
                // population[state] = pop;
                iter->second = pop;
                return;
            }
        }
        cout << "State not present in the Map" << endl;
    }
};

int main()
{
    States populationMap;
    cout << "\n *** Menu ***";
    cout << "\n 1. Search State";
    cout << "\n 2. Display All";
    cout << "\n 3. Add in Map";
    cout << "\n 4. Update Map";
    cout << "\n 5. Exit";
    int choice = 0;
    while (choice != 5)
    {

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            populationMap.find();
            break;
        }

        case 2:
        {
            populationMap.display();
            break;
        }
        case 3:
        {
            cout << "Enter the state Name ";
            string stateName;
            cin >> stateName;
            cout << "Enter Population ";
            int pop;
            cin >> pop;
            populationMap.insertpair(stateName, pop);
            break;
        }
        case 4:
        {
            cout << "Enter the state Name ";
            string stateName;
            cin >> stateName;
            cout << "Enter Population ";
            int pop;
            cin >> pop;
            populationMap.update(stateName, pop);
            break;
        }
        case 5:
        {
            cout << "Exited" << endl;
            break;
        }

        default:
            cout << "\nWrong choice!!!" << endl;
            ;
        }
    }
    return 0;
}