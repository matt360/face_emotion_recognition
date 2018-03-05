#pragma once
#include "FacialFeatures.h"

class PictureFeatures : public FacialFeatures
{
public:
	PictureFeatures();
	~PictureFeatures();

    void CalculateEmotionWeightings() override;

    std::vector<int> picture_weightings;
    // to store smile weightings
    std::ofstream pictureWeightingsFile;
};

