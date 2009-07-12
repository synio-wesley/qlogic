#ifndef LINE_H
#define LINE_H

#include <QGraphicsLineItem>

#include "sceneitem.h"
#include "bubbleitem.h"

class Line : public QGraphicsLineItem
{
public:
    Line(const QLineF &line, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    void activate();
    void setItems(SceneItem *item1, SceneItem *item2);
    SceneItem *sender() {return mySender;}
    SceneItem *receiver() {return myReceiver;}
    void setState(bool on);
    void setSides(SceneItem::Sides senderSide, SceneItem::Sides receiverSide);
    bool activeSignal() {return active;}

    static QList<SceneItem::Sides> shortestPossibleWire(SceneItem *source, SceneItem *target, BubbleItem::BubbleIcon icon);
    static SceneItem::SignalType validSignalTypesFromTo(SceneItem *from, SceneItem *to);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    SceneItem *mySender, *myReceiver;
    SceneItem::Sides senderSide, receiverSide;
    bool active;
};

#endif // LINE_H
