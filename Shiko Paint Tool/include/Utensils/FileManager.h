/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : FileManager.h
Description : Declaration of file managing systems
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include <string>
#include <Windows.h>
#include <ShObjIdl.h>

class FileManager
{
public:
	explicit FileManager(HWND Handle);
	~FileManager();

	std::string openFile();
	std::string saveFile();

private:
	OPENFILENAME MOfn{}; // Variable holding information about loading or saving file
	HWND MHwnd; // Handle current window
	HANDLE MHf{}; // Handle to a file

	char SzFile[260]{}; // Array for filename + path
};