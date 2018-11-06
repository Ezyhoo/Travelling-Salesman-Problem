/** Student Name: Yizhi Hu
 *  File Name: Matrix.c
 *  Assignment: project #3
 *
 * This file will load a matrix from txt file and assign each value into the matrix
 */
#include "Matrix.h"

double cityCosts[TOTAL_CITY][TOTAL_CITY];   //city cost adjacent matrix

/**
 * This function load the matrix from txt file
 *
 */
void loadMatrix(){

    FILE *fp;

    fp = fopen("cityWeights.txt","r");

    int i,j;
    for(i = 0; i < TOTAL_CITY; i++){
        for(j = 0; j < TOTAL_CITY; j++){
            if(i == j){
                cityCosts[i][j] = 0.0;
//                printf("%lf\n",adjacentMatrix[i][j]);
            }
            else{
                fscanf(fp, "%lf",&cityCosts[i][j]);
//                printf("%lf\n",adjacentMatrix[i][j]);
            }
        }
    }

}

/**
 * This function print out the matrix
 */

void printMatrix(){
    int i,j;
    for(i = 0; i < TOTAL_CITY; i++){
        printf("\n");
        for(j = 0; j < TOTAL_CITY; j++){
            printf("%.2lf\t",cityCosts[i][j]);
        }
    }
    printf("\n");
}

/**
 * This function get the cost going from one city to another city
 * @param from the index of city going from
 * @param to the index of city going to
 * @return cityCosts[from][to] double value of cost between traveling these two cities
 */
double getCost(int from, int to){

    return cityCosts[from][to];
}




