/*
 * Big_Num.cpp
 *
 *  Created on: 2021年5月10日
 *      Author: crh01
 */

#include "Big_Num.h"
#include <iostream>
#include <cmath>

using namespace std;

big_int::big_int(int x){
	int count=0;
	if(x != 0){
		do{
			d[count]=(x%(int)pow(10,count+1))/(int)pow(10,count);
			count++;
		}while(x>=pow(10,count));
		len=count;
	}else{
		len = 0;
		d[0] = 0;
	}
}

big_int big_int::operator=(big_int num_2){
	len = num_2.len;
	for(int i=0;i<len;i++){
		d[i]=num_2.d[i];
	}
	return *this;
}

big_int big_int::operator+(big_int num_2){
	big_int sum;
	int carry=0;
	if(num_2.len==0){
		num_2.len++;
	}
	for(int i=0;i<this->len||i<num_2.len;i++){
		int temp=this->d[i]+num_2.d[i]+carry;
		sum.d[sum.len++]=temp%10;
		carry=temp/10;
	}
	if(carry!=0){
	   sum.d[sum.len] =carry;
	}
	return sum;
}

big_int big_int::operator-(big_int num_2){
	big_int sum;
	if(num_2.len==0){
		num_2.len++;
	}
	for(int i=0;i<this->len||i<num_2.len;i++){
		if(this->d[i]<num_2.d[i]) {//如果不够减法，则向高位借位
			if(this->d[i+1]>0){
				this->d[i+1]--;
				this->d[i]+=10;
			}
		}
		sum.d[sum.len++]=this->d[i]-num_2.d[i];
	}
	while(sum.len-1>=1&&sum.d[sum.len-1]==0){
		sum.len--;
	}
	return sum;
}

big_int big_int::operator*(int num_2){
	big_int sum;
	int carry=0;
	for(int i=0;i<this->len;i++){
		int temp=this->d[i]*num_2+carry;
		sum.d[sum.len++]=temp%10;
		carry=temp/10;
	}
	while(carry!=0)
	{
		sum.d[sum.len++]=carry%10;
		carry/=10;
	}
	return sum;
}

big_int big_int::operator/(int num_2){
    big_int sum;
    int r;
	sum.len=this->len;
	for(int i=this->len-1;i>=0;i--){
		r=r*10+this->d[i];
		if(r<num_2)
			sum.d[i]=0;
		else{
			sum.d[i]=r/num_2;
			r=r%num_2;
		}
	}
	while(sum.len-1>=1&&sum.d[sum.len-1]==0){
		sum.len--;
	}
	return sum;
}

big_int pow_big(int num_1, int num_2){
	big_int num(num_1);
	for(int i=1; i<num_2; i++){
		num = num * num_1;
	}
	return num;
}

int mod(big_int num_1, int num_2){
    big_int sum;
    int r;
	sum.len=num_1.len;
	for(int i=num_1.len-1;i>=0;i--){
		r=r*10+num_1.d[i];
		if(r<num_2)
			sum.d[i]=0;
		else{
			sum.d[i]=r/num_2;
			r=r%num_2;
		}
	}
	while(sum.len-1>=1&&sum.d[sum.len-1]==0){
		sum.len--;
	}
	return r;
}

ostream &operator<< (ostream & os, big_int num){
	if(num.len!=0){
		for(int i=num.len-1; i>=0; i--){
			os << num.d[i];
		}
	}else{
		os << 0;
	}
	return os;
}

int key_Cal(int key, int n, int ed){
	return mod(pow_big(key,ed),n);
}

