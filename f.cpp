#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Graph.h"

using namespace std;

vector<string> Read_vertices(const char* file_name)
{
  ifstream inFile;
  vector<string> genes_citites;
  string v;
   
   inFile.open(file_name);
    
    if (!inFile)                             
    {
      cout << "there is no file";
      
    }
    getline(inFile,v);
    while(!inFile.eof())
   {
        if (v.back() == '\r'){
            v.erase(v.length() - 1);
         }
        genes_citites.push_back(v);
        getline(inFile,v);
    }

    inFile.close();
    Graph *graph = new Graph(static_cast<int>(genes_citites.size()));
    return genes_citites;

}

void Read_edages(const char* file_name,Graph *g){
   ifstream inFile;
   inFile.open(file_name);
   string v;
    
    if (!inFile){                         
       cout << "there is no file" <<endl;
    }
   
    getline(inFile, v, ' ');
    while(!inFile.eof())
   {
        string s = v;
        
        getline(inFile, v, ' ');
        
        string e = v;
        
        getline(inFile, v);
        
        if (v.back() == '\r'){
         v.erase(v.length() - 1);
         
      }

        double w = atof(v.c_str());
        g->addEdge(s,e,w);
        getline(inFile, v, ' ');

    }
  

}

int main(int argc, const char *argv[]){
   
   if (argc < 4){
      
      cerr << "Error: Too few arguments" << endl;
      exit(EXIT_FAILURE);
      
   }
   vector<string> cities = Read_vertices(argv[1]);
   Graph *graph = new Graph(static_cast<int>(cities.size()));
   for (int i = 0; i < cities.size(); ++i){
      graph->addVertex(cities[i]);
   }

   cout << "Genes have been readed..." << endl;
   Read_edages(argv[2],graph);
  
   cout << "edages have been readed..." << endl;
   graph->printGraph();
   
   vector<string> solution=graph->geneticTravellingSalesman(stoi(argv[3]),stoi(argv[4]));
      for (size_t i = 0; i < solution.size(); ++i){
      
      cout << solution[i] << endl;
      
   }
   delete graph;

   return EXIT_SUCCESS;

}
