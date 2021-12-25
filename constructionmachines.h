#ifndef CONSTRUCTIONMACHINES_H
#define CONSTRUCTIONMACHINES_H
#include <string>
#include <QDebug>
#include <QString>

using namespace std;

class ConstructionMachines
{
public:
    enum status {
        Work = 1,
        Repair = -1,
        Idle = 0
    };
private:

    status status_machine;
    int WorkTime;
    int RepairTime;


public:
    ConstructionMachines():  status_machine(Work), WorkTime(0),RepairTime(0) {}
    ~ConstructionMachines(){}

    string getStatus() const {
        if (status_machine == Work)
            return "Work";
        else if (status_machine == Repair)
            return "Repair";
        return "Idle";
    }

    int getWork()  {return WorkTime;}
    int getRepair()  {return RepairTime;}


    void setWork( int Entered_Work){WorkTime = Entered_Work;}
    void setRepair( int Entered_Repair){RepairTime=Entered_Repair;}

    //void setStatus(const status entered_status){status_machine = entered_status;}
    void setStatus(const string entered_status)
    {
        if (entered_status == "Work")
            status_machine = Work;
        else if (entered_status == "Repair")
            status_machine = Repair;
        else if (entered_status == "Idle")
            status_machine = Idle;
    }


    void clean()
    {
        status_machine = Idle;
        WorkTime = 0;
        RepairTime = 0;
    }

    std::string Show()
    {
        string temp = "";
        temp+="\nСтатус машины: ";
        if (status_machine == Work)
            temp += "Работает";
        else if (status_machine == Repair)
            temp += "На починке";
        else temp += "Простой";

        temp+="\nВремя работы: " + to_string(WorkTime) + " минут";
        temp+="\nВремя ремонта: " + to_string(RepairTime) + " минут";
        return temp;
    }
    int getStatusNum()
    {
        if (status_machine == Work)
            return 1;
        else if (status_machine == Repair)
            return -1;
        return 0;
    }
};

#endif // CONSTRUCTIONMACHINES_H
