#pragma warning(disable : 4996)

#include "MachineLearning.h"

int main()
{
    MachineLearning machineLearning;
    machineLearning.Learn();
    machineLearning.RecognizeEmotion();

	std::cin.get();
}

