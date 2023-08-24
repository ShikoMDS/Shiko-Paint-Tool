/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand

(c) 2023 Media Design School

File Name : FileManager.cpp
Description : Implementation of file managing systems
Author : Shikomisen (Ayoub Ahmad)
Mail : ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Utensils/FileManager.h"

FileManager::FileManager(const HWND Handle)
{
	// Clear and initialise memory for OFN
	ZeroMemory(&MOfn, sizeof(MOfn));
	MOfn.lStructSize = sizeof(MOfn);

	// Load the handle parameter and set to the member
	MHwnd = Handle;

	// Set the open filename owner
	MOfn.hwndOwner = MHwnd;

	// Initialise a string as empty, then null the first element
	MOfn.lpstrFile = reinterpret_cast<LPWSTR>(SzFile);
	MOfn.lpstrFile[0] = '\0';
	MOfn.nMaxFile = sizeof(SzFile);

	const std::string DefaultName("Untitled");

	for (int i = 0; i < DefaultName.size(); i++)
	{
		MOfn.lpstrFile[i] = DefaultName[i];
	}

	// Change file filters to change what image types we can see or save to
	MOfn.lpstrFilter = L"Portable Network Graphic (PNG)\0*.png\0All\0*.*\0";

	// What do these do idk?
	MOfn.nFilterIndex = 1;

	MOfn.lpstrFileTitle = nullptr;
	MOfn.nMaxFileTitle = 0;
	MOfn.lpstrInitialDir = nullptr;

	MOfn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
}

FileManager::~FileManager() = default;

std::string FileManager::openFile()
{
	if (GetOpenFileName(&MOfn) == true)
	{
		std::wstring Ws(MOfn.lpstrFile);
		return std::string(Ws.begin(), Ws.end());
	}

	else
	{
		return std::string();
	}
}

std::string FileManager::saveFile()
{
	if (GetSaveFileName(&MOfn) == true)
	{
		std::wstring Ws(MOfn.lpstrFile);
		return std::string(Ws.begin(), Ws.end());
	}

	else
	{
		return std::string();
	}
}
