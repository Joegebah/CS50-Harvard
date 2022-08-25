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

void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int sepiaHeight = 0; sepiaHeight < height; sepiaHeight++) {
        for (int sepiaWidth = 0; sepiaWidth < width; sepiaWidth++) {
            float originalBlue = image[sepiaHeight][sepiaWidth].rgbtBlue;
            float originalGreen = image[sepiaHeight][sepiaWidth].rgbtGreen;
            float originalRed = image[sepiaHeight][sepiaWidth].rgbtRed;

            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);

            bool blueHasOverflow = sepiaBlue > 255;
            bool greenHasOverflow = sepiaGreen > 255;
            bool redHasOverflow = sepiaRed > 255;

            if (blueHasOverflow) {
                sepiaBlue = 255;
            }

            if (greenHasOverflow) {
                sepiaGreen = 255;
            }

            if (redHasOverflow) {
                sepiaRed = 255;
            }

            image[sepiaHeight][sepiaWidth].rgbtBlue = sepiaBlue;
            image[sepiaHeight][sepiaWidth].rgbtGreen = sepiaGreen;
            image[sepiaHeight][sepiaWidth].rgbtRed = sepiaRed;
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
                bool lastRowIsCurrentlyIterated = heightIterator == 1;
                
                if (widthIsIterated && !lastRowIsCurrentlyIterated) {
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

