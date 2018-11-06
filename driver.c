/** Student Name: Yizhi Hu
 *  File Name: driver.c
 *  Assignment: project #3
 *
 *  This file is going to implement the high level implementation of finding
 *  the optimal solution from brute force and best solution from genetic algorithm
 */
#include "bruteForce.h"
#include "geneticAlgorithm.h"
#include "Input.h"
#include "timer.h"
#include "Matrix.h"

/**
 * This function implements the high level requirement of TSP
 */
void startTSP(){
    double costBF = 0;
    double costGA = 0;


    loadMatrix();
    getInputs();

    startTime();
    startBruteForce();
    endTime();
    costBF = getBFCost();

    startTime();
    startGeneticAlgorithm();
    endTime();
    costGA = getALCost();

    printf("genetic algorithm provides %.3f%c of optimal solution.\n",(costGA/costBF) * (double)PERCENTAGE,'%');
}
