#ifndef GRAPH


#include <iostream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>


using namespace std;

class Graph {
   
private:
   //using the matrix 
   int size;
   double *edgeMatrix;
    

   //Store the gene info(City)
   struct gene {
      int index;
      string name;    
   };
   
   //Store The Chromosome
   struct Chromosome {
      vector<gene*> genes;
      int fitness;
      
   };
   
   vector<gene*> genes;
   
   //helpers 
   int Fitness(Chromosome chrom);
  
   Chromosome crossover(const Chromosome &c1, const Chromosome &c2,  const int &crossoverPoint);
   
   static bool Chromosome_sort(const Chromosome &c1, const Chromosome &c2){
   return (c1.fitness > c2.fitness);
   };
   
   
public:
   //contructors 
   Graph(const int &s);
   ~Graph();
   
   //store the solution
   struct solution {
      vector<gene*> genes;
      int fitness;
   };

   //add adage and ver
   void addVertex(const string &newver);
   void addEdge(const string &start,const string &end, double weight);
   
   //get by position and by string  
   string get_gene(int pos);
   int get_position(string vertex);
   bool checkForDuplicate(const string &key);
   
   //read the from files
   bool Read_vertices(const char* file_name);
   bool Read_edages(const char* file_name);

   //print the graph
  // void printGraph();

   

   
   solution solve(const Chromosome &kid);
   solution geneticTravellingSalesman(const int &populationSize, const int &numGenerations);
   
};

#endif
