# Shiko Paint Tool

Rushed paint tool project created for GD1P03 2D Game Programming Assessment 1 Paint Tool.


## Table of Contents

- [Description]
- [Features]
- [Requirements]
- [Installation]
- [Controls]
- [Disclaimer]
- [Credits]


## Description

Shiko Paint Tool is a small program that allows the user to draw rectangles, ellipses, and lines onto a 1600 x 900 canvas. 
This program is designed with C++ and to be operated with mouse and keyboard controls. 


## Features

Shiko Paint Tool has 4 windows; Menu, Canvas, and 2 Colour windows.
Menu - Includes clickable buttons that allow the user to save the current state of the canvas into a .png file, load an image onto the canvas, select a desired tool to draw shapes, change the size of lines and outlines.
Canvas - Allows the user to draw objects onto a canvas, allows the user to zoom in and out and also drag the canvas in the window with the mouse scroll wheel and button. 
Colour Windows - On click, allows the user to change the colour of fill or line/outline.


Tools
    - Pointer: Basic mouse pointing tool, does nothing
    - Box: Basic rectangle shapes
    - Ellipse: Basic oval shapes
    - Line: Basic line tool


## Requirements

- Visual Studio 2022 (v143) is preferred
- Windows SDK 
- C++ Language Standard: ISO C++14 Standard
- C Language Standard: Legacy MSVC
- Windows x86 (Win32)
- SFML Library (Included in dependencies)


## Installation

This program can be downloaded and ran from the release folder using the .exe application, or by building in x86 with Visual Studio 2022 by opening the solution file.


## Controls

- Left Mouse Button [MB1]:
    - Click menu buttons to set tool and line/outline width, or to save canvas or load and image to the canvas
    - Click and drag on canvas to draw using the selected tool
    - Click on colour windows to set fill or line/outline colour (limited colours unfortunately)
- Right Mouse Button [MB2]:
    - While drawing, you can cancel the draw by simply clicking before letting go of MB1
- Mouse Scroll Wheel [MB3]:
    - Scroll in canvas to zoom in/out
    - CLick and drag to move the canvas around
- [F5] and [F9]:
    - [F5]: Save the current canvas as a .png file to your system locally
    - [F9]: Load an image onto the canvas


## Disclaimer

*WINDOWS ARE NOT RESIZABLE* - This is to ensure there are no crashes with the program, specifically with colour picking by accessing out of bounds data.
This program was somewhat rushed but suitable for released submission, more time on hand would have allowed for a nicer looking program with more implemented features. 
Bugs should be minimal but may be present. 
All code was written by me from remote workshops in class and my own knowledge and research of the C++ language.


## Credits

Shikomisen (Ayoub) 2023
Media Design School
GD1P03 - 2D Game Programming
Written for Assignment 1 Paint Tool