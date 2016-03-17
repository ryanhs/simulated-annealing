#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#include "sa.h"



/*
 * definition
 */
char seed[] = "abcdefghijklmnopqrstuvwxyz ";
char target[] = "astari ghaniarti";


/*
 * global variable
 */
char *solution;

/*
 * function scope
 */
void *generate_solution(){
	int smax = sizeof(seed);
	int tmax = sizeof(target);
	char *solution = malloc(tmax * sizeof(char));
	
	srand(time(0));
	
	int i;
	for(i = 0; i < tmax - 1; i++){
		int random_char = rand() % (smax - 1);
		sprintf(solution, "%s%c", solution, seed[random_char]);
	}
	
	return (void *) solution;
}
void *modifier(void *solution){
	int smax = sizeof(seed);
	int tmax = sizeof(target);
	double result = 0;
	
	char *str_solution = (char *) solution;
	
	int modif_index = rand() % (tmax - 1);
	int random_char = rand() % (smax - 1);
	str_solution[modif_index] = seed[random_char];
	
	return (void *) str_solution;
}
double evaluator(void *solution){
	int smax = sizeof(seed);
	int tmax = sizeof(target);
	double result = 0;
	
	char *str_solution = (char *) solution;
	int i;
	for(i = 0; i < tmax - 1; i++){
		if(str_solution[i] == target[i]){
			result += (double) 1 / ((double) tmax - 1);
		}
	}
	
	return result;
}

// make a better output :-)
void *output_current_result(int iterator, double temperature, void *solution, double result){
	fflush(stdout);
	printf("#%d temp: %.2fᵒ solution: %s (%.3f)\r", iterator, temperature, (char *) solution, result); // use \r instead of \n
	nanosleep((const struct timespec[]){{0, 300 * 100000L}}, NULL);
}

/*
 * main
 */
int main(){
	
	simulated_annaeling_struct sa;
	sa.generate_solution = generate_solution;
	sa.modifier = modifier;
	sa.evaluator = evaluator;
	sa.output_current_result = output_current_result;
	sa.temperature = 1000;
	
	simulated_annaeling_algorithm(&sa);


	// clean up
	free(solution);
	
	printf("\n");
	return 0;
}
