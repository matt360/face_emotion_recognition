#pragma once
#pragma warning(disable : 4996)

#include "SmileFeatures.h"
#include "PictureFeatures.h"
#include <map>

//#define GET_VAR_NAME(var) #var

class MachineLearning
{
public:
    MachineLearning();
    ~MachineLearning();
public:
    void Learn();
    void RecognizeEmotion();
    int CheckForSmile(int smallest_weighting_vector_size);
    int CheckForSad(int smallest_weighting_vector_size);

private:
    // classes
   SmileFeatures smileFeatures;
   PictureFeatures pictureFeatures;
};
