#include <fstream>
using namespace std;
int main() {
  clock_t start;

  ifstream in ("in.txt");
  ifstream out ("out.txt");

  string intest, outtest;
  in >> intest;
  if (intest != "intest"){
    cout << "unable to read from in.txt\n";
    return 3735928559;
  }
  out >> outtest;
  if (outtest != "outtest"){
    cout << "unable to read from out.txt\n";
    return 3735928559;
  }

  start = std::clock();
  cout << "hanoi init... ";
  hanoi_init();
  cout << (std::clock() - start) / (double) CLOCKS_PER_SEC << " seconds (mine took 0.491 with no -O)\n";

  int n, k;
  in >> n >> k;
  for (int i = 0; i < n; i++) {
    int a, b;
    long long ans;
    in >> a >> b;
    out >> ans;
    if (n_hanoi.size() <= a || n_hanoi[a].size() <= b) {
      cout << "\nyour code can't handle " << a << " pillars and " << b << " disks\n";
      return 3735928559;
    }
    if (n_hanoi[a][b] != ans) {
      cout << "\nnumber of moves to do " << a << " pillars and " << b << " disks is " << ans << ", but you gave " << n_hanoi[a][b] << "\n";
      return 3735928559;
    }
  }

  start = std::clock();
  cout << "hanoi func... ";

  for (int i = 0; i < k; i++) {
    int a, b;
    long long x;
    in >> a >> b;
    out >> x;

    if (n_hanoi.size() <= a || n_hanoi[a].size() <= b) {
      cout << "\nyour code can't handle " << a << " pillars and " << b << " disks\n";
      return 3735928559;
    }
    if (n_hanoi[a][b] != x) {
      cout << "\nnumber of moves to do " << a << " pillars and " << b << " disks is " << x << ", but you gave " << n_hanoi[a][b] << "\n";
      return 3735928559;
    }


    vector<VI> v;
    VI aux(a);
    for (int j = 0; j < aux.size(); j++)
      aux[j] = j;
    hanoi(v, a, b, aux);
    vector<vector<int> > p(a);
    for (int j=0;j<b;j++)
      p[0].push_back(b-j-1);
    for (int j = 0; j < v.size(); j++) {
      int f = v[j][0], t = v[j][1];
      if (!p[f].size() || p[t].size() && p[f].back()>p[t].back()){
        cout << "\nright number of moves but moves are wrong for " << a << " pillars and " << b << " disks\n";
        cout << "tried to make invalid move "<<f<<" ==> "<<t<<" on move number "<<j<<" ("<<p[f].size()<<" disks on pillar "<<f<<" and "<<p[t].size()<<" disks on pillar "<<t<<")\n";
        return 3735928559;
      }

      p[t].push_back(p[f].back());
      p[f].resize(p[f].size()-1);
    }

    if (p[0].size() || p[1].size()!=b){
      cout << "\nright number of moves but moves are wrong for " << a << " pillars and " << b << " disks\n";
      cout << "not all disks moved (" << p[0].size() << " on the first pillar and " << p[1].size() << " on the second)\n";
      return 3735928559;
    }
  }
  cout << (std::clock() - start) / (double) CLOCKS_PER_SEC << " seconds (mine took 0.156 with no -O)\n";

  cout << "\n\nall clear :D !!!\n";

  cout << string(18, ' ') << string(1, 'x') <<"\n"; cout << string(17, ' ') << string(3, 'x') <<"\n"; cout << string(16, ' ') << string(5, 'x') <<"\n"; cout << string(15, ' ') << string(7, 'x') <<"\n"; cout << string(15, ' ') << string(7, 'x') <<"\n"; cout << string(13, ' ') << string(11, 'x') <<"\n"; cout << string(9, ' ') << string(20, 'x') << string(10, ' ') << string(1, 'H') << string(1, 'A') << string(2, 'P') << string(1, 'Y') <<"\n"; cout << string(12, ' ') << string(6, '/') << string(6, '\\') << string(13, ' ') << string(1, 'H') << string(1, 'A') << string(2, 'L') << string(1, 'O') << string(1, 'W') << string(2, 'E') << string(1, 'N') <<"\n"; cout << string(11, ' ') << string(3, '/') << string(2, ' ') << string(1, 'O') << string(3, ' ') << string(1, 'O') << string(2, ' ') << string(2, '\\') << string(14, ' ') << string(1, 'D') << string(1, 'U') << string(1, 'D') << string(1, 'E') <<"\n"; cout << string(11, ' ') << string(3, '/') << string(4, ' ') << string(1, 'U') << string(4, ' ') << string(3, '\\') <<"\n"; cout << string(11, ' ') << string(2, '/') << string(3, ' ') << string(1, '\\') << string(3, '_') << string(1, '/') << string(3, ' ') << string(2, '\\') << string(9, ' ') << string(1, '/') << string(1, '\\') << string(7, ' ') << string(1, '.') <<"\n"; cout << string(14, ' ') << string(1, 'a') << string(7, ' ') << string(1, 'a') << string(12, ' ') << string(1, '\\') << string(2, ' ') << string(1, '\\') << string(1, ' ') << string(2, '_') << string(1, ' ') << string(1, '/') << string(1, '|') <<"\n"; cout << string(12, ' ') << string(5, 'a') << string(3, ' ') << string(5, 'a') << string(12, ' ') << string(1, 'o') << string(3, ' ') << string(1, 'o') <<"\n"; cout << string(9, ' ') << string(19, 'a') << string(7, ' ') << string(3, ':') << string(1, ' ') << string(1, '@') << string(1, ' ') << string(3, ':') <<"\n"; cout << string(8, ' ') << string(7, 'a') << string(2, ' ') << string(4, 'a') << string(3, ' ') << string(6, 'a') << string(7, ' ') << string(1, '\\') << string(1, '/') << string(1, ' ') << string(1, '\\') << string(1, '/') << string(4, ' ') << string(1, '\\') << string(5, ' ') << string(1, 'M') << string(2, 'e') << string(1, '-') << string(1, ' ') << string(1, 'e') << string(2, 'o') << string(1, 'W') << string(1, ' ') << string(1, '!') <<"\n"; cout << string(7, ' ') << string(5, 'a') << string(15, ' ') << string(4, 'a') << string(9, ' ') << string(1, '\\') << string(4, ' ') << string(3, '\\') <<"\n"; cout << string(6, ' ') << string(5, 'a') << string(2, ' ') << string(5, 'a') << string(1, ' ') << string(7, 'a') << string(2, ' ') << string(3, 'a') << string(10, ' ') << string(1, '\\') << string(3, ' ') << string(2, '#') << string(2, ' ') << string(1, '\\') <<"\n"; cout << "\n"; cout << string(70, '#') <<"\n"; cout << "\n"; cout << string(1, '#') << string(2, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(3, ' ') << string(4, '#') << string(1, ' ') << string(4, '#') << string(1, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') <<"\n"; cout << string(4, '#') << string(2, ' ') << string(3, '#') << string(2, ' ') << string(1, '#') << string(1, ' ') << string(2, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(2, '#') << string(2, ' ') << string(3, '#') <<"\n"; cout << string(1, '#') << string(2, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(4, ' ') << string(1, '#') << string(6, ' ') << string(1, '#') <<"\n"; cout << "\n"; cout << string(7, ' ') << string(1, '#') << string(2, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(4, ' ') << string(2, '#') << string(2, ' ') << string(1, '#') << string(5, ' ') << string(1, '#') << string(1, ' ') << string(4, '#') << string(1, ' ') << string(4, '#') << string(1, ' ') << string(1, '#') << string(2, ' ') << string(2, '#') <<"\n"; cout << string(7, ' ') << string(4, '#') << string(2, ' ') << string(3, '#') << string(2, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(2, ' ') << string(1, '#') << string(2, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(2, ' ') << string(1, '#') << string(2, '-') << string(2, ' ') << string(1, '#') << string(2, '-') << string(2, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') <<"\n"; cout << string(7, ' ') << string(1, '#') << string(2, ' ') << string(1, '#') << string(1, ' ') << string(1, '#') << string(3, ' ') << string(1, '#') << string(1, ' ') << string(3, '#') << string(1, ' ') << string(3, '#') << string(2, ' ') << string(2, '#') << string(4, ' ') << string(3, '#') << string(3, ' ') << string(4, '#') << string(1, ' ') << string(4, '#') << string(1, ' ') << string(2, '#') << string(2, ' ') << string(1, '#') <<"\n"; cout << "\n"; cout << string(71, '#') <<"\n";

  in.close();
  out.close();
  return 0;
}
