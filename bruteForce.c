/** Student Name: Yizhi Hu
 *  File Name: bruteForce.c
 *  Assignment: project #3
 *
 *  This file is going to implement brute force algorithm to find the
 *  optimal route and cost for TSP
 */
#include "Matrix.h"
#include "bruteForce.h"
#include "Input.h"

int numOfCity;  //number of city to brute force

double minCost;     //the minimal cost of the all the permutation

int *minRoute;      //the route with minimal cost

long long int tourCounter;      //the counter of how many tours have been generated

int * currentTour;      //the current tour array


/**assign value for numOfCity from input*/
void assignValue(){
    numOfCity = getNumOfCity();
}

/**the high level implementation of brute force*/
void startBruteForce(){
    printf("Now, program is running brute force algorithm.\n");
    assignValue();
    buildArray();
    permutation(factorial(numOfCity - 1));
    showResults();
    freeArraysForBruteForce();

}

/**
 * This function swap the two index of current tour
 * @param a and b are the two index to swap
 *
 */
void swap(int a, int b){

    int temp = currentTour[a];
    currentTour[a] = currentTour[b];
    currentTour[b] = temp;

}

/**
 * This function returns a factorial of a number by recursive calling
 * @param num the number to calculate factorial
 * @return the factorial of the number
 */
long long int factorial(long long int num){
    if(num == 1 || num == 0){
        return 1;
    }
    return num * factorial(num - 1);
}

/**
 * This function build the arrays declare globally
 * and assign "0 1 2 3 .... numOfCity-1 0" into currentTour
 */
void buildArray(){
    long long int i = 0;

    //build city array
    currentTour = malloc(sizeof(int) * (numOfCity + 1)) ;
    for(i = 0; i < numOfCity; i++){
        currentTour[i] = i;
    }
    currentTour[i] = 0;

    minRoute = malloc(sizeof(int ) * numOfCity + 1);

}

/**
 * This function will permute from right to left so that
 * we can try all the different combination to calculate the
 * minimal cost of this TSP. In our case, we pass (numOfCity - 1)!
 * to get the cost for all the permutation.
 *
 * @param n the number of times to permute
 */
void permutation(long long int n){
     int m, k, p , q;
     long long int i;

    processTour();   //process the original tour before changing it

     for(i = 1; i < n; i++)
     {
       m = numOfCity - 2;
       while(currentTour[m]>currentTour[m+1])
       {
          m = m - 1;
       }
       k = numOfCity-1;
       while(currentTour[m] > currentTour[k])
       {
          k = k - 1;
       }

       swap(m,k);

       p = m + 1;
       q = numOfCity-1;
       while(p < q)
       {
         swap(p,q);
         p++;
         q--;
       }
        processTour();
     }
}

/**
 * This function process the currentTour by comparing the cost of
 * the currentTour with the minimal cost the program have at that time
 *
 */
void processTour(){

    double currentTourCost = getTourCost();

    //if this is the first tour or the cost of current tour is less than minimal cost
    if(tourCounter == 0 || currentTourCost < minCost){
        minCost = currentTourCost;
        copyTour(minRoute,currentTour);
    }
    tourCounter ++;

}

/**
 * This function copy one integer array to another
 * @param destination the int array copying to
 * @param source the int array copying from
 */
void copyTour(int *destination, int *source){
    int i;
    for(i = 0; i < numOfCity + 1; i++){
        destination[i] = source[i];
    }
}

/**
 * This array returns the cost of the currentTour by calling
 * getCost defined in Matrix.c
 * @return cost cost of the currentTour
 */

double getTourCost(){
    double cost = 0;
    int i;
    for(i = 0; i < numOfCity ; i++){
        cost += getCost(currentTour[i],currentTour[i+1]);
    }
    return cost;
}


//void printCurrentTour(){
//    int i = 0;
//
//    for(i = 0; i < numOfCity + 1; i++){
//        printf("%d\t",currentTour[i]);
//    }
//    printf("\n");
//}

/**
 * This function will be called after brute force implementation finished
 * and it will print out the route with minimal cost and
 * the minimal cost
 */
void showResults(){
    printf("The route with minimal cost for %d cities is: ", numOfCity);
    int i;
    for(i = 0; i < numOfCity + 1; i++){
        printf("%d ",minRoute[i]);
    }
    printf("\n");
    printf("with minimal cost: %lf\n",minCost);
}


/**
 * This function free all the dynamic location
 */
void freeArraysForBruteForce(){
    free(currentTour);
    free(minRoute);
}

/**
 * This function return the minimal cost of brute force algorithm
 * @return minCost the optimal solution of brute force
 */
double getBFCost(){
    return minCost;
}
