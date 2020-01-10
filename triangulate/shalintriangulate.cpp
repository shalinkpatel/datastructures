#include <vector>
#include <cmath> 
#include <climits>
#include <iomanip>
#include <iostream>
using std::vector;
using std::cout;
using std::cin; 


//Point in R2 because it makes everything prettier
struct point { 
    double x, y; 
    explicit point(double x, double y): x(x), y(y) {}
}; 

//Reducing Cluter 
typedef vector<point> VP;
typedef vector<vector<vector<double>>> VVVD;

//Euclidean Distance
double cost(point p1, point p2) {
    return std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y)); 
}  

//Outputs the Diagonals Used in Triangulation
void getTriangulation(int i, int j, VVVD &table){
    if((j-i) < 2) return;
    getTriangulation(i,table[i][j][1], table);
    if(j-i != table.size()-1) cout << i << " " << j << '\n';
    getTriangulation(table[i][j][1],j, table);
}

//Minimum Cost Triangulation Main Function
void mct(VP &points, int n) { 
    if (n < 3) return; 
    VVVD table(n, vector<vector<double>>(n, vector<double>(2, LONG_MAX))); 

    for (int jmp = 0; jmp < n; ++jmp) {           
        for (int i = 0, j = jmp; j < n; ++i, ++j) { 
            if (j < i+2){ 
                table[i][j][0] = 0.0; 
                table[i][j][1] = i;
            }
            else { 
                for (int k = i+1; k < j; ++k) { 
                    int w1,w2;
                    k-i==1?w1 = 0: w1 = 1;
                    j-k==1?w2 = 0: w2 = 1;
                    double val = table[i][k][0] + table[k][j][0] + w1*cost(points[i], points[k]) + w2*cost(points[k], points[j]); 
                    if (table[i][j][0] > val) {
                        table[i][j][0] = val;
                        table[i][j][1] = k;
                    }
                } 
            } 
        }
    }
    cout << table[0][n-1][0] << '\n';
    getTriangulation(0,n-1,table);
} 

//Driver Function a.k.a "./exec < infile > outfile"
int main() { 
    VP points;
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i){
        double x,y;
        cin >> x >> y;
        points.push_back(point(x,y));
    }
    mct(points, N);
    return 0; 
} 