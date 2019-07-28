#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Graph.h"

using namespace std;

int stoi(const char *item){
 
 return static_cast<int>(atof(item));   
    
}

bool compareByLength(const Graph::solution  &a, const Graph::solution  &b)
{
    return a.fitness <  b.fitness;
}

int main(int argc, const char *argv[]){
   
   if (argc < 4){
      
      cerr << "Error: Too few arguments" << endl;
      exit(EXIT_FAILURE);
      
   }
   Graph *graph = new Graph(25);

   graph->Read_vertices(argv[1]);
   cout << "Genes have been readed..." << endl;
   graph->Read_edages(argv[2]);
   cout << "edages have been readed..." << endl;
   //graph->printGraph();
  
   Graph::solution solution;
   vector<Graph::solution> best;

   cout<< "run suveral solutiones and use the lowest cost" <<endl;
   for (int i=0;i<=15;i++){
          solution= graph->geneticTravellingSalesman(stoi(argv[3]), stoi(argv[4]));
          best.push_back(solution);
          cout <<solution.fitness<<endl;
   
   }


  sort(best.begin(), best.end(), compareByLength);
   cout <<"the best cost is:"<<best[0].fitness<<endl;
   
   cout <<"the path of the best cost" <<endl;
  for (int i =0; i<=best[0].genes.size();i++){
   cout <<best[0].genes[i]->index << " : " << best[0].genes[i]->name <<endl;
  }

   delete graph,solution, best;

   return EXIT_SUCCESS;
   

}
