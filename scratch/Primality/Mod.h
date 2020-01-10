/*
    Due: October 1, 2018
    Assignment: Implement the following class. Make sure that it handles all signed 8-byte
integers correctly and without overflow.
    For now, if the user attempts to divide by zero or set the modulus to something < 2, you
can just "fail fast" with exit(-1).
*/
#ifndef ____Mod__
#define ____Mod__
#include <iostream>
#include <cassert>
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;

class Mod {
public:
    Mod(long t); //done
    Mod(const Mod& m); //done 
    Mod& operator=(const Mod& m); //done
    Mod& operator+=(const Mod& m); //ostensibly done
    Mod& operator-=(const Mod& m); //ostensibly done
    Mod& operator*=(const Mod& m); //ostensibly done
    Mod& operator/=(const Mod& m); //done
    Mod operator-() const; //done
    Mod pwr(long e) const; //done
    long val() const; //done
    static void set_modulus(const long m); //done
    static long get_modulus() { return modulus; } //done

private:
    long x;
    static long modulus; 
    static Mod inv(long r0); //done but may be danger of overflow
};

Mod operator+(const Mod& a, const Mod& b); //done
Mod operator+(long t, const Mod& m); //done
Mod operator-(const Mod& a, const Mod& b); //done
Mod operator-(long t, const Mod& m); //done
Mod operator*(const Mod& a, const Mod& b); //done
Mod operator*(long t, const Mod& m); //done
Mod operator/(const Mod& a, const Mod& b); //done
Mod operator/(long t, const Mod& m); //done
bool operator==(const Mod& a, const Mod& b); //done
bool operator==(long t, const Mod& m); //done
bool operator!=(const Mod& a, const Mod& b); //done
bool operator!=(long t, const Mod& m); //done
istream& operator>>(istream& is, Mod& m); //done 
ostream& operator<<(ostream& os, const Mod& m); //done

//long Mod::modulus = 17;
#endif /* defined(____Mod__) */