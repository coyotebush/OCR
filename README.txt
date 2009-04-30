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



Supported fonts
-----
The text in the input image must be in a supported font.
Currently, the fonts supported are:

 - FreeSans
 - FreeMono
 
Learning a font
-----
A font data generation program is also provided.
The parameters for this program consist of a font name for data storage,
followed by the filenames of any number of bitmap images, each containing the
below characters in the desired font.

    ./0123456789?@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz

Usage:

    ocr-learn myfont myfont1.bmp myfont2.bmp...