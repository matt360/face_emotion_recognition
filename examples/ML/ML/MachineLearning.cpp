#include "MachineLearning.h"

MachineLearning::MachineLearning()
{
}

MachineLearning::~MachineLearning()
{
}

int MachineLearning::GenerateLearningVectorFromFile(const char* emotion_learning_file, std::vector<int>& learning_data)
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
    while (EOF != fscanf(file, " %[^,], %s, %s ", str1, str2))
    {
        learning_data.push_back(std::stoi(str1));
        learning_data.push_back(std::stoi(str2));
    }
    // close the file after reading the data into the vector
    fclose(file);
}

void MachineLearning::Learn()
{
    GenerateLearningVectorFromFile("../../smile.csv", smileFeatures.learning_data);
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

    // CHECK FOR SMILE
    smileFeatures.PopulateFacialFeaturesVectors(smileFeatures.learning_data);
    smileFeatures.CalculateEmotionWeightings("smile_weightings.csv");
    //smileFeatures.DisplayFacialFeaturesVectors();

    pictureFeatures.PopulateFacialFeaturesVectors(smileFeatures.learning_data);
    pictureFeatures.CalculateEmotionWeightings("picture_weightings.csv");
    //pictureFeatures.DisplayFacialFeaturesVectors();

}












/*float data[100][100];
std::ifstream file("/../../smile.csv");

std::cout <<  << std::endl;

for (int row = 0; row < 100; ++row)
{
std::string line;
std::getline(file, line);
if (!file.good())
break;

std::stringstream iss(line);

for (int col = 0; col < 100; ++col)
{
std::string val;
std::getline(iss, val, ',');
if (!iss.good())
break;

std::stringstream convertor(val);
convertor >> data[row][col];
}
}

std::cout << data[0][0] << std::endl;*/

//	if (!m_FileData.is_open()) std::cout << "ERROR: File Open" << '\n';
//
//	/*string firstname;
//	string lastname;
//	string age;
//	string weight;
//*/
//	while (m_FileData.good()) {
//
//		/*getline(ip, firstname, ',');
//		getline(ip, lastname, ',');
//		getline(ip, age, ',');
//		getline(ip, weight, '\n');
//
//		std::cout << "Name: " << firstname << " " << lastname << '\n';
//		std::cout << "Age: " << age << '\n';
//		std::cout << "Weight: " << weight << '\n';
//		std::cout << "-------------------" << '\n';*/
//		std::string line;
//		std::getline(m_FileData, line, ',');
//
//	}
//
//	m_FileData.close();

//void MachineLearning::CheckEmotionFromPicture()
//{
//    /*
//    Check emtion from a picture:
//    - Read facial features of a single face from a file
//    - Create facial features vector
//    - Create an emotion weighted vector
//    - Read emotion weighting from a file (in a group of 3)
//    - Create emotion weighted vectors (in a group of 3)
//    - Compare the emotion weighted vector (of a single face) with the emotion weighted vectors (created from the learning file),
//    like smile_weightings_vector, sad_weightenings_vector ect.
//    - The one with the least score is the most likely to be that emotion:
//    smile_probability.push_back(emotion weighted vectors(i) - emotion weight from a single picture)
//    */
//
//    /* Read facial features of a single face from a file */
//    // file to store the .csv 
//    FILE *fp;
//    // two chars to read from two columns in each row in the .csv file
//    char str1[10], str2[10];
//
//    // open the .csv file to read the data
//    fp = fopen("../../smile_test.csv", "r");
//    // check if the file was opened correctly
//    if (NULL == fp)
//    {
//        printf("\nError in opening file.");
//    }
//    else
//    {
//        // read data into a vector from a .csv file with two columns
//        while (EOF != fscanf(fp, " %[^,], %s, %s ", str1, str2))
//        {
//            /* Create facial features vector*/
//            facial_features_from_picture.push_back(std::stoi(str1));
//            facial_features_from_picture.push_back(std::stoi(str2));
//        }
//    }
//
//    /* Create emotion weighted vector */
//    //facial_features_from_picture
//
//    #if 0
//    /* Read emotion weighting from a file */
//    // close the file after reading the data into the vector
//    fclose(fp);
//
//    // file to store the .csv 
//    FILE *fpe;
//    // two chars to read from two columns in each row in the .csv file
//    char str1[10], str2[10];
//
//    // open the .csv file to read the data
//    fpe = fopen("smile_learning.csv", "r");
//    // check if the file was opened correctly
//    if (NULL == fp)
//    {
//        printf("\nError in opening file.");
//    }
//    else
//    {
//        // read data into a vector from a .csv file with two columns
//        while (EOF != fscanf(fpe, " %[^,], %s, %s ", str1, str2))
//        {
//            /* Create emotion weighting vectors */
//            smile_weightings.push_back(std::stoi(str1));
//            smile_weightings.push_back(std::stoi(str2));
//        }
//    }
//    // close the file after reading the data into the vector
//    fclose(fp);
//    #endif // 0
//
//}
