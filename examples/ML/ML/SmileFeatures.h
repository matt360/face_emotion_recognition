#pragma once
#include "FacialFeatures.h"

class SmileFeatures : public FacialFeatures
{
public:
	SmileFeatures();
	~SmileFeatures();

    void CalculateEmotionWeightings() override;

    // emotion weighted values (emv)
    //std::vector<int> top_lip_bottom_lip_distance;
    //std::vector<int> left_eyebrow_left_eye_distance;
    //std::vector<int> right_eyebrow_right_eye_distance;
    //std::vector<int> nose_tip_nose_bridge_distance;
    std::vector<int> smile_weightings;
    // to store smile weightings
    std::ofstream smileWeightingsFile;
};

