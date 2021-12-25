
#include "QFont"\

#include "dialog.h"
#include "ui_dialog.h"
#include <QScrollBar>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    delete ui;
}



    void Dialog::showDialog(const std::vector <int> x, const std::vector <int> bully, const std::vector <int> ExcY)
    {
        QFont newfont("Courier",12,QFont::Bold);

        QLineSeries *series = new QLineSeries();
        series->setPen(QPen(QBrush(QColor(Qt::red)),1));

        for (std::vector<int>::size_type i = 0; i < x.size(); i++)
        {
            series->append(x[i], bully[i]);
        }

        QLineSeries *series2 = new QLineSeries();
        series2->setPen(QPen(QBrush(QColor(Qt::green)),1));

        for (std::vector<int>::size_type i = 0; i < x.size(); i++)
        {
            series2->append(x[i], ExcY[i]);
        }

        //    max = (y[i] > max)? y[i] : max;

        QChart *chart = new QChart();
        QChart *chart2 = new QChart();
        chart->legend()->hide();
        chart->setTitleFont(newfont);
        chart->setBackgroundBrush(QBrush(QColor(Qt::black)));
        chart->setTitle("График состояний Бульдозера");
        chart->setTitleBrush(QBrush(QColor(Qt::green)));
        chart->addSeries(series);


        chart2->legend()->hide();
        chart2->setTitleFont(newfont);
        chart2->setBackgroundBrush(QBrush(QColor(Qt::black)));
        chart2->setTitle("График состояний Экскаватора");
        chart2->setTitleBrush(QBrush(QColor(Qt::green)));
        chart2->addSeries(series2);


        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, (int)(x.size()));
        axisX->setTickCount(2);
        axisX->setLabelsColor(QColor(Qt::green));
        axisX->setLabelFormat("%.d");
        axisX->setGridLineColor(QColor(Qt::black));
        axisX->setTitleText(tr("Время (мин.)"));
        axisX->setTitleFont(newfont);
        axisX->setTitleBrush(QBrush(QColor(Qt::green)));

        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(-1, 1);
        axisY->setTickCount(3);
        axisY->setLabelFormat("%.d");
        axisY->setLabelsColor(QColor(Qt::green));
        axisY->setShadesVisible(false);
        axisY->setGridLineColor(QColor(Qt::black));
        axisY->setTitleFont(newfont);
        axisY->setTitleText(tr("Статусы"));
        axisY->setTitleBrush(QBrush(QColor(Qt::green)));


        QValueAxis *axisX2 = new QValueAxis;
        axisX2->setRange(0, (int)(x.size()));
        axisX2->setTickCount(2);
        axisX2->setLabelsColor(QColor(Qt::green));
        axisX2->setLabelFormat("%.d");
        axisX2->setGridLineColor(QColor(Qt::black));
        axisX2->setTitleText(tr("Время (мин.)"));
        axisX2->setTitleFont(newfont);
        axisX2->setTitleBrush(QBrush(QColor(Qt::green)));

        QValueAxis *axisY2 = new QValueAxis;
        axisY2->setRange(-1, 1);
        axisY2->setTickCount(3);
        axisY2->setLabelFormat("%.d");
        axisY2->setLabelsColor(QColor(Qt::green));
        axisY2->setShadesVisible(true);
        axisY2->setGridLineColor(QColor(Qt::black));
        axisY2->setTitleFont(newfont);
        axisY2->setTitleText(tr("Статусы"));
        axisY2->setTitleBrush(QBrush(QColor(Qt::green)));



        QChartView *chartView = new QChartView(chart);
        QChartView *chartView2 = new QChartView(chart2);


        chartView->chart()->setAxisX(axisX, series);
        chartView->chart()->setAxisY(axisY, series);
        chartView->setRubberBand(QChartView::HorizontalRubberBand);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->gridLayout->addWidget(chartView);
        chartView2->chart()->setAxisX(axisX2, series2);
        chartView2->chart()->setAxisY(axisY2, series2);
        chartView2->setRubberBand(QChartView::HorizontalRubberBand);
        chartView2->setRenderHint(QPainter::Antialiasing);
        ui->gridLayout->addWidget(chartView2);
        QScrollBar *scroll = new QScrollBar(Qt::Orientation::Horizontal);
        ui->gridLayout->addWidget(scroll);
        ui->gridLayout->maximumSize();

    }
