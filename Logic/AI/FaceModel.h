#ifndef KOPYTKO_FACEMODEL_H
#define KOPYTKO_FACEMODEL_H

#include <dlib/matrix.h>
#include <string>
#include <vector>
#include <UI/Context.h>
#include <iostream>
#include <DataProcessing/DataProcessor.h>

#define FACEMODEL_FACE_NONE -1

using namespace std;

class FaceModel {
public:
    FaceModel(int faceId, dlib::matrix<float, 0, 1> descriptor);
    FaceModel(string fileLine);
    float compare(dlib::matrix<float, 0, 1> other);

    string toString();
    int getFaceId();

    static void writeModelsFile(DataProcessor *dataProcessor, vector<FaceModel*> &models, string fileName);
    static void readModelsFile(DataProcessor *dataProcessor, vector<FaceModel*> &models, string fileName);
    static int findSimilar(vector<FaceModel*> &models, dlib::matrix<float, 0, 1> descriptor);
private:
    int faceId;
    dlib::matrix<float, 0, 1> descriptor;
};


#endif //KOPYTKO_FACEMODEL_H
