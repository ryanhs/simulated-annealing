#ifndef _SA
#define _SA

typedef struct{	
	void *(*generate_solution)();
	void *(*modifier)(void *);
	double (*evaluator)(void *);
	
	int iterator;
	double temperature;
	double result;
	void *solution;
} simulated_annaeling_struct;


void simulated_annaeling_algorithm(simulated_annaeling_struct *sa);

#endif
