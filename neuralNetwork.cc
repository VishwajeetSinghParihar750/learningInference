
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// how much sleep , how good is weather  
vector<vector<double>> l1weights{{.7, .8}, {.3, .4}};
// generally dont wanna run 
vector<double> l1biases {-1, 3};

vector<vector<double>> l2weights{ {.2, .1}};
// generally dont wanna run 
vector<double> l2biases {2};


vector<double> inputs{.5, .9};


auto relu ( double outputWithBias) {
    return max( outputWithBias, (double)0);
}

vector<double> neuralNetLayer(vector<double> inputs, vector<vector<double>> weights, vector<double> biases) {
    //
    int countNeurons = weights.size();

    vector<double> output = biases; 

    for(int i = 0; i < countNeurons; i ++)
    {
        for (int  j =0 ; j < inputs.size(); j ++)
            output[i] += weights[i][j] * inputs[j]; 
         
        output[i] = relu(output[i]);
    }

    return output;
}

int main () {
    

    auto l1ans =  neuralNetLayer(inputs, l1weights, l1biases);
    auto l2ans = neuralNetLayer(l1ans, l2weights , l2biases);

    
    for(auto i : l2ans) cout << i << " ";
    cout << endl;

}