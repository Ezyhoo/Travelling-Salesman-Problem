/** Student Name: Yizhi Hu
 *  File Name: geneticAlgorithm.c
 *  Assignment: project #3
 *
 *  This file is going to implement genetic algorithm to try to find the
 *  optimal route and cost for TSP
 */
#include "geneticAlgorithm.h"
#include "Input.h"
#include "Matrix.h"

int numOfCity;
int numOfTourEachGeneration;
int numOfGeneration;
double percentOfMutationGeneration;
int numOfMutationPerGeneration;
int numOfPermutationPerGeneration;

int *minRoute;      //the route with minimal cost
double minRouteCost = 0;    //the minimal route cost
int *currentTour;    //the int array of current city tour
int **generation;
double *costArrays;     //the associated array of generation

int currentLine = 0;    //counter to keep track of the current row

int *elite1;    //the best cost in the generation
int *elite2;    //the second best cost in the generation

double elite1Cost = 0;
double elite2Cost = 0;


/**
 * This function assign value to the variables: numOfCity, numOfTourEachGeneration
 * percentOfMutationGeneration, numOfMutationPerGeneration, numOfPermutationPerGeneration
 * These values assigned from Input file
 *
 */
void assignValues(){
    numOfCity = getNumOfCity();
    numOfTourEachGeneration = getNumOfTourEachGeneration();

    numOfGeneration = getNumOfGeneration();
    percentOfMutationGeneration = getPercentOfMutationGeneration();

    numOfMutationPerGeneration = numOfTourEachGeneration * percentOfMutationGeneration/(double) PERCENTAGE;

    numOfPermutationPerGeneration = numOfTourEachGeneration - numOfMutationPerGeneration - NUM_OF_ELITES;

}

/**
 * This function dynamically allocate the memory for int arrays or double arrays
 * and initialize the currentTour as "0 1 2 3.... numOfCity-1 0"
 */
void mallocArray(){

    minRoute = malloc(sizeof(int) * (numOfCity + 1));
    currentTour = malloc(sizeof(int) * (numOfCity + 1));
    int i;
    for(i = 0; i < numOfCity; i++){
        currentTour[i] = i;
    }
    currentTour[i] = 0;

    generation = malloc(sizeof(int *) * numOfTourEachGeneration);
    for(i = 0; i < numOfTourEachGeneration + 1; i++){
        generation[i] = malloc(sizeof(int ) * (numOfCity + 1));
    }
    costArrays = malloc(sizeof(double) * numOfTourEachGeneration);


    elite1 = malloc(sizeof(int) * (numOfCity + 1));
    elite2 = malloc(sizeof(int) * (numOfCity + 1));
}

/**
 * The high level implementation of genetic algorithm
 *
 */
void startGeneticAlgorithm(){
    printf("Now, program is running genetic algorithm.\n");
    srand((unsigned) time(NULL));
    assignValues();
    mallocArray();
    generateGenerations();
    showMinResult();
    freeArrays();
}

/**
 * This function print out the route with the minimal cost genetic algorithm generates
 * and the minimal cost genetic algorithm generates
 */
void showMinResult(){
    printf("The route with minimal cost for genetic algorithm for %d cities is: ",numOfCity);
    printTour(minRoute,numOfCity + 1);
    printf("With the minimal cost %f\n",minRouteCost);
}

/**
 * This function free up the memory of the arrays had been dynamically allocated
 *
 */
void freeArrays(){
    free(minRoute);
    free(currentTour);
    free(generation);
    free(costArrays);

}


/**
 * This function generates number of generations user entered
 * The first generation will contain only permutations
 * from the second permutation, the generation will contain 2 elites
 * #numOfPermutationPerGeneration permutations, and #numOfMutationPerGeneration mutations
 */
void generateGenerations(){
    addTourToGeneration(currentTour);   //add the first tour into generation
    addToCostArray(currentTour);
    currentLine++;
    //generate first generation with #numOfTourEachGeneration individual
    addPermutationToGeneration(numOfTourEachGeneration);
    currentLine = 0;

    int i;

    //process the generation from second and to numOfGeneration
    for(i = 1; i < numOfGeneration; i++){

        findTwoElites();
        addElitesToGeneration();
        copyRoute(currentTour,generation[0]);   //permute based on elite
        addMutationToGeneration();
        addPermutationToGeneration(numOfPermutationPerGeneration + 1);

        currentLine = 0;
    }



}

/**
 * This function swap the two index of the tour passed in
 * @param tourToSwap the int array to swap index
 * @param a and b are the two index to swap
 */
void swapping(int *tourToSwap,int indexA, int indexB){
    int temp = tourToSwap[indexA];
    tourToSwap[indexA] = tourToSwap[indexB];
    tourToSwap[indexB] = temp;

}

/**
 * This function will add permutation to generation by swapping cities
 * from right to left.
 *
 * @param n the number of permutation to add into generation
 */
void addPermutationToGeneration(long long int n){

     int m, k, p , q;
     long long int i;


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

       swapping(currentTour,m,k);

       p = m + 1;
       q = numOfCity-1;
       while(p < q)
       {
         swapping(currentTour,p,q);
         p++;
         q--;
       }
        addTourToGeneration(currentTour);
        addToCostArray(currentTour);
        currentLine++;
     }
}

/**
 * This function adds tour to generation
 * @param tourToAdd the int array to add into generation
 */
void addTourToGeneration(int *tourToAdd){
    int i;
    for(i = 0; i < numOfCity + 1; i++){
        generation[currentLine][i] = tourToAdd[i];
    }
}

/**
 * This function adds mutation into generation by randomly swap two cities in that array
 * If the array after swapping has lower cost, add this array into generation
 */
void addMutationToGeneration(){
    int i;
    int indexA = 0;
    int indexB = 0;

    double lastCost;
    int tempTour[numOfCity + 1];

    for(i = 0; i < numOfMutationPerGeneration; i++){
        indexA = randomCityIndex();
        do{
            indexB = randomCityIndex();
        }
        while(indexA == indexB);
        lastCost = costArrays[i];
        copyRoute(tempTour,generation[i]);
        swapping(tempTour,indexA,indexB);

        //if the swap makes the cost of that tour lower, add the new tour into generation
        if(getRouteCost(tempTour) < lastCost){
            addTourToGeneration(tempTour);
            addToCostArray(tempTour);
        }
            currentLine++;
    }

}
//void addNewPermutation(){
//    int i;
//    for(i = NUM_OF_ELITES + numOfMutationPerGeneration; i < numOfTourEachGeneration; i++){
//
//    }
//
//}

/**
 * This function adds two elites into the first two index of the generation
 */
void addElitesToGeneration(){

    //add two elites into the generation
    addTourToGeneration(elite1);
    addToCostArray(elite1);
    currentLine++;

    addTourToGeneration(elite2);
//    printf("add array below into cost Array: ");
//    printTour(elite2,numOfCity + 1);
    addToCostArray(elite2);
    currentLine++;


}

/**
 * This function finds the two lowest cost as two elites
 *
 */
void findTwoElites(){
    double min;
    double secMin;

    //if two elites has not been initialized
    if(elite1Cost == elite2Cost && elite2Cost == 0){
        min = costArrays[0];
        secMin = costArrays[1];
    }
    //if two elites has been initialized
    else{
        min = elite1Cost;
        secMin = elite2Cost;
    }

    int minIdx = 0;
    int secMinIdx = 0;

    int i;
    for(i = 0; i < numOfTourEachGeneration; i++){
        if(costArrays[i] <= min ){
            secMin = min;
            min = costArrays[i];

            secMinIdx = minIdx;
            minIdx = i;
        }
        else if(costArrays[i] >= min && costArrays[i] <= secMin){
            secMin = costArrays[i];

            secMinIdx = i;
        }
    }
//    elite1Index = minIdx;
//    elite2Index = secMinIdx;

//    printf("cost array : ");
//    for(i = 0; i < numOfTourEachGeneration; i++){
//        printf("%f \n",costArrays[i]);
//    }


    copyRoute(elite1,generation[minIdx]);
    copyRoute(elite2,generation[secMinIdx]);

    elite1Cost = min;
    elite2Cost = secMin;



//    printf("The first elite with cost %f, at index %d: ",elite1Cost,minIdx);
//    printTour(elite1,numOfCity + 1);

//    printf("The second elite with cost %f, at index %d: ",elite2Cost,secMinIdx);
//    printTour(elite2,numOfCity + 1);
}

/**
 * This function gets the cost of tour and return it
 * @param tour the int array to calculate cost
 * @return the routeCost double value of the total cost of this tour
 */
double getRouteCost(int *tour){
    double routeCost = 0;
    int i;
    for(i = 0; i < numOfCity ; i++){
        routeCost += getCost(tour[i],tour[i+1]);
        }
    return routeCost;
}

/**
 * This function adds a cost of a tour into the cost array
 * @param tourToAdd the cost of that tour to add into cost array
 */
void addToCostArray(int *tourToAdd){
    double routeCost = getRouteCost(tourToAdd);

    costArrays[currentLine] = routeCost;

    assignMin(tourToAdd,routeCost);
}


/**
 * This function assign the minimal cost and the tour with minimal cost
 * into minRouteCost and minRoute if such cost is less than current minRouteCost
 */
void assignMin(int *tourToAdd,double routeCost){
    if(minRouteCost <= 0 || minRouteCost > routeCost){
        minRouteCost = routeCost;
        copyRoute(minRoute,tourToAdd);
//        printf("Assign route : ");
//        printTour(tourToAdd,numOfCity + 1);
//        printf("Now the min route is ");
//        printTour(minRoute,numOfCity + 1);
    }
}

/**
 * This function print out the array passed in
 * @param tour the int array to print
 * @param size the size of the array to print
 */
void printTour(int *tour, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d ",tour[i]);
    }
    printf("\n");
}

/**
 * This function print out the current generation
 */
void printGeneration(){
    int j,k;
    for(j = 0; j < numOfTourEachGeneration; j++){
        printf("#%d tour: ",j);
        for(k = 0; k < numOfCity + 1; k++){
            printf("%d ", generation[j][k]);
        }
        printf("cost: %f\n",costArrays[j]);
    }
    printf("\n");
}

/**
 * This function copy one route to another route
 * @param destination the int array copy to
 * @param source the int array copy from
 */
void copyRoute(int *destination, int *source){
    int i;
    for(i = 0; i < numOfCity + 1; i++){
        destination[i] = source[i];
    }
}

/**
 * This function generates a random number for choosing a city
 * to swap in mutation function
 * @return randomNum the index to swap
 *
 */
int randomCityIndex(){

    //generate a random number between [1,numOfCity];
    int randomNum = rand() % (numOfCity - 1) + 1;
//    printf("Generate for city index %d\n",randomNum);
    return randomNum;
}
/**
 * This function generates a random number for choosing a tour
 * to swap in generation. This function will be called in mutation function
 * @return randomNum the index to swap
 *
 */
int randomTourIndex(){

    //generate a random number between [0,numOfnumOfTourEachGeneration]
    int randomNum = rand() % (numOfTourEachGeneration);
    printf("Generate for Tour index %d\n",randomNum);
    return randomNum;
}

/**
 * This function generates a random number for choosing a elite
 * @return randomNum the index of elite (0-1)
 *
 */
int randomEliteIndex(){

    int randomNum = rand() % (NUM_OF_ELITES);
    printf("Generate for elite index %d\n",randomNum);
    return randomNum;
}

/**
 * This function returns a factorial of a number by recursive calling
 * @param num the number to calculate factorial
 * @return the factorial of the number
 */
long long int fact(long long int n){
    if(n <= 1){
        return 1;
    }
    return n * fact(n-1);
}

/**
 * This function get the minimal cost of the genetic algorithm
 *
 */
double getALCost(){
    return minRouteCost;
}

