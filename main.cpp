#include "main.h"


int testDigit(string path, Network network) {
    ExampleReader exampleReader;
    vector<double> grayScale = exampleReader.ImageToVector(path);
    vector<double> output = network.feedForward(grayScale);

    /*cout << "\n" << "Output" << "\n";
    for (double i: output)
        cout << i << ' ';
    cout << "\n" << "\n";*/

    int max = distance(output.begin(),max_element(output.begin(), output.end()));

    cout << "Highest Value: " << output[max] << " at " << max << "\n";
    return 0;
}

int main(void) {
    srand(time(NULL));
    
    Math math;
    Network network({784, 100, 10});
    ExampleReader exampleReader;
    string base_dir = "examples/mnist/";
    string img_path = base_dir + "train-images.idx3-ubyte";
    string label_path = base_dir + "train-labels.idx1-ubyte";

    vector<pair<vector<double>,int>> dataset = exampleReader.loadFormatMNIST(img_path, label_path);    

    network.stochasticGradientDescent(dataset, 2000, 100, 0.01);
    
    testDigit("examples/0.png", network);
    testDigit("examples/9.png", network);
    testDigit("examples/3.png", network);
    testDigit("examples/1.png", network);
    testDigit("examples/7.png", network);
    testDigit("examples/8.png", network);
    
    
    //cout << math.cost(output, math.perfectResult(10, 9)) << "\n";


    return 0;
}