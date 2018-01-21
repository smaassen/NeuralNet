//
//  XORTrainingData.hpp
//  NeuralNet
//
//  Created by Steve Maassen on 15.10.17.
//  Copyright © 2017 Steve Maassen. All rights reserved.
//

#ifndef XORTrainingData_hpp
#define XORTrainingData_hpp

#include <vector>


using namespace std;

namespace NN {
    
    struct data {
        vector<double> inputs;
        vector<double> outputs;
    };
    
    class XORTrainingdata {
    public:
        XORTrainingdata(unsigned N);
        //virtual ~XORTrainingdata();
        
        void createData();
        vector<data> getData() const {return trainData;};
        void showData();
        
    private:
        unsigned N;
        double XOR(double a, double b);
        vector<data> trainData;
    };
}


#endif /* XORTrainingData_hpp */
