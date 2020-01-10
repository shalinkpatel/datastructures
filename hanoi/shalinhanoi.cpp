#include <vector>
#include <iostream>
#include <math.h>
#include <limits>

using std::vector;
using std::swap;
using std::cout;
using std::endl;


typedef vector<int> VI;
typedef vector<long> VL;
vector<VL> n_hanoi;
vector<VI> k_hanoi;

//helper bc hanoi_init was getting messy
void pop_n_k(int n_twrs, int n_dsks){
    long prev = n_hanoi[n_twrs][n_dsks];
    for (int i = k_hanoi[n_twrs][n_dsks-1]; i < n_dsks; i++) {
        long n = 2*n_hanoi[n_twrs][i] + n_hanoi[n_twrs - 1][n_dsks - i];
        //n < n_hanoi[n_twrs][i] ? n = LONG_MAX : n; //Was an overflow check
      
        if (n < n_hanoi[n_twrs][n_dsks]) {
            n_hanoi[n_twrs][n_dsks] = n;
            k_hanoi[n_twrs][n_dsks] = i;
        }

        if(n >= prev) break;
        prev = n;
    }
}

void hanoi_init(){
    VL n(10001, LONG_MAX);
    VI k(10001, 0);
    for (int i = 0; i < 11; i++) {
        n_hanoi.push_back(n);
        k_hanoi.push_back(k);
    }

    for (int i = 1; i < 10001; i++) {
        k_hanoi[3][i] = i - 1;
    }

    for (int i = 0; i < 11; i++) {
        n_hanoi[i][1] = 1;
        n_hanoi[i][0] = 0;
        k_hanoi[i][1] = 1;
        k_hanoi[i][0] = 0;
    }

    long powr = 2;
    for (int i = 2; i < 63; ++i) {
        powr <<= 1;
        n_hanoi[3][i] = powr-1;
    }

    for (int i = 2; i < 10001; ++i) {
        for(int j =  4; j < 11; ++j){
            pop_n_k(j, i);
        }
    }
}

void hanoi(vector<VI>& moves, int n_twrs, int n_dsks, VI& aux) {
	if (n_dsks == 1) {
		VI move;
		move.push_back(aux[0]);
		move.push_back(aux[1]);
		moves.push_back(move);
	}

	else if(n_dsks > 1){
		int k = k_hanoi[n_twrs][n_dsks];

		int tmp = aux[aux.size() - 1];
		int second = aux[1];
		int old = aux[0];

		aux[aux.size() - 1] = second;
		aux[1] = tmp;

		hanoi(moves, n_twrs, k, aux);

		aux[1] = second;
		aux.pop_back();

		hanoi(moves, n_twrs - 1, n_dsks - k, aux);

		aux[0] = tmp;
		aux.push_back(old);

		hanoi(moves, n_twrs, k, aux);

		aux[0] = old;
		aux[1] = second;
		aux[aux.size() - 1] = tmp;
	}
}