#include "Network.h"
#include "XORTrainingData.hpp"
//using namespace NN;


int main() {
    
    // Create Training Data
    NN::XORTrainingdata myTrainingData(50000);
    myTrainingData.createData();
    //myTrainingData.showData();
    vector<NN::data> myData =myTrainingData.getData();
    
    
    
    
    

	//Create network
	vector<unsigned> myTopology;
	myTopology.push_back(2);
	myTopology.push_back(20);
    myTopology.push_back(10);
    myTopology.push_back(1);

	NN::Network myNetwork(myTopology);

	//Train Network
    myNetwork.train(myData);

	return 0;
}
