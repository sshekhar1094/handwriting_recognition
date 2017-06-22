#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <stdlib.h>
#include <cmath>
using namespace std;

#define px 28
#define laplace 0.1
#define totalTraining 5000
#define totalTest 1000

char 	testImages[] = "testimages.txt",	
		testLabels[] = "testlabels.txt",
		trainingImages[] = "trainingimages.txt",
		trainingLabels[] = "traininglabels.txt";
		

int arr[10][28][28][2] = {0}, answers[1009], results[1009], trainResults[5009], countLabels[10] = {0};
double likelihood[10][28][28][2];
ofstream fout;
ifstream fin;

void getData(){	
	int ithlabel;
	char line[30];

	fin.open(trainingLabels);
	for(int i=0; i<totalTraining; i++){
		fin>>ithlabel;
		trainResults[i] = ithlabel;		//storing the resultant digit of training images
		countLabels[ithlabel]++;		//storing frequency of each class
	}
	fin.close();	//close training labels

	fin.open(trainingImages);		
	for(int i=0; i<totalTraining; i++){
		for(int j=0; j<28; j++){
			fin.getline(line, 30);
			for(int k=0; k<28; k++){
				if(line[k] == ' ') arr[ trainResults[i] ][j][k][0]++;
				else arr[ trainResults[i] ][j][k][1]++;
			}
		}
	}
	fin.close();		//close training images
}

void train(){
	double a,b;

	for(int c=0; c<10; c++){
		for(int i=0; i<28; i++){
			for(int j=0; j<28; j++){
				a = (double)( arr[c][i][j][0] + laplace);
				b = (double)( countLabels[c] + laplace*2);
				likelihood[c][i][j][0] = a/b;		//no of times pixel(i,j) has value=0 for class c / no of occurences of class c

				a = (double)( arr[c][i][j][1] + laplace);
				likelihood[c][i][j][1] = a/b;		//no of times pixel(i,j) has value=1 for class c / no of occurences of class c
			}
		}
	}
}

void getTestLabels(){
	int ithlabel;
	fin.open(testLabels);
	for(int i=0; i<totalTest; i++){
		fin>>ithlabel;
		answers[i] = ithlabel;
	}
	fin.close();
}

void testing(){
	char line[30][30];
	double val=1, max=-5.0;

	fin.open(testImages);
	for(int img=0; img<totalTest; img++){
		max = -5.0;
		for(int i=0; i<28; i++)
			fin.getline(line[i], 100);
		for(int cls=0; cls<10; cls++){
			val = 1.7e300;
			for(int i=0; i<28; i++){
				//cout<<line[i]<<endl;
				for(int j=0; j<28; j++){
					if(line[i][j] == ' ') 
						val = val * likelihood[cls][i][j][0];
					else 
						val = val * likelihood[cls][i][j][1];
				}
			}
			//cout<<img<<":"<<cls<<":"<<val<<endl;
			if(val > max){
				//cout<<img<<":"<<cls<<":"<<val<<endl;
				max = val;
				results[img] = cls;
			}
		}
	}
	fin.close();
}

void getAccuracy(){
	int ct=0;
	int clsAccuracy[10] = {0}, occurenceCt[10]={0};
	for(int i=0; i<totalTest; i++){
		if(answers[i] == results[i]){
			ct++;
			clsAccuracy[results[i]]++;
		}
		occurenceCt[answers[i]]++;
		//if(i%100 == 0) cout<<ct<<"/"<<i<<endl;
		//if(answers[i] != results[i]) cout<<i<<":"<<answers[i]<<":"<<results[i]<<endl;
	}
	cout<<"accuracy is "<<ct<<"/1000\n";
	cout<<"Class accuracy:\n";
	for(int i=0; i<10; i++){
		cout<<i<<"-->"<<clsAccuracy[i]<<"/"<<occurenceCt[i]<<"="<<((double)(clsAccuracy[i]))/((double)(occurenceCt[i]))<<endl;
	}
}


int main(int argc, char *argv[]){
	getData();
	train();
	getTestLabels();
	testing();
	getAccuracy();

	return 0;
}

