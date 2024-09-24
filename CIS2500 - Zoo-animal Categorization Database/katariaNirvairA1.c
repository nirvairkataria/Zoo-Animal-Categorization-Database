#include "givenA1.h"

/* Task 1 - Takes a file, scans the contents and stores it in the Animal struct dataZoo*/
int readFromFile (char fName[30], struct Animal dataZoo [NUM_SAMPLES]) {
    FILE *fptr;
    fptr = fopen (fName, "r");
    if (fptr == NULL) {
        return -1;
    } else {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        fscanf(fptr, "%s", dataZoo[i].animalName);
        for (int j = 0; j < NUM_FEATURES; j++) {
            fscanf(fptr, "%d", &dataZoo[i].features[j]);
        }
        fscanf(fptr, "%d", &dataZoo[i].classLabel);
    }
    fclose(fptr);
    return 1;
    }
}

/* Task 2 - Takes an animal struct and a specific feature to find the mean and mode of that feature in the struct for */
int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode) {
    if (whichFeature > 16 || whichFeature < 1) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) { // loop to calculate the sum which will be used for average
        sum = sum + dataZoo[i].features[whichFeature - 1];
    }
    *mean =  ((float)sum / (float)NUM_SAMPLES);

    int occurences[NUM_SAMPLES];
    // populate the occurences array with all zeros
    for (int p = 0; p < NUM_SAMPLES; p++) {
        occurences[p] = 0;
    }
    // increase occurences by one for each feature index that has the same number
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_SAMPLES; j++) {
            if ((dataZoo[i].features[whichFeature - 1] == dataZoo[j].features[whichFeature - 1]) && (i != j)) {
                occurences[i]++;
            }
        }
    }
    
    // find which index of the occurence array has the most occurences
    int largestOccurenceIndex = 0;
    for (int f = 0; f < NUM_SAMPLES; f++) {
        if (occurences[f] > occurences[largestOccurenceIndex]) {
            largestOccurenceIndex = f;
        }
    }

    // if the largest index has a value of 0, there was no mode
    if (occurences[largestOccurenceIndex] == 0) {
        *mode = -1; // there is no mode
    } else {
        // the largestOccurenceIndex entry of the dataZoo will contain the mode of that specific feature
        *mode = dataZoo[largestOccurenceIndex].features[whichFeature - 1];
    }
    return 1;
}

/* Task 3 - Prints a histogram of the class distrubtion from the animal struct passed in */
void classDistribution (struct Animal dataZoo [NUM_SAMPLES]) {
    int classCounter[7];
    for (int i = 0; i < 8; i++) {
        classCounter[i] = 0;
    }
    // count the number of animals in each class
    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (dataZoo[i].classLabel == 1) {
            classCounter[0]++;
        } else if (dataZoo[i].classLabel == 2) {
            classCounter[1]++;
        } else if (dataZoo[i].classLabel == 3) {
            classCounter[2]++;
        } else if (dataZoo[i].classLabel == 4) {
            classCounter[3]++;
        } else if (dataZoo[i].classLabel == 5) {
            classCounter[4]++;
        } else if (dataZoo[i].classLabel == 6) {
            classCounter[5]++;
        } else if (dataZoo[i].classLabel == 7) {
            classCounter[6]++;
        }
    }

    // notes the class with the highest frequency, since the histogram prints top down
    int mostFrequentClass = classCounter[0];
    for (int i = 0; i < 7; i++) {
        if (classCounter[i] > mostFrequentClass) {
            mostFrequentClass = classCounter[i];
        }
    }

    // prints the histogram, starting with the most frequent class and iterating downwards until it reaches the frequency of the other classes
    for (int i = mostFrequentClass; i > 0; i--) {
        printf("   ");
        for (int j = 0; j < 7; j++) {
            if (classCounter[j] >= i) {
                printf("*       ");
            } else {
                printf("        ");
            }
        }
        printf("\n");
    }

    for (int i = 1; i < 8; i++) {
        printf("Class %d\t", i);
    }
    printf("\n");
}

/* Task 4 - Prints the Euclidean Distance between two given samples */
float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    float eucDist;
    int sum = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        sum = sum + pow((vector1[i] - vector2[i]), 2);
    }
    eucDist = sqrt(sum);
    return eucDist; 
}

/* Task 5 - Prints the Hamming Distance between two given samples */
int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    int notTheSame = 0;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] != vector2[i]) {
            notTheSame++;
        }
    }
    return notTheSame; 
}

/* Task 6 - Prints the Jaccard Similarity between two given samples */
float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]) {
    int zeroPairs = 0;
    int onePairs = 0;
    float jacSim;
    for (int i = 0; i < NUM_FEATURES; i++) {
        if ((vector1[i] == vector2[i]) && (vector1[i] == 1)) {
            onePairs++;
        } else if ((vector1[i] == vector2[i]) && (vector1[i] == 0)) {
            zeroPairs++;
        }
    }

    jacSim = ((float)(onePairs) / (float)(NUM_FEATURES - zeroPairs));
    return jacSim;
}

/* Task 7 - Finds the "k" nearest neighbours for a new sample using the current dataZoo database */
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], 
    int newSample [NUM_FEATURES], 
    int k, 
    int whichDistanceFunction, 
    int kNearestNeighbors [NUM_SAMPLES]) {
       
       int comparisonValues[NUM_SAMPLES];
       int storedIndices[NUM_SAMPLES];

       if (whichDistanceFunction == 1) {
            for (int i = 0; i < NUM_SAMPLES; i++) {
                comparisonValues[i] = euclideanDistance(newSample, dataZoo[i].features);
                storedIndices[i] = i;
            }
        }

        if (whichDistanceFunction == 2) {
            for (int i = 0; i < NUM_SAMPLES; i++) {
                comparisonValues[i] = hammingDistance(newSample, dataZoo[i].features);
                storedIndices[i] = i;
            }
        }

        if (whichDistanceFunction == 3) {
            for (int i = 0; i < NUM_SAMPLES; i++) {
                comparisonValues[i] = jaccardSimilarity(newSample, dataZoo[i].features);
                storedIndices[i] = i;
            }
        }

        // The following sorting algorithm was provided from ChatGPT and has been cited in the next line
        // OpenAI. (2024, January 31). Sorting algorithm for finding k-nearest neighbors. Version 1.0. Retrieved from ChatGPT
        // Sorting the comparisonValues array in increasing order (using Bubble Sort)
        for (int i = 0; i < NUM_SAMPLES - 1; i++) {
                for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
                    if (comparisonValues[j] > comparisonValues[j + 1]) {
                        // Swap values if they are in the wrong order
                        int temp = comparisonValues[j];
                        comparisonValues[j] = comparisonValues[j + 1];
                        comparisonValues[j + 1] = temp;

                        int temp2 = storedIndices[j];
                        storedIndices[j] = storedIndices[j + 1];
                        storedIndices[j + 1] = temp2;
                    }
                }
            } // End of code provided from ChatGPT

        for (int f = 0; f < k; f++) {
            kNearestNeighbors[f] = storedIndices[f];
        }

    }

/* Task 8 - Predicts the class of the new sample based on its k nearest neighbours */
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int newSample [NUM_FEATURES], int k) {
    // the k nearest neighbours are already stored in neighborsForNewSample
    int kCounter = 0;
    int arrCounter = 0;
    int arrOfClasses[NUM_SAMPLES];

    // Fill arrOfClasses with the class labels of the k neighbours
    for (int i = 0; i < NUM_SAMPLES; i++) {
        if ((neighborsForNewSample[i] > -1) && (kCounter < k)) { // This checks if the index is empty and if k amount of values has been checked
            kCounter++;
            arrOfClasses[arrCounter] = dataZoo[neighborsForNewSample[i]].classLabel;
            arrCounter++;
        }
    }

    if (kCounter == 0) {
        return -1; // The above loop failed to find any k-neighbours
    }

    // Find the mode of the arrOfClasses, using the same array method used in task 2
    int numOccurences[arrCounter];
    for (int i = 0; i < arrCounter; i++) {
        numOccurences[i] = 0;
    }
    for (int i = 0; i < arrCounter; i++) {
        for (int j = 0; j < arrCounter; j++) {
            if ((arrOfClasses[i] == arrOfClasses[j]) && (i != j)) {
                numOccurences[i]++;
            }
        }
    }
    int indexHolder = 0;
    for (int i = 0; i < arrCounter; i++) {
        if (numOccurences[i] > numOccurences[indexHolder]) {
            indexHolder = i;
        }
    }

    // Assign the class to the sample
    int perdictedClass = arrOfClasses[indexHolder];
    return perdictedClass;
}

/* Task 9 - Calculates the accuracy of the predicted class with the actual classes provided from a new dataset */
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k) {
    int storedNeighbors [NUM_SAMPLES];
    int storedPredictedClass;
    int nPredictionsMade = 0;
    int nCorrect = 0;
    float accuracy;
    for (int i = 0; i < NUM_TEST_DATA; i++) {
        // Find the k nearest neighbours of each testData sample
        findKNearestNeighbors(dataZoo, testData[i].features, k, 1, storedNeighbors);
        storedPredictedClass = predictClass(dataZoo, storedNeighbors, testData[i].features, k);
        nPredictionsMade++;
        // If the prediction was correct, increase the number of correction predictions variable
        if (storedPredictedClass == testData[i].classLabel) {
            nCorrect++;
        }
    }
    accuracy = ((float) nCorrect) / ((float) nPredictionsMade);
    return accuracy;
}