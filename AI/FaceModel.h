#ifndef KOPYTKO_FACEMODEL_H
#define KOPYTKO_FACEMODEL_H

#include <dlib/matrix.h>
#include <string>
#include <vector>

using namespace std;

class FaceModel {
public:
    FaceModel(string label, dlib::matrix<float, 0, 1> descriptor);
    FaceModel(string fileLine);
    float compare(dlib::matrix<float, 0, 1> other);

    string toString();

    static void writeModelsFile(vector<FaceModel*> &models, string fileName);
    static void readModelsFile(vector<FaceModel*> &models, string fileName);
private:
    string label;
    dlib::matrix<float, 0, 1> descriptor;
};


#endif //KOPYTKO_FACEMODEL_H
