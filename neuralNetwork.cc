#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;


class Layer {
    vector<vector<double>> weights;
    vector<double> biases;

    static auto relu ( double outputWithBias) {
        return max( outputWithBias, (double)0);
    }

public:
    Layer(vector<vector<double>> weights, vector<double> biases) : weights(weights), biases(biases) {
        assert(weights.size() == biases.size() && !biases.empty());
    }

    vector<double> forward(vector<double> inputs) {
        //
        int countNeurons = this->weights.size();
        vector<double> output = this->biases; 

        for(int i = 0; i < countNeurons; i ++)
        {
            for (int  j =0 ; j < inputs.size(); j ++)
                output[i] += this->weights[i][j] * inputs[j]; 
            
            output[i] = relu(output[i]);
        }
        return output;
    }
};


class Network {

    vector<Layer> layers;

public:
    Network(vector<Layer> layers) : layers(layers) {
        assert(!layers.empty());
    }

    static Network loadNetwork(string filePath) {
        ifstream inFile(filePath);
        
        int countLayers;
        inFile >> countLayers;

        assert(countLayers > 0);

        vector<Layer> layers;

        for(int i = 0; i < countLayers; i ++) {
            //
            int neuronsCount, inputCount;
            inFile >> neuronsCount >> inputCount;

            vector<vector<double>> weights(neuronsCount, vector<double>(inputCount));
            vector<double> biases(neuronsCount);

            for(int j = 0; j < neuronsCount; j ++) {
                for(int k = 0; k < inputCount; k ++) {
                    inFile >> weights[j][k];
                }
            }
            for(int j = 0; j < neuronsCount; j ++) 
                inFile >> biases[j];


            layers.emplace_back(weights, biases);

        }


        return layers;
    }

    vector<double> forward(vector<double> inputs) {

        auto output = layers[0].forward(inputs);
        for(int i = 1; i < this->layers.size(); i++ ) {
            output = layers[i].forward(output);
        }
        return output;
    }

};


int main() {
    Network net = Network::loadNetwork("./input.txt");
    auto result = net.forward({.5, .9});
    for (auto v : result) cout << v << " ";
    cout << endl;
}