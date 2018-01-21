/*
 * Neuron.cpp
 *
 *  Created on: 10.10.2017
 *      Author: SteveMaassen
 */

#include "Neuron.h"
#include <cmath>
#include <iostream>

using namespace std;
namespace NN {

double Neuron::learnRate_=0.15;
double Neuron::alpha_=0.5;

Neuron::Neuron(unsigned numOutputs,unsigned id) {
    biasterm_=rand()/RAND_MAX;
    deltaBiasterm_=0;
	outputValue_=0;
	this->id_=id;
	for (int i=0; i< numOutputs;i++){
		outputWeights_.push_back(Connection());
        outputWeights_.back().weight=(double)rand()/RAND_MAX;
        outputWeights_.back().deltaWeight=0;
	}
}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

void Neuron::feedForward(const Layer &prevLayer){
	double sum=0.0;
	for (int i=0;i<prevLayer.size();i++){
		sum+=prevLayer[i].outputValue_*prevLayer[i].outputWeights_[this->id_].weight;
	}
	sum=sum/(prevLayer.size()-1);
    sum+=biasterm_;
    outputValue_=transferFct(sum);
}

void Neuron::calcOutputLayerGrad(double const target){
    double delta=this->outputValue_-target;
    //gradient_= transferFctDer(outputValue_)*delta;
    gradient_= outputValue_*(1-outputValue_)*delta;
    //cout<<"output: "<< outputValue_ << " target: "<<target<<endl;
    //cout<<"delta: "<< delta << " gradient: "<<gradient_<<endl;
}

void Neuron::calcHiddenLayerGrad(Layer & nextLayer){
    double sum=0;
    for (int n=0; n< nextLayer.size(); n++){
        sum+=nextLayer[n].gradient_*outputWeights_[n].weight;
    }
    //gradient_=transferFctDer(outputValue_)*sum;
    gradient_=outputValue_*(1-outputValue_)*sum;
}
    
void Neuron::updateInputWeights(Layer & prevLayer){
    for (int n=0; n < prevLayer.size(); n++){
        //prevLayer[n].outputWeights_[this->id_].deltaWeight=
        //    (1-alpha_) * (learnRate_ * this->gradient_ * prevLayer[n].outputValue_)
        //   + alpha_ * prevLayer[n].outputWeights_[this->id_].deltaWeight;
        prevLayer[n].outputWeights_[this->id_].deltaWeight=
           (-learnRate_ * this->gradient_ * prevLayer[n].outputValue_)
           + alpha_ * prevLayer[n].outputWeights_[this->id_].deltaWeight;
        
        prevLayer[n].outputWeights_[this->id_].weight+=prevLayer[n].outputWeights_[this->id_].deltaWeight;
        //deltaBiasterm_=(1-alpha_) * (learnRate_ * this->gradient_ )
        //               + alpha_ * deltaBiasterm_;
        deltaBiasterm_= (-learnRate_ * this->gradient_ );
        //               + alpha_ * deltaBiasterm_;
        
        biasterm_+=deltaBiasterm_;
    }
}
    
double Neuron::transferFct(double x){
	return 0.5*(1+tanh(x/2));
}

double Neuron::transferFctDer(double x){
    return transferFct(x)*(1-transferFct(x));
}
    
} /* namespace MyOwnNameSpace */
