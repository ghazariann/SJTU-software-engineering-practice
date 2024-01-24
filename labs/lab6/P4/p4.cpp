#include "solution.h"
#include <iostream>
#include <vector>

using namespace std;

void Solution::dfs(vector<vector<int>> &matrix, int remain, int used, int n,
                   int m, int &best) {
  int this_k_unavailable;
  int i, j;
  int x, y;
  if (used >= best)
    return;

  if (remain == 0) {
    best = min(best, used);
    return;
  }

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      // 找到一个空格子，尝试填入一个正方形
      if (matrix[i][j] == 0) {
        for (int k = min(n - i, m - j); k >= 1; k--) {
          this_k_unavailable = 0;
          x = i;
          y = j;

          for (int a = 0; a < k; a++)
            for (int b = 0; b < k; b++)
              if (matrix[x + a][y + b])
                this_k_unavailable = 1;

          if (this_k_unavailable)
            continue;
          for (int a = 0; a < k; a++)
            for (int b = 0; b < k; b++)
              matrix[x + a][y + b] = 1;

          remain -= k * k;
          used++;
          dfs(matrix, remain, used, n, m, best);
          used--;
          remain += k * k;

          for (int a = 0; a < k; a++)
            for (int b = 0; b < k; b++)
              matrix[x + a][y + b] = 0;
        }

        return;
      }
}

int Solution::tilingRectangle(int n, int m) {
  int best = n * m;

  vector<vector<int>> matrix(n, vector<int>(m, 0));

  dfs(matrix, n * m, 0, n, m, best);

  return best;
}