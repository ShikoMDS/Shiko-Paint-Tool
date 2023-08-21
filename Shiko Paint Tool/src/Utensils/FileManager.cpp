#include "Utensils/FileManager.h"

FileManager::FileManager(HWND _Handle)
{
	// Clear and initialise memory for OFN
	ZeroMemory(&m_OFN, sizeof(m_OFN));
	m_OFN.lStructSize = sizeof(m_OFN);

	// Load the handle parameter and set to the member
	m_Hwnd = _Handle;

	// Set the open filename owner
	m_OFN.hwndOwner = m_Hwnd;

	// Initialise a string as empty, then null the first element
	m_OFN.lpstrFile = (LPWSTR)szFile;
	m_OFN.lpstrFile[0] = '\0';
	m_OFN.nMaxFile = sizeof(szFile);

	std::string DefaultName("Untitled");

	for (int i = 0; i < DefaultName.size(); i++)
	{
		m_OFN.lpstrFile[i] = DefaultName[i];
	}

	// Change file filters to change what image types we can see or save to
	m_OFN.lpstrFilter = L"Portable Network Graphic (PNG)\0*.png\0All\0*.*\0";

	// What do these do idk?
	m_OFN.nFilterIndex = 1;

	m_OFN.lpstrFileTitle = NULL;
	m_OFN.nMaxFileTitle = 0;
	m_OFN.lpstrInitialDir = NULL;

	m_OFN.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
}

FileManager::~FileManager()
{

}

std::string FileManager::OpenFile()
{
	if (GetOpenFileName(&m_OFN) == true)
	{
		std::wstring ws(m_OFN.lpstrFile);
		return std::string(ws.begin(), ws.end());
	}

	else
	{
		return std::string();
	}
}

std::string FileManager::SaveFile()
{
	if (GetSaveFileName(&m_OFN) == true)
	{
		std::wstring ws(m_OFN.lpstrFile);
		return std::string(ws.begin(), ws.end());
	}

	else
	{
		return std::string();
	}
}
