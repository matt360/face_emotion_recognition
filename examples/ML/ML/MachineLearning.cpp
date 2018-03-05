#include "MachineLearning.h"

MachineLearning::MachineLearning()
{
	//m_FileData.open("/../../smile.csv");
}


MachineLearning::~MachineLearning()
{

}

void MachineLearning::Learn()
{
	
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
