#include "Mod.h"
#include <climits>
#include <cmath>
#include <vector>
#include <iostream>

using std::vector;

long Mod::modulus = 17;

//member functions

//Constructor for a Mod object given a long t. Internally represents t as an unsigned long t % modulus
Mod::Mod(long t){
	t % modulus < 0 ? x = (t % modulus) + std::abs(modulus) : x = t % modulus;
}


//Copy constructor for a Mod object
Mod::Mod(const Mod& m){
	x = m.x;
}


//Assignment operator that takes a reference to Mod m on the RHS and assigns its value to the Mod on the LHS
Mod& Mod::operator=(const Mod& m){
	x = m.x;
	return *this;
}


//Asigns the value of the LHS plus Mod m on the RHS to the LHS
Mod& Mod::operator+=(const Mod& m){
	if(m.val() >= LONG_MAX - x){
		long new_m = m.val() - (LONG_MAX - x);
		x = LONG_MAX % modulus;
		x = (x + new_m) % modulus;
	}
	else{
		x = (x + m.val()) % modulus;
	}

	return *this;
}


//Asigns the value of the LHS minus Mod m on the RHS to the LHS
Mod& Mod::operator-=(const Mod& m){
	x = (x - m.val()) % modulus;
	x >= 0 ? x : x += modulus;
	return *this;
}


//Asigns the value of the LHS times Mod m on the RHS to the LHS
Mod& Mod::operator*=(const Mod& m){
	if (m.val() == 0){
		x = 0;
		return *this;
	}

	Mod temp = *this;
	long val = m.val();
	Mod res{0};
	while(val != 0){
		res += (temp.val() * (val-(val >> 1 << 1)));
		val >>= 1;
		temp += temp;
	}

	x = res.val();
	return *this;
}

//Asigns the value of the LHS divided by Mod m on the RHS to the LHS. Utilizes LHS*inv(m.val) for calculation
Mod& Mod::operator/=(const Mod& m){
	if(m.val() == 0) exit(-1);
	return (*this*=inv(m.val()));
}

//Provides the modular negative. 
Mod Mod::operator-() const{
	Mod ret{-x};
	return ret;
}

//Uses Russian peasant's method to effeciently take exponential mod
Mod Mod::pwr(long e) const{
	Mod temp = *this;
	long val = e;
	Mod res{1};
	while(val != 0){
		(val-(val >> 1 << 1) == 0) ? val : res *= temp;
		val >>= 1;
		temp *= temp;
	}

	return res;
}

//returns internal value
long Mod::val() const{
	return x;
}

//sets the global modulus
void Mod::set_modulus(const long m){
	if (m < 2)
	{
		exit(-1);
	}
	modulus = m;
}

//uses EEA to determine the inverse of r0 mod modulus. Only works if (r0, modulus) = 1
Mod Mod::inv(long r0){
	long m0 = modulus; 
    long y = 0;
    long x = 1; 
  
    while (r0 > 1 && m0 > 0){ 
        long q = r0 / m0; 
        long s = m0; 
  
        m0 = r0 % m0;
        r0 = s; 
        s = y; 

        y = x - q * y; 
        x = s; 
    } 
  
  	Mod res{x};
  	return res;
}


//non-member functions

//modular addition
Mod operator+(const Mod& a, const Mod& b){
	Mod t = a;
	return t+=b;
}

//modulur addition with long as first part
Mod operator+(long t, const Mod& m){
	Mod ret{t};
	return ret+=m;
}

//modular subtraction
Mod operator-(const Mod& a, const Mod& b){
	Mod t = a;
	return t-=b;
}

//modulur subtratction with long as first part
Mod operator-(long t, const Mod& m){
	Mod ret{t};
	return ret-=m;
}

//modular multuplication
Mod operator*(const Mod& a, const Mod& b){
	Mod t = a;
	return t*=b;
}

//modular subtraction with long as first part
Mod operator*(long t, const Mod& m){
	Mod ret{t};
	return ret*=m;
}

//modular division
Mod operator/(const Mod& a, const Mod& b){
	Mod t = a;
	return t/=b;
}

//modular division with long as first part
Mod operator/(long t, const Mod& m){
	Mod ret{t};
	return ret/=m;
}

//modular equality
bool operator==(const Mod& a, const Mod& b){
	return (a.val() == b.val());
}

//modular equality with long as first part
bool operator==(long t, const Mod& m){
	Mod comp{t};
	return (comp == m);
}

//modular nequality
bool operator!=(const Mod& a, const Mod& b){
	return !(a == b);
}

//modular nequality with long as first part
bool operator!=(long t, const Mod& m){
	return !(t == m);
}

//reads input long into a Mod object
istream& operator>>(istream& is, Mod& m){
	long in;
	is >> in;
	Mod ch{in};
	m = ch;
	return is;
}

//prints Mod object as its internal representation
ostream& operator<<(ostream& os, const Mod& m){
	return (os << m.val());
}