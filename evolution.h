#ifndef evolution
#define evolution

#include <assert.h>     // assert
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <algorithm>    // std::sort

class individual
{
public:
    float cost_total;

    virtual void sum_total_cost() = 0;
    virtual void print()
    {
        std::cout << "This individual class does not have print() overriden" << std::endl;
    }
};


template <typename T_individual, typename T_cost_function, typename T_mut_function>
class population
{
private:
    T_cost_function cost_function;
    T_mut_function mut_function;

public:
    std::vector<T_individual> individuals;

    // Generate population of size 'n'
    population(int pop_size, T_cost_function cost_fun, T_mut_function mut_fun)
    {
        individuals = std::vector<T_individual>(pop_size);
        cost_function = cost_fun;
        mut_function = mut_fun;
    }

    // Print each individual in population
    void print()
    {
        for (auto& ind : individuals)
        {
            ind.print();
        }
    }

    // Indexing operator for population
    T_individual& operator[](size_t i)
    {
        return individuals[i];
    }

    // Evaluate each individual in population - Args are specific to individual's cost function
    template <typename... Args>
    void evaluate(Args &...args)
    {
        for (auto& ind : individuals)
        {
            cost_function(ind, args...);
        }
    }

    // Sort population individuals by their total_cost
    void sort()
    {
        std::sort(individuals.begin(), individuals.end(), [](const T_individual& a, const T_individual& b)
            { return a.cost_total < b.cost_total; });
    }

    // Populate the population with 'n' best individuals
    void keep_n_individuals(int n)
    {
        assert(0 < n);
        for (int i = 0; i < individuals.size(); i++)
        {
            individuals[i] = individuals[i % n];
        }
    }

    // Populate the population with 'p' percentage of best individuals
    void keep_n_individuals(float p)
    {
        int n = (int)(individuals.size() * p);
        keep_n_individuals(n);
    }

    // Mutate each individual given probabilty and magnitude
    template <typename... Args>
    void mutate(Args &...args)
    {
        for (auto& ind : individuals)
        {
            mut_function(ind, args...);
        }
    }
};

#endif
