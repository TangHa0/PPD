#include "pathplanningdemonstrator.h"
#include "ui_pathplanningdemonstrator.h"

#include <QDebug>
#include <QFileDialog>
#include <QtXml>
#include <QFile>

#include "dijkstrapathplanner.h"

PathPlanningDemonstrator::PathPlanningDemonstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PathPlanningDemonstrator)
{
    ui->setupUi(this);

    map_ = new Map;
    ui->graphics_view->setAcceptDrops(true);
    ui->graphics_view->setScene(map_);

    map_->setPathPlanner(new DijkstraPathPlanner);
}

PathPlanningDemonstrator::~PathPlanningDemonstrator()
{
    delete ui;
}

void PathPlanningDemonstrator::on_actionLoad_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Image", ".", "Map files (*.map)");
    if (filename.isEmpty())
    {
        qWarning("No file chosen");
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "Cannot open file:" << filename;
        return;
    }

    QTextStream stream(&file);

    QPoint source, terminal;
    stream >> source.rx() >> source.ry();
    map_->addSource(source);
    stream >> terminal.rx() >> terminal.ry();
    map_->addTerminal(terminal);

    int ostacle_num;
    stream >> ostacle_num;
    for (int i = 0; i < ostacle_num; ++i)
    {
        int vertex_num;
        stream >> vertex_num;
        QPolygonF polygon(vertex_num);
        for (int v = 0; v < vertex_num; v++)
        {
            stream >> polygon[v].rx() >> polygon[v].ry();
        }
        map_->addOstacle(polygon);
    }
}

void PathPlanningDemonstrator::on_pushButton_clicked()
{
    map_->plan();
}
