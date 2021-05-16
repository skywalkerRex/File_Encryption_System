//============================================================================
// Name        : Sender_CMPE130.cpp
// Author      : Ruihua Cai
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : File Encrypter
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <cmath>
#include <numeric>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include "Big_Num.h"
#include "AES.h"
using namespace std;

int prime[164]={ 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 59, 61, 67, 71, 73, 79, 83, 89, 97,
		101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
		211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
		307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
		401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
		503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
		601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
		701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
		809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
		907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

int main_meun();
void RSA_Key_Generate(int i);
bool is_prime(int i);
int gcd(int a, int b);
string decrypte_Serial();

int main() {
	int choice;
	int enter;
	string serial, file, format;
	cout << "Welcome to Rex File Encrypter System" << endl;
	while (true){
		choice = main_meun();
		if (choice == 1){
			cout << "Enter a random number:";
			cin  >> enter;
			RSA_Key_Generate(enter);
			cout << "Key Generation has finished. Please send Public.txt to the Receiver." << endl;
		}else if (choice == 2){
			serial=decrypte_Serial();
			cout << "What kind of file you wanted to entrypt?" << endl;
			cout << "1. jpg" << endl;
			cout << "2. zip" << endl;
			cout << "3. png" << endl;
			cout << "4. txt" << endl;
			cout << "Your choice is: ";
			cin >> choice;
			switch (choice){
			case 1:
				format = ".jpg";
				break;

			case 2:
				format = ".zip";
				break;

			case 3:
				format = ".png";
				break;
			
			default:
				format = ".txt";
				break;
			}
			cout << "The name of the file(without format): ";
			cin >> file;
			clock_t start = clock();
			clock_t end;
			switch (AES_File_Encrypter(file+format, "Encrypte.Rkey", serial)){
			case -1:
				end   = clock();
				cout << "input file not found." << endl;
				break;

			case -2:
				end   = clock();
				cout << "Output file cannot be created." << endl;
				break;
			
			default:
				end   = clock();
				cout << "Encryption take: " << (double)(end - start) / CLOCKS_PER_SEC
						<< " seconds" << endl;
				cout << "Encryption has finished. Please send Encrypte.Rkey to the Receiver." << endl;
				break;
			}
		}else{
			break;
		}
	}
	cout << endl << "Thank you for using this System" << endl;
	return 0;
}

string decrypte_Serial(){
	ifstream serial_rsa, rsa_private;
	string temp;
	stringstream serial;
	int n,d;
	long int temp_int, m;
	rsa_private.open("Private.txt");
	if(rsa_private.fail()){
		cout << "Private_Key Not Found" << endl;
		return "";
	}
	getline(rsa_private,temp);
	n=stoi(temp);
	getline(rsa_private,temp);
	d=stoi(temp);
	rsa_private.close();
	serial_rsa.open("serial_num.txt");
	if(serial_rsa.fail()){
		cout << "file not found";
	}else{
		getline(serial_rsa,temp);
		do{
			temp_int=stoi(temp);
			m=key_Cal(temp_int, n, d);
			serial << setw(2) << setfill('0') << m;
			getline(serial_rsa,temp);
		}while(!serial_rsa.eof());
		cout << "Decryption done" << endl;
	}
	cout << endl;
	serial_rsa.close();
	return serial.str();
}

void RSA_Key_Generate(int i){
	int p, q, n, r;
	int e = 53;
	int d = 1;
	ofstream rsa_private, rsa_public;
	rsa_private.open("Private.txt");
	rsa_public.open("Public.txt");
	srand((unsigned)time(NULL)+1);
	p = prime[rand()%(20)];
	do{
		q = prime[rand()%(20)];
	}while(p == q);
	n = p*q;
	r = (p-1)*(q-1);
	while(((e*d)%r)!=1){
        d++;
    }
	rsa_private << n << endl << d  << endl;
	rsa_public  << n << endl << e  << endl;
	rsa_private.close();
	rsa_public.close();
	cout        << "The public key will be" << endl;
	cout        << "(" << n << "," << e << ")" << endl;
}

bool is_prime(int i){ 
    if(i<=1)
        return false;    
    for(int j=2;j<i;j++){
        if(i%j==0)return false;
    }
    return true;
}

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int main_meun(){
	string choice;
	cout << endl;
	cout << "Main Meun:" << endl;
	cout << "1. Generate RSA Encryption key" << endl;
	cout << "2. Encrypte File" << endl;
	cout << "Enter your choice (Enter -1 to break):";
	cin  >> choice;
	if (stoi(choice)==1 || stoi(choice)==2){
		return stoi(choice);
	}else{
		return -1;
	}
}
