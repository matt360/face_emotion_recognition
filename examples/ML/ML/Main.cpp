#pragma warning(disable : 4996)

#include <iostream>
#include <sstream>
#include <vector>

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

	FILE *fp;
	char str1[10], str2[10];
	std::vector<int> learning_data;
	std::vector<int> top_lip_bottom_lip_distance;
	std::vector<int> left_eyebrow_left_eye_distance;
	std::vector<int> right_eyebrow_right_eye_distance;

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

	for (int i = 0; i < learning_data.size() / 144; i++)
	{
		//for (int j = 0; j < 72 * 2; j++)
		//{
			/*
			if (j % 2 == 0) // place in the learning data vector is even (0, 2, 4 ... 10)
				std::cout << "even j: " << j << " learning_data: " << learning_data.at(j) << std::endl;
			else // place in the learning data vector is odd (1, 3, 5 ... 13)
				std::cout << "odd  j: " << j << " learning_data: " << learning_data.at(j) << std::endl;
			*/

			// chin
			std::cout << "chin" << std::endl;
			for (int i = 0; i < 17 * 2; i += 2) // we need to multiply it by 2 to get all the data since it's a 1D array
			{
				std::cout << learning_data.at(i) << std::endl;
				std::cout << learning_data.at(i + 1) << std::endl;
			}
			// left eyebrow 
			std::cout << "left eyebrow" << std::endl;
			for (int i = 17 * 2; i < (17 * 2 + 5 * 2); i += 2)
			{
				std::cout << learning_data.at(i) << std::endl;
				std::cout << learning_data.at(i + 1) << std::endl;
			}
			// right_eyebrow
			std::cout << "right eyebrow" << std::endl;
			for (int i = (17 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2); i += 2)
			{
				std::cout << learning_data.at(i) << std::endl;
				std::cout << learning_data.at(i + 1) << std::endl;
			}
			// nose_bridge 
			std::cout << "nose bridge" << std::endl;
			for (int i = (17 * 2 + 5 * 2 + 5 * 2); i < (17 * 2 + 5 * 2 + 5 * 2 + 4 * 2); i += 2)
			{
				std::cout << learning_data.at(i) << std::endl;
				std::cout << learning_data.at(i + 1) << std::endl;
			}
			//// nose_tip   
			//for (int i = 17 + 5 + 5 + 4; i < 17 + 5 + 5 + 4 + 5; ++i)
			//{

			//}
			//// left_eye    
			//for (int i = 17 + 5 + 5 + 4 + 5; i < 17 + 5 + 5 + 4 + 5 + 6; ++i)
			//{

			//}
			//// right_eye
			//for (int i = 17 + 5 + 5 + 4 + 5 + 6; i < 17 + 5 + 5 + 4 + 5 + 6 + 6; ++i)
			//{

			//}
			//// top_lip     
			//for (int i = 17 + 5 + 5 + 4 + 5 + 6 + 6; i < 17 + 5 + 5 + 4 + 5 + 6 + 6 + 12; ++i)
			//{

			//}
			//// bottom_lip
			//for (int i = 17 + 5 + 5 + 4 + 5 + 6 + 6 + 12; i < 17 + 5 + 5 + 4 + 5 + 6 + 6 + 12 + 12; ++i)
			//{

			//}

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

			// a distance of the right_eyebrow from the right_eye 

			// a distance of the top_lip from the bottom_lip
		//}

	}

	std::cin.get();
}
