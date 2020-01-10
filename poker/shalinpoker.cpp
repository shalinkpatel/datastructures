#include<vector>
#include<iostream>
#include<cmath>
#include<fstream>
#include<ctime>
#include<vector>
#include<iostream>
#include<cmath>
#include<map>
#include<unordered_map>

using std::unordered_map;
using std::vector;
using std::pow;
using std::cout;
using std::endl;
using std::swap;
using std::cin;

//precomputed constants
const int pws[] = {1, 13, 169, 2197, 28561, 371293};
const int cards[] =  {65537,65538,65540,65544,65552,65568,65600,65664,65792,66048,
66560,67584,69632,32769,32770,32772,32776,32784,32800,
32832,32896,33024,33280,33792,34816,36864,16385,16386,
16388,16392,16400,16416,16448,16512,16640,16896,17408,
18432,20480,8193,8194,8196,8200,8208,8224,8256,8320,
8448,8704,9216,10240,12288};

//return the hand
vector<int> unhand(){
	vector<int> hand(5);
	for(int i = 0; i < 5; ++i){
		cin >> hand[i];
	}

	return hand;
}

//returns cards to drop
vector<int> eval() {
	vector<int> hand = unhand();
	unordered_map<int, int> trace;
	unordered_map<int, int> flushtrace;
	int a = cards[13 * (hand[0] % 4) + hand[0]/4];
	int b = cards[13 * (hand[1] % 4) + hand[1]/4];
	int c = cards[13 * (hand[2] % 4) + hand[2]/4];
	int d = cards[13 * (hand[3] % 4) + hand[3]/4];
	int e = cards[13 * (hand[4] % 4) + hand[4]/4];
	vector<int> flushc(4, 0);
	vector<int> values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
	for (int i = 0; i < 5; i++){
		values[hand[i] / 4]++;
		trace[hand[i] / 4] = hand[i];
		flushc[hand[i] % 4]++;
		flushtrace[hand[i] % 4] = hand[i];
	}
	bool ffc = false;
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
			vector<int> ret{0};
			return ret;
		}
		else{
			vector<int> ret{0};
			return ret;
		}
	}
	else if(flush){
		vector<int> ret{0};
		return ret;
	} 
	int XOR = (a ^ b ^ c ^ d ^ e) & 8191;
	int x = __builtin_popcount(OR);
	int y = __builtin_popcount(XOR);
	bool two = false, dtwo = false, three = false, full = false, four = false;
	two = (x+y == 7);
	dtwo = (x+y == 4);
	three = (x+y == 6);
	if(x+y == 3){
		for (int i = 12; i >= 0; i--){
			if (values[i] == 4) four = true;
		} 
		if(!four) full = true;
	}

	if(two){
		vector<int> ret{3};
		for(int i = 0; i < 13; ++i){
			if(values[i] == 1) ret.push_back(trace[i]);
		}
		return ret;
	}
	else if(dtwo){
		int odd;
		for(int i = 0; i < 13; ++i){
			if(values[i] == 1) odd = trace[i];
		}
		vector<int> ret{1,odd};
		return ret;
	}
	else if(three){
		vector<int> ret{2};
		for(int i = 0; i < 13; ++i){
			if(values[i] == 1) ret.push_back(trace[i]);
		}
		return ret;
	}
	else if(full){
		vector<int> ret{0};
		return ret;
	}
	else if(four){
		int odd = -1;
		for(int i = 0; i < 13; ++i){
			if(values[i] == 1 && i < 6) odd = trace[i];
		}
		if(odd == -1){
			vector<int> ret{0};
			return ret;
		}
		else{
			vector<int> ret{0, odd};
			return ret;
		}
	}
	else{
		vector<int> ret;
		for(int i = 0; i < 4; ++i){
			if(flushc[i] == 4){
				ffc = true;
			}
		}
		if(ffc){
			ret.push_back(1);
			for(int i = 0; i < 4; ++i){
				if(flushc[i] == 1) ret.push_back(flushtrace[i]);
			}
			return ret;
		}
		bool fs = false;
		int fst;
		for(int i = 0; i < 9; ++i){
			int cntr = 0;
			for(int j = i; j < i + 5; ++j){
				if(values[j] == 1) cntr++;
			}
			if(cntr == 4 && i > 0 && i < 12){
				for(int j = 0; j < 13; ++j){
					if(values[j] == 1 && (j < i || j > i+4)) fst = trace[j];
				}
				fs = true;
			}
		}
		if(fs){
			ret.push_back(1);
			ret.push_back(fst);
		}
		else {
			ret.push_back(3);
			int cntr = 0;
			for(int i = 0; i < 13 && cntr < 3; ++i){
				if(values[i] == 1) {ret.push_back(trace[i]); cntr++;}
			}
		}
		return ret;
	}
}

int main() {
	while(true){
	vector<int> evaled = eval();
	for(int i : evaled){
		cout << i << " ";
	}
	cout << '\n';}
	return 0;
}