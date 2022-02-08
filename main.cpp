#include "main.h"


int main(void) {
    srand(time(NULL));
    ExampleReader exampleReader;
    Math math;
    Network network({784, 16, 10});

    string base_dir = "examples/mnist/";
    string img_path = base_dir + "train-images.idx3-ubyte";
    string label_path = base_dir + "train-labels.idx1-ubyte";

    vector<pair<vector<double>,int>> dataset = exampleReader.loadFormatMNIST(img_path, label_path);    
    
    vector<double> grayScale = exampleReader.ImageToVector("examples/3.png");

    vector<double> output = network.feedForward(grayScale);
    
    grayScale = dataset[1000].first;

    cout << dataset[1000].second << endl;

    cout << endl;
    cout << "------------INPUT------------" << endl;
    for (double i: grayScale)
        cout << i << ' ';
    cout << endl << "-----------------------------" << endl << endl;

    cout << "Output" << endl;

    for (double i: output)
        cout << i << ' ';
    cout << endl << endl;

    int max = distance(output.begin(),max_element(output.begin(), output.end()));

    cout << "Highest Value: " << output[max] << " at " << max << endl << endl;
    
    cout << math.cost(output, math.perfectResult(10, 3)) << endl;


    return 0;
}