/*
 * Network.h
 *
 *  Created on: 10.10.2017
 *      Author: SteveMaassen
 */

#include <vector>
#include "Neuron.h"
#include "XORTrainingData.hpp"



#ifndef NETWORK_H_
#define NETWORK_H_
using namespace std;
namespace NN {

class Network {
public:
	Network(vector<unsigned> const topology);
	virtual ~Network();

	void feedForward(vector<double> const inputValues, bool verbose=false);
    void backPropagation(vector<double> const targetValues);
	void showResults(vector<double> const targetValues);
    void train(const vector<data>& trainData, bool verbose=false , double learnRate=0.2, double alpha=0.2);

private:
	vector<unsigned> topology_;
	vector<Layer> layers_;
    double overError;

};

} /* namespace MyOwnNameSpace */

#endif /* NETWORK_H_ */
