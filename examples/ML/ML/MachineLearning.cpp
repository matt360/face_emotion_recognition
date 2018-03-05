#include "MachineLearning.h"
#include <algorithm>

MachineLearning::MachineLearning()
{
}

MachineLearning::~MachineLearning()
{
}

void MachineLearning::Learn()
{
    // Learn smile
    /* first variable is the name of the file that contains features of a certain emotion, second is the name of the file mainly serving debugging purposes so we can check what weightings for a given emotion are */
    smileFeatures.Learn("../../smile.csv", "smile_weightings.csv");
    /* similarly it goes for the picture we want to recognize. We pass a file containing the facial features and the second file is mainly for the debugging purposes. It doesn't have to be passed. There's an overloaded version of Learn function that takes only the name of the learning file */
    pictureFeatures.Learn("../../smile_test.csv", "picture_smile_weightings.csv");
}

void MachineLearning::RecognizeEmotion()
{
    /*
    Check emtion from a picture:
    - Read facial features of a single face from a file
    - Create facial features vector
    - Create an emotion weighted vector
    - Read emotion weighting from a file (in a group of 3)
    - Create emotion weighted vectors (in a group of 3)
    - Compare the emotion weighted vector (of a single face) with the emotion weighted vectors (created from the learning file),
    like smile_weightings_vector, sad_weightenings_vector ect.
    - The one with the least score is the most likely to be that emotion:
    smile_probability.push_back(emotion weighted vectors(i) - emotion weight from a single picture)
    */

    /* it's best to keep learning files the same sizes but in case we were learning one emotion more than the other, we'll take the smallest size from the wieghting vector and use that to recognize the emotion */
    int smallest_weighting_vector_size = std::min({ smileFeatures.weightingsVector.size(), pictureFeatures.weightingsVector.size(), smileFeatures.weightingsVector.size() } ); // use { initializer list } to get the mininum value from more than 2 variables

    int smile_prob = CheckForEmotion(smallest_weighting_vector_size, smileFeatures, pictureFeatures);
    int sad_prob = CheckForEmotion(smallest_weighting_vector_size, smileFeatures, pictureFeatures);
    int angry_prob = 1;

    int most_likely_emotion = std::min( { smile_prob, sad_prob } );
    bool smiley = most_likely_emotion == smile_prob;
    bool sad = most_likely_emotion == sad_prob;
    bool angry = most_likely_emotion == angry_prob;

    // the closer the value is to 0 the more likely it is to be this emotion
    std::cout << "\nIt is most likely ";
    if (smiley) std::cout << "(or) smiley face ";
    if (sad) std::cout << "(or) sad face";
    if (angry) std::cout << "(or) angry face\n";
}

int MachineLearning::CheckForEmotion(const int& smallest_weighting_vector_size,
    const FacialFeatures& emotion_weightings, // 
    const FacialFeatures& emotion_to_recognize_weightings)
{
    // test only against the same amount of weightings from the test picture and tested picture
    int emotion_prob = 0;
    for (int i = 0; i < smallest_weighting_vector_size; i++)
    {
        emotion_prob += emotion_weightings.weightingsVector.at(i) - emotion_to_recognize_weightings.weightingsVector.at(i);
    }
    // check for negative values
    if (emotion_prob  < 0)
        emotion_prob = std::abs(emotion_prob);

    return emotion_prob;
}
