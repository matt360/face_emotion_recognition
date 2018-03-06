#pragma once


#include "FacialFeatures.h"

//#define GET_VAR_NAME(var) #var

class MachineLearning
{
public:
    MachineLearning();
    ~MachineLearning();
public:
    void Learn();
    std::string LearnPicture();
    void RecognizeEmotion();
    int CheckForEmotion(const int& smallest_weighting_vector_size,
        const FacialFeatures& emotion_weightings,
        const FacialFeatures& emotion_to_recognize_weightings);

private:
    // classes
   FacialFeatures smileFeatures;
   FacialFeatures angryFeatures;
   FacialFeatures sadFeatures;
   FacialFeatures pictureFeatures;
};
