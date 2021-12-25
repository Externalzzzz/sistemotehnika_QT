#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constructionmachines.h"
#include "workers.h"
#include "math.h"
#include <random>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include "dialog.h"
#include <stdlib.h>
#include <ctime>
#include <QMessageBox>
vector <int> BullY;
vector <int> X;
vector <int> ExcY;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Расчет прибыли от работы машин");
    ui->pushButton_2->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int expanent(double times) // Экспоненциальное распределение, вводится время в часах, выводится в минутах
{
    int rnd = qrand() % 16 + 1;
    return (int)ceil(((1 - exp(-1 / times * rnd)) * times * 60));
}
void paint(vector <int> X, vector <int> BullY, vector <int> ExcY)
{
    Dialog diag;
    diag.showDialog(X, BullY, ExcY);
    diag.showFullScreen();
    diag.exec();
}
void MainWindow::on_pushButton_clicked()
{
    // out.setCodec("utf-8")
    //srand(time(NULL));
    //Переменные, считываемые с окна ввода
     double Exc_Repair_Both = ui->bothexc->value();
     double Exc_Repair_W6 = ui->w6exc->value();
     double Exc_Repair_W3 = ui->w3exc->value();
     double Bull_Repair_W6 = ui->w6bull->value();
     double Bull_Repair_Both = ui->bothbull->value();
     qDebug() << Bull_Repair_Both << "Мат ожидание ремонта буль оба";

     double math_EXP_BULLDOZER = ui->matbullwork->value();
     double math_EXP_excavator = ui->matexcwork->value();

     int DayRange = ui->spinBox_15->value();

     double stavkaExc = ui->spinBox_11->value();
     double stavkaBull = ui->spinBox_12->value();

     double stavkaProstoiExc = ui->spinBox_13->value();
     double stavkaProstoiBull = ui->spinBox_14->value();

     double stavkaWorker3 = ui->spinBox_8->value();
     double stavkaWorker6 = ui->spinBox_10->value();

    const int daydiag = ui->spinBox_18->value();

    int days =  ui->spinBox_16->value();
    if (daydiag > days || daydiag <= 0)
    {
        QMessageBox::warning(this, "Ошибка!",
                                      "Количество дней на графике должно быть больше нуля и больше, чем количество дней в модели!");
        return;
    }
    int nakladnaya = ui->spinBox_17->text().toInt();


    bool both = false;
    if (ui->radioButton_2->isChecked())
        both = true;
    else  if (ui->radioButton->isChecked())
        both = false;

    QString filename= "";
    if (both)
            filename= QFileDialog::getSaveFileName(this, "Сохранение результата",
                                                    "/home/result36worker", "Text files(*.txt)");
    else
        filename = QFileDialog::getSaveFileName(this, "Сохранение результата",
                                                 "/home/result6worker", "Text files(*.txt)");

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        return;

    QTextStream out(&file);

    BullY.clear();
    X.clear();
    ExcY.clear();

    //Переменные статистика машин за всю жизнь модели
    //Переменные статистика машин за всю жизнь модели
    int AllIdleTimeBUll = 0;
    int AllWorkTimeBULL = 0;
    int AllRepairTimeBULL = 0;
    int AllIdleTimeExcavator = 0;
    int AllWorkTimeExcavator = 0;
    int AllRepairTimeExcavator = 0;

    //Переменные статистики рабочих
    int DayWorkTimeW6 = 0;
    int DayWorkTimeW3 = 0;
    int DayWorkTimeBoth = 0;


    for (int day = 0; day < days; day++)
    {
        ConstructionMachines Bulldozer;
        ConstructionMachines Excavator;
        Workers worker3;
        Workers worker6;

        out <<trUtf8( "ДЕНЬ:" )<< day;
        out <<trUtf8( "\nНАЧАЛО ДНЯ");
        out <<trUtf8( "\n=========================================================================================================================");
        out <<trUtf8( "\nБульдозер");
        out << QString::fromStdString(Bulldozer.Show());
        out <<trUtf8(  "\nЭкскаватор");
        out <<QString::fromStdString( Excavator.Show());
        //out << "=========================================================================================================================";

        //Переменные статистики машин за день
        int DayIdleTimeBUll = 0;
        int DayWorkTimeBULL = 0;
        int DayRepairTimeBULL = 0;
        int DayIdleTimeExcavator = 0;
        int DayWorkTimeExcavator = 0;
        int DayRepairTimeExcavator = 0;

        Bulldozer.setWork(expanent(math_EXP_BULLDOZER));
        qDebug() << Bulldozer.getWork();
        Excavator.setWork(expanent(math_EXP_excavator));
        qDebug() << Excavator.getWork();
        for (int minute = 0; minute < DayRange * 60; minute++)
        {


            //Логика перехода состояний бульдозера
            if (Bulldozer.getStatus() == "Work")
            {
                if (Bulldozer.getWork() == minute)
                {
                    if (Excavator.getStatus() != "Repair")
                    {
                        Bulldozer.setStatus("Repair");
                        Bulldozer.setWork(0);
                        if (both)
                        {
                            qDebug() << "МИНУТА" << minute;
                            int tempexmp = expanent(Bull_Repair_Both);
                            qDebug() << "ЭКСПАНЕНТА" << tempexmp;
                            Bulldozer.setRepair(minute + expanent(Bull_Repair_Both));

                            qDebug() << "БУЛЬДОЗЕР ЧИНИТЬСЯ БУДЕТ:" << Bulldozer.getRepair() - minute;
                            worker6.setStatus("Work");
                            worker6.setWorkTime(Bulldozer.getRepair()-minute);
                            worker6.setType("Bulldozer");

                            worker3.setStatus("Work");
                            worker3.setWorkTime(Bulldozer.getRepair()-minute);
                            worker3.setType("Bulldozer");

                            DayWorkTimeBoth+=worker6.getWorkTime();
                            qDebug() << worker6.getWorkTime();
                        }

                        else
                        {
                            Bulldozer.setRepair(minute + expanent(Bull_Repair_W6));
                            worker6.setStatus("Work");
                            worker6.setWorkTime(Bulldozer.getRepair() - minute);
                            worker6.setType("Bulldozer");

                            DayWorkTimeW6+=worker6.getWorkTime();
                            qDebug() << worker6.getWorkTime();
                        }
                    }
                    else
                    {
                        Bulldozer.setStatus("Idle");
                        Bulldozer.setWork(0);
                    }
                }
                else
                    DayWorkTimeBULL++;

            }
            else if (Bulldozer.getStatus() == "Repair")
            {
                if (Bulldozer.getRepair() == minute)
                {
                    Bulldozer.setStatus("Work");
                    Bulldozer.setWork(minute + expanent(math_EXP_BULLDOZER));
                    Bulldozer.setRepair(0);
                    worker6.setStatus("Idle");
                    worker6.setType("none");
                    worker6.setWorkTime(0);

                    worker3.setStatus("Idle");
                    worker3.setType("none");
                    worker3.setWorkTime(0);
                }
                else
                    DayRepairTimeBULL++;
            }
            else if(Bulldozer.getStatus() == "Idle")
            {
                if (Excavator.getStatus() == "Work")
                {
                    Bulldozer.setStatus("Repair");
                    Bulldozer.setWork(0);
                    if (both)
                    {
                        Bulldozer.setRepair(minute + expanent(Bull_Repair_Both));

                        worker6.setStatus("Work");
                        worker6.setWorkTime(Bulldozer.getRepair()-minute);
                        worker6.setType("Bulldozer");

                        worker3.setStatus("Work");
                        worker3.setWorkTime(Bulldozer.getRepair()-minute);
                        worker3.setType("Bulldozer");

                        DayWorkTimeBoth+=worker6.getWorkTime();
                        qDebug() << worker6.getWorkTime();
                    }
                    else
                    {
                        Bulldozer.setRepair(minute + expanent(Bull_Repair_W6));

                        worker6.setStatus("Work");
                        worker6.setWorkTime(Bulldozer.getRepair()-minute);
                        worker6.setType("Bulldozer");

                        DayWorkTimeW6+= worker6.getWorkTime();
                        qDebug() << worker6.getWorkTime();
                    }
                }
                else
                    DayIdleTimeBUll++;
            }
            //Логика переключения состояний экскаватора
            if (Excavator.getStatus() == "Work")
            {
                if (Excavator.getWork() == minute)
                {
                    if (Bulldozer.getStatus() != "Repair")
                    {
                        Excavator.setStatus("Repair");
                        Excavator.setWork(0);
                        if (both)
                        {
                            Excavator.setRepair(minute + expanent(Exc_Repair_Both));

                            worker6.setStatus("Work");
                            worker6.setWorkTime(Excavator.getRepair()-minute);
                            worker6.setType("Excavator");

                            worker3.setStatus("Work");
                            worker3.setWorkTime(Excavator.getRepair() - minute);
                            worker3.setType("Excavator");

                            DayWorkTimeBoth+= worker6.getWorkTime();
                            qDebug() << worker6.getWorkTime();
                        }

                        else
                        {
                            Excavator.setRepair(minute + expanent(Exc_Repair_W6));

                            worker6.setStatus("Work");
                            worker6.setWorkTime(Excavator.getRepair() - minute);
                            worker6.setType("Excavator");

                            DayWorkTimeW6+= worker6.getWorkTime();
                            qDebug() << worker6.getWorkTime();
                        }
                    }
                    else
                    {
                        Excavator.setStatus("Idle");
                        Excavator.setWork(0);
                    }
                }
                else
                    DayWorkTimeExcavator++;

            }
                else if (Excavator.getStatus() == "Repair")
                {
                    if (Excavator.getRepair() == minute)
                    {
                        Excavator.setStatus("Work");
                        Excavator.setWork(minute + expanent(math_EXP_excavator));
                        Excavator.setRepair(0);
                        worker6.setStatus("Idle");
                        worker6.setType("none");
                        worker6.setWorkTime(0);

                        worker3.setStatus("Idle");
                        worker3.setType("none");
                        worker3.setWorkTime(0);
                    }
                    else
                        DayRepairTimeExcavator++;
                }
                else if(Excavator.getStatus() == "Idle")
                    {
                        if (Bulldozer.getStatus() == "Work")
                        {
                            Excavator.setStatus("Repair");
                            Excavator.setWork(0);
                            if (both)
                            {
                                Excavator.setRepair(minute + expanent(Exc_Repair_Both));

                                worker6.setStatus("Work");
                                worker6.setWorkTime(Excavator.getRepair() - minute);
                                worker6.setType("Excavator");

                                worker3.setStatus("Work");
                                worker3.setWorkTime(Excavator.getRepair() - minute );
                                worker3.setType("Excavator");
                                DayWorkTimeBoth+= worker6.getWorkTime();
                                qDebug() << worker6.getWorkTime();
                            }
                            else
                            {
                                Excavator.setRepair(minute + expanent(Exc_Repair_W6));

                                worker6.setStatus("Work");
                                worker6.setWorkTime(Excavator.getRepair() - minute);
                                worker6.setType("Excavator");
                                DayWorkTimeW6+= worker6.getWorkTime();
                                qDebug() << worker6.getWorkTime();

                            }
                        }
                        else
                            DayIdleTimeExcavator++;
                    }

            if (day < daydiag)
           {
                BullY.push_back(Bulldozer.getStatusNum());
                ExcY.push_back(Excavator.getStatusNum());
           }

//        qDebug() <<"Оба работали" << DayWorkTimeBoth;
//        qDebug() << "шестой" << DayWorkTimeW6;
        }
        out <<trUtf8( "\n\nКОНЕЦ РАБОЧЕГО ДНЯ");
        out <<trUtf8(" \n=========================================================================================================================");
        out <<trUtf8( "\nБульдозер");
        out << QString::fromStdString(Bulldozer.Show());
        out <<trUtf8(  "\nВремя работы бульдозера ")<< DayWorkTimeBULL
            << trUtf8( " минут. Время простоя бульдозера " )<< DayIdleTimeBUll
            << trUtf8(" минут. Время починки бульдозера ")
            << DayRepairTimeBULL << trUtf8( " минут.");
        out <<trUtf8( "\n=========================================================================================================================");
        out <<trUtf8(  "\nЭкскаватор");
        out << QString::fromStdString(Excavator.Show());
        out << trUtf8( "\nВремя работы экскаватора ") << DayWorkTimeExcavator
            << trUtf8( " минут. Время простоя экскаватора ") << DayIdleTimeExcavator
            << trUtf8( " минут. Время починки экскаватора ") << DayRepairTimeExcavator
            << trUtf8( " минут.");
        out << "\n=========================================================================================================================\n";

        AllIdleTimeBUll+= DayIdleTimeBUll;
        AllIdleTimeExcavator+= DayIdleTimeExcavator;
        AllRepairTimeBULL+= DayRepairTimeBULL;
        AllRepairTimeExcavator+= DayRepairTimeExcavator;
        AllWorkTimeBULL+= DayWorkTimeBULL;
        AllWorkTimeExcavator+= DayWorkTimeExcavator;

    }

    for (int i = 0; i < daydiag * 60 * DayRange; i++)
    {
        X.push_back(i);
    }

    AllIdleTimeBUll= round(AllIdleTimeBUll/60);
    AllIdleTimeExcavator= round (AllIdleTimeExcavator/60);
    AllRepairTimeBULL = round (AllRepairTimeBULL/60);
    AllRepairTimeExcavator = round (AllRepairTimeExcavator /60);
    AllWorkTimeBULL = round(AllWorkTimeBULL /60);
    AllWorkTimeExcavator = round(AllWorkTimeExcavator / 60);
    DayWorkTimeW6 = round (DayWorkTimeW6/60);
    DayWorkTimeBoth = round(DayWorkTimeBoth/60);
     double ProfitExc = AllWorkTimeExcavator * stavkaExc - (AllIdleTimeExcavator + AllRepairTimeExcavator ) * stavkaProstoiExc;
     double ProfitBull = AllWorkTimeBULL * stavkaBull - (AllIdleTimeBUll + AllRepairTimeBULL ) * stavkaProstoiBull;

     //double SalaryWorker3 = DayWorkTimeW3/60 * stavkaWorker3 + nakladnaya * DayWorkTimeW3/60;
     double SalaryWorker6 = DayWorkTimeW6 * stavkaWorker6 ;
     double SalaryBrigada = DayWorkTimeBoth * (nakladnaya); // возможно лучше сложить ставки рабочих

     double AllSallary =  SalaryWorker6 + SalaryBrigada;
     double AllProfit = ProfitBull + ProfitExc;
     double CleanProfit = AllProfit - AllSallary;

    out <<  trUtf8("\nВывод: ");
    out <<  trUtf8("\nСуммарные расходы на рабочих:") << (int)AllSallary <<  trUtf8(" рублей");
    out <<  trUtf8("\nОбщая прибыль машин составляет: ") << (int)(AllProfit) << trUtf8( " рублей");
    out <<  trUtf8("\nЧистая прибыль составляет: ") << (int)(CleanProfit) << trUtf8( " рублей");


    out <<trUtf8(  "\nБульдозер работал: " )<< (int)AllWorkTimeBULL <<  trUtf8(" часов");
    out <<trUtf8(  "\nЭксаватор работал: " )<< (int)AllWorkTimeExcavator << trUtf8( " часов");
    out <<trUtf8(  "\nБульдозер был на починке: " ) << (int)(AllRepairTimeBULL) << trUtf8( " часов");
    out <<trUtf8(  "\nЭксаватор был на починке: " ) << (int)(AllRepairTimeExcavator) << (((int)(AllRepairTimeExcavator)!=1)? trUtf8("часов"): trUtf8("час"));
    out <<trUtf8(  "\nБульдозер был в простое: "  ) << (int)AllIdleTimeBUll << trUtf8( " часов");
    out <<trUtf8(  "\nЭкскаватора был в простое: ") << (int)AllIdleTimeExcavator << trUtf8( " часов");
    //out.close();
   //
    ui->pushButton_2->setEnabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    paint(X, BullY, ExcY);
}

