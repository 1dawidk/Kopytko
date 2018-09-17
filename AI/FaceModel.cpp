#include "FaceModel.h"

FaceModel::FaceModel(string label, dlib::matrix<float, 0, 1> descriptor) {
    this->label= label;
    this->descriptor= descriptor;
}

FaceModel::FaceModel(string fileLine) {

}

float FaceModel::compare(dlib::matrix<float, 0, 1> other) {
    return 0;
}

string FaceModel::toString() {
    string builder= label;
    builder+=",[";
    for(int i=0; i<descriptor.nr(); i++){
        builder+=std::to_string(descriptor(i,0));
        if(i<descriptor.nr()-1)
            builder+=",";
    }
    builder+="]";
    return builder;
}

void FaceModel::writeModelsFile(vector<FaceModel*> &models, string fileName) {
    ofstream file(fileName);

    if(file.is_open()) {
        for (int i = 0; i < models.size(); i++) {
            file << models[i]->toString();
        }

        file.close();
    }
}

void FaceModel::readModelsFile(vector<FaceModel*> &models, string fileName) {
    string line;
    ifstream file(fileName);

    if(file.is_open()){
        while (getline(file, line)){
            models.push_back(new FaceModel(line));
        }

        file.close();
    }
}

