/*
 * Big_Num.h
 *
 *  Created on: 2021Äê5ÔÂ10ÈÕ
 *      Author: crh01
 */

#ifndef BIG_NUM_H_
#define BIG_NUM_H_

#include<iostream>
using namespace std;

class big_int{
private:
	int d[9999999];
	int len;
public:
	big_int(int x=0);
	big_int operator=(big_int num_2);
	big_int operator+(big_int num_2);
	big_int operator-(big_int num_2);
	big_int operator*(int num_2);
	big_int operator/(int num_2);
	friend int mod(big_int num_1, int num_2);
	friend ostream & operator << (ostream & os, big_int num);
};

big_int pow_big(int num_1, int num_2);

int key_Cal(int key, int n, int ed);

#endif /* BIG_NUM_H_ */
