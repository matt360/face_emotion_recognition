#pragma once

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

    void PopulateFacialFeaturesVectors(const std::vector<int>& learning_data);
    void DisplayFacialFeaturesVectors();

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

