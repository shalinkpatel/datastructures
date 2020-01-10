#include <vector>
#include <iostream>
#include <mach/mach_time.h>

using namespace std;

typedef unsigned long long ULL;
typedef vector<int> VI;

ULL qm[417][417] = {};
ULL q[417] = {};

double time() {
  return 1E-9 * mach_absolute_time();
}

ULL part_q(int n);

ULL part_qk(int n, int m) {
  if (n == 0 || n == 1) return 1;
  if (q[n] == 0) part_q(n);
  if (m >= n) return q[n];
  ULL t = 0;
  for (int i = 1; i <= m; i++) t += qm[n][i];
  return t;
}

// return how many partitions n has
ULL part_q(int n) {
  if (n == 0 || n == 1) return 1;
  if (q[n] != 0) return q[n];
  
  ULL t = 0;
  for (int i = 1; i <= n; i++) {
    qm[n][i] = part_qk(n - i, i);
    //    printf("qm[%d][%d] = %llu\n", n, i, qm[n][i]);
    t += qm[n][i];
  }
  q[n] = t;
  return t;
}

VI part_km(int n, int m, ULL k) {
  //  printf("part_km(%d,%d,%llu)\n", n, m, k);
  VI r;
  if (n == 0) return r;
  if (n == 1) {
    r.push_back(1);
    return r;
  }
  ULL c = 0;
  int i = m;
  while (c + qm[n][i] <= k) {
    c += qm[n][i];
    i--;
  }
  //  cout << "i " << i << "\n";
  //  cout << "c " << c << "\n";
  r.push_back(i);
  VI s = part_km(n - i, i, k - c);
  for (int i = 0; i < s.size(); i++) r.push_back(s[i]);
  return r;  
}

// return kth partition of n
VI part_k(int n, ULL k) {
  part_q(n);
  return part_km(n, n, k);
}

// p - vector
// i - index
// m - max
// s - sum
// r - rest
ULL part_im(const VI& p, int i, int m, int s, int r) {
  //  printf("[%d][%d][%llu][%llu]\n", i, m, s, r);
  if (i == p.size()) return 0;
  if (r == 0) return 0;
  ULL t = 0;
  int j = m;
  while (j > p[i]) {
    t += qm[r][j];
    j--;
  }
  t += part_im(p, i + 1, p[i], s + p[i], r - p[i]);
  return t;
}

// return index of part p (guaranteed p is valid part)
ULL part_i(const VI& p) {
  int s = 0;
  for (int i = 0; i < p.size(); i++) s += p[i];
  part_q(s);
  return part_im(p, 0, s, 0, s);
}

int main() {
  VI ans = part_k(416, 39);
    for(int i = 0; i < ans.size(); ++i){
        cout << ans[i] << " ";
    }
    cout << endl;
    cout << part_i(ans) << endl;
    return 0;
}
