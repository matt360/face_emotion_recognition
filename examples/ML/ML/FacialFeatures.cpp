#include "FacialFeatures.h"

FacialFeatures::FacialFeatures()
{
}

FacialFeatures::~FacialFeatures()
{
}

void FacialFeatures::PopulateFacialFeaturesVectors(const std::vector<int>& learning_data)
{
    // the number of rows to cover all the feautres from one picture is 72 but because there's two colums and they are stored in 1D array we must divide the size 
    // by 144 to get the number of pictures examined.
    std::cout << "STEP: " << STEP << std::endl;
    std::cout << "learning_data size / STEP: " << learning_data.size() / STEP << std::endl;
    // for the same reason we increase 'i' by 144
    int i = 0;
    for (int j = 0; j < learning_data.size() / STEP; j++)
    {
        // chin (17) [1] - (number of paired elements for the facial feature) [place in the .csv file + i]
        //for (int i = 0; i < 34; i++) 
        for (; i < (CHIN * 2) + j * STEP; i++) // we need to multiply by 2 to get all the data since it's a 1D array
                                               // create a vector of chin positions
            chin.push_back(learning_data.at(i));

        // left eyebrow (5) [18]
        //for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2) + j * STEP; i++)
            left_eyebrow.push_back(learning_data.at(i));

        // right_eyebrow (5) [23]
        //for (int i = (17 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2) + j * STEP; i++)
            right_eyebrow.push_back(learning_data.at(i));

        // nose_bridge (4) [28]
        //std::cout << "nose bridge" << std::endl;
        //for (int i = (17 * 2 + 5 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2) + j * STEP; i++)
            nose_bridge.push_back(learning_data.at(i));

        // nose_tip (5) [32]
        //std::cout << "nose tip" << std::endl;
        //for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2) + j * STEP; i++)
        {
            nose_tip.push_back(learning_data.at(i));
        }

        // left_eye (6) [37]
        //std::cout << "left eye" << std::endl;
        //for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2) + j * STEP; i++)
            left_eye.push_back(learning_data.at(i));

        // right_eye (6) [43]
        //std::cout << "right eye" << std::endl;
        //for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2) + j * STEP; i++)
            right_eye.push_back(learning_data.at(i));

        // top_lip (12) [49]
        //std::cout << "top lip" << std::endl;
        //for (; i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2 + TOP_LIP * 2) +
            j * STEP; i++)
            top_lip.push_back(learning_data.at(i));

        // bottom_lip (12) [61]
        //std::cout << "bottom lip" << std::endl;
        //for (; i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2 + 12 *  2); i += 2)
        for (; i < (CHIN * 2 + LEFT_EYEBROW * 2 + RIGHT_EYEBROW * 2 + NOSE_BRIDGE * 2 + NOSE_TIP * 2 + LEFT_EYE * 2 + RIGHT_EYE * 2 + TOP_LIP * 2 +
            BOTTOM_LIP * 2) + j * STEP; i++)
            bottom_lip.push_back(learning_data.at(i));
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
