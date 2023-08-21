#pragma once
#include <Windows.h>
#include <ShObjIdl.h>
#include <string>

class FileManager
{
public:
	FileManager(HWND _Handle);
	~FileManager();

	std::string OpenFile();
	std::string SaveFile();

private:
	OPENFILENAME m_OFN; // Variable holding information about loading or saving file
	HWND m_Hwnd; // Handle current window
	HANDLE m_hf; // Handle to a file

	char szFile[260]; // Array for filename + path
};