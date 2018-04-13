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
    smileFeatures.Learn("../../smile.csv");
    angryFeatures.Learn("../../angry.csv");
    sadFeatures.Learn("../../sad.csv");   
}

/* similarly it goes for the picture we want to recognize. We pass a file containing the facial features and the second file is mainly for the debugging purposes. It doesn't have to be passed. There's an overloaded version of Learn function that takes only the name of the learning file */
std::string MachineLearning::LearnPicture()
{
    // name of the picture we want to recognize an emotion from
    std::cout << "Type a name of the picture to recognize an emotion from: ";
    std::string recognize_picture_name;
    std::cin >> recognize_picture_name;
    // add a path to the pictures .csv data
    std::string pic_name;
    pic_name = "../../" + recognize_picture_name + ".csv";
    // extract emotion weightings from the picture
    pictureFeatures.Learn(pic_name.c_str());

    return pic_name;
}

void MachineLearning::RecognizeEmotion()
{
    /* it's best to keep learning files the same sizes but in case we were learning one emotion more than the other, we'll take the smallest size from the wieghting vector and use that to recognize the emotion */
    const int smallest_weighting_vector_size = std::min({ smileFeatures.weightingsVector.size(), sadFeatures.weightingsVector.size(), angryFeatures.weightingsVector.size(), pictureFeatures.weightingsVector.size(), } ); // use { initializer list } to get the mininum value from more than 2 variables

    const int smile_prob = CheckForEmotion(smallest_weighting_vector_size, smileFeatures, pictureFeatures);
    const int sad_prob = CheckForEmotion(smallest_weighting_vector_size, sadFeatures, pictureFeatures);
    const int angry_prob = CheckForEmotion(smallest_weighting_vector_size, angryFeatures, pictureFeatures);

    int const most_likely_emotion = std::min( { smile_prob, sad_prob, angry_prob } ); // put 1 here for testing to see that angry will be the most likely emotion here
    bool smiley = most_likely_emotion == smile_prob;
    bool sad = most_likely_emotion == sad_prob;
    bool angry = most_likely_emotion == angry_prob;

    // the closer the value is to 0 the more likely it is to be this emotion
    std::cout << "\nIt is most likely ";
    if (smiley) std::cout << "(or) smiley face ";
    if (sad) std::cout << "(or) sad face";
    if (angry) std::cout << "(or) angry face";

    std::cout << std::endl << std::endl;
    std::cout << "smile_prob " << smile_prob << std::endl;
    std::cout << "sad_prob " << sad_prob << std::endl;
    std::cout << "angry_prob " << angry_prob << std::endl;

    pictureFeatures.Release();
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
