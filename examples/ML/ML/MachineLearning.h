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
    int CheckForEmotion(const int& smallest_weighting_vector_size,
        const FacialFeatures& emotion_weightings,
        const FacialFeatures& emotion_to_recognize_weightings);

private:
    // classes
   SmileFeatures smileFeatures;
   PictureFeatures pictureFeatures;
};
