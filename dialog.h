#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QList>
#include <QDebug>
#include <QVector>
#include <QtCharts>
#include <QValueAxis>

#include <QSplineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QtCharts>
#include <QLineSeries>
#include <ui_dialog.h>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog;}
QT_END_NAMESPACE

/*!
 * \brief The Diagram class - класс Диаграмма
 */
class Dialog : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief showDiagram - метод вывода диаграммы на экран
     */
    void showDialog(const std::vector <int> x, const std::vector <int> bully, const std::vector <int> ExcY);

    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;


};

#endif // DIALOG_H
