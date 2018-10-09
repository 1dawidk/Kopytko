#include "FaceModel.h"

FaceModel::FaceModel(string label, dlib::matrix<float, 0, 1> descriptor) {
    this->label= label;
    this->descriptor= descriptor;
}

FaceModel::FaceModel(string fileLine) {
    size_t first= fileLine.find_first_of('[');
    label= fileLine.substr(0, first);
    descriptor.set_size(128, 1);

    size_t nextComaPos;
    size_t lastComaPos= first+1;
    for(int i=0; i<128; i++){
        nextComaPos= fileLine.find_first_of("|]", lastComaPos);
        descriptor(i,0)=stof(fileLine.substr(lastComaPos, nextComaPos-lastComaPos));
        lastComaPos=nextComaPos+1;
    }
}

float FaceModel::compare(dlib::matrix<float, 0, 1> other) {
    return dlib::length(descriptor-other);
}

string FaceModel::toString() {
    string builder= label;
    builder+="[";
    for(int i=0; i<descriptor.nr(); i++){
        builder+=std::to_string(descriptor(i,0));
        if(i<descriptor.nr()-1)
            builder+="|";
    }
    builder+="]";
    return builder;
}

string FaceModel::getName(){
    return label;
}

void FaceModel::writeModelsFile(Context *context, vector<FaceModel*> &models, string fileName) {
    ofstream file= context->openWriteFile("/data/"+fileName, OPEN_FILE_MODE_RELATIVE);

    if(file.is_open()) {
        for (int i = 0; i < models.size(); i++) {
            file << models[i]->toString() << endl;
        }

        file.close();
    }
}

void FaceModel::readModelsFile(Context *context, vector<FaceModel*> &models, string fileName) {
    string line;
    ifstream file= context->openReadFile("/data/"+fileName, OPEN_FILE_MODE_RELATIVE);

    if(file.is_open()){
        while (getline(file, line)){
            if(!line.empty())
                models.push_back(new FaceModel(line));
        }

        file.close();
    }
}

int FaceModel::findSimilar(vector<FaceModel *> &models, dlib::matrix<float, 0, 1> descriptor) {
    for(int i=0; i<models.size(); i++){
        if(models[i]->compare(descriptor)<0.6)
            return i;
    }

    return FACEMODEL_FACE_NONE;
}

