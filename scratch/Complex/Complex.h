#include <cmath>
#include <iostream>

class Complex{
public:
    Complex(double re = 0, double im = 0): re(re), im(im) {}
    
    Complex(const Complex& z): re(z.re), im(z.im) {}
    
    Complex& operator =(const Complex& z){
        re = z.re;
        im = z.im;
        return *this;
    }
    
    Complex& operator +=(const Complex& z){
        re += z.re;
        im += z.im;
        return *this;
    }
    
    Complex& operator *=(const Complex& z){
        re *= z.re;
        im *= z.im;
        return *this;
    }
    
    friend std::ostream& operator <<(std::ostream&, const Complex&);
    
private:
    double re, im;
};

Complex operator +(const Complex& z, const Complex& w){
    Complex t = z;
    return t+=w;
}

Complex operator *(const Complex& z, const Complex& w){
    Complex t = z;
    return t*=w;
}

Complex operator *(const double t, const Complex& w){
    return w*Complex(t);
}

std::ostream& operator <<(std::ostream& ou, const Complex& ret){
    return ou << ret.re << '+' << ret.im << 'i' << '\n';
}
