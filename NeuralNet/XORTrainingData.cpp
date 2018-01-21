//
//  XORTrainingData.cpp
//  NeuralNet
//
//  Created by Steve Maassen on 15.10.17.
//  Copyright © 2017 Steve Maassen. All rights reserved.
//

#include "XORTrainingData.hpp"
#include <iostream>

namespace NN {
    XORTrainingdata::XORTrainingdata(unsigned N){
        this->N=N;
    }
    
    void XORTrainingdata::createData(){
        
        for (int n=0; n < N; n++) {
            // Set inputs randomly
            data currData;
            currData.inputs.push_back(rand() % 2);
            currData.inputs.push_back(rand() % 2);
            
            //calc output
            currData.outputs.push_back(XOR(currData.inputs[0],currData.inputs[1]));
            
            //add to training datad
            trainData.push_back(currData);
        }
        
    }
    
    double XORTrainingdata::XOR(double a, double b){
        if (a+b==0 || a+b==2 ) return 0; else return 1;
    }
    
    void XORTrainingdata::showData(){
        std::cout<< "Training Data:--------------"<<endl;
        for (int n=0; n< trainData.size();n++){
            std::cout<< "Input : ";
            for (int i=0; i< trainData[n].inputs.size();i++){
                std::cout<< " " << trainData[n].inputs[i];
            }
            
            std::cout<< "  Output : ";
            for (int i=0; i< trainData[n].outputs.size();i++){
                std::cout<< " " << trainData[n].outputs[i];
            }
            std::cout<<endl;
        }
    }
    
}
