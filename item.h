#ifndef ITEM_H
#define ITEM_H

#include <QtWidgets/QGraphicsPixmapItem>
#include <string>
class Item : public QGraphicsPixmapItem
{
public:
    Item(const std::string& path, int row, int column, QGraphicsRectItem* root);

    // getter
    std::string getPath() const;
    int getRow() const;
    int getColumn() const;
    // setter
    void setRow(int row);
    void setColumn(int column);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    // 각각 마우스를 눌렀을떄 좌표와 땠을때 좌표를 불러온다.
private:
    std::string _path;
    int _row;
    int _column;
    QPointF _pressPos;

};

#endif // ITEM_H
