#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
vector<vector<vector<double>>> JSONtoJS() {
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

vector<vector<double>> getBiases() {
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

int main(void) {
    vector<vector<vector<double>>> networkData = JSONtoJS();
    string output = "var data = [";
    for (int i = 0; i < networkData.size(); i++) {
        output.append("[");
        vector<vector<double>> column = networkData[i];
        for (int j = 0; j < column.size(); j++) {
            output.append("[");
            vector<double> weights = column[j];
            for (int k = 0; k < weights.size(); k++) {
                output.append(to_string(weights[k]));
                if(k < weights.size() - 1) 
                    output.append(", ");
            }
            output.append("]");
            if(j < column.size() - 1) 
                    output.append(", ");
        }
        output.append("]");
        if(i < networkData.size() - 1) 
                    output.append(", ");
    }
    output.append("];");
    
    ofstream file_id("WebInterface/js/networkData.js");
    file_id << output;
    file_id << '\n';

    vector<vector<double>> networkDataBiases = getBiases();
    output = "var biases = [";
    for (int i = 0; i < networkDataBiases.size(); i++) {
        output.append("[");
        vector<double> column = networkDataBiases[i];
        for (int j = 0; j < column.size(); j++) {
            output.append(to_string(column[j]));
            if(j < column.size() - 1) 
                    output.append(", ");
        }
        output.append("]");
        if(i < networkDataBiases.size() - 1) 
                    output.append(", ");
    }
    output.append("];");
    file_id << output;

    return 0;
}