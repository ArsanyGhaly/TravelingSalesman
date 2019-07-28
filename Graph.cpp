#include "Graph.h"
using namespace std;


Graph::Graph(const int &s){
   
   //do this multiplication once
   int matrix = (s * s);
   
   //assign the values to the adj matrix 
   edgeMatrix = new double[matrix];
   size = s;
   
   //initialize the matrix with all -1
   for (int i = 0; i < matrix; ++i){
      
      edgeMatrix[i] = -1.0;
      
   }
   srand(static_cast<unsigned>(time(NULL)));
}
   
Graph::~Graph(){
      
   delete [] edgeMatrix;
      
}

void Graph::addVertex(const string &newver){
	//check for duplicate 
	if(checkForDuplicate(newver)){
		cout <<"This Gene is already there";
	}
	
  gene *newgene = new gene;
	
	newgene->name = newver;
  newgene->index = static_cast<int>(genes.size());

  genes.push_back(newgene);

 }


 void Graph::addEdge(const string &start,const string &end, double weight){
	//get the positionstions of the start and the end points
	int Sindex = get_position(start);
	int Eindex = get_position(end);
 	
 	//validations
 	if (start == end){  
	cout << "The strat is the same as the end.";     
   }

   //add the wight to the matrix (convert to array)
	edgeMatrix[(Sindex * size) + Eindex] = weight;
 }
  
bool Graph::checkForDuplicate(const string &key){
   
   for (size_t i = 0; i < genes.size(); ++i){
      
      if (genes[i]->name == key) 
        return 1;
      
   }
   
   return 0;
 }

string Graph::get_gene(int pos){
	return genes.at(pos)->name;
}

int Graph::get_position(string vertex){
 	for (size_t i = 0; i< genes.size(); ++i)
	{
		if (genes[i]->name == vertex)
		{
			return i;
		}
	}
	return -1;
 }
/*
 void Graph::printGraph(){
   
   for (size_t i = 0; i < genes.size(); ++i){
      
      gene *item = genes[i];
      
      cout << "Gene name: " << item->name << endl;
      cout << "Edges:" << endl;
      
      for (size_t j = 0; j < size; ++j){
         
         double w = edgeMatrix[(i * size) + j];
         
         //check for empty
         if (w != -1){ 
            cout << genes[i]->name << " " << genes[j]->name << " " << w << endl;
         }
         
      }
      
      cout << endl;
      
   }}
   */

 


int Graph::Fitness(Chromosome chrom){
   
   int fitness = 0;
   
   for (size_t i = 0; i < (chrom.genes.size() - 1); ++i){
      
      fitness += edgeMatrix[(chrom.genes[i]->index * size) + chrom.genes[i + 1]->index];
      
   }
   
   //add the start point back
   fitness += edgeMatrix[chrom.genes[0]->index];
   //add the end point back
   fitness += edgeMatrix[(chrom.genes[chrom.genes.size() - 1]->index * size)];
   
   // since it is a maximations problem *-1
   return (-1 * fitness); 
}

Graph::solution  Graph::geneticTravellingSalesman(const int &populationSize, const int &numGenerations){
  
   //prepare the current genration 
   //create the first generation
   vector<Chromosome> *currentGeneration = new vector<Chromosome>(populationSize);
   
   //create the next generation
   vector<Chromosome> *nextGeneration = NULL;
   
   //copy 
   for (size_t i = 0; i < populationSize; ++i){
      
      //copy the genes, and remove the first gene
      vector<gene*> temp(genes);
      temp.erase(temp.begin()); 
      
      //popluations random permurtions of chromsomes 
      random_shuffle(temp.begin(), temp.end());
      (*currentGeneration)[i].genes = temp;

      //set the fitness of the cuurent  
      (*currentGeneration)[i].fitness = Fitness((*currentGeneration)[i]);
      
   }
   //-------------------------------------------------------------------------------- 
   //genrate the next genrations 
   
   //sort generation in decending order based on fitness
   sort(currentGeneration->begin(), currentGeneration->end(),Chromosome_sort);
   
   for (size_t i = 1; i < numGenerations; ++i){
      
      //cout << "G: " << i + 1 << " of " << numGenerations << endl;
      
      //create the new genration 10-4-2 method 
      nextGeneration = new vector<Chromosome>(currentGeneration->begin(), currentGeneration->begin() + 10);
      
      //select the best 10 at rondom from the current
      while (nextGeneration->size() < populationSize){
         
         vector<Chromosome> *t = new vector<Chromosome>;
         
         //get the first rondom 10
         for (size_t j = 0; j < 10; ++j){ 
            
            t->push_back((*currentGeneration)[rand() % currentGeneration->size()]);
            
         }
         
         //sort the 10 on desanding order
         sort(t->begin(), t->end(),Chromosome_sort);
        
         //select the best random  4 of the 10
         vector<Chromosome> *t2 = new vector<Chromosome>(t->begin(), t->begin() + 4);
         delete t;
         
         int r1 = rand() % 4;

         //select the 2 to cross over 
         Chromosome c1 = (*t2)[r1];
         t2->erase(t2->begin() + r1); 
         
         Chromosome c2 = (*t2)[rand() % 3];
         r1 = rand() % c1.genes.size(); 
         
         //the cross over process
         nextGeneration->push_back(crossover(c1, c2, r1));
         nextGeneration->push_back(crossover(c2, c1, r1));
         
         delete t2;
         
      }
      
      //free the memory 
      vector<Chromosome> *temp = currentGeneration;
      currentGeneration = nextGeneration;
      delete temp;
      
      //sort them 
      sort(currentGeneration->begin(), currentGeneration->end(),Chromosome_sort);
      
   }
   
   // get the solution 

   return solve((*currentGeneration)[0]);
   
}


Graph::Chromosome Graph::crossover(const Chromosome &c1, const Chromosome &c2,  const int &crossoverPoint){
   
   Chromosome kid;
   
   //generate the new kid (the first is above the cross over point
   for (size_t i = 0; i < crossoverPoint; ++i){
      
      kid.genes.push_back(c1.genes[i]);
      
   }
   
   //(the second is blew the cross over point
   for (size_t i = crossoverPoint; i < c2.genes.size(); ++i){
      
      kid.genes.push_back(c2.genes[i]);
      
   }
   
   //-----------------------------------------------------------
   //to solve the problem of muliple representations 

   //create a list of all cities
   vector<gene*> all_cities;
   
   //check for duplicate cities
   for (size_t i = 0; i < kid.genes.size(); ++i){
      
      all_cities.push_back(kid.genes[i]);
      
      for (size_t j = (i + 1); j < kid.genes.size(); ++j){
         
         //check for dublications
         if (kid.genes[i]->index == kid.genes[j]->index){   
            kid.genes.erase(kid.genes.begin() + j);  
         }
         
      }
      
   }
   
   //now instead the dublication that already gone add the not used
   while (kid.genes.size() < (genes.size() - 1)){
      
      //find the gene that is now been used and add it to the list
      for (size_t i = 1; i < genes.size(); ++i){
         
         if (find(all_cities.begin(), all_cities.end(), genes[i]) == all_cities.end()){
            
            kid.genes.push_back(genes[i]);
            
         }
         
      }
      
   }
   
   // get the solution the fitness (the path cost of the kid)
   kid.fitness = Fitness(kid);
   return kid;
   
}


Graph::solution Graph::solve(const Chromosome &kid){
  //string temp,temp1,temp2,temp3;
  vector<gene*> answer;
  Graph::solution s;

  
  //push the first step
  //temp = genes[0]->name;
  //cout << temp <<endl;
  //solution.push_back(temp);

 answer.push_back(genes[0]);

  //push the entrie steps
  /*for (size_t i = 0; i < kid.genes.size(); ++i){
      temp1=  (kid.genes[i]->index + 1) + " : " + kid.genes[i]->name;
      cout << temp1<<endl;
      solution.push_back(temp1);
   }
*/
   for (size_t i = 0; i < kid.genes.size(); ++i){
      answer.push_back(kid.genes[i]);    
   }

   answer.push_back(genes[0]);
   //push the last step
   /*
   temp3 = "Cost: " + (-1 * kid.fitness);
   cout << temp3 <<endl;
   solution.push_back(temp3);
 */
   s.genes = answer;
   s.fitness =(-1 * kid.fitness);
  
   return s;
   
}


bool Graph::Read_vertices(const char* file_name)
{
    ifstream inFile;
  
  inFile.open(file_name);
    
    if (!inFile)                    
    {
        return false;
    }

    while(!inFile.eof())
  {
        string v;
        getline(inFile,v, '\n');

    this->addVertex(v);
    }

    inFile.close();
    return true;

}
  
bool Graph::Read_edages(const char* file_name){
    ifstream inFile;
  inFile.open(file_name);
    
    if (!inFile){                 
        return false;
    }
    
    while(!inFile.eof())
  {
        string v1, v2, w = "0";
        
        getline(inFile, v1, ' ');
        getline(inFile, v2, ' ');
        getline(inFile, w, '\n');

        this->addEdge(v1, v2, atoi(w.c_str()));
    }
    inFile.close();
    return true;

}


