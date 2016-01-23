#include "map.h"

#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

#include "config.h"

Map::Map(QObject *parent) :
    QGraphicsScene(parent), source_(NULL), terminal_(NULL)
{
//    this->installEventFilter(this);
    connect(this, SIGNAL(changed(const QList<QRectF> &) ), this, SLOT(changed( const QList<QRectF> &)));
}

void Map::addSource(QPointF _source)
{
    if (source_)
    {
        qCritical("You cannot add source twice");
        return;
    }

//    source_ = new Vertex(_source.x(), _source.y(), VERTEX_RADIUS, VERTEX_RADIUS, QColor("red"));
//    this->addItem(source_);
    source_ = this->addEllipse(0, 0, VERTEX_RADIUS, VERTEX_RADIUS, QPen(), QBrush(QColor("red"), Qt::SolidPattern));
    source_->setPos(_source.x(), _source.y());
    source_->setFlags(QGraphicsPolygonItem::ItemIsMovable);
}

void Map::addTerminal(QPointF _terminal)
{
    if (terminal_)
    {
        qCritical("You cannot add terminal twice");
        return;
    }

//    terminal_ = new Vertex(_terminal.x(), _terminal.y(), VERTEX_RADIUS, VERTEX_RADIUS, QColor("blue"));
//    this->addItem(terminal_);
    terminal_ = this->addEllipse(0, 0, VERTEX_RADIUS, VERTEX_RADIUS, QPen(), QBrush(QColor("blue"), Qt::SolidPattern));
    terminal_->setPos(_terminal.x(), _terminal.y());
    terminal_->setFlags(QGraphicsPolygonItem::ItemIsMovable);
}

void Map::addOstacle(QPolygonF _polygon)
{
//    Obstacle *obstacle = new Obstacle(_polygon);
//    this->addItem(obstacle);
    QGraphicsPolygonItem * obstacle = this->addPolygon(_polygon, QPen(), QBrush(Qt::SolidPattern));
    obstacle->setFlags(QGraphicsPolygonItem::ItemIsMovable);
//    this->installEventFilter(obstacle);
//    obstacle->installSceneEventFilter(this);
    obstacles_.push_back(obstacle);
}

void Map::plan()
{
    qDebug() << "Start to plan";

    QPointF source(source_->scenePos());
    QPointF terminal(terminal_->scenePos());

    std::vector<QPolygonF> obstacles(obstacles_.size());
    for (uint i = 0; i < obstacles_.size(); ++i)
    {
        QPolygonF polygon = obstacles_[i]->polygon();
        for (int j = 0; j < polygon.size(); ++j)
            obstacles[i].push_back(obstacles_[i]->mapToScene(polygon[j]));
    }

    std::vector<QPointF> path;
    if (path_planner_->plan(source, terminal, obstacles, this, path))
    {
#if 0
        path.push_back(QPointF(0, 0));
        path.push_back(QPointF(100, 100));
        path.push_back(QPointF(200, 300));
#endif
        if (path.size() == 0)
        {
            qCritical("Empty path");
            return;
        }

        QPainterPath _path;
        _path.moveTo(path[0]);
        for (uint i = 1; i < path.size(); ++i)
        {
            _path.lineTo(path[i]);
        }

        if (path_)
        {
            this->removeItem(path_);
        }
        path_ = this->addPath(_path, QPen(QColor("green")));
    }
    else
        qCritical() << "Failed to plan";
}

void Map::setPathPlanner(PathPlanner *planner)
{
    this->path_planner_ = planner;
}

void Map::clear()
{
    qDebug() << "Clear the map";
}

void Map::changed(const QList<QRectF> &)
{
    qDebug() << "scene changed";
    clear();
}

//bool Map::eventFilter(QObject *watched, QEvent *event)
//{
//    if (event->type() == QEvent::MouseMove)
//    {
//        bool object_moved = false;
//        if (dynamic_cast<QGraphicsEllipseItem *>(watched) == source_)
//        {
//            object_moved = true;
//        }
//        else if (dynamic_cast<QGraphicsEllipseItem *>(watched) == terminal_)
//        {
//            object_moved = true;
//        }
//        else
//        {
//            for (uint i = 0; i < obstacles_.size(); ++i)
//            {
//                if (dynamic_cast<QGraphicsPolygonItem *>(watched) == obstacles_[i])
//                {
//                    object_moved = true;
//                    break;
//                }
//            }
//        }

//        if (object_moved)
//        {
//            qDebug() << "Object moved";
//        }
//    }

//    return QGraphicsScene::eventFilter(watched, event);
//}
