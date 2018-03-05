#pragma warning(disable : 4996)

#include "FacialFeatures.h"

// emotion weighted values (emv)
//std::vector<int> top_lip_bottom_lip_distance;
//std::vector<int> left_eyebrow_left_eye_distance;
//std::vector<int> right_eyebrow_right_eye_distance;
//std::vector<int> nose_tip_nose_bridge_distance;
std::vector<int> smile_weightings;
// to store smile weightings
std::ofstream m_SmileWeightings;
void CalculateEmotionWeightingsForSmile(std::ofstream& smileWeightingsFile)
{
	// std::ios_bas::app - all output operations happen at the end of the file, appending to its existing contents.
	smileWeightingsFile.open("smile_learning.csv", std::ios_base::app);

	// data in the facial_recognition algorithm has a layout:
	/*
	'chin',          17 * (a, b)
	'left_eyebrow',  5 * (a, b)
	'right_eyebrow', 5 * (a, b)
	'nose_bridge',   4 * (a, b)
	'nose_tip',      5 * (a, b)
	'left_eye',      6 * (a, b)
	'right_eye',     6 * (a, b)
	'top_lip',       12 * (a, b)
	'bottom_lip'     12 * (a, b)
	*/
	// in order to extract facial features we need to take the appropriate pairs of data and subtrack them so we can get:
	// a distance of the left_eyebrow from the left_eye :
	// 5 - 6  = (5 pairs of numbers) - (6 pairs of numbers) = (even - odd) + ... + (even - odd) = 
	// (0 - 1) + (2 - 3) + (4 - 5) + (6 - 7) + (8 - 9) = -(weight value for the emotion)
	/*
	const int CHIN = 17;			 // 17 * (a, b) - number of variables for a facial feature is 34 (17 * 2 variables) - reason: it's stored in a 1D array
	const int LEFT_EYEBROW = 5;      //  5 * (a, b)
	const int RIGHT_EYEBROW = 5;     //  5 * (a, b)
	const int NOSE_BRIDGE = 4;       //  4 * (a, b)
	const int NOSE_TIP = 5;          //  5 * (a, b)
	const int LEFT_EYE = 6;          //  6 * (a, b)
	const int RIGHT_EYE = 6;         //  6 * (a, b)
	const int TOP_LIP = 12;          // 12 * (a, b)
	const int BOTTOM_LIP = 12;       // 12 * (a, b)
	const int LIP_DIST = 12;
	const int EYE_EYEBROW_DIST = 5;
	const int NOSE_DIST = 4;
	*/

	// append emotion weighted values for smile into the file
	//for (int i = 1; i < left_eyebrow.size() - 1; i++)
	//{
	//	// (5 - 6)
	//	// at the beginning we don't have to adjust for vector size difference
	//	if (i == 1 || i == 2)
	//		left_eyebrow_left_eye_distance.push_back(left_eyebrow.at(i - 1) - left_eye.at(i - 1));
	//	// do reduction only if 'i' is dividable by 3
	//	else if (i % 3 == 0 && i % 4 != 0 && i % 6 != 0)
	//		left_eyebrow_left_eye_distance.push_back(left_eyebrow.at(i - 1) - (left_eye.at(i) - left_eye.at(i - 1))); // we add one to acomodate for different vector sizes
	//	else
	//		left_eyebrow_left_eye_distance.push_back(left_eyebrow.at(i - 1) - left_eye.at(i));
	//}
	for (int i = 0; i < left_eyebrow.size(); i++)
	{
		// (5 - 6)
		// at the beginning we don't have to adjust for vector size difference
		smile_weightings.push_back(left_eyebrow.at(i) - left_eye.at(i + 1));
		smileWeightingsFile << left_eyebrow.at(i) - left_eye.at(i + 1) << std::endl;
	}

	// a distance of the right_eyebrow from the right_eye: 
	for (int i = 0; i < right_eyebrow.size(); i++)
	{
		// (5 - 6)
		smile_weightings.push_back(right_eyebrow.at(i) - right_eye.at(i + 1));
		smileWeightingsFile << right_eyebrow.at(i) - right_eye.at(i + 1) << std::endl;
	}

	// a distance of the top_lip from the bottom_lip:
	for (int i = 0; i < top_lip.size(); i++)
	{
		// (12 - 12)
		smile_weightings.push_back(top_lip.at(i) - bottom_lip.at(i));
		smileWeightingsFile << top_lip.at(i) - bottom_lip.at(i) << std::endl;
	}

	// a distance from the nose tip to the nose bridge:
	for (int i = 0; i < nose_bridge.size(); i++)
	{
		// (5 - 4)
		smile_weightings.push_back(nose_bridge.at(i) - nose_tip.at(i + 1));
		smileWeightingsFile << nose_bridge.at(i) - nose_tip.at(i + 1) << std::endl;
	}

	// if (emv != any set of values in the file)
	//for (auto it_0 = left_eyebrow_left_eye_distance.begin(); it != left_eyebrow_left_eye_distance.end(); ++it)
	//	for (auto it_1 = right_eyebrow_right_eye_distance.begin(); it != right_eyebrow_right_eye_distance.end(); ++it)
	//		for (auto it_2 = top_lip_bottom_lip_distance.begin(); it != top_lip_bottom_lip_distance.end(); ++it)
	//			for (auto it_3 = nose_tip_nose_bridge_distance.begin(); it != nose_tip_nose_bridge_distance.end(); ++it)
	//			{
	//				m_SmileWeightings << 
	//				*it_0 << ',' << 
	//				*it_1 << ',' << 
	//				*it_2 << ',' << 
	//				*it_3 << std::endl; // ',' - makes it go to the next cell in the .csv file
	//			}

}

std::vector<int> facial_features_from_picture; 
void CheckEmotionFromPicture()
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

	/* Read facial features of a single face from a file */
	// file to store the .csv 
	FILE *fp;
	// two chars to read from two columns in each row in the .csv file
	char str1[10], str2[10];

	// open the .csv file to read the data
	fp = fopen("../../smile_test.csv", "r");
	// check if the file was opened correctly
	if (NULL == fp)
	{
		printf("\nError in opening file.");
	}
	else
	{
		// read data into a vector from a .csv file with two columns
		while (EOF != fscanf(fp, " %[^,], %s, %s ", str1, str2))
		{
			/* Create facial features vector*/
			facial_features_from_picture.push_back(std::stoi(str1));
			facial_features_from_picture.push_back(std::stoi(str2));
		}
	}

	/* Create emotion weighted vector */
	//facial_features_from_picture

	#if 0
	/* Read emotion weighting from a file */
	// close the file after reading the data into the vector
	fclose(fp);

	// file to store the .csv 
	FILE *fpe;
	// two chars to read from two columns in each row in the .csv file
	char str1[10], str2[10];

	// open the .csv file to read the data
	fpe = fopen("smile_learning.csv", "r");
	// check if the file was opened correctly
	if (NULL == fp)
	{
		printf("\nError in opening file.");
	}
	else
	{
		// read data into a vector from a .csv file with two columns
		while (EOF != fscanf(fpe, " %[^,], %s, %s ", str1, str2))
		{
			/* Create emotion weighting vectors */
			smile_weightings.push_back(std::stoi(str1));
			smile_weightings.push_back(std::stoi(str2));
		}
	}
	// close the file after reading the data into the vector
	fclose(fp);
	#endif // 0

}

int main()
{
    //FacialFeatures facialFeatures;
    //facialFeatures.GenerateLearningVectorFromFile();

    //facialFeatures.PopulateFacialFeaturesVectors(learning_data);

	CalculateEmotionWeightingsForSmile();

    //facialFeatures.DisplayFacialFeaturesVectors();

	CheckEmotionFromPicture();

	m_SmileWeightings.close();

	std::cin.get();
}

