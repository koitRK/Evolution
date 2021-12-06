#include "evolution.h"
#include <stdlib.h> // rand()


/* Create your own class for individuals with custom parameters and methods. Must derive from class 'individual' */
class individual_A : public individual
{
private:
    /* USER CODE: PRIVATE MEMBERS - START */
    /* USER CODE: PRIVATE MEMBERS - END */
public:
    /* USER CODE: PUBLIC MEMBERS - START */

    // Parameters to be optimized/mutated
    float a;
    float b;
    // Costs (cost_total in baseclass is used for evaluation)
    float cost_a;
    float cost_b;

    /* USER CODE: PUBLIC MEMBERS - END */
    /* You can add custom methods, i.e "create_individual_with_random_values()" */

    /* Must define sum_total_cost() method that calculates total cost for an individual. total_cost is used in evaluation */
    void sum_total_cost()
    {
        /* USER CODE: COST_TOTAL - START */
        cost_total = cost_a + cost_b;
        /* USER CODE: COST_TOTAL - END */
    }

    void print()
    {    
        /* USER CODE: PRINT INDIVIDUAL - START */
        std::cout << "a: " << a << ", b: " << b << " cost_total: " << cost_total << std::endl;
        /* USER CODE: PRINT INDIVIDUAL - END */
    }
};


/* Create your own population class with custom parameters and methods. Must derive from class 'population' */
template <typename T_individual, typename T_cost_function, typename T_mut_function>
class population_A : public population<T_individual, T_cost_function, T_mut_function>
{
private:
    /* USER CODE: PRIVATE MEMBERS - START */
    /* USER CODE: PRIVATE MEMBERS - END */
public:

    population_A(int pop_size, T_cost_function cost_fun, T_mut_function mut_fun) : population<T_individual, T_cost_function, T_mut_function>(pop_size, cost_fun, mut_fun) {}
    
    /* USER CODE: PUBLIC MEMBERS - START */
    /* You can add custom methods, i.e "fill_population_with_random_individuals()"
    /* USER CODE: PUBLIC MEMBERS - END */
};


/* Example cost function. Custom arguments can be added - when creating population instance, function template must be changed accordingly */
void cost_function_A(individual_A& ind)
{
    ind.cost_a = (ind.a+2) * (ind.a+2);
    ind.cost_b = (ind.b-5.5) * (ind.b-5.5);
    ind.sum_total_cost(); // Always calculate total cost of the individual!
}


/* Example mutation function. Custom arguments can be added - when creating population instance, function template must be changed accordingly */
void mut_function_A(individual_A& ind)
{
    static float mutation_probability = 0.5;
    static float mutation_magnitude = 0.5;

    // Mutate parameter 'a'
    if (rand() / (float)RAND_MAX < mutation_probability){
        ind.a += ((rand() / (float)RAND_MAX < 0.5)*2-1) * mutation_magnitude;
    }

    // Mutate parameter 'b'
    if (rand() / (float)RAND_MAX < mutation_probability){
        ind.b += ((rand() / (float)RAND_MAX < 0.5)*2-1) * mutation_magnitude;
    }
}


int main()
{
    int population_size = 10;
    int num_generations = 15;

    /* Evaluation (cost_function) and mutation  (mut_function) can have custom arguments.
    For custom arguments to work, function's template must be changed accordingly when creating a population object.
    child_pop_class <child_ind_class, cost_fun_template, mut_function_template> my_pop(size, cost_function, mut_function); */
    
    // Create new population
    static population_A<individual_A, void (*)(individual_A&), void (*)(individual_A&)> my_pop(population_size, cost_function_A, mut_function_A);

    for (int i=0; i<num_generations; i++){

        // Mutate each individual
        my_pop.mutate();

        // Evaluate each individual
        my_pop.evaluate();

        // Sort individuals in population by cost_total
        my_pop.sort();
        
        // Keep only the best individuals and reproduce to fill the population
        my_pop.keep_n_individuals(2);

        // View this generation's best individual
        std::cout << "Generation " << i << " best individual: ";
        my_pop[0].print();
    }
    
    std::cout << "\nBest individual: ";
    my_pop[0].print();
    
    return 0;
}
