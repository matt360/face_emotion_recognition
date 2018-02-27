#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define CHIN          17   // 17 * (a, b) - number of variables for a facial feature is 34 (17 * 2 variables) - reason: it's stored in a 1D array
#define LEFT_EYEBROW   5   //  5 * (a, b)
#define RIGHT_EYEBROW  5   //  5 * (a, b)
#define NOSE_BRIDGE    4   //  4 * (a, b)
#define NOSE_TIP       5   //  5 * (a, b)
#define LEFT_EYE       6   //  6 * (a, b)
#define RIGHT_EYE      6   //  6 * (a, b)
#define TOP_LIP       12   // 12 * (a, b)
#define BOTTOM_LIP    12   // 12 * (a, b)
#define LIP_DIST           12
#define EYE_EYEBROW_DIST   5
#define NOSE_DIST          4

// vector to store the data of the facial features to learn from
std::vector<int> learning_data;

int GenerateLearningVectorFromAFile()
{
	// file to store the .csv 
	FILE *fp;
	// two chars to read from two columns in each row in the .csv file
	char str1[10], str2[10];

	// open the .csv file to read the data
	fp = fopen("../../smile.csv", "r");
	// check if the file was opened correctly
	if (NULL == fp)
	{
		printf("\nError in opening file.");
		return 0;
	}

	// read data into a vector from a .csv file with two columns
	while (EOF != fscanf(fp, " %[^,], %s, %s ", str1, str2))
	{
		learning_data.push_back(std::stoi(str1));
		learning_data.push_back(std::stoi(str2));
	}
	// close the file after reading the data into the vector
	fclose(fp);
}

// face features vectors (stack memory)
std::vector<int> chin;
std::vector<int> left_eyebrow;
std::vector<int> right_eyebrow;
std::vector<int> nose_bridge;
std::vector<int> nose_tip;
std::vector<int> left_eye;
std::vector<int> right_eye;
std::vector<int> top_lip;
std::vector<int> bottom_lip;

void PopulateFacialFeaturesVectors()
{
	// the number of rows to cover all the feautres from one picture is 72 but because there's two colums and they are stored in 1D array we must divide the size 
	// by 144 to get the number of pictures examined.
	std::cout << "learning_data size: " << floor(learning_data.size() / 144) << std::endl;
	// for the same reason we increase 'i' by 144
	for (int i = 0; i < learning_data.size(); i += 144)
	{
		// chin (17) [1] - (number of paired elements for the facial feature) [place in the .csv file + i]
		//for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
		for (int i = 0; i < 34; i++) // we need to multiply it by 2 to get all the data since it's a 1D array
									 // create a vector of chin positions
			chin.push_back(learning_data.at(i));

		// left eyebrow (5) [18]
		//for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
		for (int i = 34; i < 44; i++)
			left_eyebrow.push_back(learning_data.at(i));;

		// right_eyebrow (5) [23]
		//for (int i = (17 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2); i += 2)
		for (int i = 44; i < 54; i++)
			right_eyebrow.push_back(learning_data.at(i));;;

		// nose_bridge (4) [28]
		//std::cout << "nose bridge" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i += 2)
		for (int i = 54; i < 62; i++)
			nose_bridge.push_back(learning_data.at(i));

		// nose_tip (5) [32]
		//std::cout << "nose tip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i += 2)
		for (int i = 62; i < 72; i++)
			nose_tip.push_back(learning_data.at(i));

		// left_eye (6) [37]
		//std::cout << "left eye" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i += 2)
		for (int i = 72; i < 84; i++)
			left_eye.push_back(learning_data.at(i));

		// right_eye (6) [43]
		//std::cout << "right eye" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2); i += 2)
		for (int i = 84; i < 96; i++)
			right_eye.push_back(learning_data.at(i));

		// top_lip (12) [49]
		//std::cout << "top lip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2); 
		//     i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2); i += 2)
		for (int i = 96; i < 120; i++)
			top_lip.push_back(learning_data.at(i));

		// bottom_lip (12) [61]
		//std::cout << "bottom lip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2); 
		//     i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2 + 12 *  2); i += 2)
		for (int i = 120; i < 144; i++)
			bottom_lip.push_back(learning_data.at(i));
	}
}

void DisplayFacialFeaturesVectors()
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

// emotion weighted values (emv)
std::vector<int> top_lip_bottom_lip_distance;
std::vector<int> left_eyebrow_left_eye_distance;
std::vector<int> right_eyebrow_right_eye_distance;
std::vector<int> nose_tip_nose_bridge_distance;
// to store smile weightings
std::ofstream m_SmileWeightings;

void CalculateEmotionWeightingsForSmile()
{
	// std::ios_bas::app - all output operations happen at the end of the file, appending to its existing contents.
	m_SmileWeightings.open("smile_learning.csv", std::ios_base::app);

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
	if (left_eyebrow.size() == left_eye.size())
		for (int i = 0; i < left_eyebrow.size(); i++)
			left_eyebrow_left_eye_distance.push_back(left_eyebrow.at(i) - left_eye.at(i));

	// a distance of the right_eyebrow from the right_eye: 
	if (right_eyebrow.size() == right_eye.size())
		for (int i = 0; i < right_eyebrow.size(); i++)
			right_eyebrow_right_eye_distance.push_back(right_eyebrow.at(i) - right_eye.at(i));

	// a distance of the top_lip from the bottom_lip:
	if (top_lip.size() == bottom_lip.size())
		for (int i = 0; i < top_lip.size(); i++)
			top_lip_bottom_lip_distance.push_back(top_lip.at(i) - bottom_lip.at(i));

	// nose tip - nose bridge:
		for (int i = 0; i < nose_tip.size(); i++)
			nose_tip_nose_bridge_distance.push_back(nose_tip.at(i) - nose_bridge.at(i));

	// append emotion weighted values for smile into the file
	// if (emv != any set of values in the file)
		


	m_SmileWeightings << 1 << ',' << 2 << ',' << 3 << std::endl; // ',' - makes it go to the next cell in the .csv file
}

int main()
{
	GenerateLearningVectorFromAFile();

	PopulateFacialFeaturesVectors();

	CalculateEmotionWeightingsForSmile();

	DisplayFacialFeaturesVectors();

	/*
	Check emtion from a picture:
		- Read facial features of a single face from a file
		- Create an emotion weighted vector
		- Read emotion weighted vectors from a file (in a group of 3)
		- Create emotion weighted vectors (in a group of 3)
		- Compare the emotion weighted vector (of a single face) with the emotion weighted vectors (created from the learning file), 
		like smile_weightings_vector, sad_weightenings_vector ect.
		- The one with the least score is the most likely to be that emotion:
		smile_probability.push_back(emotion weighted vectors(i) - emotion weight from a single picture)
	*/

	m_SmileWeightings.close();

	std::cin.get();
}