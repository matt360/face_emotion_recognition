//#pragma once
//
//#include <iterator>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <string>
//
//class CSVRow
//{
//public:
//	std::string const& operator[](std::size_t index) const
//	{
//		return m_data[index];
//	}
//	std::size_t size() const
//	{
//		return m_data.size();
//	}
//	void readNextRow(std::istream& str)
//	{
//		std::string         line;
//		std::getline(str, line);
//
//		std::stringstream   lineStream(line);
//		std::string         cell;
//
//		m_data.clear();
//		while (std::getline(lineStream, cell, ','))
//		{
//			m_data.push_back(cell);
//		}
//		// This checks for a trailing comma with no data after it.
//		if (!lineStream && cell.empty())
//		{
//			// If there was a trailing comma then add an empty element.
//			m_data.push_back("");
//		}
//	}
//private:
//	std::vector<std::string>    m_data;
//};
//
//std::istream& operator >> (std::istream& str, CSVRow& data)
//{
//	data.readNextRow(str);
//	return str;
//}
//
//int main()
//{
//	std::ifstream file("\..\smile.csv");
//
//	CSVRow row;
//	while (file >> row)
//	{
//		std::cout << "4th Element(" << row[1] << ")\n";
//	}
//
//	std::cin.get();
//}
//

#pragma warning(disable : 4996)

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main()
{

	FILE *fp;
	char str1[10], str2[10], str3[10], str4[10];

	fp = fopen("../../smile.csv", "r");
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

	std::cin.get();
}
