#include "main.h"
Network::Network(vector<int> params) {
    num_layers = params.size();
    sizes = params;
    for (int i = 1; i < num_layers; i++) {
        vector<double> biases_output;
        for (int j = 0; j < params[i]; j++) {
            biases_output.push_back(math.RandomGauss());
            }
        biases.push_back(biases_output);
    }
    for (int i = 1; i < num_layers; i++) {
        vector<vector<double>> weightNeurons;
        for (int j = 0; j < params[i]; j++) {
            vector<double> weightLines;
            for (int k = 0; k < params[i - 1]; k++) {
                weightLines.push_back(math.RandomGauss());
            }
            weightNeurons.push_back(weightLines);
        }
        weights.push_back(weightNeurons);
    }
}

vector<double> Network::calcLayerNeurons(vector<double> layerInput, vector<vector<double>> layerWeights, vector<double> layerBiases) {
    vector<double> outputNeurons;

    //Iterate over number of new neurons
    for (int i = 0; i < layerWeights.size(); i++) {
        //Array of current weights
        vector<double> currentWeights = layerWeights[i];

        //Define output neuron with bias value to not to have to add it later
        double outputNeuron = layerBiases[i];

        //Iterate over weights of current neuron
        for (int j = 0; j < currentWeights.size(); j++) {
            //Multiply every weight with the previous layer and add to output
            outputNeuron +=  currentWeights[j] * layerInput[j];
        }
        outputNeurons.push_back(math.Sigmoid(outputNeuron));
    }
    return outputNeurons;
}

vector<double> Network::feedForward(vector<double> input) {
    //Iterate over weights to iterate over layers to calculate
    for (int i = 0; i < weights.size(); i++) {
        vector<vector<double>> currentWeights = weights[i];
        vector<double> currentBiases = biases[i];
        //Calculating layer of neurons by setting a new input to the new layer
        input = calcLayerNeurons(input, currentWeights, currentBiases);
    }
    return input;
}
void pv(vector<double> vec) {
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << endl << endl;
}
void Network::stochasticGradientDescent(vector<pair<vector<double>,int>> trainingData, int miniBatchSize, int epochs, double learningRate) {
    int trainingDataSize = trainingData.size();
    //Loop wanted epochs times
    for (int i = 0; i < epochs; i++) {
        //Random shuffle of training data
        random_shuffle(begin(trainingData), end(trainingData));
        //Split trainingData in miniBatches
        vector<vector<pair<vector<double>,int>>> miniBatches;
        vector<pair<vector<double>,int>> tmpBatch;
        for (int j = 0; j < trainingDataSize; j++) {
            tmpBatch.push_back(trainingData[j]);
            //If miniBachSize is reached, push to miniBatches and clear tmpBatch 
            if ((j % miniBatchSize == 0 || j == trainingDataSize - 1) && j) {
                miniBatches.push_back(tmpBatch);
                tmpBatch.clear();
            }
        }
        //Applying function over each miniBatch
        int miniBatchesSize = miniBatches.size();
        for (int k = 0; k < miniBatchesSize; k++) {
            updateNetwork(miniBatches[k], learningRate);
            break;
        }
    }
    
}

void Network::updateNetwork(vector<pair<vector<double>,int>> miniBatch, double learningRate) {
    //Iterate over miniBatch
    for (int i = 0; i < miniBatch.size(); i++) {
        vector<double> grayScale = miniBatch[i].first;
        int grayScaleDigit = miniBatch[i].second;
        //Calculate each neron value
        vector<vector<double>> neuronValues;
        neuronValues.push_back(grayScale);
        for (int i = 0; i < weights.size(); i++) {
            vector<vector<double>> currentWeights = weights[i];
            vector<double> currentBiases = biases[i];
            //Calculating layer of neurons by setting a new input to the new layer
            grayScale = calcLayerNeurons(grayScale, currentWeights, currentBiases);
            neuronValues.push_back(grayScale);
        }
        //Calculating deltaWeights
        vector<vector<vector<double>>> deltaWeights;


        vector<vector<double>> deltaNeurons;
        //Start weights from the back for backpropagation 
        for (int i = weights.size() - 1; i >= 0; i--) {
            //Current weight column
            vector<vector<double>> weightLayer = weights[i];
            vector<double> neuronLayer = neuronValues[i];
            vector<vector<double>> deltaNeuronLayer;
            vector<double> deltaErrors;

            if (i == weights.size() - 1) {
                //Calculate error for output layer
                vector<double> targets = math.perfectResult(weightLayer.size(), grayScaleDigit);
                for (int j = 0; j < targets.size(); j++) {
                    deltaErrors.push_back(targets[j] - neuronValues[i + 1][j]);
                }
                deltaNeurons.push_back(deltaErrors);
                break;
            }
            for (int j = 0; j < weightLayer.size(); j++) {
                vector<double> previousErrors = deltaNeurons[weights.size() - 2 - j];
                
            }


        }
        //REMOVE LATER
        break;
    }
}
