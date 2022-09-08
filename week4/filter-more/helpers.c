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
            int validCounter = 1;
            int originalBlueValue = image[blurHeight][blurWidth].rgbtBlue;
            int originalGreenValue = image[blurHeight][blurWidth].rgbtGreen;
            int originalRedValue = image[blurHeight][blurWidth].rgbtRed;
            int currentBlurBlueValue;
            int currentBlurGreenValue;
            int currentBlurRedValue;
            int sumOfBlue = originalBlueValue;
            int sumOfGreen = originalGreenValue;
            int sumOfRed = originalRedValue;
            
            for (int heightIterator = -1; heightIterator <= 1; heightIterator++) {
                for (int widthIterator = -1; widthIterator <= 1; widthIterator++) {
                    bool adjacentPixelIsValid = (blurHeight + heightIterator) >= 0 && (blurHeight + heightIterator) < height && (blurWidth + widthIterator) >= 0 && (blurWidth + widthIterator) < width;
                    bool isActuallyOriginalValue = heightIterator == blurHeight && widthIterator == blurWidth;

                    if (adjacentPixelIsValid) {
                        currentBlurBlueValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtBlue;
                        currentBlurGreenValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtGreen;
                        currentBlurRedValue = image[blurHeight + heightIterator][blurWidth + widthIterator].rgbtRed;
                    }

                    if (adjacentPixelIsValid && !isActuallyOriginalValue) {
                        sumOfBlue = sumOfBlue + currentBlurBlueValue;
                        sumOfGreen = sumOfGreen + currentBlurGreenValue;
                        sumOfRed = sumOfRed + currentBlurRedValue;
                        validCounter++;
                    }                    
                }   
            }

            averageBlue = round(sumOfBlue / validCounter);
            averageGreen = round(sumOfGreen / validCounter);
            averageRed = round(sumOfRed / validCounter);

            image[blurHeight][blurWidth].rgbtBlue = averageBlue;
            image[blurHeight][blurWidth].rgbtGreen = averageGreen;
            image[blurHeight][blurWidth].rgbtRed = averageRed;
        } 
    }

    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int copyHeight = 0; copyHeight < height; copyHeight++) {
        for (int copyWidth = 0; copyWidth < width; copyWidth++) {
            copy[copyHeight][copyWidth] = image[copyHeight][copyWidth];
        }
    }

    int sumOfBlueGx;
    int sumOfGreenGx;
    int sumOfRedGx;
    int sumOfBlueGy;
    int sumOfGreenGy;
    int sumOfRedGy;
    int currentEdgeBlueValue;
    int currentEdgeGreenValue;
    int currentEdgeRedValue;

    for (int edgeHeight = 0; edgeHeight < height; edgeHeight++) {
        for (int edgeWidth = 0; edgeWidth < width; edgeWidth++) {
            sumOfBlueGx = 0;
            sumOfGreenGx = 0;
            sumOfRedGx = 0;
            sumOfBlueGy = 0;
            sumOfGreenGy = 0;
            sumOfRedGy = 0;
            bool sumOfBlueGxHasOverflow = sumOfBlueGx > 255;
            bool sumOfGreenGxHasOverflow = sumOfGreenGx > 255;
            bool sumOfRedGxHasOverflow = sumOfRedGx > 255;
            bool sumOfBlueGyHasOverflow = sumOfBlueGy > 255;
            bool sumOfGreenGyHasOverflow = sumOfGreenGy > 255;
            bool sumOfRedGyHasOverflow = sumOfRedGy > 255;

            for(int heightIterator = -1; heightIterator <= 1; heightIterator++) {
                for (int widthIterator = -1; widthIterator <= 1; widthIterator++) {      
                    bool adjacentPixelIsValid = (edgeHeight + heightIterator) >= 0 && (edgeHeight + heightIterator) < height && (edgeWidth + widthIterator) >= 0 && (edgeWidth + widthIterator) < width;
                    bool upperRowIsIterated = heightIterator == -1;
                    bool middleRowIsIterated = heightIterator == 0;
                    bool lowerRowIsIterated = heightIterator == -1;
                    bool upperLeftNeighborIsAdressed = widthIterator == -1;
                    bool upperRightNeighborIsAdressed = widthIterator == 1;
                    bool leftNeighborIsAdressed = widthIterator == -1;
                    bool rightNeighborIsAdressed = widthIterator == 1;
                    bool lowerLeftNeighborIsAdressed = widthIterator == -1;
                    bool lowerRightNeighborIsAdressed = widthIterator == 1;

                    if (adjacentPixelIsValid) {
                        currentEdgeBlueValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtBlue;
                        currentEdgeGreenValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtGreen;
                        currentEdgeRedValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtRed;
                    }
                    else {
                        currentEdgeBlueValue = 0;
                        currentEdgeGreenValue = 0;
                        currentEdgeRedValue = 0;
                    }

                    if (upperRowIsIterated) {
                        if (upperLeftNeighborIsAdressed) {
                            sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * -1);
                            sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue * -1);
                            sumOfRedGx = sumOfRedGx + (currentEdgeRedValue * -1);
                        }

                        if (upperRightNeighborIsAdressed) {
                        sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * 1);
                        sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue  * 1);
                        sumOfRedGx = sumOfRedGx + (currentEdgeRedValue  * 1);
                        }
                    }
                    
                    if (middleRowIsIterated) {
                        if (leftNeighborIsAdressed) {
                            sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * -2);
                            sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue  * -2);
                            sumOfRedGx = sumOfRedGx + (currentEdgeRedValue  * -2);
                        }

                        if (rightNeighborIsAdressed) {
                            sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * 2);
                            sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue  * 2);
                            sumOfRedGx = sumOfRedGx + (currentEdgeRedValue  * 2);
                        }
                    }
                    
                    if (lowerRowIsIterated) {
                        if (lowerLeftNeighborIsAdressed) {
                            sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * -1);
                            sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue  * -1);
                            sumOfRedGx = sumOfRedGx + (currentEdgeRedValue  * -1);
                        }

                        if (lowerRightNeighborIsAdressed) {
                            sumOfBlueGx = sumOfBlueGx + (currentEdgeBlueValue * 1);
                            sumOfGreenGx = sumOfGreenGx + (currentEdgeGreenValue  * 1);
                            sumOfRedGx = sumOfRedGx + (currentEdgeRedValue  * 1);
                        }
                    }
                }  
            }

            if (sumOfBlueGxHasOverflow) {
                sumOfBlueGx = 255;
            }

            if (sumOfGreenGxHasOverflow) {
                sumOfGreenGx = 255;
            }

            if (sumOfRedGxHasOverflow) {
                sumOfRedGx = 255;
            }
            
            for (int heightIterator = -1; heightIterator <= 1; heightIterator++) {
                for (int widthIterator = -1; widthIterator <= 1; widthIterator++) {
                    bool adjacentPixelIsValid = (edgeHeight + heightIterator) >= 0 && (edgeHeight + heightIterator) < height && (edgeWidth + widthIterator) >= 0 && (edgeWidth + widthIterator) < width;
                    bool upperRowIsIterated = heightIterator = -1;
                    bool lowerRowIsIterated = heightIterator = 1;
                    bool upperLeftNeighborIsAdressed = widthIterator == -1;
                    bool lowerLeftNeighborIsAdressed = widthIterator == -1;
                    bool upperMiddleNeighborIsAdressed = widthIterator == 0;
                    bool lowerMiddleNeighborIsAdressed = widthIterator == 0;
                    bool upperRightNeighborIsAdressed = widthIterator == 1;
                    bool lowerRightNeighborIsAdressed = widthIterator == 1;

                    if (adjacentPixelIsValid) {
                        currentEdgeBlueValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtBlue;
                        currentEdgeGreenValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtGreen;
                        currentEdgeRedValue = copy[edgeHeight + heightIterator][edgeWidth + widthIterator].rgbtRed;
                    }
                    else {
                        currentEdgeBlueValue = 0;
                        currentEdgeGreenValue = 0;
                        currentEdgeRedValue = 0;
                    }

                    if (upperRowIsIterated) {
                        if (upperLeftNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * -1);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * -1);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * -1);
                        }

                        if (upperMiddleNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * -2);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * -2);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * -2);
                        }
                    
                    if (upperRightNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * -1);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * -1);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * -1);
                        }
                    }

                    if (lowerRowIsIterated) {
                        if (lowerLeftNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * 1);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * 1);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * 1);
                        }

                    if (lowerMiddleNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * 2);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * 2);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * 2);
                        }

                    if (lowerRightNeighborIsAdressed) {
                            sumOfBlueGy = sumOfBlueGy + (currentEdgeBlueValue * 1);
                            sumOfGreenGy = sumOfGreenGy + (currentEdgeGreenValue  * 1);
                            sumOfRedGy = sumOfRedGy + (currentEdgeRedValue  * 1);
                        }

                    }
                }
                
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

            int gxAndGyCombinedBlue = sqrt((sumOfBlueGx * sumOfBlueGx) + (sumOfBlueGy * sumOfBlueGy));
            int gxAndGyCombinedGreen = sqrt((sumOfGreenGx * sumOfGreenGx) + (sumOfGreenGy * sumOfGreenGy));
            int gxAndGyCombinedRed = sqrt((sumOfRedGx * sumOfRedGx) + (sumOfRedGy * sumOfRedGy));
            
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
