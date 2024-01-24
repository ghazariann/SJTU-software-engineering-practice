#include "Grid.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QDebug>
QMap<int, QColor> colorMap = {{0, Qt::red},         {1, Qt::green},
                              {2, Qt::blue},        {3, Qt::yellow},
                              {4, Qt::magenta},     {5, Qt::cyan},
                              {6, Qt::transparent}, {7, Qt::darkRed},
                              {8, Qt::darkGreen},   {9, Qt::darkBlue}};

Grid::Grid(int x, int y, int colorIndex, int speciality, int cellSize, int offsetX, int offsetY)
    : x(x), y(y), colorIndex(colorIndex), speciality(speciality) {
    setRect(x * cellSize + offsetX, y * cellSize + offsetY, cellSize, cellSize);

    color();
 }

void Grid::setSpecialBorder() {

     // Add a special border
     QPen pen;
     pen.setWidth(4);         // Set the width of the border
     pen.setColor(Qt::black); // Set the color of the border
     setPen(pen);

}
void Grid::color() {
    if (speciality > 0) {
        setSpecialBorder();
        switch (speciality) {
          case 1:
            setBrush(QColor(200, 200, 255)); // light blue
            break;
          case 2:
            setBrush(QColor(200, 255, 200)); // light green
            break;
          case 3:
            setBrush(QColor(255, 200, 200) ); // light red
            break;
        }
      }
    else
      setBrush(colorMap[colorIndex]);
}
QColor Grid::getColor() const { return this->brush().color(); }
