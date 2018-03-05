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

    int smile_prob = CheckForSmile(smallest_weighting_vector_size);
    int sad_prob = CheckForSad(smallest_weighting_vector_size);
    int angry_prob = 1;

    int most_likely_emotion = std::min( { smile_prob, sad_prob, 1 } );
    bool smiley = most_likely_emotion == smile_prob;
    bool sad = most_likely_emotion == sad_prob;
    bool angry = most_likely_emotion == angry_prob;

    // the closer the value is to 0 the more likely it is to be this emotion
    std::cout << "\nIt is most likely ";
    if (smiley) std::cout << "(or) smiley face ";
    if (sad) std::cout << "(or) sad face";
    if (angry) std::cout << "(or) angry face\n";
}

int MachineLearning::CheckForSmile(int smallest_weighting_vector_size)
{
    // test only against the same amount of weightings from the test picture and tested picture
    int smile_prob = 0;
    for (int i = 0; i < smallest_weighting_vector_size; i++)
    {
        smile_prob += smileFeatures.weightingsVector.at(i) - pictureFeatures.weightingsVector.at(i);
    }
    // check for negative values
    if (smile_prob < 0)
        smile_prob = std::abs(smile_prob);
    // the closer the value is to 0 the more likely it is to be this emotion
    std::cout << std::endl;
    std::cout << "smile_prob " << smile_prob << std::endl;
    
    return smile_prob;
}

int MachineLearning::CheckForSad(int smallest_weighting_vector_size)
{
    // test only against the same amount of weightings from the test picture and tested picture
    int sad_prob = 0;
    for (int i = 0; i < smallest_weighting_vector_size; i++)
    {
        sad_prob += smileFeatures.weightingsVector.at(i) - pictureFeatures.weightingsVector.at(i);
    }
    // check for negative values
    if (sad_prob < 0)
        sad_prob = std::abs(sad_prob);
    // the closer the value is to 0 the more likely it is to be this emotion
    std::cout << "sad_prob " << sad_prob << std::endl;

    return sad_prob;
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
