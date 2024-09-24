#include "givenA1.h"

int main() {
    struct Animal dataZoo [NUM_SAMPLES];
	struct Animal testData [NUM_SAMPLES];
	
	char nameOfTestFile[30];
	strcpy(nameOfTestFile, "textData.txt");
	readFromFile(nameOfTestFile, testData); 

	char nameOfFile[30];
    int fileReadStatus;
	
    int mode = -1;
    float mean = -1;
	
	int featureNumber;
	int sampleChoice1;
	int sampleChoice2;

	float euclidTest;
	int hammingTest;
	float jaccardTest;
	
	int userK = -1;
	int userDistanceFunction;
	
	
	int calfSampleFeatures[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
	int newSameNeighbors [NUM_SAMPLES];
	
	int predictedClass;
	
	float userAccuracy;
	
	
	int choice = -1;

	// For first time running
	while (choice == -1) {
		printf("Enter the file name you would like to load Animal data from\n");
		scanf("%s", nameOfFile);
		fileReadStatus = readFromFile(nameOfFile, dataZoo);
        if (fileReadStatus == 1) {
            printf("Reading for a file with name %s was successful\n\n", nameOfFile);
			choice = 1;
        }
        if (fileReadStatus == -1) {
            printf("Reading for a file with name %s was unsuccessful\n\n", nameOfFile);
        }
	}

	while ((choice > 0) && (choice < 10)) {
		printf("Please enter an integer from 1 to 9 to select a function - If any other integer is input the program will end\n");
		printf("1 - Read from a given file name\n");
		printf("2 - Calculate the mean and mode of a specific feature\n");
		printf("3 - Display the class distribution histogram\n");
		printf("4 - Calculate the euclidian distance between 2 samples\n");
		printf("5 - Calculate the hamming distance between 2 samples\n");
		printf("6 - Calculate the jaccard similarity between 2 samples\n");
		printf("7 - Find an integer amount of nearest neighbours between the data structure and a new sample\n");
		printf("8 - Predict the class label of a new sample\n");
		printf("9 - Find the accuracy of the algorithm used in this program\n\n");
		
		scanf("%d", &choice);
		if (choice == 1) {
			printf("Enter the file name you would like to load Animal data from\n");
			scanf("%s", nameOfFile);
			fileReadStatus = readFromFile(nameOfFile, dataZoo);
            if (fileReadStatus == 1) {
                printf("Reading for a file with name %s was successful\n\n", nameOfFile);
            }
            if (fileReadStatus == -1) {
                printf("Reading for a file with name %s was unsuccessful\n\n", nameOfFile);
            }
		}
		if (choice == 2) {
			printf("Enter the feature number (1 to 16) you would like to store the mean and mode of\n");
			scanf("%d", &featureNumber);
            printf("You have chosen to test feature %d\n", featureNumber);
			generateStatisticsFeatureX(dataZoo, featureNumber, &mean, &mode);
			printf("The mean for your selected feature is %f\n", mean);
			printf("The mode for your selected feature is %d\n\n", mode);
		}
		if (choice == 3) {
			printf("Class Distribution Histogram\n\n\n");
			classDistribution(dataZoo);
		}
		if (choice == 4) {
			printf("Enter 2 sample numbers (both from 0 to 99) to use from the database and calculate its Euclidean Distance\n");
			scanf("%d %d", &sampleChoice1, &sampleChoice2);
			euclidTest = euclideanDistance(dataZoo[sampleChoice1].features, dataZoo[sampleChoice2].features);
			printf("The calculated euclidean distance is %f\n", euclidTest);
		}
		if (choice == 5) {
			printf("Enter 2 sample numbers (both from 0 to 99) to use from the database and calculate its Hamming Distance\n");
			scanf("%d %d", &sampleChoice1, &sampleChoice2);
			hammingTest = hammingDistance(dataZoo[sampleChoice1].features, dataZoo[sampleChoice2].features);
			printf("The calculated hamming distance is %d\n", hammingTest);
		}
		if (choice == 6) {
			printf("Enter 2 sample numbers (both from 0 to 99) to use from the database and calculate its jaccardSimilarity\n");
			scanf("%d %d", &sampleChoice1, &sampleChoice2);
			jaccardTest = jaccardSimilarity(dataZoo[sampleChoice1].features, dataZoo[sampleChoice2].features);
			printf("The calculated jaccard similarity is %f\n", jaccardTest);
		}
		if (choice == 7) {
			printf("Enter the number of nearest number of neighbors you would like to check for\n");
			scanf("%d", &userK);
			printf("Which distance function would you like to use? Enter 1 for Euclidean, 2 for Hamming, or 3 for Jaccard Similarity\n");
			scanf("%d", &userDistanceFunction);
			if ((userDistanceFunction > 0) && (userDistanceFunction < 4)) {
				findKNearestNeighbors(dataZoo, calfSampleFeatures, userK, userDistanceFunction, newSameNeighbors);
				printf("Done. Run function 8 to predict the class for this new sample based on its k nearest neighbors\n");
			} else {
				printf("That is not in the range of valid distance functions. Please run this function again and try again.\n");
			}
		}
		if ((choice == 8) && (userK > -1)) {
			printf("The class prediction for the sample is:\n");
			predictedClass = predictClass(dataZoo, newSameNeighbors, calfSampleFeatures, userK);
			printf("%d\n", predictedClass);
		} else if (choice == 8) {
			printf("You must run function 7 first in order to establish kNeighbors\n");
		}
		if (choice == 9) {
            printf("Enter the number of k nearest neighbors to check the accuracy for: \n");
            scanf("%d", &userK);
            printf("\n");
			printf("This function will print the accuracy using the Euclidean distance:\n");
			userAccuracy = findAccuracy(dataZoo, testData, userK);
			printf("%f\n", userAccuracy);
		}
	}
}