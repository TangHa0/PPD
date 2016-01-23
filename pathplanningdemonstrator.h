#ifndef PATHPLANNINGDEMONSTRATOR_H
#define PATHPLANNINGDEMONSTRATOR_H

#include <QMainWindow>

#include "map.h"

namespace Ui {
    class PathPlanningDemonstrator;
}

class PathPlanningDemonstrator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PathPlanningDemonstrator(QWidget *parent = 0);
    ~PathPlanningDemonstrator();

private slots:
    void on_actionLoad_triggered();

    void on_pushButton_clicked();

private:
    Ui::PathPlanningDemonstrator *ui;

    Map *map_;
};

#endif // PATHPLANNINGDEMONSTRATOR_H
