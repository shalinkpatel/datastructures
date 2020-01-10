#include <iostream>
#include <vector>

int main() {
  vector<vector<vector<int> > > pieces;
    vector<set<vector<vector<int> > > > symmetries(n);
    int sh;
    int maxsym = 0;
    int totalSize = 0;

    for (int i = 0; i < n; ++i) {
      string pc;
      cin >> pc;

      int x = 0, y = 0, minx = 0, miny = 0, maxx = 0, maxy = 0;
      stack<char> dir;

      // Finds bounding box size for piece
      for (int j = 0; j < pc.size(); ++j) {
        if (pc[j] > '9') {
          dir.push(pc[j]);
          if (pc[j] == 'N') --y;
          if (pc[j] == 'S') ++y;
          if (pc[j] == 'E') ++x;
          if (pc[j] == 'W') --x;
          minx = x<minx?x:minx;
          miny = y<miny?y:miny;
          maxx = x>maxx?x:maxx;
          maxy = y>maxy?y:maxy;
        } else {
          for (int k = 0; k < pc[j] - '0'; ++k) {
            if (dir.top() == 'N') ++y;
            if (dir.top() == 'S') --y;
            if (dir.top() == 'E') --x;
            if (dir.top() == 'W') ++x;
            dir.pop();
          }
        }
      }

      // Creates piece container
      pieces.push_back(vector<vector<int> >(maxx-minx+1, vector<int>(maxy-miny+1)));
      x = -minx;
      y = -miny;
      dir = stack<char>();

      // Loads piece
      for (int j = 0; j< pc.size(); ++j) {
        pieces[i][x][y] = 1;
        if (pc[j] > '9') {
          dir.push(pc[j]);
          if (pc[j] == 'N') --y;
          if (pc[j] == 'S') ++y;
          if (pc[j] == 'E') ++x;
          if (pc[j] == 'W') --x;
        } else {
          for (int k = 0; k < pc[j] - '0'; ++k) {
            if (dir.top() == 'N') ++y;
            if (dir.top() == 'S') --y;
            if (dir.top() == 'E') --x;
            if (dir.top() == 'W') ++x;
            dir.pop();
          }
        }
      }
      pieces[i][x][y] = 1;

      // Checks piece size
      totalSize += getPieceSize(pieces[i]);

      // Finds number of piece orientations
      symmetry_explore(pieces[i], symmetries[i]);
      if (symmetries[i].size() > maxsym) {
        maxsym = symmetries[i].size();
        sh = i;
      }
    }
    return 0;
}