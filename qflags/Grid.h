#ifndef GRID_H
#define GRID_H

#include <QGraphicsRectItem>
#include <QColor>

class Grid : public QGraphicsRectItem {
public:
    Grid(int x, int y, int colorIndex, int speciality, int cellSize, int offsetX, int offsetY);
    void setSpecialBorder();
    QColor getColor() const;
    int x, y;
    int colorIndex;
    int speciality;
    void color();
};

#endif // GRID_H
