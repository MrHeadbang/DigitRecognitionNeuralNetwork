#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
using namespace std;
using namespace cv;

class ExampleReader {
    public:
        vector<double> ImageToVector(string ImagePath);
        vector<pair<Mat,int>> loadBinary(const string &datapath, const string &labelpath);
        vector<pair<vector<double>,int>> loadFormatMNIST(const string &datapath, const string &labelpath);
        void VectorToImage(vector<double> ImageVector);
};
class Math {
    public:
        double Sigmoid(double value);
        double RandomGauss(void);
        double cost(vector<double> vec1, vector<double> vec2);
        vector<double> perfectResult(int numberElements, int i);
        double SigmoidDerivative(double value);
};
class Network {
    Math math;
    public:
        int num_layers;
        vector<int> sizes;
        vector<vector<double>> biases; // Format: 2D Array of Biases for every column
        vector<vector<vector<double>>> weights; // Format: 3D Array [[[Weights] in Neuron] in Layers]
        Network(vector<int> params);
        vector<double> feedForward(vector<double> input);
        vector<double> calcLayerNeurons(vector<double> layerInput, vector<vector<double>> layerWeights,vector<double> layerBiases);
        void stochasticGradientDescent(vector<pair<vector<double>,int>> trainingData, int miniBatchSize, int epochs, double learningRate);
        void updateMiniBatch(vector<pair<vector<double>,int>> miniBatch, double learningRate);
        
        //Needs probably to be changed
        pair<double, vector<vector<vector<double>>>> backpropagation(/*Params expected*/);

};
