/** Student Name: Yizhi Hu
 *  File Name: geneticAlgorithm.h
 *  Assignment: project #3
 *
 *  This is a header file for bruteForce.c
 *  All the function and constant declaration will be here
 */
#ifndef GENETICALGORITHM_H_INCLUDED
#define GENETICALGORITHM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_OF_ELITES 2
#define PERCENTAGE 100

void startGeneticAlgorithm();
void mallocArray();
void addPermutationToGeneration(long long int n);
void addMutationToGeneration();
void generateGenerations();
void freeArrays();
void swapping(int *tourToSwap,int indexA, int indexB);
void addTourToGeneration(int *tourToAdd);
void assignMin(int *tourToAdd,double routeCost);
void showMinResult();
void addElitesToGeneration();
void findTwoElites();
double getRouteCost(int *tour);
void addToCostArray(int *tourToAdd);
void copyRoute(int *destination, int *source);
void printGeneration();
void printTour(int *tour, int size);
int randomCityIndex();
int randomTourIndex();
int randomEliteIndex();
long long int fact(long long int n);
double getALCost();


#endif // GENETICALGORITHM_H_INCLUDED
