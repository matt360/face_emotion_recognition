#pragma once

#include "FacialFeatures.h"

class MachineLearning
{
public:
    MachineLearning();
    ~MachineLearning();

    void Learn();

private:

};
	


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
