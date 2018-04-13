#include "MachineLearning.h"

int main()
{
    MachineLearning machineLearning;
    // Learn to recognize emotions
    machineLearning.Learn();
    // Pass a picture to recognize an emotion from
    std::string output;
   while(true)
   {
        output = machineLearning.LearnPicture();
        /* because LearnPicture function alwyas returns a string in a fashion: "../../string.csv" (It adds a path and a file extension)
        it's easier to see if the LearnPicture function has returned 'exit' in a fashion: "../../exit.csv" */
        if (output == "../../exit.csv")
            return 0;
        machineLearning.RecognizeEmotion();
    }
}

