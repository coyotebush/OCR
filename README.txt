Omophagic Content Reader
=====

Summary
-----
This program identifies text in a bitmap image.
Given a bitmap image and a supported font name, the text
recognized in the image will be printed.

Compilation
-----
    make all

Usage
-----
    ocr <font name> <bitmap filename>

Learning a font
-----
A font data generation program is also provided.
The input to this program must consist of any number of bitmap
images, each containing the characters in "characters.txt" in 
the desired font. Font data will be printed to standard output
and should be redirected to a file.
Usage:

    ocr-learn <image file>... > font/myfont.font

Supported fonts
-----
The text in the input image must be in a supported font.
Currently, the fonts supported are:

 - FreeSans
 - FreeMono