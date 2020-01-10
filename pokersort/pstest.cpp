#include<fstream>
#include<ctime>
#include<vector>
#include<iostream>
#include<cmath>
#include<map>

using namespace std;

const int pws[] = {1, 13, 169, 2197, 28561, 371293};

//express as base 13 number
int eval(const vector<int>& handvalue){
	int value = 0;
	for(int i = 0; i < 6; ++i){
		if(i < handvalue.size()){
			value += handvalue[i] * pws[5-i];
		}
	}
	return value;
}

//return the hand
vector<int> unhand(int c){
	vector<int> res;
	for (int i = 0; i < 5; i++) {
    	res.push_back(c % 52);
    	c /= 52;
  	}
	return res;
}

//creates value vector for the hand
vector<int> val(int c) {
	vector<int> hand = unhand(c); 
	vector<int> values{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
	for (int i = 0; i < 5; i++) values[hand[i] / 4]++;
	bool flush = true;
	int rk = hand[0] % 4;
 	for (int i = 1; i < 5; i++) if (hand[i] % 4 != rk) flush = false;

	vector<int> handval;
	int idx = 0;
 	while (values[idx] == 0) idx++;
  	bool straight = true;
  	for (int i = 0; i < 5; i++) if (values[idx++] != 1) straight = false;
  	if (values[0] == 1 && values[1] == 1 && values[2] == 1 && values[3] == 1 && values[12] == 1) straight = true;
  	if (straight) {
  		if(flush){
  			handval.push_back(8);
	    	if(values[12]){
	    		for (int i = 11; i >= 0; i--) if (values[i]) handval.push_back(i);
	    		handval.push_back(12);
	    	}
	    	else{
	    		for (int i = 12; i >= 0; i--) if (values[i]) handval.push_back(i);
	    	}
    		return handval;
  		}
    	handval.push_back(4);
    	if(values[12]){
    		for (int i = 11; i >= 0; i--) if (values[i]) handval.push_back(i);
    		handval.push_back(12);
    	}
    	else{
    		for (int i = 12; i >= 0; i--) if (values[i]) handval.push_back(i);
    	}
    	return handval;
    } 
	else if (flush) { 
	    handval.push_back(5);
	    for (int i = 12; i >= 0; i--) {
	    	for (int j = 0; j < values[i]; j++) handval.push_back(i);
	    }
	    return handval;
	} 

  	//check for the multiples
  	int four = -1, three = -1, p1 = -1, p2 = -1;
  	for (int i = 12; i >= 0; i--) {
  		if (values[i] == 4) four = i;
    	if (values[i] == 3) three = i;
    	if (values[i] == 2 && p1 == -1) p1 = i;
    	else if (values[i] == 2) p2 = i;
  	}
  	if(four > -1){
  		handval.push_back(7);
      	handval.push_back(four);
      	for (int i = 0; i < 13; i++) if (values[i] == 1) handval.push_back(i);
      	return handval;
  	}
  	else if (three > -1 && p1 > -1) {
   		handval.push_back(6);
    	handval.push_back(three);
    	handval.push_back(p1);
    	return handval;
  	} 
  	else if (three > -1) {
    	handval.push_back(3);
    	handval.push_back(three);
    	for (int i = 12; i >= 0; i--) if (values[i] == 1) handval.push_back(i);
    	return handval;
  	} 
  	else if (p1 > -1 && p2 > -1) {
    	handval.push_back(2);
    	handval.push_back(p1);
    	handval.push_back(p2);
    	for (int i = 12; i >= 0; i--) if (values[i] == 1) handval.push_back(i);
    	return handval;
  	} 
  	else if (p1 > -1) {
    	handval.push_back(1);
    	handval.push_back(p1);
    	for (int i = 12; i >= 0; i--) if (values[i] == 1) handval.push_back(i);
    	return handval;
  	}

  	// high card
  	handval.push_back(0);
  	for (int i = 12; i >= 0; i--) if (values[i] == 1) handval.push_back(i);
  	return handval;
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
		if(high - low < 20){
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

void poker_sort(vector<int>& a){
	vector<int> sort(a.size());
	for(int i = 0; i < a.size(); ++i){
		sort[i] = eval(val(a[i]));
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