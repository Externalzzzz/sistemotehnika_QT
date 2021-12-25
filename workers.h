#ifndef WORKERS_H
#define WORKERS_H
#include<string>

class Workers
{
public:
    enum status {
        Work = 1,
        Idle = 0
    };
    enum machine{
        Excavator,
        Bulldozer,
        none = 0
    };

private:
    int WorkTime;
    status Worker_status;
    machine Machine_type;
public:
    Workers():WorkTime(0), Worker_status(Idle), Machine_type(none) {}
    ~Workers() {}

    int getWorkTime(){return WorkTime;}
    std::string GetType() const
    {
        if (Machine_type == Excavator)
            return "Excavator";
        else if (Machine_type == Bulldozer)
            return "Bulldozer";
        return "None";
    }
    std::string GetStatus() const
    {
        if (Worker_status ==  Work)
            return "Work";
        return "Idle";
    }


    void setWorkTime( int temp_work){WorkTime  = temp_work;}
    void setType(const std::string temp_type)
    {
        if (temp_type == "Excavator")
            Machine_type = Excavator;
        else if (temp_type == "Bulldozer")
            Machine_type = Bulldozer;

    }

    void setStatus(const std::string temp_status)
    {
        if (temp_status == "Work")
            Worker_status = Work;
        else if (temp_status == "Idle")
            Worker_status = Idle;
    }

};

#endif // WORKERS_H
