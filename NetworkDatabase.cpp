#include "main.h"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
void NetworkDatabase::saveWeights(vector<vector<vector<double>>> weights) {
    Json::Value jsonWeights;
    for (int i = 0; i < weights.size(); i++) {
        vector<vector<double>> neuronColumn = weights[i];
        Json::Value jsonNeuronColumns;
        for (int j = 0; j < neuronColumn.size(); j++) {
            vector<double> neuronWeights = neuronColumn[j];
            Json::Value jsonNeuronWeights(Json::arrayValue);
            for (int k = 0; k < neuronWeights.size(); k++) {
                jsonNeuronWeights.append(neuronWeights[k]);
            }
            jsonNeuronColumns.append(jsonNeuronWeights);
        }
        jsonWeights.append(jsonNeuronColumns);
    }
    ofstream file_id;
    file_id.open("networkWeights.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(jsonWeights);
    file_id.close();
}
vector<vector<vector<double>>> NetworkDatabase::getWeights() {
    vector<vector<vector<double>>> output;
    ifstream jsonWeightsFile("networkWeights.json");
    Json::Value jsonWeights;
    jsonWeightsFile >> jsonWeights;
    
    for (int i = 0; i < jsonWeights.size(); i++) {
        Json::Value jsonNeuronColumn = jsonWeights[i];
        vector<vector<double>> neuronColumns;
        for (int j = 0; j < jsonNeuronColumn.size(); j++) {
            Json::Value jsonNeuronWeights = jsonNeuronColumn[j];
            vector<double> neuronWeights;
            for (int k = 0; k < jsonNeuronWeights.size(); k++) {
                neuronWeights.push_back(jsonNeuronWeights[k].asDouble());
            }
            neuronColumns.push_back(neuronWeights);
        }
        output.push_back(neuronColumns);
    }
    return output;
}
void NetworkDatabase::saveBiases(vector<vector<double>> biases) {
    Json::Value jsonBiases;
    for (int i = 0; i < biases.size(); i++) {
        vector<double> neuronColumn = biases[i];
        Json::Value jsonNeuronColumns;
        for (int j = 0; j < neuronColumn.size(); j++) {
            jsonNeuronColumns.append(neuronColumn[j]);
        }
        jsonBiases.append(jsonNeuronColumns);
    }
    ofstream file_id;
    file_id.open("networkBiases.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(jsonBiases);
    file_id.close();
}
vector<vector<double>> NetworkDatabase::getBiases() {
    vector<vector<double>> output;
    ifstream jsonBiasesFile("networkBiases.json");
    Json::Value jsonBiases;
    jsonBiasesFile >> jsonBiases;
    
    for (int i = 0; i < jsonBiases.size(); i++) {
        Json::Value jsonNeuronColumn = jsonBiases[i];
        vector<double> neuronColumns;
        for (int j = 0; j < jsonNeuronColumn.size(); j++) {
            neuronColumns.push_back(jsonNeuronColumn[j].asDouble());
        }
        output.push_back(neuronColumns);
    }
    return output;
}