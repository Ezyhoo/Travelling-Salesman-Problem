
/** Student Name: Yizhi Hu
 *  File Name: Input.c
 *  Assignment: project #3
 *
 * This file will dealing with inputs, including read input from user (standard input)
 * and have getter function bruteForce.c and geneticAlgorithm.c
 */

#include "Input.h"

int numOfCity;
int numOfTourEachGeneration;
int numOfGeneration;
double percentOfMutationOfGeneration;

/**
 * This function gets the inputs
 */
void getInputs(){
    printf("Enter the number of cities to run: ");
    scanf("%d",&numOfCity);

    printf("Enter the number of individual tours are in a given generation: ");
    scanf("%d",&numOfTourEachGeneration);

    printf("Enter the number of generation to run: ");
    scanf("%d",&numOfGeneration);

    printf("Enter the percentage of a generation should be comprised of mutations: ");
    scanf("%lf",&percentOfMutationOfGeneration);

    printf("\n");
}

/**
 * This function get the number of cities
 * @return numOfCity
 */
int getNumOfCity(){
    return numOfCity ;
}
/**
 * This function get the number of tour each generation
 * @return numOfTourEachGeneration
 */
int getNumOfTourEachGeneration(){
    return numOfTourEachGeneration;
}
/**
 * This function get the number of generation
 * @return numOfGeneration
 */
int getNumOfGeneration(){
    return numOfGeneration;
}
/**
 * This function get the percent of mutation of a generation
 * @return percentOfMutationOfGeneration
 */
double getPercentOfMutationGeneration(){
    return percentOfMutationOfGeneration;
}
