#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include<vector>
#include<iostream>
#include<cmath>
#include<map>

using namespace std;

using std::vector;
using std::pow;
using std::cout;
using std::endl;
using std::swap;

//precomputed constants
const int pws[] = {1, 13, 169, 2197, 28561, 371293};
const int cards[] =  {65537,65538,65540,65544,65552,65568,65600,65664,65792,66048,66560,67584,69632,32769,32770,32772,32776,32784,32800,32832,32896,33024,33280,33792,34816,36864,16385,16386,16388,16392,16400,16416,16448,16512,16640,16896,17408,18432,20480,8193,8194,8196,8200,8208,8224,8256,8320,8448,8704,9216,10240,12288};
const int translate[] = {0,67108864,134217728,201326592,268435456,335544320,402653184,469762048, 536870912};

//return the hand
vector<int> unhand(int c){
	vector<int> res;
	for (int i = 0; i < 5; i++) {
    	res.push_back(c % 52);
    	c /= 52;
  	}
	return res;
}

//creates value for the hand as a 30 bit number [4 - placement, 13 - important, 13 - lexographic]
//use XOR and OR to reveal pertinant things from the data
int val(int z) {
	vector<int> hand = unhand(z); 
	int eval = 0;
	int a = cards[13 * (hand[0] % 4) + hand[0]/4];
	int b = cards[13 * (hand[1] % 4) + hand[1]/4];
	int c = cards[13 * (hand[2] % 4) + hand[2]/4];
	int d = cards[13 * (hand[3] % 4) + hand[3]/4];
	int e = cards[13 * (hand[4] % 4) + hand[4]/4];
	bool strt;
	int OR = (a | b | c | d | e) & 8191;
	if(OR == 4111) strt = true;
	else{
		strt = ((OR >> __builtin_ctz(OR)) == 31);
	}
	int AND = (a & b & c & d & e);
	bool flush = AND;
	if(strt){
		if(OR == 4111) OR = 15;
		if(flush){
			eval += translate[8];
			eval += OR;
			return eval;
		}
		else{
			eval += translate[4];
			eval += OR;
			return eval;
		}
	}
	else if(flush){
		eval += translate[5];
		eval += OR;
		return eval;
	}
	int XOR = (a ^ b ^ c ^ d ^ e) & 8191;
	int x = __builtin_popcount(OR);
	int y = __builtin_popcount(XOR);
	bool two = false, dtwo = false, three = false, full = false, four = false;
	two = (x+y == 7);
	dtwo = (x+y == 4);
	three = (x+y == 6);
	if(x+y == 3){
		vector<int> values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
		for (int i = 0; i < 5; i++) values[hand[i] / 4]++;
		for (int i = 12; i >= 0; i--){
			if (values[i] == 4) four = true;
		} 
		if(!four) full = true;
	}

	if(two){
		eval += translate[1];
		eval += ((OR ^ XOR) << 13);
		eval += XOR;
		return eval;
	}
	else if(dtwo){
		eval += translate[2];
		eval += ((OR ^ XOR) << 13);
		eval += XOR;
		return eval;
	}
	else if(three){
		eval += translate[3];
		vector<int> values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
		for (int i = 0; i < 5; i++) values[hand[i] / 4]++;
		int boop;
		for (int i = 12; i >= 0; i--) if (values[i] == 3) boop = i;
		int loc = pow(2,boop);
		int tres = loc & OR;
		eval += (tres << 13);
		eval += (loc^OR);
		return eval;
	}
	else if(full){
		eval += translate[6];
		eval += (OR ^ XOR);
		eval += (XOR << 13);
		return eval;
	}
	else if(four){
		eval += translate[7];
		eval += ((OR ^ XOR) << 13);
		eval += (XOR);
		return eval;
	}
	else{
		eval += translate[0];
		eval += OR;
		return eval;
	}
}

//insertion sort
void is(vector<int>& ref, vector<int>& sort, int low, int n){
	for(int i = low + 1; i < low+n+1; ++i){
		int val1 = sort[i];
		int val2 = ref[i];

		int j = i;
		while(j > low && sort[j-1] > val1){
			sort[j] = sort[j-1];
			ref[j] = ref[j-1];
			j--;
		}
		sort[j] = val1;
		ref[j] = val2;
	}
}

//partition function takes median of low high and mid for pivot
int partition(vector<int>& ref, vector<int>& sort, int low, int high){
	int pivot;
	int center = (low+high)/2;
	if(sort[center] - sort[low] > 0){
		if(sort[high] - sort[center] > 0){
			pivot = sort[center];
			swap(sort[center], sort[high]);
			swap(ref[center], ref[high]);
		}
		else{
			pivot = sort[high];
		}
	}
	else{
		if(sort[high] - sort[low] > 0){
			pivot = sort[low];
			swap(sort[low], sort[high]);
			swap(ref[low], ref[high]);
		}
		else{
			pivot = sort[high];
		}
	}

	int idx = low-1;
	for(int i = low; i < high; ++i){
		if(sort[i] <= pivot){
			idx++;
			swap(sort[i], sort[idx]);
			swap(ref[i], ref[idx]);
		}
	}

	swap(sort[idx+1], sort[high]);
	swap(ref[idx+1], ref[high]);

	return idx+1;
}

//quicksort driver /w is used if size < 15
void qs(vector<int>& ref, vector<int>& sort, int low, int high) 
{ 
    while(low < high){
		if(high - low < 15){
			is(ref, sort, low, high-low);
			break;
		}

		else{
			int pivot = partition(ref, sort, low, high);
			if(pivot - low < high - pivot){
				qs(ref, sort, low, pivot - 1);
				low = pivot + 1;
			}
			else{
				qs(ref, sort, pivot + 1, high);
				high = pivot - 1;
			}
		}
	}
}

//main sorting function
void poker_sort(vector<int>& a){
	vector<int> sort(a.size());
	for(int i = 0; i < a.size(); ++i){
		sort[i] = val(a[i]);
	}
	qs(a, sort, 0, a.size()-1);
}

int main() {
  ifstream in("in.txt");

  int m, n, rr, v;
  in >> m;
  for (int mm = 0; mm < m; mm++) {
    in >> n;
    cout << n << " elements... ";
    vector<int> a(n);
    map<int, int> r;
    for (int i = 0; i < n; i++) {
      in >> a[i] >> rr;
      r[a[i]] = rr;
    }

    clock_t start = std::clock();
    poker_sort(a);
    cout << "\t"<<( std::clock() - start ) / (double) CLOCKS_PER_SEC << " seconds\n";
    cout << "\tvalidating...\t";
    for (int i = 0; i < n - 1; i++)
      if (r[a[i]] > r[a[i + 1]]) {
        cout << "\n\thand " << a[i] << " = (";
        v = a[i];
        for (int j = 0; j < 5; j++) {
          if (j) cout << "\t";
          cout << (v % 52) / 4 << " " << ((v % 4) == 0 ? 'A' : (v % 4) == 1 ? 'B' : (v % 4) == 2 ? 'C' : 'D');
          v /= 52;
        }
        cout << ") is better than hand " << a[i + 1] << " = (";
        v = a[i+1];
        for (int j = 0; j < 5; j++) {
          if (j) cout << "\t";
          cout << (v % 52) / 4 << " " << ((v % 4) == 0 ? 'A' : (v % 4) == 1 ? 'B' : (v % 4) == 2 ? 'C' : 'D');
          v /= 52;
        }
        cout << ") but you put these in the sorted array in the opposite order\n";
        return -1;
      }
    cout << "valid!\n";
  }
}