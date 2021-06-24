#include <fstream>   
#include <sstream>  
#include <qmessagebox.h>
#include "Disassembler.h"
#include "PortableExecutable.h"

using namespace std;

PortableExecutable::PortableExecutable(){}

PortableExecutable::PortableExecutable(const QString& filename)
{
	Open(filename);
}


bool PortableExecutable::Open(const QString& filename)
{

	if (sections)
		for (int i = 0; i < fileHeader.NumberOfSections; i++)
			delete[] sections[i].Data;

	delete[] DOSProgram;
	delete[] sectionHeaders;
	delete[] sections;

	ifstream ifile;
	
	try {
		ifile.open(filename.toStdString().c_str(), ios::binary);

		ifile.read((char*)&dosHeader, sizeof(EXECUTABLE_DOS_HEADER));

		DOSProgram = new unsigned char[dosHeader.AddressOfNewEXEHeader - sizeof(EXECUTABLE_DOS_HEADER)];

		ifile.read((char*)DOSProgram, dosHeader.AddressOfNewEXEHeader - sizeof(EXECUTABLE_DOS_HEADER));

		ifile.read((char*)&fileHeader, sizeof(EXECUTABLE_FILE_HEADER));

		ifile.read((char*)&optionalHeader, sizeof(EXECUTABLE_OPTIONAL_HEADER));

		sectionHeaders = new EXECUTABLE_SECTION_HEADER[fileHeader.NumberOfSections];

		for (int i = 0; i < fileHeader.NumberOfSections; i++)
			ifile.read((char*)&sectionHeaders[i], sizeof(EXECUTABLE_SECTION_HEADER));

		sections = new Section[fileHeader.NumberOfSections];

		for (int i = 0; i < fileHeader.NumberOfSections; i++)
		{
			sections[i].Data = new unsigned char[sectionHeaders[i].SizeOfRawData];
			sections[i].Length = sectionHeaders[i].SizeOfRawData;
			int j = 0;
			ifile.seekg(sectionHeaders[i].PointerToRawData);
			while (ifile.tellg() < sectionHeaders[i].PointerToRawData + sectionHeaders[i].SizeOfRawData)
				ifile.read((char*)&sections[i].Data[j++], sizeof(unsigned char));
		}

		return true;
	}
	catch (ifstream::failure e) {
		QMessageBox::warning(NULL, "Failure", "Exception while opening/reading/closing file.", QMessageBox::Ok);
		return false;
	}

	return false;

}

int PortableExecutable::GetEntrySectionIndex() 
{
	for (int i = 0; i < fileHeader.NumberOfSections; i++) {
		if ((sectionHeaders[i].VirtualAddress < optionalHeader.AddressOfEntryPoint) < (sectionHeaders[i].VirtualAddress + sectionHeaders[i].VirtualSize))
			return i;
	}

	return 0;
}

void PortableExecutable::Save(const QString& filename)
{
	ofstream ofile(filename.toStdString().c_str(), ios::binary);

	ofile.write((char*)&dosHeader, sizeof(EXECUTABLE_DOS_HEADER));

	ofile.write((char*)DOSProgram, dosHeader.AddressOfNewEXEHeader - sizeof(EXECUTABLE_DOS_HEADER));

	ofile.write((char*)&fileHeader, sizeof(EXECUTABLE_FILE_HEADER));

	ofile.write((char*)&optionalHeader, sizeof(EXECUTABLE_OPTIONAL_HEADER));

	for (int i = 0; i < fileHeader.NumberOfSections; i++)
		ofile.write((char*)&sectionHeaders[i], sizeof(EXECUTABLE_SECTION_HEADER));

	for (int i = 0; i < fileHeader.NumberOfSections; i++)
	{
		int j = 0;
		ofile.seekp(sectionHeaders[i].PointerToRawData);
		while (ofile.tellp() < sectionHeaders[i].PointerToRawData + sectionHeaders[i].SizeOfRawData)
			ofile.write((char*)&sections[i].Data[j++], sizeof(unsigned char));
	}
}