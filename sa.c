#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#include "sa.h"

/*
typedef struct{	
	void *(*generate_solution)();
	void *(*modifier)(void *);
	double (*evaluator)(void *);
	
	int iterator;
	double temperature;
	double result;
	void *solution;
} simulated_annaeling_struct;
*/

void simulated_annaeling_algorithm(simulated_annaeling_struct *sa){
	srand(time(0));
	
	int init_temperature = sa->temperature;
	sa->solution = (void *) sa->generate_solution();
	sa->result = sa->evaluator(sa->solution);
	
	sa->iterator = 0;
	while(sa->temperature > 0 && sa->result != 1){
		sa->iterator++;
		
		char *new_solution = malloc(sizeof(sa->solution) * sizeof(char));
		strcpy(new_solution, sa->solution);
		
		new_solution = sa->modifier(new_solution);
		double new_result = sa->evaluator(new_solution);
		
		
		if(new_result > sa->result){
			free(sa->solution);
			sa->solution = new_solution;
			sa->result = new_result;
			printf("#%d temp: %.2fᵒ solution: %s (%.3f)\n", sa->iterator, sa->temperature, (char *) sa->solution, sa->result);
		}else{
			double d = new_result - sa->result;
			int e = floor(log2(-d/sa->temperature)) + 1;
			double r = (rand() % 1000) / 1000.0;
			
			free(new_solution);
			/*
			if(e > r){
				free(sa->solution);
				sa->solution = new_solution;
				sa->result = new_result;
			}else{
				free(new_solution);
			}
			*/
		}
		
		if(sa->iterator % 1000 == 0 && sa->result < 0.3){
			free(sa->solution);
			sa->solution = (void *) sa->generate_solution();
			sa->result = sa->evaluator(sa->solution);
			sa->temperature = init_temperature;
		}
		
		
		sa->temperature *= 0.9;
	}
	
}

