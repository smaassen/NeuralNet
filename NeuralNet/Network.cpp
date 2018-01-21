/*
 * Network.cpp
 *
 *  Created on: 10.10.2017
 *      Author: SteveMaassen
 */
#include <iostream>
#include "Network.h"

using namespace std;
namespace NN {

Network::Network(vector<unsigned> topology) {
    overError=0;
	this->topology_=topology;
	for (int i=0; i<topology.size();i++){
		// Create new layer
		layers_.push_back(Layer());
		cout << "Layer " << i <<" created with " << topology[i]<< " nodes." <<endl;

		// Check if bias node is added
		int biasNode=0;
		//if (i == 0 || i == topology.size()-1) biasNode=0; else biasNode=1;

		// Create the specified nodes in current layer
		for(int j=0; j<topology[i]+biasNode;j++){
			if (i==topology.size()-1){
				layers_.back().push_back(Neuron(0,j));
			} else {
				layers_.back().push_back(Neuron(topology[i+1],j));
			}
			cout << "Neuron "<< j <<" created created in layer " << i << endl;
		}
	}

}

Network::~Network() {
	// TODO Auto-generated destructor stub
}

void Network::feedForward(vector<double> const inputValues,bool verbose){
	if (verbose) cout << "Feed Forwarding: -------------" << endl;
	try {
		// Set input values
		for (int i=0; i < inputValues.size() ;i++){
			layers_[0][i].setOutputMan(inputValues[i]);
		}
		if (verbose) cout << "  Input values set" << endl;
	}
	catch (int e) {
		if (verbose) cout << "The input size does not match the size of first layer" << endl;
		throw e;
	}



	//Propagate through network
	for (int currL = 1 ; currL < layers_.size(); currL++){
		for (int n=0; n< layers_[currL].size(); n++){
			layers_[currL][n].feedForward(layers_[currL-1]);
		}
        
        if (verbose)  {
            cout << "  propagated layer "<< currL;
            for (int n=0; n< layers_[currL].size(); n++){
                cout << "   node " << n << " : " << layers_[currL][n].getOutput() << "   ";
            }
            cout << endl;
        }
	}
}
    
void Network::backPropagation(vector<double> const targetValues){
    // Calculate current overal Error
    overError=0;
    try {
        for (int n=0; n<layers_.back().size();n++){
            overError+=layers_.back()[n].getOutput()-targetValues[n] * layers_.back()[n].getOutput()-targetValues[n];
        }
        overError=sqrt(overError);
        overError/=(layers_.back().size()-1);
    }
    catch (int e) {
        cout << "number of target values does not match last layer" << endl;
        throw e;
    }
    
    // Outputlayer gradients
    for (int n=0; n< layers_.back().size(); n++){
        layers_.back()[n].calcOutputLayerGrad(targetValues[n]);
    }
    
    // Hidden Layer gradients
    for (unsigned long l=layers_.size()-2; l > 0; l--){
        for (int n=0; n< layers_[l].size();n++){
            layers_[l][n].calcHiddenLayerGrad(layers_[l+1]);
        }
    }
    
    // update weights for all layers
    for (unsigned long l=layers_.size()-1; l>0 ; l--){
        for (int n=0; n< layers_[l].size(); n++){
            layers_[l][n].updateInputWeights(layers_[l-1]);
        }
    }
    
    // update biasses
        // TO DO
    
}

void Network::showResults(vector<double> const targetValues){
	cout << "Results: --------------------" << endl;
	cout << "  Inputs: ";
	for (int n=0 ; n < layers_[0].size(); n++){
		cout << layers_[0][n].getOutput() << " ";
	}
	cout << endl;
    cout <<"  Output: t: ";
    for (int n=0 ; n < targetValues.size(); n++){
        cout << targetValues[n] << " ";
    }
    cout << "n: ";
	for (int n=0 ; n < layers_.back().size(); n++){
		cout << layers_.back()[n].getOutput() << " ";
	}
	cout<< endl;

}

    void Network::train(const vector<data>& trainData, bool verbose , double learnRate, double alpha){
        for(int d=0 ; d<trainData.size(); d++){
            feedForward(trainData[d].inputs);
            backPropagation(trainData[d].outputs);
            showResults(trainData[d].outputs);
        }
    }

} /* namespace MyOwnNameSpace */

