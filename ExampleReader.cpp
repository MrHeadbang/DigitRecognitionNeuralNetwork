#include "main.h"

vector<double> ExampleReader::ImageToVector(string ImagePath) {
    vector<double> grayScaleOutput;
    Mat numberImage = imread(ImagePath);

    int numberRows = numberImage.rows;
    int numberColumns = numberImage.cols;
    for (int i = 0; i < numberRows; i++) {
        for (int j = 0; j < numberColumns; j++) {
            double grayScale = (double)numberImage.at<Vec3b>(i, j)[0] / 255;
            grayScaleOutput.push_back(grayScale);
        }
    }
    return grayScaleOutput;

}

void ExampleReader::VectorToImage(vector<double> ImageVector) {

}

int reverseInt (int i) {
    unsigned char c1, c2, c3, c4;
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
vector<pair<Mat,int>> ExampleReader::loadBinary(const string &datapath, const string &labelpath) {
    vector<pair<Mat,int>> dataset;
    ifstream datas(datapath, ios::binary);
    ifstream labels(labelpath, ios::binary);

    if (!datas.is_open() || !labels.is_open())
        throw runtime_error("binary files could not be loaded");

    int magic_number=0; int number_of_images=0;int r; int c;
    int n_rows=0; int n_cols=0; unsigned char temp=0;

    // parse data header
    datas.read((char*)&magic_number,sizeof(magic_number));
    magic_number=reverseInt(magic_number);
    datas.read((char*)&number_of_images,sizeof(number_of_images));
    number_of_images=reverseInt(number_of_images);
    datas.read((char*)&n_rows,sizeof(n_rows));
    n_rows=reverseInt(n_rows);
    datas.read((char*)&n_cols,sizeof(n_cols));
    n_cols=reverseInt(n_cols);

    // parse label header - ignore
    int dummy;
    labels.read((char*)&dummy,sizeof(dummy));
    labels.read((char*)&dummy,sizeof(dummy));

    for(int i=0;i<number_of_images;++i){
        Mat img(n_rows,n_cols,CV_32FC1);

        for(r=0;r<n_rows;++r){
            for(c=0;c<n_cols;++c){
                datas.read((char*)&temp,sizeof(temp));
                img.at<float>(r,c) = 1.0-((float)temp)/255.0;
            }
        }
        labels.read((char*)&temp,sizeof(temp));
        dataset.push_back(make_pair(img,(int)temp));
    }
    return dataset;
}

vector<pair<vector<double>,int>> ExampleReader::loadFormatMNIST(const string &datapath, const string &labelpath) {
    vector<pair<Mat,int>> rawData = loadBinary(datapath, labelpath);
    vector<pair<vector<double>,int>> output;

    for (int i = 0; i < rawData.size(); i++) {
        int finalInt = rawData[i].second;
        Mat currentMatrix = rawData[i].first;
        vector<double> finalVector;

        for (int i = 0; i < currentMatrix.rows; i++) {
            for (int j = 0; j < currentMatrix.cols; j++) {
                double grayScale = (double)currentMatrix.at<float>(i, j);
                finalVector.push_back(grayScale);
            }
        }

        pair<vector<double>,int> pair = make_pair(finalVector, finalInt);
        output.push_back(pair);
    }
    return output;
}