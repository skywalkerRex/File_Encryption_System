//============================================================================
// Name        : Recevior_CMPE130.cpp
// Author      : Ruihua Cai
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : File Decryptor
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <iomanip>
#include <ctime>
#include "Big_Num.h"
#include "AES.h"
using namespace std;

int main_meun();
bool get_motherborad_Serial(string &serial_num);
string encrypte_Serial(string serial);

int main() {
	int choice;
	string serial, temp, format;
	cout << "Welcome to Rex File Decrypter System" << endl;
	while (true){
		choice = main_meun();
		if (choice == 1){
			if(get_motherborad_Serial(temp)){
				serial=encrypte_Serial(temp);
				cout << "Encryption has been done. Please send serial_num.txt to the Receiver." << endl;
			}else{
				cout << "false to check motherboard serial" << endl;
			}
		}else if (choice == 2){
			if(get_motherborad_Serial(temp)){
				serial=encrypte_Serial(temp);
				cout << "What kind of file you wanted to detrypt?" << endl;
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
				clock_t start = clock();
				clock_t end;
				switch(AES_File_Decrypter("Encrypte.Rkey", "Out"+format, serial)){
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
					cout << "Decryption take: " << (double)(end - start) / CLOCKS_PER_SEC
							<< " seconds" << endl;
					cout << "Decryption has finished. Please check Out" << format << "." << endl;
					break;
				}
			}else{
				cout << "false to check motherboard serial" << endl;
			}
		}else{
			break;
		}
	}
	cout << endl << "Thank you for using this System" << endl;
	return 0;
}

bool get_motherborad_Serial(string &serial_num){
	ifstream Serial;
	char temp;
	system("wmic cpu get processorid >> temp.txt");
	system("wmic baseboard get serialnumber >> temp.txt");
	Serial.open("temp.txt");
	if(Serial.fail()){
		Serial.close();
		system("del temp.txt");
		return false;
	}else{
		serial_num="";
		while(!Serial.eof()){
			Serial >> temp;
			if((int)temp != 0){
				serial_num.push_back(temp);
			}
		}
		Serial.close();
		system("del temp.txt");
		return true;
	}
}

string encrypte_Serial(string serial){
	ofstream serial_rsa;
	ifstream rsa_public;
	stringstream out;
	string temp;
	int n,e, count, t_i;
	rsa_public.open("Public.txt");
	if(rsa_public.fail()){
		cout << "Private_Key Not Found" << endl;
		return "";
	}
	getline(rsa_public,temp);
	n=stoi(temp);
	getline(rsa_public,temp);
	e=stoi(temp);
	rsa_public.close();
	serial_rsa.open("serial_num.txt");
	count = 0;
	for(int i=0; i<8; i++){
		t_i=0;
		for(int j=0; j<7; j++){
			t_i+=(int)serial[j+count];
		}
		count+=7;
		t_i = t_i%100;
		out  << setw(2) << setfill('0') << t_i;
		serial_rsa << key_Cal(t_i, n, e) << endl;
	}
	serial_rsa.close();
	return out.str();
}


int main_meun(){
	string choice;
	cout << endl;
	cout << "Main Menu:" << endl;
	cout << "1. Generate AES Encryption key" << endl;
	cout << "2. Decrypte File" << endl;
	cout << "Enter your choice (Enter -1 to break):";
	cin  >> choice;
	if (stoi(choice)==1 || stoi(choice)==2){
		return stoi(choice);
	}else{
		return -1;
	}
}
