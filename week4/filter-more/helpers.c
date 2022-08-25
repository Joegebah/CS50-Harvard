#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int grayscaleHeight = 0; grayscaleHeight < height; grayscaleHeight++) {
        for (int grayscaleWidth = 0; grayscaleWidth < width; grayscaleWidth++) {
            int averageColorValue = round((image[grayscaleHeight][grayscaleWidth].rgbtBlue + image[grayscaleHeight][grayscaleWidth].rgbtGreen + image[grayscaleHeight][grayscaleWidth].rgbtRed) / 3.0);
            image[grayscaleHeight][grayscaleWidth].rgbtBlue = averageColorValue;
            image[grayscaleHeight][grayscaleWidth].rgbtGreen = averageColorValue;
            image[grayscaleHeight][grayscaleWidth].rgbtRed = averageColorValue;
        }
    }

    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int reflectedHeight = 0; reflectedHeight < height; reflectedHeight++) {
        for (int reflectedWidth = 0; reflectedWidth < width; reflectedWidth++) {
            image[reflectedHeight][reflectedWidth] = image[reflectedHeight][width * 2 - reflectedWidth];
        }
    }

    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    int averageBlue;
    int averageGreen;
    int averageRed;

    for (int blurHeight = 0; blurHeight < height; blurHeight++) {
        for (int blurWidth = 0; blurWidth < width; blurWidth++) {
            bool allSumsAreComputed = false;
            int heightIterator = -1;
            int widthIterator = -1;
            float validCounter = 1.0;
            int originalBlueValue = image[blurHeight][blurWidth].rgbtBlue;
            int originalGreenValue = image[blurHeight][blurWidth].rgbtGreen;
            int originalRedValue = image[blurHeight][blurWidth].rgbtRed;
            int currentBlurBlueValue;
            int currentBlurGreenValue;
            int currentBlurRedValue;
            int sumOfBlue = originalBlueValue;
            int sumOfGreen = originalGreenValue;
            int sumOfRed = originalRedValue;
            
            while (!allSumsAreComputed) {
                currentBlurBlueValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtBlue;
                currentBlurGreenValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtGreen;
                currentBlurRedValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtRed;

                bool adjacentPixelIsValid = (blurHeight + heightIterator) >= 0 && (blurHeight + heightIterator) < height && (blurWidth + widthIterator) >= 0 && (blurWidth + widthIterator) < width;
                bool isActuallyOriginalValue = heightIterator == blurHeight && widthIterator == blurWidth;

                if (adjacentPixelIsValid && !isActuallyOriginalValue) {
                    sumOfBlue = sumOfBlue + currentBlurBlueValue;
                    sumOfGreen = sumOfGreen + currentBlurGreenValue;
                    sumOfRed = sumOfRed + currentBlurRedValue;
                    validCounter++;
                }

                widthIterator++;
                bool widthIsIterated = widthIterator == 1;
                bool lastRowIsIterated = heightIterator == 1;
                
                if (widthIsIterated && !lastRowIsIterated) {
                    heightIterator++;
                    widthIterator = -1;
                }

                bool blockIsIteratedThrough = heightIterator == 1 && widthIterator == 1;

                if (blockIsIteratedThrough) {
                    allSumsAreComputed = true;
                }
            }

            averageBlue = round(sumOfBlue / validCounter);
            averageGreen = round(sumOfGreen / validCounter);
            averageRed =round(sumOfRed / validCounter);

            image[blurHeight][blurWidth].rgbtBlue = averageBlue;
            image[blurHeight][blurWidth].rgbtGreen = averageGreen;
            image[blurHeight][blurWidth].rgbtRed = averageRed;
        } 
    }

    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width]) {
    for (int edgeHeight = 0; edgeHeight < height; edgeHeight++) {
        for (int edgeWidth = 0; edgeWidth < width; edgeWidth++) {
            bool allKernelCasesForGxAreComputed = false;
            bool allKernelCasesForGyAreComputed = false;
            int heightIterator = -1;
            int widthIterator = -1;
            int currentBlurBlueValue;
            int currentBlurGreenValue;
            int currentBlurRedValue;
            int sumOfBlueGx = 0;
            int sumOfGreenGx = 0;
            int sumOfRedGx = 0;
            int sumOfBlueGy = 0;
            int sumOfGreenGy = 0;
            int sumOfRedGy = 0;

            while (!allKernelCasesForGxAreComputed) {
                currentBlurBlueValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtBlue;
                currentBlurGreenValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtGreen;
                currentBlurRedValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtRed;

                bool adjacentPixelIsValid = (edgeHeight + heightIterator) >= 0 && (edgeHeight + heightIterator) < height && (edgeWidth + widthIterator) >= 0 && (edgeWidth + widthIterator) < width;
                bool upperLeftNeighborIsAdressed = heightIterator == -1 && widthIterator == -1;
                bool upperRightNeighborIsAdressed = heightIterator == -1 && widthIterator == 1;
                bool leftNeighborIsAdressed = heightIterator == 0 && widthIterator == -1;
                bool rightNeighborIsAdressed = heightIterator == 0 && widthIterator == 1;
                bool lowerLeftNeighborIsAdressed = heightIterator == 1 && widthIterator == -1;
                bool lowerRightNeighborIsAdressed = heightIterator == 1 && widthIterator == 1;
                bool sumOfBlueGxHasOverflow = sumOfBlueGx > 255;
                bool sumOfGreenGxHasOverflow = sumOfGreenGx > 255;
                bool sumOfRedGxHasOverflow = sumOfRedGx > 255;
                bool isActuallyOriginalValue = heightIterator == edgeHeight && widthIterator == edgeWidth;

                if (!adjacentPixelIsValid) {
                    currentBlurBlueValue = 0;
                    currentBlurGreenValue = 0;
                    currentBlurRedValue = 0;
                }
 
                if (upperLeftNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * -1);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue * -1);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue * -1);
                }

                if (leftNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * -2);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue  * -2);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue  * -2);
                }

                if (lowerLeftNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * -1);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue  * -1);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue  * -1);
                }

                if (upperRightNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * 1);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue  * 1);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue  * 1);
                }

                if (rightNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * 2);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue  * 2);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue  * 2);
                }

                if (lowerRightNeighborIsAdressed) {
                    sumOfBlueGx = sumOfBlueGx + (currentBlurBlueValue * 1);
                    sumOfGreenGx = sumOfGreenGx + (currentBlurGreenValue  * 1);
                    sumOfRedGx = sumOfRedGx + (currentBlurRedValue  * 1);
                }
            
                bool widthIsIterated = widthIterator == 1;
                bool lastRowIsIterated = heightIterator == 1;
                
                if (widthIsIterated && !lastRowIsIterated) {
                    heightIterator++;
                    widthIterator = -1;
                }

                bool blockIsIteratedThrough = heightIterator == 1 && widthIterator == 1;

                if (blockIsIteratedThrough) {
                    allKernelCasesForGxAreComputed = true;

                    if (sumOfBlueGxHasOverflow) {
                        sumOfBlueGx = 255;
                    }

                    if (sumOfGreenGxHasOverflow) {
                        sumOfGreenGx = 255;
                    }

                    if (sumOfRedGxHasOverflow) {
                        sumOfRedGx = 255;
                    }
                }
                
                widthIterator++;
            }
            
            heightIterator = -1;
            widthIterator = -1;

            while (!allKernelCasesForGyAreComputed) {
                currentBlurBlueValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtBlue;
                currentBlurGreenValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtGreen;
                currentBlurRedValue = image[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtRed;

                bool adjacentPixelIsValid = (edgeHeight + heightIterator) >= 0 && (edgeHeight + heightIterator) < height && (edgeWidth + widthIterator) >= 0 && (edgeWidth + widthIterator) < width;
                bool upperLeftNeighborIsAdressed = heightIterator == -1 && widthIterator == -1;
                bool lowerLeftNeighborIsAdressed = heightIterator == 1 && widthIterator == -1;
                bool upperMiddleNeighborIsAdressed = heightIterator == -1 && widthIterator == 0;
                bool lowerMiddleNeighborIsAdressed = heightIterator == 1 && widthIterator == 0;
                bool upperRightNeighborIsAdressed = heightIterator == -1 && widthIterator == 1;
                bool lowerRightNeighborIsAdressed = heightIterator == 1 && widthIterator == 1;
                bool sumOfBlueGyHasOverflow = sumOfBlueGy > 255;
                bool sumOfGreenGyHasOverflow = sumOfGreenGy > 255;
                bool sumOfRedGyHasOverflow = sumOfRedGy > 255;
                bool isActuallyOriginalValue = heightIterator == edgeHeight && widthIterator == edgeWidth;

                if (!adjacentPixelIsValid) {
                    currentBlurBlueValue = 0;
                    currentBlurGreenValue = 0;
                    currentBlurRedValue = 0;
                }

                if (upperLeftNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * -1);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * -1);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * -1);
                }

                if (upperMiddleNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * -2);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * -2);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * -2);
                }
                
                if (upperRightNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * -1);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * -1);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * -1);
                }

                if (lowerLeftNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * 1);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * 1);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * 1);
                }

                if (lowerMiddleNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * 2);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * 2);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * 2);
                }

                if (lowerRightNeighborIsAdressed) {
                    sumOfBlueGy = sumOfBlueGy + (currentBlurBlueValue * 1);
                    sumOfGreenGy = sumOfGreenGy + (currentBlurGreenValue  * 1);
                    sumOfRedGy = sumOfRedGy + (currentBlurRedValue  * 1);
                }
            
                bool widthIsIterated = widthIterator == 1;
                bool lastRowIsIterated = heightIterator == 1;
                
                if (widthIsIterated && !lastRowIsIterated) {
                    heightIterator++;
                    widthIterator = -1;
                }

               
                bool blockIsIteratedThrough = heightIterator == 1 && widthIterator == 1;

                if (blockIsIteratedThrough) {
                    allKernelCasesForGyAreComputed = true;
                    
                    if (sumOfBlueGyHasOverflow) {
                        sumOfBlueGy = 255;
                    }

                    if (sumOfGreenGyHasOverflow) {
                        sumOfGreenGy = 255;
                    }

                    if (sumOfRedGyHasOverflow) {
                        sumOfRedGy = 255;
                    }
                }

                widthIterator++;
            }

            int gxAndGyCombinedBlue = sqrt(pow(sumOfBlueGx, 2) + pow(sumOfBlueGy, 2));
            int gxAndGyCombinedGreen = sqrt(pow(sumOfGreenGx, 2) + pow(sumOfGreenGy, 2));
            int gxAndGyCombinedRed = sqrt(pow(sumOfRedGx, 2) + pow(sumOfRedGy, 2));
            bool combinedBlueHasOverflow = gxAndGyCombinedBlue > 255;
            bool combinedGreenHasOverflow = gxAndGyCombinedGreen > 255;
            bool combinedRedHasOverflow = gxAndGyCombinedRed > 255;

            if (combinedBlueHasOverflow) {
                gxAndGyCombinedBlue = 255;
            }

            if (combinedGreenHasOverflow) {
                gxAndGyCombinedGreen = 255;
            }

            if (combinedRedHasOverflow) {
                gxAndGyCombinedRed = 255;
            }

            image[edgeHeight][edgeWidth].rgbtBlue = gxAndGyCombinedBlue;
            image[edgeHeight][edgeWidth].rgbtGreen = gxAndGyCombinedGreen;
            image[edgeHeight][edgeWidth].rgbtRed = gxAndGyCombinedRed;
        }
    }
   
   return;
}
