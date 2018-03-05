#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Consts.h"

class FacialFeatures
{
public:
	FacialFeatures();
    // virtual destructor ensures that both destructors will be called; of the base and the derived class
	virtual ~FacialFeatures();

    void PopulateFacialFeaturesVectors();
    void PopulateFacialFeaturesVectors(const std::vector<int>& learning_data);
    void DisplayFacialFeaturesVectors();
    void CalculateEmotionWeightings(const char* file_name);
    void CalculateEmotionWeightings();

    // emotion weighted values (ewv)
    std::vector<int> weightingsVector;
    // to store smile weightings
    std::ofstream weightingsFile;

public:
    int GenerateLearningVectorFromFile(const char* emotion_learning_file);
    void Learn(const char* learning_file_name, const char* weightings_file_name);
    void Learn(const char * learning_file_name);
    // learning variables - vector to store the data of the facial features to learn from
    std::vector<int> learning_data;

protected:
    // face features vectors (stack memory)
    std::vector<int> chin;
    std::vector<int> left_eyebrow;
    std::vector<int> right_eyebrow;
    std::vector<int> nose_bridge;
    std::vector<int> nose_tip;
    std::vector<int> left_eye;
    std::vector<int> right_eye;
    std::vector<int> top_lip;
    std::vector<int> bottom_lip;
};

