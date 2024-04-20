# PPM Image Editor

## Description

This program allows the user to perform various image processing operations on PPM (Portable Pixmap) format images. Supported operations include converting to grayscale, creating a negative, adjusting brightness, rotating the image, and applying an aging effect.

## Features

- **Grayscale Conversion:** Converts the image to grayscale using luminosity method.
- **Negative Image:** Generates the negative of the image.
- **Brightness Adjustment:** Increases or decreases the image brightness.
- **Image Rotation:** Rotates the image by 90 degrees.
- **Aging Effect:** Applies an aging effect, reducing the brightness slightly.

## Prerequisites

To compile and run this program, you need a C compiler (like GCC) and a standard C library.

## Compilation

Compile the program using the following GCC command:

```bash
gcc -o ppm-editor ppm-editor.c
```

## Usage

Run the program using:

```bash
./image_processor
```

## Input

The program expects a file name of the PPM image as input.
It reads the PPM file, applies selected effects based on user choices, and outputs a new PPM file named resultado.ppm.
Output
Outputs the processed image in PPM format as resultado.ppm.
The image will have the same dimensions and format as the input unless rotated (dimensions will swap).

## Limitations
- Only supports PPM format.
- There's minimal error handling for file operations.

## Example
Here is how to use the program:
1. Compile the program.
2. Run the executable
3. Enter the filename of the PPM image
4. Choose the effects you want to apply one by one
5. The final image will be saved as resultado.ppm
