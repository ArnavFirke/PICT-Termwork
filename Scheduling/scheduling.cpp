#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

class process
{
private:
    string processid;
    int arrivalTime, bt, ct, wt, tat, remaint;
    int priority;

public:
    process(string id = "", int a = 0, int b = 0, int p = 0)
    {
        processid = id, arrivalTime = a, bt = remaint = b;
        ct = wt = tat = 0, priority = p;
    }
    friend class scheduling;
};

class scheduling
{
private:
    vector<process> rq;
    float avgwt, avgtat, totct;
    int size;

public:
    scheduling() : avgtat(0), avgwt(0), totct(0) {}

    // Function to compare rq based on their arrival time
    static bool compareAT(const process &p1, const process &p2)
    {
        return p1.arrivalTime < p2.arrivalTime;
    }

    static bool comparePr(const process &p1, const process &p2)
    {
        if (p1.arrivalTime == p2.arrivalTime)
            return p1.priority > p2.priority;
        else
            return p1.arrivalTime < p2.arrivalTime;
    }

    // Function to set the size of the ready queue
    void setsize()
    {
        cout << "Size: ";
        cin >> size;
        rq.resize(size);
        avgtat = avgwt = totct = 0;
    }

    // Function to take input and set values for the rq
    void schedule()
    {
        string id;
        int at, bt;
        cout << "Enter\nid  at  bt" << endl;
        for (int i = 0; i < size; i++)
        {
            cin >> id >> at >> bt;
            rq[i] = process(id, at, bt); // Set values for the existing elements
        }
    }
    // Function to take input and set values for the rq with priority
    void schedule_priority()
    {
        string id;
        int at, bt, pr;
        cout << "Enter\nid  at  bt  pr" << endl;
        for (int i = 0; i < size; i++)
        {
            cin >> id >> at >> bt >> pr;
            rq[i] = process(id, at, bt, pr); // Set values for the existing elements
        }
    }

    // Function to calculate turnaround time for each process
    void findTurnAroundTime()
    {
        int tot = 0;
        for (int i = 0; i < size; i++)
            rq[i].tat = rq[i].bt + rq[i].wt, tot += rq[i].tat;
        avgtat = float(tot) / float(size);
    }

    // Function to calculate completion time for each process
    void findCompletionTime()
    {
        rq[0].ct = rq[0].bt;
        totct += rq[0].ct;
        for (int i = 1; i < size; i++)
            rq[i].ct = rq[i - 1].ct + rq[i].bt, totct += rq[i].ct;
    }

    // Function to display the process details
    void display()
    {
        cout << "Id"
             << "  AT"
             << "  BT"
             << "  Pr"
             << "  CT"
             << "  TAT"
             << " WT" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << rq[i].processid << setw(4)
                 << rq[i].arrivalTime << setw(4)
                 << rq[i].bt << setw(4)
                 << rq[i].priority << setw(4)
                 << rq[i].ct << setw(4)
                 << rq[i].tat << setw(4)
                 << rq[i].wt
                 << endl;
        }
        cout << "\nTotal Completion Time is: " << totct << endl;
        cout << "Average TurnAround time Time is: " << avgtat << endl;
        cout << "Average Waiting Time is: " << avgwt << endl;
    }

    // Function to implement First-Come-First-Serve (FCFS) scheduling algorithm
    void FCFS()
    {
        cout << "\nFCFS Scheduling\n"
             << endl;
        int tt = 0;
        sort(rq.begin(), rq.end(), compareAT);
        findCompletionTime();

        rq[0].wt = 0;
        for (int i = 1; i < size; i++)
        {
            rq[i].wt = rq[i].ct - rq[i].arrivalTime - rq[i].bt;
            tt += rq[i].wt;
        }
        avgwt = float(tt) / float(size);
        findTurnAroundTime();
        display();
    }

    // Function to implement Shortest Job First (SJF) scheduling algorithm
    void SJF()
    {
        findCompletionTime();
        int remainTime[size];

        for (int i = 0; i < size; i++)
            remainTime[i] = rq[i].bt;

        int complete = 0, currt = 0, minm = INT_MAX;
        int shortest = 0, finish_time;
        bool check = false;

        while (complete != size)
        {
            // Find process with minimum remaining time among the
            // rq that arrives till the current time
            for (int j = 0; j < size; j++)
            {
                if ((rq[j].arrivalTime <= currt) && (remainTime[j] < minm) && remainTime[j] > 0)
                {
                    minm = remainTime[j];
                    shortest = j;
                    check = true;
                }
            }

            if (check == false)
            {
                currt++;
                continue;
            }

            // Reduce remaining time by one
            remainTime[shortest]--;

            // Update minimum
            minm = remainTime[shortest];
            if (minm == 0)
                minm = INT_MAX;

            // If a process gets completely executed
            if (remainTime[shortest] == 0)
            {
                // Increment complete
                complete++;
                check = false;

                // Find finish time of the current process
                finish_time = currt + 1;

                // Calculate waiting time
                rq[shortest].wt = finish_time - rq[shortest].bt - rq[shortest].arrivalTime;

                if (rq[shortest].wt < 0)
                    rq[shortest].wt = 0;
            }
            // Increment time
            currt++;
        }
        findTurnAroundTime();
        display();
    }

    // Function to implement Priority scheduling algorithm
    void Priority()
    {
        sort(rq.begin(), rq.end(), compareAT);
        int currtime = 0, highprindex, highpr;
        bool completed;
        while (true)
        {
            completed = true;
            highprindex = -1, highpr = INT_MIN;

            for (int i = 0; i < size; i++)
            {
                if (rq[i].remaint > 0)
                {
                    completed = false;
                    if (rq[i].arrivalTime <= currtime)
                    {
                        if (rq[i].priority > highpr)
                        {
                            highpr = rq[i].priority;
                            highprindex = i;
                        }
                    }
                }
            }
            if (completed)
            {
                break;
            }

            rq[highprindex].remaint = 0;
            currtime += rq[highprindex].bt;
            rq[highprindex].ct = currtime;
        }
        totct = currtime;
        int totwt = 0;
        for (int i = 0; i < size; i++)
            rq[i].wt = rq[i].ct - rq[i].arrivalTime - rq[i].bt, totwt += rq[i].wt;
        avgwt = float(totwt) / (float)size;
        findTurnAroundTime();
        display();
    }

    // Function to implement Round Robin scheduling algorithm
    void RoundRobin(int qtime)
    {
        int currtime = rq[0].arrivalTime;
        int completed = size;
        for (int i = 0;; i = (i + 1) % size)
        {
            if (rq[i].remaint > 0 && rq[i].arrivalTime <= currtime)
            {
                if (rq[i].remaint <= qtime)
                {
                    currtime += rq[i].remaint;
                    rq[i].ct = currtime;
                    rq[i].remaint = 0;
                    completed--;
                }
                else
                {
                    currtime += qtime;
                    rq[i].remaint -= qtime;
                }
            }

            if (completed == 0)
            {
                break;
            }
        }
        int totwt = 0;
        for (int i = 0; i < size; i++)
            rq[i].wt = rq[i].ct - rq[i].arrivalTime - rq[i].bt, totwt += rq[i].wt;
        avgwt = float(totwt) / (float)size;
        findTurnAroundTime();
        display();
    }
};

int main()
{
    scheduling sh;
    int choice, qt;
    while (true)
    {
        cout << "\n1.Set the number of processess" << endl;
        cout << "2.Schedule Process without priority" << endl;
        cout << "3.Schedule Process with priority" << endl;
        cout << "4.FCFS Scheduling" << endl;
        cout << "5.SJF preemptive Scheduling" << endl;
        cout << "6.Priority Scheduling" << endl;
        cout << "7.Round Robin Scheduling" << endl;
        cout << "8.Display" << endl;
        cout << "9.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            sh.setsize();
            break;
        case 2:
            sh.schedule();
            break;
        case 3:
            sh.schedule_priority();
            break;
        case 4:
            sh.FCFS();
            break;
        case 5:
            sh.SJF();
            break;
        case 6:
            sh.Priority();
            break;
        case 7:
            cout << "Enter the quantum time: ";
            cin >> qt;
            sh.RoundRobin(qt);
            break;
        case 8:
            sh.display();
        case 9:
            return 0;
        default:
            cout << "\nEnter correct operation" << endl;
        }
    }
    return 0;
}
