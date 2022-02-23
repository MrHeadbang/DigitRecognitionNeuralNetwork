#include "main.h"
double Math::Sigmoid(double value) {
    return 1 / (1 + pow(2.71828182845904, -value));
}
double Math::SigmoidDerivative(double sig) {
    //double sig = Sigmoid(value);
    return sig * (1 - sig);
}
double Math::RandomGauss(void) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}
double Math::cost(vector<double> vec1, vector<double> vec2) {
    double costOutput = 0;
    for (int i = 0; i < vec1.size(); i++) {
        double difference = vec1[i] - vec2[i];
        costOutput += difference * difference;
    }
    return costOutput;
}
vector<double> Math::perfectResult(int numberElements, int i) {
    //Create vector of perfect result, like {0,0,0,1,0,0,0} for cost function
    vector<double> output;
    for (int i = 0; i < numberElements; i++) {
        output.push_back(0);
    }
    output[i] = 1;
    return output;
}