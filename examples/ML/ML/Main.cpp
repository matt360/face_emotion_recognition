#pragma warning(disable : 4996)

#include "FacialFeatures.h"

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

	//CalculateEmotionWeightingsForSmile();

    //facialFeatures.DisplayFacialFeaturesVectors();

	CheckEmotionFromPicture();

	//m_SmileWeightings.close();

	std::cin.get();
}

