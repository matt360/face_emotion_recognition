#include "FacialFeatures.h"

FacialFeatures::FacialFeatures()
{
}

FacialFeatures::~FacialFeatures()
{
}

void FacialFeatures::Release()
{
    learning_data.clear();
    weightingsVector.clear();
    chin.clear();
    left_eyebrow.clear();
    right_eyebrow.clear();
    nose_bridge.clear();
    nose_tip.clear();
    left_eye.clear();
    right_eye.clear();
    top_lip.clear();
    bottom_lip.clear();
}

int FacialFeatures::GenerateLearningVectorFromFile(const char* emotion_learning_file)
{
    // file to store the .csv 
    FILE *file;
    // two chars to read from two columns in each row in the .csv file
    char str1[10], str2[10];

    // open the .csv file to read the data
    file = fopen(emotion_learning_file, "r");
    // check if the file was opened correctly
    if (NULL == file)
    {
        printf("\nError in opening file.");
        return 0;
    }

    // read data into a vector from a .csv file with two columns
    while (EOF != fscanf(file, " %[^,], %s ", str1, str2))
    {
        learning_data.push_back(std::stoi(str1));
        learning_data.push_back(std::stoi(str2));
    }
    // close the file after reading the data into the vector
    fclose(file);
}

// data in the facial_recognition algorithm has a layout:
//
// 'chin',          17 * (a, b)
// 'left_eyebrow',  5 * (a, b)
// 'right_eyebrow', 5 * (a, b)
// 'nose_bridge',   4 * (a, b)
// 'nose_tip',      5 * (a, b)
// 'left_eye',      6 * (a, b)
// 'right_eye',     6 * (a, b)
// 'top_lip',       12 * (a, b)
// 'bottom_lip'     12 * (a, b)
//
// in order to extract facial features we need to take the appropriate pairs of data and subtrack them so we can get:
// a distance of the left_eyebrow from the left_eye :
// 5 - 6  = (5 pairs of numbers) - (6 pairs of numbers) = (even - odd) + ... + (even - odd) = 
// (0 - 1) + (2 - 3) + (4 - 5) + (6 - 7) + (8 - 9) = -(weight value for the emotion)
//
// const int CHIN = 17;	// 17 * (a, b) - number of variables for a facial feature is 34 (17 * 2 variables) - reason: it's stored in a 1D array
// const int LEFT_EYEBROW = 5;      //  5 * (a, b)
// const int RIGHT_EYEBROW = 5;     //  5 * (a, b)
// const int NOSE_BRIDGE = 4;       //  4 * (a, b)
// const int NOSE_TIP = 5;          //  5 * (a, b)
// const int LEFT_EYE = 6;          //  6 * (a, b)
// const int RIGHT_EYE = 6;         //  6 * (a, b)
// const int TOP_LIP = 12;          // 12 * (a, b)
// const int BOTTOM_LIP = 12;       // 12 * (a, b)
// const int LIP_DIST = 12;
// const int EYE_EYEBROW_DIST = 5;
// const int NOSE_DIST = 4;
void FacialFeatures::PopulateFacialFeaturesVectors()
{

    // the number of rows to cover all the feautres from one picture is 72 but because there's two colums and they are stored in 1D array we must divide the size 
    // by 144 to get the number of pictures examined.
    std::cout << "STEP: " << STEP << std::endl;
    std::cout << "FacialFeatures::FacialFeatures::learning_data size / STEP: " << FacialFeatures::learning_data.size() / STEP << std::endl;
    // for the same reason we increase 'i' by 144
    int i = 0;
    for (int j = 0; j < FacialFeatures::learning_data.size() / STEP; j++)
    {
        // chin (17) [1] - (number of paired elements for the facial feature) [place in the .csv file + i]
        //for (int i = 0; i < 34; i++) 
        for (; i < (CHIN * 2) + j * STEP; i++) // we need to multiply by 2 to get all the data since it's a 1D array
            chin.push_back(FacialFeatures::learning_data.at(i)); // create a vector of chin positions

        // left eyebrow (5) [18]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2) + j * STEP; i++)
            left_eyebrow.push_back(FacialFeatures::learning_data.at(i));

        // right_eyebrow (5) [23]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2) + j * STEP; i++)
            right_eyebrow.push_back(FacialFeatures::learning_data.at(i));

        // nose_bridge (4) [28]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2) + j * STEP; i++)
            nose_bridge.push_back(FacialFeatures::learning_data.at(i));

        // nose_tip (5) [32]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2) + j * STEP; i++)
        {
            nose_tip.push_back(FacialFeatures::learning_data.at(i));
        }

        // left_eye (6) [37]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2) + j * STEP; i++)
            left_eye.push_back(FacialFeatures::learning_data.at(i));

        // right_eye (6) [43]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2) + j * STEP; i++)
            right_eye.push_back(FacialFeatures::learning_data.at(i));

        // top_lip (12) [49]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2 + TOP_LIP * 2) +
            j * STEP; i++)
            top_lip.push_back(FacialFeatures::learning_data.at(i));

        // bottom_lip (12) [61]
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2 + TOP_LIP * 2 +
            BOTTOM_LIP * 2) + j * STEP; i++)
            bottom_lip.push_back(FacialFeatures::learning_data.at(i));
    }
    // check if populating vectors with facial features went ok. The sizes of all vector features added together should equal 'i'
    if (i == chin.size() + left_eyebrow.size() + right_eyebrow.size() + nose_bridge.size() + nose_tip.size() + left_eye.size() + right_eye.size() +
        top_lip.size() + bottom_lip.size())
        std::cout << "Papulating Facial Features Vectors went OK!" << std::endl;
}

void FacialFeatures::DisplayFacialFeaturesVectors()
{
    // 'chin', 17 * (a, b)
    std::cout << "chin " << "size: " << chin.size() % 17 << std::endl; // 0 means its okay
    for (int i = 0; i < 17 * 2; i += 2)
        std::cout << chin.at(i) << ", " << chin.at(i + 1) << std::endl;
    // 'left_eyebrow', 5 * (a, b)
    std::cout << "left_eyebrow" << "size: " << left_eyebrow.size() % 5 << std::endl;
    for (int i = 0; i < 5 * 2; i += 2)
        std::cout << left_eyebrow.at(i) << ", " << left_eyebrow.at(i + 1) << std::endl;
    // 'right_eyebrow', 5 * (a, b)
    std::cout << "right_eyebrow" << "size: " << left_eyebrow.size() % 5 << std::endl;
    for (int i = 0; i < 5 * 2; i += 2)
        std::cout << right_eyebrow.at(i) << ", " << right_eyebrow.at(i + 1) << std::endl;
    // 'nose_bridge', 4 * (a, b)
    std::cout << "nose_bridge" << "size: " << nose_bridge.size() % 4 << std::endl;
    for (int i = 0; i < 4 * 2; i += 2)
        std::cout << nose_bridge.at(i) << ", " << nose_bridge.at(i + 1) << std::endl;
    // 'nose_tip', 5 * (a, b)
    std::cout << "nose_tip" << "size: " << nose_tip.size() % 5 << std::endl;
    for (int i = 0; i < 5 * 2; i += 2)
        std::cout << nose_tip.at(i) << ", " << nose_tip.at(i + 1) << std::endl;
    // 'left_eye', 6 * (a, b)
    std::cout << "left_eye" << "size: " << left_eye.size() % 6 << std::endl;
    for (int i = 0; i < 6 * 2; i += 2)
        std::cout << left_eye.at(i) << ", " << left_eye.at(i + 1) << std::endl;
    // 'right_eye', 6 * (a, b)
    std::cout << "right_eye" << "size: " << right_eye.size() % 6 << std::endl;
    for (int i = 0; i < 6 * 2; i += 2)
        std::cout << right_eye.at(i) << ", " << right_eye.at(i + 1) << std::endl;
    // 'top_lip', 12 * (a, b)
    std::cout << "top_lip" << "size: " << top_lip.size() % 12 << std::endl;
    for (int i = 0; i < 12 * 2; i += 2)
        std::cout << top_lip.at(i) << ", " << top_lip.at(i + 1) << std::endl;
    // 'bottom_lip', 12 * (a, b)
    std::cout << "bottom_lip" << "size: " << bottom_lip.size() % 12 << std::endl;
    for (int i = 0; i < 12 * 2; i += 2)
        std::cout << bottom_lip.at(i) << ", " << bottom_lip.at(i + 1) << std::endl;
}

void FacialFeatures::CalculateEmotionWeightings()
{
    for (int i = 0; i < left_eyebrow.size(); i++)
    {
        // (5 - 6)
        // at the beginning we don't have to adjust for vector size difference
        weightingsVector.push_back(left_eyebrow.at(i) - left_eye.at(i + 1));
    }

    // a distance of the right_eyebrow from the right_eye: 
    for (int i = 0; i < right_eyebrow.size(); i++)
    {
        // (5 - 6)
        weightingsVector.push_back(right_eyebrow.at(i) - right_eye.at(i + 1));
    }

    // a distance of the top_lip from the bottom_lip:
    for (int i = 0; i < top_lip.size(); i++)
    {
        // (12 - 12)
        weightingsVector.push_back(top_lip.at(i) - bottom_lip.at(i));
    }

    // a distance from the nose tip to the nose bridge:
    for (int i = 0; i < nose_bridge.size(); i++)
    {
        // (5 - 4)
        weightingsVector.push_back(nose_bridge.at(i) - nose_tip.at(i + 1));
    }
}

void FacialFeatures::Learn(const char* learning_file_name)
{
    GenerateLearningVectorFromFile(learning_file_name);

    PopulateFacialFeaturesVectors();
    CalculateEmotionWeightings();
}
