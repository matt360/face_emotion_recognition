#include "MachineLearning.h"

MachineLearning::MachineLearning()
{
	//m_FileData.open("/../../smile.csv");
}


MachineLearning::~MachineLearning()
{

}

int MachineLearning::GenerateLearningVectorFromFile()
{
    // file to store the .csv 
    //FILE *fp;
    // two chars to read from two columns in each row in the .csv file
    char str1[10], str2[10];

    // open the .csv file to read the data
    smile = fopen("../../smile.csv", "r");
    // check if the file was opened correctly
    if (NULL == smile)
    {
        printf("\nError in opening file.");
        return 0;
    }

    // read data into a vector from a .csv file with two columns
    while (EOF != fscanf(smile, " %[^,], %s, %s ", str1, str2))
    {
        learning_data.push_back(std::stoi(str1));
        learning_data.push_back(std::stoi(str2));
    }
    // close the file after reading the data into the vector
    fclose(smile);
}

void MachineLearning::Learn()
{
    GenerateLearningVectorFromFile();

    smileFeatures.PopulateFacialFeaturesVectors(learning_data);

    smileFeatures.CalculateEmotionWeightings();

    smileFeatures.DisplayFacialFeaturesVectors();
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
