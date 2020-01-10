#include <vector>
#include <iostream>
using namespace std;

void insertsort2(vector<int>& lol) {
    int bla;
    for (int i = 0; i != lol.size(); ++i) {
        for (int j = i; j != 0 && lol[j]/4 < lol[j-1]/4; --j) {
            bla = lol[j-1];
            lol[j-1] = lol[j];
            lol[j] = bla;
        }
    }
}

int sorthand(int f) {
    int t;
    vector<int> c(5);
    /*for (int i = 0; i != 5; ++i) {
        c[i] = f % 52;
        f /= 52;
    }*/
    c[0] = f % 52;
    c[1] = f/52 % 52;
    c[2] = f/2704 % 52;
    c[3] = f/140608 % 52;
    c[4] = f/7311616 % 52;
    //for (int i = 0; i!= 5; ++i) {cout << c[i] << " ";}
    //cout << "end of stuff out of order" << '\n';
    for (int i = 0; i != 5; ++i) {
        for (int j = i; j != 0 && c[j]/4 < c[j-1]/4; --j) {
            //cout << i << " " << j << "       " << c[j] << " " << c[j-1] << '\n';
            t = c[j-1];
            c[j-1] = c[j];
            c[j] = t;
        }
    }
    //for (int i = 0; i!= 5; ++i) {cout << c[i] << " ";}
    //cout << "end of stuff" << '\n';
    //if (c[0] + c[1]*52 + c[2]*2704 + c[3]*140608 + c[4]*7311616 == 319849263) {for (int i = 0; i!= 5; ++i) {cout << c[i] << " ";}}
    //return c[0] + c[1]*52 + c[2]*2704 + c[3]*140608 + c[4]*7311616;
    return c[0] + c[1]*52 + c[2]*2704 + c[3]*140608 + c[4]*7311616;
}

int evaluate(int a) {
    vector<int> v(5);
    vector<int> s(4);
    vector<int> r(13);
    int ret = 0;
    a = sorthand(a);
    //cout << a << '\n';
    for (int i = 0; i != 5; ++i) {
        int k = a % 52;
        v[i] = k/4;
        r[k/4] += 1;
        s[k%4] += 1;
        a /= 52;
    }
    /*for (int j = 0; j != 5; ++j) {cout << v[j] << ' ';}
    cout << '\n';
    for (int j = 0; j != 13; ++j) {cout << r[j] << ' ';}
    cout << '\n';
    for (int j = 0; j != 4; ++j) {cout << s[j] << ' ';}*/

    int four = -1;
    int three = -1;
    int twob = -1;
    int twos = -1;
    for (int j = 12; j != -1; --j) {
        if (r[j] == 4) {four = j; break;}
        if (r[j] == 3) {three = j;}
        if (r[j] == 2 && twob == -1) {twob = j;}
        else if (r[j] == 2) {twos = j; break;}
    }
    if (twob != -1) {
        if (twos == -1 && three == -1) {
            ret += twob;
            for (int j = 4; j != -1; --j) {
                if (v[j] != twob) {
                    ret *= 13;
                    ret += v[j];
                }
            }
            ret += 2000000;
            return ret;
        }
        else if (twos != -1) {
            ret += twob;
            ret *= 13;
            ret += twos;
            for (int j = 4; j != -1; --j) {
                if (v[j] != twob && v[j] != twos) {
                    ret *= 13;
                    ret += v[j];
                    break;
                }
            }
            ret += 3000000;
            return ret;
        }
        else if (three != -1) {
            ret += three;
            ret *= 13;
            ret += twob;
            for (int j = 4; j != -1; --j) {
                if (v[j] != three && v[j] != twob) {
                    ret *= 13;
                    ret += v[j];
                }
            }
            ret += 7000000;
            return ret;
        }
    }
    else {
        if (three != -1) {
            ret += three;
            for (int j = 4; j != -1; --j) {
                if (v[j] != three) {
                    ret *= 13;
                    ret += v[j];
                }
            }
            ret += 4000000;
            return ret;
        }
        else if (four != -1) {
            ret += four;
            for (int j = 4; j != -1; --j) {
                if (v[j] != four) {
                    ret *= 13;
                    ret += v[j];
                    break;
                }
            }
            ret += 8000000;
            return ret;
        }
        else {
            bool flush = 0;
            for (int j = 0; j != 4; ++j) {
                if (s[j] == 5) {flush = 1; break;}
            }
            /*
            bool straight = 1;
            for (int j = 4; j != 0; --j) {
                if (v[j] - v[j-1] != 1 && !(j == 4 && v[4] == 12 && v[3] == 3)) {straight = 0; break;}
            }*/
            bool straight = 0;
            if (v[4] - v[0] == 4 || (v[3] - v[0] == 3 && v[4] - v[3] == 9)) {straight = 1;}
            if (straight) {
                if (v[0] == 0 && v[4] == 12) {ret = 3;}
                else {ret = v[0] + 4;}
                ret += 5000000;
                if (flush) {ret += 4000000;}
                return ret;
            }
            else {
                for (int j = 4; j != -1; --j) {
                    ret *= 13;
                    ret += v[j];
                }
            }
            ret += 1000000;
            if (flush) {ret += 5000000;}
            return ret;
        }
    }
}

int main(){
    while(true){
    vector<int> h(5);
    int matthew = 0;
    for (int i = 0; i != 5; ++i) {
        cin >> h[i];
        //cout << h[i] << '\n';
        matthew = matthew*52 + h[i];
    }
    insertsort2(h);
    matthew = sorthand(matthew);
    //cout << matthew << '\n';
    int evaled = evaluate(matthew);
    if (evaled >= 4000000) {cout << "0" << '\n';}
    else {
        cout << "3" << " ";
        cout << h[0] << " " << h[1] << " " << h[2] << '\n';
    }}
}

