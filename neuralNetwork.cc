
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int countNeurals = 2;
// how much sleep , how good is weather  
vector<vector<double>> weights{{.7, .8}, {.3, .4}};
// generally dont wanna run 
vector<double> biases {-1, 3};


vector<double> inputs{.5, .9};


auto relu ( double outputWithBias) {
    return max( outputWithBias, (double)0);
}

vector<double> neuralNetLayer(vector<double> inputs, vector<vector<double>> weights, vector<double> biases) {
    //
    int count = weights.size();

    vector<double> output = biases; 

    for(int i = 0; i < count; i ++)
    {
        for (int  j =0 ; j < inputs.size(); j ++)
            output[i] += weights[i][j] * inputs[j]; 
         
        output[i] = relu(output[i]);
    }

    return output;
}

int main () {
    auto ans =  neuralNetLayer(inputs, weights, biases);
    for(auto i  :ans) cout << i << " ";
    cout << endl;

}