

#ifndef FIELD_H_
#define FIELD_H_
#include<iostream>
#include<map>
#include<climits>
#include<string.h>
std::string toStringOneNumber(__int128 x){
    if(x % 10 == 0)return "0" ;
	if(x % 10 == 1)return "1" ;
	if(x % 10 == 2)return "2" ;
	if(x % 10 == 3)return "3" ;
	if(x % 10 == 4)return "4" ;
	if(x % 10 == 5)return "5" ;
	if(x % 10 == 6)return "6" ;
	if(x % 10 == 7)return "7" ;
	if(x % 10 == 8)return "8" ;
	return "9" ;
}
__int128 charToDigit(char x){
    if(x == '0')return 0;
	if(x == '1')return 1;
	if(x == '2')return 2;
	if(x == '3')return 3;
	if(x == '4')return 4;
	if(x == '5')return 5;
	if(x == '6')return 6;
	if(x == '7')return 7;
	if(x == '8')return 8;
	return 9 ;
}
std::string toString(__int128 x){
    if(x == 0)return "0";
	std::string ans = "";
	bool minus=false;
	if(x<0){
		minus=true;
		x = -x;
	}
	while(x != 0){
		ans = toStringOneNumber(x)+ans;
		x /=10;
	}
	if(minus)ans="-"+ans;
	return ans;
}
__int128 fromString(std::string x){
	__int128 ans = 0;
	__int128 multiplier = 1;
	for(int i = (int)x.size()-1;i>-1;i--){
		if(x[i]=='-')return -ans;
		ans+=charToDigit(x[i])*multiplier;
		multiplier*=10;
	}
	return ans;
}
class field{
    static   __int128 p;
    static   __int128 m;
    static field almostPrimitiveRoot;
    static __int128 odd;
    static __int128 degreeOfDegree;
    __int128 value;
public:
    static std::map< __int128,__int128> inverse;
    static void  setEasyThings();
    static void  setAlmostPrimitiveRoot();
    __int128 static getP(){
        return p;
    }
    __int128 static getM(){
        return m;
    }
    field static getAlmostPrimitiveRoot(){
        return almostPrimitiveRoot;
    }
    __int128 static getOdd(){
        return odd;
    }
    __int128 static getDegreeOfDegree(){
        return degreeOfDegree;
    }
    static void setP( __int128 x);
    static void setPsilly(__int128 x);
    static void insertInverse(field a,field b){
        field::inverse[a.value] = b.value;
        field::inverse[b.value] = a.value;
    }
    field(){
        this->value = 0;
    }
    field(  __int128 val){
        if(val >= 0)this->value = val%p;
        else this->value = (val+p)%p;
    }
    field(field& a){
        this->value = a.value;
    }
    field(const field& a){
        this->value = a.value;
    }
    __int128 getValue()const{
        return this->value;
    }
    field &operator=(const field &);
    field inline &operator++();
    field inline operator++(int temp);
    field inline &operator--();
    field inline operator--(int temp);
    friend inline field &operator+=(field &, const field &);
    friend inline field operator+(const field &, const field &);
    friend inline field operator-(const  field &, const field &);
    friend inline field &operator-=(field &, const field &);
    friend bool inline operator==(const field &, const field &);
    friend bool inline operator!=(const field &, const field &);
    friend bool inline operator>(const field &, const field &);
    friend bool inline operator>=(const field &, const field &);
    friend bool inline operator<(const field &, const field &);
    friend bool inline operator<=(const field &, const field &);
    friend field &operator*=(field &, const field &);
    friend field operator*(const field &, const field &);
    friend field &operator/=(field &, const field &);
    friend field operator/(const field &, const field &);
    friend field inline &operator ^=(field &,const __int128 &);
    friend field inline operator^(field &,  __int128  &);
    friend std::ostream &operator<<(std::ostream &,const field &);
    friend std::istream &operator>>(std::istream &, field &);
};
__int128 field::p = 2;
__int128 field::m = 1;
__int128 field::odd = 1;
field field::almostPrimitiveRoot = field(1);
__int128 field::degreeOfDegree = 0;
std::map<  __int128,  __int128>field::inverse = std::map<  __int128, __int128>();
field &field::operator=(const field &a){
    value = a.value;
    return *this;
}
field &field::operator++(){
    this->value = (value+1)%field::p;
    return *this;
}
field field::operator++(int temp){
    field aux(*this);
    ++(*this);
    return aux;
}
field &field::operator--(){
    this->value = (field::p+value-1)%field::p;
    return *this;
}
field field::operator--(int temp){
    field aux(*this);
    --(*this);
    return aux;
} 
field &operator+=(field &a,const field& b){
    a.value = (a.value+b.value)%field::p;
    return a;
}
field operator+(const field &a, const field &b){
    field temp;
    temp = a;
    temp += b;
    return temp;
} 
field &operator-=(field&a,const field &b){
    a.value = (a.value-b.value+field::p)%field::p;
    return a;
}
field operator-(const field& a,const field&b){
    field temp;
    temp = a;
    temp -= b;
    return temp;
}
bool operator==(const field &a, const field &b){
    return a.value == b.value;
}
bool operator!=(const field & a,const field &b){
    return !(a == b);
}
bool operator<(const field &a, const field &b){
    return a.value < b.value;
}
bool operator<=(const field & a,const field &b){
    return a.value <= b.value;
}
bool operator>(const field &a, const field &b){
    return a.value > b.value;
}
bool operator>=(const field & a,const field &b){
    return !(a >= b);
}
field &operator*=(field &a, const field &b){
    if(b.getValue() <= field::m){
        a = field(b.getValue()*a.getValue());
    } 
    else if(b.getValue() > field::m){
        __int128 A = a.getValue();
        __int128 B = b.getValue();//mk+l
        __int128 k = B/field::m;
        __int128 l = B%field::m;
        field ans1 = field(A)*field(field::m);
        ans1 *= field(k);
        field ans2(A);
        ans2*=l;
        a = ans1 + ans2;
    }
    return a;
}
field operator*(const field&a,const field&b){
    field temp;
    temp = a;
    temp *= b;
    return temp;
} 
field &operator^=(field & a, __int128 const & b){
    __int128 B = (b%(field::p-1));
    if(field::odd == 0)B=b; 
    field A(a);
    if(B == 0){
        a  = 1;
    }
    if(B == -1){
        if(a == 0)throw("Arithmetic Error: Division By 0");
        if(field::inverse.count(a.getValue()) == 0){
            field::insertInverse(a, A^=(field::p-2));
        }
        a = field(field::inverse[a.getValue()]);
    }
    if(B > 1){
        field multiplier = a;
        field ans = 1;
        while(B != 0){
            if(B % 2 == 1)ans *= multiplier;
            multiplier *= multiplier;
            B = B>> 1;
        }
        a = ans;
        return a;
    }
    if(B<-1){
        a^=-1;
        a^=(-B);
    }
    return a;
}
field operator^(field & a, __int128 b){
    field temp(a);
    temp ^= b;
    return temp;
} 
field &operator/=(field& a,const field &b){
    field B(b.getValue());
    field z = (B^(__int128)(-1));
    a*=z;
    return a;
}
field operator/(const field &a,const field &b){
    field temp;
    temp = a;
    temp /= b;
    return temp;
} 
std::istream &operator>>(std::istream &in,field&a){
    std::string s;
    in >> s;
    a = field(fromString(s));
    return in;
}
std::ostream &operator<<(std::ostream &out,const field &a){
    std::cout << toString(a.value);
    return out;
}
void field::setP( __int128 x){
    field::inverse.clear();
    field::p = x;
    __int128 y = field::p - 1;
    __int128 degree = 0;
    while(y % 2 == 0){
        degree++;
        y /= 2;
    }
    __int128 maximum = 1;
    __int128 s = 1;
    for(int i = 0; i<126; i++){
        s*=2;
        maximum +=s;
    }
    field::m = maximum  / x ;    
    field::odd = y;
    field::degreeOfDegree = degree;
    field r;
    for(__int128 i = 2; i<field::p;i++){
        r = field(i);
        r ^= ((field::p-1)/2);
        if(r.getValue() != 1){
            r = field(i);
            field::almostPrimitiveRoot = r^(__int128)field::odd;
            break;
        }
    }
    
} 
void field::setPsilly(__int128 x){
    field::inverse.clear();
    field::p = x;
    field::odd = 0;
    field::degreeOfDegree = 0;
    __int128 maximum = 1;
    __int128 s = 1;
    for(int i = 0; i<126; i++){
        s*=2;
        maximum +=s;
    }
    field::m = maximum / x ;
}
#endif

 