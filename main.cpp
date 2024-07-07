#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n; // no. of processes
// pid,  at,  bt,  priority
vector<tuple<int, int, int, int>> processes;
// completion time
vector<int> ct;
// turn around time
vector<int> tat;
// waiting time
vector<int> wt;

// function to take inputs from user
void takeInput(bool isPriority)
{
    cout << "Enter no. of processes : ";
    cin >> n;
    cout << endl;
    int at, bt, priority;
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i << endl;
        cout << "Enter Arrival Time : ";
        cin >> at;
        cout << endl;
        cout << "Enter Burst Time : ";
        cin >> bt;
        cout << endl;
        if (!isPriority)
        {
            processes.push_back(make_tuple(i, at, bt, 0));
        }
        else
        {
            cout << "Enter Priority : ";
            cin >> priority;
            cout << endl;
            processes.push_back(make_tuple(i, at, bt, priority));
        }
    }
}

void displayOutput()
{
    int sumTAT = 0, sumWT = 0;
    for (int i = 0; i < n; i++)
    {
        sumTAT += tat[i];
        sumWT += wt[i];
    }
    float avgTAT = (float)sumTAT / n;
    float avgWT = (float)sumWT / n;
    float throughput = (float)n / ct.back();
    int sumBT = 0;
    for (int i = 0; i < n; i++)
    {
        sumBT += get<2>(processes[i]);
    }
    float cpu = ((float)sumBT / ct.back()) * 100;
    cout << "Average Turn Around Time : " << avgTAT << endl;
    cout << "Average Waiting Time : " << avgWT << endl;
    cout << "Throughput : " << throughput << endl;
    cout << "CPU utilization(%) : " << cpu << "%" << endl;
}

void firstComeFirstServe()
{
    // take from inputs user
    takeInput(false);

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return get<1>(a) < get<1>(b); });

    // completionTime;
    int cTime = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        if (i == 0 || get<1>(processes[i]) > cTime)
        {
            // If CPU is idle, move to the arrival time of the current process
            cTime = max(cTime, get<1>(processes[i]));
        }
        cTime += get<2>(processes[i]);
        ct.push_back(cTime);
        // turnAroundTime;
        tat.push_back(ct[i] - get<1>(processes[i]));
        // waitingTime(wt);
        wt.push_back(tat[i] - get<2>(processes[i]));
    }
    displayOutput();
}

struct compareTuples
{
    bool operator()(const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b)
    {
        if (get<2>(a) == get<2>(b))
        {
            return get<1>(a) > get<1>(b);
        }
        return get<2>(a) > get<2>(b);
    }
};

void shortestJobFirst()
{
    takeInput(false);

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return get<1>(a) < get<1>(b); });

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, compareTuples> pq;
    int i = 0, completed = 0, currTime = 0;
    while (completed != n)
    {
        while (i < n && get<1>(processes[i]) <= currTime)
        {
            pq.push(processes[i]);
            i++;
        }

        // queue is empty means cpu is idle
        if (pq.empty())
        {
            if (i < n)
            {
                currTime = get<1>(processes[i]);
            }
        }
        else
        {
            tuple<int, int, int, int> currProcess = pq.top();
            pq.pop();
            currTime += get<2>(currProcess);
            ct.push_back(currTime);
            tat.push_back(currTime - get<1>(currProcess));
            wt.push_back(tat.back() - get<2>(currProcess));
            completed++;
        }
    }
    displayOutput();
}

void shortestRemainingTime()
{
    takeInput(false);

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return get<1>(a) < get<1>(b); });

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, compareTuples> pq;

    vector<int> remainingBt(n);
    for (int i = 0; i < n; i++)
    {
        remainingBt[i] = get<2>(processes[i]);
    }

    int completed = 0, currTime = 0, i = 0;

    while (completed < n)
    {
        while (i < n && get<1>(processes[i]) <= currTime)
        {
            pq.push(processes[i]);
            i++;
        }

        if (pq.empty())
        {
            if (i < n)
            {
                currTime = get<1>(processes[i]);
            }
        }
        else
        {
            tuple<int, int, int, int> currProcess = pq.top();
            pq.pop();

            int burstTime = get<2>(currProcess);
            int pid = get<0>(currProcess);

            int processIndex = 0;
            while (get<0>(processes[processIndex]) != pid)
            {
                processIndex++;
            }

            if (remainingBt[processIndex] > 0)
            {
                if (remainingBt[processIndex] > 1)
                {
                    currTime++;
                    remainingBt[processIndex]--;

                    while (i < n && get<1>(processes[i]) <= currTime)
                    {
                        pq.push(processes[i]);
                        i++;
                    }

                    pq.push({pid, get<1>(currProcess), remainingBt[processIndex], get<3>(currProcess)});
                }
                else
                {
                    currTime += remainingBt[processIndex];
                    remainingBt[processIndex] = 0;
                    ct.push_back(currTime);
                    tat.push_back(currTime - get<1>(currProcess));
                    wt.push_back(tat.back() - burstTime);
                    completed++;
                }
            }
        }
    }
    displayOutput();
}

void roundRobinScheduling(int tq)
{
    takeInput(false);

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         { return get<1>(a) < get<1>(b); });

    vector<int> remainingBt(n, 0);

    for (int i = 0; i < n; i++)
    {
        remainingBt[i] = get<2>(processes[i]);
    }

    queue<int> q;
    int i = 0;
    int currTime = 0;
    int completed = 0;

    while (completed < n)
    {
        while (i < n && get<1>(processes[i]) <= currTime)
        {
            q.push(i);
            i++;
        }

        if (q.empty() && i < n)
        {
            currTime = get<1>(processes[i]);
        }
        else
        {
            int index = q.front();
            q.pop();

            if (remainingBt[index] > tq)
            {
                currTime += tq;
                remainingBt[index] -= tq;

                // add processes arrived while executing current process
                while (i < n && get<1>(processes[i]) <= currTime)
                {
                    q.push(i);
                    i++;
                }
                // again add current process to queue
                q.push(index);
            }
            else
            {
                currTime += remainingBt[index];
                ct.push_back(currTime);
                tat.push_back(ct.back() - get<1>(processes[index]));
                wt.push_back(tat.back() - get<2>(processes[index]));
                remainingBt[index] = 0;
                completed++;
            }
        }
    }
    displayOutput();
}

struct comparePriority
{
    bool operator()(const tuple<int, int, int, int> &a, const tuple<int, int, int, int> &b)
    {
        if (get<3>(a) == get<3>(b))
        {
            // Compare by arrival time if priorities are the same
            return get<1>(a) > get<1>(b);
        }
        // Higher priority means lower number
        return get<3>(a) > get<3>(b);
    }
};

void priority()
{
    takeInput(true);

    sort(processes.begin(), processes.end(), [](const auto &a, const auto &b)
         {
             return get<1>(a) < get<1>(b); // Sort by arrival time
         });

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, comparePriority> pq;

    vector<int> remainingBt(n);
    for (int i = 0; i < n; ++i)
    {
        remainingBt[i] = get<2>(processes[i]);
    }

    int completed = 0, currTime = 0, i = 0;

    while (completed < n)
    {
        while (i < n && get<1>(processes[i]) <= currTime)
        {
            pq.push(processes[i]);
            i++;
        }

        if (pq.empty())
        {
            if (i < n)
            {
                currTime = get<1>(processes[i]);
            }
        }
        else
        {
            tuple<int, int, int, int> currProcess = pq.top();
            pq.pop();

            int processIndex = 0;
            while (get<0>(processes[processIndex]) != get<0>(currProcess))
            {
                processIndex++;
            }

            int burstTime = remainingBt[processIndex];
            if (burstTime > 0)
            {
                if (burstTime > 1)
                {
                    currTime++;
                    remainingBt[processIndex]--;

                    while (i < n && get<1>(processes[i]) <= currTime)
                    {
                        pq.push(processes[i]);
                        i++;
                    }

                    pq.push({get<0>(currProcess), get<1>(currProcess), remainingBt[processIndex], get<3>(currProcess)});
                }
                else
                {
                    currTime += burstTime;
                    remainingBt[processIndex] = 0;
                    ct.push_back(currTime);
                    tat.push_back(currTime - get<1>(currProcess));
                    wt.push_back(tat.back() - get<2>(currProcess));
                    completed++;
                }
            }
        }
    }
    displayOutput();
}

int main()
{
    int choice;
    cout << "Select Scheduling Algorithm:\n";
    cout << "1. FCFS\n2. SJF\n3. shortestRemainingTime\n4. Priority\n5. Round Robin\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        firstComeFirstServe();
        break;
    case 2:
        shortestJobFirst();
        break;
    case 3:
        shortestRemainingTime();
        break;
    case 4:
        priority();
        break;
    case 5:
        int tq;
        cout << "Enter Time Quantum : ";
        cin >> tq;
        roundRobinScheduling(tq);
        break;
    default:
        cout << "Invalid choice\n";
    }

    return 0;
}
