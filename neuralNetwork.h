/*
  neuralNetwork.h
*/
#ifndef __neuralNetwork_H_INCLUDED__
#define __neuralNetwork_H_INCLUDED__

class neuralNetwork
{
private:
  int nInput, nHidden, nOutput;
  
  //neurons
  double* inputNeurons;
  double* hiddenNeurons;
  double* outputNeurons;
 
  //weights
  double** wInputHidden;
  double** wHiddenOutput;

  //methods
  void initializeWeights();
  void epoch( double* pattern );
  double sigmoidActivation( double t );
public:
  neuralNetwork(int numInput, int numHidden, int numOutput);
  ~neuralNetwork();
  int* epochPattern( double* pattern );
};

#endif
