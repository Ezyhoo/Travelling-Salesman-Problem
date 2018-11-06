/** Student Name: Yizhi Hu
 *  File Name: bruteForce.h
 *  Assignment: project #3
 *
 *  This is a header file for bruteForce.c
 *  All the function declaration will be here
 */
#ifndef BRUTEFORCE_H_INCLUDED
#define BRUTEFORCE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startBruteForce();
void permutation(long long int n);
void processTour();
double getTourCost();
void copyTour(int *destination, int *source);
void showResults();
void buildArray();
long long int factorial(long long int num);
void freeArraysForBruteForce();
double getBFCost();

#endif // BRUTEFORCE_H_INCLUDED
