#include <vector>
#include <random>


/*
 * Neuron.h
 *
 *  Created on: 10.10.2017
 *      Author: SteveMaassen
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <vector>



struct Connection
{
    double weight;
    double deltaWeight;
};

namespace NN {

class Neuron;

typedef std::vector<Neuron> Layer;

using namespace std;

class Neuron {
public:
	Neuron(unsigned numOutputs,unsigned id);
	virtual ~Neuron();
	void feedForward(const Layer &prevLayer);
	double getOutput() const {return outputValue_;};
	void setOutputMan(double value) {outputValue_=value;};
    void calcOutputLayerGrad(double const target);
    void calcHiddenLayerGrad(Layer & nextLayer);
    void updateInputWeights(Layer & prevLayer);

private:
	std::vector<Connection> outputWeights_;
	double outputValue_;
    double biasterm_;
    double deltaBiasterm_;
    double gradient_;
	unsigned id_;
	static double transferFct(double x);
    static double transferFctDer(double x);
    static double learnRate_;
    static double alpha_;
};

    



} /* namespace MyOwnNameSpace */



#endif /* NEURON_H_ */




