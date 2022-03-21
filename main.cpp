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
void pv(vector<double> vec) {
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
    cout << "\n" << "\n";
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

    for (int i = 0; i < dataset.size(); i++) {
        vector<double> scale = dataset[i].first;
        for (int j = 0; j < scale.size(); j++) {
            if (scale[j] != 1)
                dataset[i].first[j] = 0;
        }
    }

    network.stochasticGradientDescent(dataset, 60000, 200, 0.0005);
    
    testDigit("examples/0.png", network);
    testDigit("examples/1.png", network);
    testDigit("examples/2.png", network);
    testDigit("examples/3.png", network);
    testDigit("examples/4.png", network);
    testDigit("examples/7.png", network);
    testDigit("examples/8.png", network);
    testDigit("examples/9.png", network);



    return 0;
}

//g++ main.cpp Math.cpp ExampleReader.cpp Network.cpp NetworkDatabase.cpp -o main.o -ljsoncpp `pkg-config --cflags --libs opencv4` && ./main.o