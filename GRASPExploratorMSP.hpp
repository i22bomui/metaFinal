#ifndef		__GRASP_EXPLORATOR_MSP__
#define		__GRASP_EXPLORATOR_MSP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "Miscelanea.hpp"

#include "SolutionMSP.hpp"
#include "SolGeneratorMSP.hpp"
#include "neighborOperatorMSP.hpp"
#include "neighborExploratorMSP.hpp"
#include "localSearchMSP.hpp"

#include <iostream>

#define GP 4	//Numero de subsoluciones a generar para generar una solucion

using namespace std;



class GRASPExploratorMSP{



	private:

		localSearchMSP _busquedaLocal;


	public:


		GRASPExploratorMSP(){};
		GRASPExploratorMSP(const localSearchMSP &busquedaLocal){

			_busquedaLocal = busquedaLocal;
		}


		int mejorCandidato(const vector < vector <int> > &clauses, vector <SolutionMSP> &candidatos){


			int posMejor = 0;
			int fitnessMejor = candidatos[0].getFitness();

			for(int i = 1; i < candidatos.size(); i++){


				if( candidatos[i].getFitness() > fitnessMejor ){

					posMejor = i;
					fitnessMejor = candidatos[i].getFitness();
				}

			}

		  return posMejor;
		}



		SolutionMSP greedyConstructor(const int &problemSize){



			SolutionMSP solucionFinal(problemSize), randomSol;
			vector <SolutionMSP> aux;

			SolGeneratorMSP g;

			int pos1, pos2, i = 0;


			//Creamos la solucion aleatoria en i partes	----> Pseudo GREEDY
			while(i < (problemSize / GP)){

				pos1 = i * (problemSize / GP);
				pos2 = (i + 1) * (problemSize / GP);

				while(aux.size() < 10){	//Creamos una lista con 10 subsoluciones


					randomSol = g.randomSolutionGenerator(problemSize, pos1, pos2);
					randomSol.setAptitude(_busquedaLocal.getOperator().getClauses());
					aux.push_back(randomSol);
				}


				int posMejor = mejorCandidato(_busquedaLocal.getOperator().getClauses(), aux);

				for(int j = pos1; j < pos2; j++)

					solucionFinal.setSolution(j, aux[posMejor].getSolution(j));


				aux.clear();

				i++;
			}


			solucionFinal.setAptitude(_busquedaLocal.getOperator().getClauses());

		  return solucionFinal;
		}



		SolutionMSP GRASP(const int &problemSize){


			SolutionMSP actualSolution, currentSolution, bestSolution = greedyConstructor(problemSize);
			double actualFitness, bestFitness = bestSolution.getFitness();


			for(int i = 0; i < 100; i++){

//				cout << "Iteracion: " << i << endl;
				currentSolution = greedyConstructor(problemSize);
				_busquedaLocal.localOptimum(currentSolution, actualSolution, actualFitness);

				if(actualFitness > bestFitness){

					bestSolution = actualSolution;
					bestFitness = actualFitness;
				}
			}

		  return bestSolution;
		}




};


#endif
