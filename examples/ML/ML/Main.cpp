#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

std::ofstream m_Smile;

int main()
{
	/*
	FILE *fp;
	char str1[10], str2[10], str3[10], str4[10];

	fp = fopen("G:\\data1.csv", "r");
	if (NULL == fp)
	{
	printf("\nError in opening file.");
	return 0;
	}
	while (EOF != fscanf(fp, " %[^,], %[^,], %[^,], %s, %s, %s, %s ", str1, str2, str3, str4))
	{
	printf("\n%s %s %s %s", str1, str2, str3, str4);
	}
	fclose(fp);

	// [^,], ^ -it inverts logic , means match any string that does not contain comma then last , says to match comma that terminated previous string.
	*/

	// std::ios_bas::app - All output operations happen at the end of the file, appending to its existing contents.
	m_Smile.open("smile_learning.csv", std::ios_base::app);

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
	/*
	std::vector<int> top_lip_bottom_lip_distance;
	std::vector<int> left_eyebrow_left_eye_distance;
	std::vector<int> right_eyebrow_right_eye_distance;
	*/

	FILE *fp;
	char str1[10], str2[10];
	std::vector<int> learning_data;

	fp = fopen("../../smile.csv", "r");
	if (NULL == fp)
	{
		printf("\nError in opening file.");
		return 0;
	}

	while (EOF != fscanf(fp, " %[^,], %s, %s ", str1, str2))
	{
		learning_data.push_back(std::stoi(str1));
		learning_data.push_back(std::stoi(str2));
	}
	fclose(fp);

	/*
	for (auto c : learning_data)
		std::cout << c << std::endl;
	*/

	// the number of rows to cover all the feautres from one picture is 72 but because there's two colums and they are stored in 1D array we must divide the size 
	// by 144 to get the number of pictures examined.
	std::cout << "size: " << floor(learning_data.size() / 144) << std::endl;

	for (int i = 0; i < learning_data.size(); i += 144)
	{
		/*
		if (j % 2 == 0) // place in the learning data vector is even (0, 2, 4 ... 10)
			std::cout << "even j: " << j << " learning_data: " << learning_data.at(j) << std::endl;
		else // place in the learning data vector is odd (1, 3, 5 ... 13)
			std::cout << "odd  j: " << j << " learning_data: " << learning_data.at(j) << std::endl;
		*/

		// chin (17) [1] - (number of paired elements for the facial feature) [place in the .csv file + i]
		std::cout << "chin" << std::endl;
		//for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
		for (int i = 0; i < 34; i++) // we need to multiply it by 2 to get all the data since it's a 1D array
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			// create a vector of chin positions
			chin.push_back(learning_data.at(i));
		}
		// left eyebrow (5) [18]
		std::cout << "left eyebrow" << std::endl;
		//for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
		for (int i = 34; i < 44; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			left_eyebrow.push_back(learning_data.at(i));;
		}
		// right_eyebrow (5) [23]
		std::cout << "right eyebrow" << std::endl;
		//for (int i = (17 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2); i += 2)
		for (int i = 44; i < 54; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			right_eyebrow.push_back(learning_data.at(i));;;
		}
		// nose_bridge (4) [28]
		std::cout << "nose bridge" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i += 2)
		for (int i = 54; i < 62; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			nose_bridge.push_back(learning_data.at(i));
		}
		// nose_tip (5) [32]
		std::cout << "nose tip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i += 2)
		for (int i = 62; i < 72; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			nose_tip.push_back(learning_data.at(i));
		}
		// left_eye (6) [37]
		std::cout << "left eye" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i += 2)
		for (int i = 72; i < 84; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			left_eye.push_back(learning_data.at(i));
		}
		// right_eye (6) [43]
		std::cout << "right eye" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2); i += 2)
		for (int i = 84; i < 96; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			right_eye.push_back(learning_data.at(i));
		}
		// top_lip (12) [49]
		std::cout << "top lip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2); 
		//     i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2); i += 2)
		for (int i = 96; i < 120; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			top_lip.push_back(learning_data.at(i));
		}
		// bottom_lip (12) [61]
		std::cout << "bottom lip" << std::endl;
		//for (int i = (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2); 
		//     i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2 + 5 * 2 + 6 * 2 + 6 * 2 + 12 * 2 + 12 *  2); i += 2)
		for (int i = 120; i < 144; i++)
		{
			/*std::cout << learning_data.at(i) << ", ";
			std::cout << learning_data.at(i + 1) << std::endl;*/
			bottom_lip.push_back(learning_data.at(i));
		}

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
		// a distance of the left_eyebrow from the left_eye 
		// 5 - 6  = (5 pairs of numbers) - (6 pairs of numbers) = (even - odd) + ... + (even - odd) = 
		// (0 - 1) + (2 - 3) + (4 - 5) + (6 - 7) + (8 - 9) = -(weight value for the emotion)
		//                                                      
		// a distance of the right_eyebrow from the right_eye 
		// 5 - 6 (
		// a distance of the top_lip from the bottom_lip
		// 12 - 12
		// nose tip - nose bridge
		// 5 - 4
	}

	// append emotion weighted values (emv) for the smile
	// if (emv != any set of values in the file)
	m_Smile << 1 << ',' << 2 << ',' << 3 << std::endl; // ',' - makes it go to the next cell in the .csv file

	// 'chin', 17 * (a, b)
	std::cout << "chin" << std::endl;
	std::cout << "size: " << chin.size() % 17 << std::endl; // 0 means its okay
	for (int i = 0; i < 17 * 2; i += 2)
		std::cout << chin.at(i) << ", " << chin.at(i + 1) << std::endl;
	// 'left_eyebrow', 5 * (a, b)
	std::cout << "left_eyebrow" << std::endl;
	for (int i = 0; i < 5 * 2; i += 2)
		std::cout << left_eyebrow.at(i) << ", " << left_eyebrow.at(i + 1) << std::endl;
	// 'right_eyebrow', 5 * (a, b)
	std::cout << "right_eyebrow" << std::endl;
	for (int i = 0; i < 5 * 2; i += 2)
		std::cout << right_eyebrow.at(i) << ", " << right_eyebrow.at(i + 1) << std::endl;
	// 'nose_bridge', 4 * (a, b)
	std::cout << "nose_bridge" << std::endl;
	for (int i = 0; i < 4 * 2; i += 2)
		std::cout << nose_bridge.at(i) << ", " << nose_bridge.at(i + 1) << std::endl;
	// 'nose_tip', 5 * (a, b)
	std::cout << "nose_tip" << std::endl;
	for (int i = 0; i < 5 * 2; i += 2)
		std::cout << nose_tip.at(i) << ", " << nose_tip.at(i + 1) << std::endl;
	// 'left_eye', 6 * (a, b)
	std::cout << "left_eye" << std::endl;
	for (int i = 0; i < 6 * 2; i += 2)
		std::cout << left_eye.at(i) << ", " << left_eye.at(i + 1) << std::endl;
	// 'right_eye', 6 * (a, b)
	std::cout << "right_eye" << std::endl;
	for (int i = 0; i < 6 * 2; i += 2)
		std::cout << right_eye.at(i) << ", " << right_eye.at(i + 1) << std::endl;
	// 'top_lip', 12 * (a, b)
	std::cout << "top_lip" << std::endl;
	for (int i = 0; i < 12 * 2; i += 2)
		std::cout << top_lip.at(i) << ", " << top_lip.at(i + 1) << std::endl;
	// 'bottom_lip', 12 * (a, b)
	std::cout << "bottom_lip" << std::endl;
	for (int i = 0; i < 12 * 2; i += 2)
		std::cout << bottom_lip.at(i) << ", " << bottom_lip.at(i + 1) << std::endl;

	m_Smile.close();

	std::cin.get();
}