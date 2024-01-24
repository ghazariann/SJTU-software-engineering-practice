#ifndef MAP_H
#define MAP_H
#include "Grid.h"

#include <QGraphicsScene>
class Map {
public:
  Map(QGraphicsScene *scene, int gridLen, int cellSize);
  void initializeGrid();
  void shuffleColors(QList<int> &colorIndices);
  void populateScene();
  void eraseSquare(int x, int y);
  void createSquare(int x, int y, int colorIndex);
  bool isMoveAllowed(int x, int y);
  int getCellSize() const;
  bool checkWinCondition();
  void clearMap();
  QString serialize() const;
  void deserialize(const QString &s);
  int getSceneSize() const;
  int getMapSize() const;
  int getGridLen() const;
  void printMap() const;
  std::pair<QPoint, QPoint> isSolvable();
  void rearrangeGrids();
  Grid *getTouchedGrid(int x, int y) const;
  Grid* getGridAt(int x, int y);
    ~Map();

private:
  QGraphicsScene *scene;
  int cellSize;
  int remainingGrids;

  int gridLen;
  int sceneSize;
  int mapSize;
  Grid ***map;
  int specialityCounter = 1; // To keep track of the speciality type
  int offsetX;
  int offsetY;
};

#endif // MAP_H
