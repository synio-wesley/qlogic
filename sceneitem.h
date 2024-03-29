#ifndef SCENEITEM_H
#define SCENEITEM_H

#include <QGraphicsSvgItem>

class QTimeLine;
class Line;
class QMenu;

class SceneItem : public QGraphicsSvgItem
{
    Q_OBJECT

public:
    enum ItemType {Switch, Oscillator,
                   Led,
                   AndGate, NandGate, OrGate, NorGate, NotGate,
                   Bubble};
    enum SignalType {Locked = 0x0, Sender = 0x1, Receiver = 0x2, SenderAndReceiver = 0x3, Invalid = 0x4};
    enum Sides {None = 0x0, Left = 0x1, Top = 0x2, Right = 0x4, Bottom = 0x8};
    enum {Type = UserType + 1};

    void initItem();
    virtual void initAfterCreation();
    int type() const {return Type;}
    ItemType itemType() const {return myType;}
    SignalType signalType();
    void showOverlayItem();
    void hideOverlayItem();
    bool checkCollision();
    void attachInWire(Line *wire);
    void attachOutWire(Line *wire);
    void lockOpacity(qreal opacity);
    void updateSignalsOnWires();
    bool outSignal() {return on;}
    virtual void processIncomingSignals() {}
    QList<SceneItem*> attachedDevices();
    int inputSides() {return myInputSides;}
    int outputSides() {return myOutputSides;}

    bool canConnectToInput();
    bool canConnectToOutput();

public slots:
    void deleteItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void setSvgs() {}
    void changeSvg(const QStringList &svgs);
    ItemType myType;
    QMenu *myContextMenu;
    SignalType mySignalType;
    QList<Line*> attachedInWires;
    bool on;
    int myInputSides, myOutputSides;
    int maxGhostOpacity;
    int maxIn;
    int maxOut;

private slots:
    void setItemOpacity(int opacity);
    void reverseState();

private:
    void moveWithWires(QPointF newPosition);
    int currentOpacity;
    QTimeLine *timeLine;
    QGraphicsRectItem *overlayItem;
    QPointF oldPosition;
    QList<Line*> attachedOutWires;
    bool ghost;
};

#endif // SCENEITEM_H
