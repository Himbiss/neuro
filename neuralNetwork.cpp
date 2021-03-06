#include <cmath>
#include <stdio.h>
#include <cstdlib>

#include "neuralNetwork.h"

using namespace std;

// constructor
neuralNetwork::neuralNetwork(int nI, int nH, int nO) : nInput(nI), nHidden(nH), nOutput(nO)
{
  // initialize neurons
  inputNeurons = new( double[nInput+1] );
  for (int i = 0; i < nInput; i++) {
  	inputNeurons[i] = 0;
  }

  hiddenNeurons = new( double[nHidden+1] );
  for (int i = 0; i < nHidden; i++) {
  	hiddenNeurons[i] = 0;
  }

  outputNeurons = new( double[nOutput+1] );
  for (int i = 0; i < nOutput; i++) {
  	outputNeurons[i] = 0;
  }
   
  // bias neuron
  inputNeurons[nInput] = -1;
  
  // initialize weight tables
  wInputHidden = new( double*[nInput+1] );
  for (int i = 0; i <= nInput; i++) {
  	wInputHidden[i] = new( double[nHidden] );
        for (int j = 0; j < nHidden; j++) {
        	wInputHidden[i][j] = 0;
        }
  }  

  wHiddenOutput = new( double*[nHidden+1] );
  for (int i = 0; i <= nHidden; i++) {
        wHiddenOutput[i] = new( double[nOutput] );
         for (int j = 0; j < nOutput; j++) {
                wHiddenOutput[i][j] = 0;	
         }
  }
  
  // initialize weights
  initializeWeights();
}

// destructor
neuralNetwork::~neuralNetwork()
{
  delete[] inputNeurons;
  delete[] hiddenNeurons;
  delete[] outputNeurons;

  for (int i = 0; i <= nInput; i++) {
  	delete[] wInputHidden[i];
  }
  delete[] wInputHidden;

  for (int j = 0; j <= nHidden; j++) {
        delete[] wHiddenOutput[j];
  }
  delete[] wHiddenOutput;
}

void neuralNetwork::initializeWeights()
{
  double rangeH = 1/sqrt( (double) nInput );
  double rangeO = 1/sqrt( (double) nHidden );

  for (int i = 0; i <= nInput; i++) {
        for (int j = 0; j < nHidden; j++) {
             wInputHidden[i][j] = (( (double)(rand()%100)+1 )/100 * 2 * rangeH) - rangeH;                	
        }
  }
  
  for (int i = 0; i <= nHidden; i++) {
        for (int j = 0; j < nOutput; j++) {
        	wHiddenOutput[i][j] = (( (double)(rand()%100)+1)/100 * 2 * rangeO) - rangeO;
        }
  }
}

void neuralNetwork::epoch( double* pattern )
{
   for (int i = 0; i < nInput; i++) {
        inputNeurons[i] = pattern[i];	
   }

   // hidden layer values
   for (int j = 0; j < nHidden; j++) {
   	hiddenNeurons[j] = 0;

        for (int i = 0; i <= nInput; i++) {
               hiddenNeurons[j] += inputNeurons[i] * wInputHidden[i][j];
               hiddenNeurons[j] = sigmoidActivation( hiddenNeurons[j] );	
        }
   }

   for (int k = 0; k < nOutput; k++) {
        outputNeurons[k] = 0;
   
        for (int j = 0; j <= nHidden; j++) {
        	outputNeurons[k] += hiddenNeurons[j] * wHiddenOutput[j][k];
                outputNeurons[k] = sigmoidActivation( outputNeurons[k] );
        }		
   }
}

int* neuralNetwork::epochPattern( double* pattern )
{
  epoch(pattern);

  int* results = new int[nOutput];
  for (int i = 0; i < nOutput; i++) {
  	results[i] = outputNeurons[i];
        printf("%g\n",outputNeurons[i]);
  }
  return results;
}

double neuralNetwork::sigmoidActivation( double t )
{
  return 1/(1+exp(-t)); 
}
