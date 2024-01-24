#include "Map.h"
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QGraphicsRectItem>
#include <QPair>
#include <QRandomGenerator>
#include <QSet>
#include <QTextStream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <random> // for std::default_random_engine and std::shuffle
#include <chrono> // for std::chrono::system_clock

const int EMPTY_IDX = 6;
const int SPACIAL_IDX = 5;

// const int NUM_COLORS = 10;
// const int NUM_CELLS_PER_COLOR = 10;

Map::Map(QGraphicsScene *scene, int gridLen, int cellSize)
    : scene(scene), cellSize(cellSize), gridLen(gridLen) {
  // TODO 1)n*m 2) odd number , coloring logic
  sceneSize = scene->width(); // or height, it's symmetric
  mapSize = gridLen * cellSize;
  remainingGrids = gridLen * gridLen;
  offsetX = (scene->width() - mapSize) / 2;
  offsetY = (scene->height() - mapSize) / 2;

  initializeGrid();
  populateScene();
}
void Map::initializeGrid() {
  map = new Grid **[gridLen];
  for (int i = 0; i < gridLen; ++i) {
    map[i] = new Grid *[gridLen];
    // Initialize to nullptr
    for (int j = 0; j < gridLen; ++j) {
      map[i][j] = nullptr;
    }
  }
}
void Map::createSquare(int x, int y, int colorIndex) {
  int speciality = 0;
  // Check for empty index
  if (colorIndex == -1 || colorIndex == EMPTY_IDX) {
    return;
  }
  // Check for speciality
  if (colorIndex == SPACIAL_IDX) {
    speciality = specialityCounter;
    specialityCounter = (specialityCounter % 3) + 1; // Cycle through 1, 2, 3
  }

  Grid *newGrid = new Grid(x, y, colorIndex, speciality, cellSize, offsetX, offsetY);
  map[y][x] = newGrid;
  scene->addItem(newGrid);
}
void Map::populateScene() {
  QList<int> allColorIndices;
  for (int i = 0; i < gridLen; ++i) {
    for (int j = 0; j < gridLen; ++j) {
      allColorIndices.append(i);
    }
  }

  shuffleColors(allColorIndices);

  int index = 0;
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      int colorIndex = allColorIndices[index];
      createSquare(x, y, colorIndex);
      index++;
    }
  }
}
void Map::shuffleColors(QList<int> &colorIndices) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(colorIndices.begin(), colorIndices.end(), std::default_random_engine(seed));
}
void Map::eraseSquare(int x, int y) {
  if (x >= 0 && x < gridLen && y >= 0 && y < gridLen) {
    Grid *gridToRemove = map[y][x];
    if (gridToRemove != nullptr) {
      scene->removeItem(gridToRemove); // Remove from QGraphicsScene
      delete gridToRemove;             // Delete the grid
      map[y][x] = nullptr;             // Set the map entry to nullptr
      remainingGrids--;
    }
  }
}

bool Map::isMoveAllowed(int x, int y) {
  // Check if the new x and y coordinates are inside the grid (map)
  if (x >= offsetX && x <= (offsetX + mapSize - cellSize) && y >= offsetY &&
      y <= (offsetY + mapSize - cellSize)) {

    int gridX = (x - offsetX) / cellSize;
    int gridY = (y - offsetY) / cellSize;

    // Allow movement only if the grid at the new coordinates is nullptr
    if (map[gridY][gridX] == nullptr) {
      return true;
    }

    return false;
  }

  // Check if the new x and y coordinates are outside the scene
  if (x < 0 || x >= sceneSize || y < 0 || y >= sceneSize) {
    return false;
  }

  return true;
}

Grid *Map::getTouchedGrid(int x, int y) const {
  if (x >= offsetX && x <= (offsetX + mapSize - cellSize) && y >= offsetY &&
      y <= (offsetY + mapSize - cellSize)) {

    int gridX = (x - offsetX) / cellSize;
    int gridY = (y - offsetY) / cellSize;
    return map[gridY][gridX];
  }

  return nullptr; // if the grid was not touched
}
Grid* Map::getGridAt(int x, int y) {
  if (x >= 0 && x < gridLen && y >= 0 && y < gridLen) {
    return map[y][x];
  }
  return nullptr;
}
std::pair<QPoint, QPoint> Map::isSolvable() {
  std::unordered_map<int, QPoint> colorToPoint;  // To keep track of the number of
                                            // each color in the outer layer
  std::queue<std::pair<int, int>> bfsQueue; // Queue for BFS
  std::vector<std::vector<bool>> visited(
      gridLen, std::vector<bool>(gridLen, false)); // Visited array

  // Initialize BFS with all nullptr grids
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      if (map[y][x] == nullptr) {
        bfsQueue.push({x, y});
        visited[y][x] = true;
      }
    }
  }

  // Directions for BFS (up, down, left, right)
  int dx[] = {0, 0, -1, 1};
  int dy[] = {-1, 1, 0, 0};

  while (!bfsQueue.empty()) {
    int x = bfsQueue.front().first;
    int y = bfsQueue.front().second;

    bfsQueue.pop();

    for (int i = 0; i < 4; ++i) { // Check all 4 neighbors
      int newX = x + dx[i];
      int newY = y + dy[i];

      if (newX >= 0 && newX < gridLen && newY >= 0 && newY < gridLen &&
          !visited[newY][newX]) {
        visited[newY][newX] = true; // Mark as visited
        if ((map[newY][newX] != nullptr)) {
            int colorIdx = map[newY][newX]->colorIndex;

            if (colorToPoint.find(colorIdx) != colorToPoint.end()) {
                        return std::make_pair(QPoint(newX, newY), colorToPoint[colorIdx]);
                      }
                      colorToPoint[colorIdx] = QPoint(newX, newY);
        }
        bfsQueue.push({newX, newY});
      }
    }
  }

  return std::make_pair(QPoint(-1, -1), QPoint(-1, -1));
}
int Map::getCellSize() const { return cellSize; }
int Map::getGridLen() const{return gridLen;}
int Map::getSceneSize() const { return sceneSize; }
int Map::getMapSize() const { return mapSize; }
void Map::printMap() const {
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      if (map[y][x] == nullptr)
        qDebug() << -1 << " ";
      else
        qDebug() << map[y][x]->colorIndex << " ";
    }
    qDebug() << '\n';
  }
}
void Map::clearMap() {
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      if (map[y][x] != nullptr) {
        scene->removeItem(map[y][x]); // Remove from QGraphicsScene
        delete map[y][x];             // Delete the grid
        map[y][x] = nullptr;          // Set the map entry to nullptr
      }
    }
  }
}
Map::~Map() {
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      delete map[y][x];
    }
    delete[] map[y];
  }
  delete[] map;
}
bool Map::checkWinCondition() { return remainingGrids == 0; }
QString Map::serialize() const {
  QString s;
  QTextStream out(&s);
  for (int y = 0; y < gridLen; ++y) {
    for (int x = 0; x < gridLen; ++x) {
      if (map[y][x] == nullptr) {
        out << "-1 "; // Use -1 to indicate nullptr
      } else {
        out << map[y][x]->colorIndex << " ";
      }
    }
    out << "\n";
  }
  return s;
}
void Map::deserialize(const QString &serializedMap) {
  clearMap(); // Clear the existing map

  QStringList lines = serializedMap.split("\n", Qt::SkipEmptyParts);
  int y = 0;

  for (const QString &line : lines) {
    QStringList values = line.split(" ", Qt::SkipEmptyParts);
    int x = 0;

    for (const QString &value : values) {
      int colorIndex = value.toInt();

      createSquare(x, y, colorIndex);
      ++x;
    }
    ++y;
  }
}
void Map::rearrangeGrids() {
    QList<int> colorIndexes;

    // Collect all color indexes into a list
    for (int y = 0; y < gridLen; ++y) {
        for (int x = 0; x < gridLen; ++x) {
            if (map[y][x] != nullptr && map[y][x]->colorIndex != SPACIAL_IDX) {
                colorIndexes.append(map[y][x]->colorIndex);
            }
        }
    }

    // Shuffle the color indexes
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(colorIndexes.begin(), colorIndexes.end(), std::default_random_engine(seed));

    // Update the color indexes and colors of the existing Grid objects
    int index = 0;
    for (int y = 0; y < gridLen; ++y) {
        for (int x = 0; x < gridLen; ++x) {
            if (map[y][x] != nullptr && map[y][x]->colorIndex != SPACIAL_IDX) {
                map[y][x]->colorIndex = colorIndexes[index++];
                map[y][x]->color();  // Update the color in the UI
            }
        }
    }
}
