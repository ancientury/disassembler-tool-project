#include "PortableExecutable.h"

using namespace std;

PortableExecutable::~PortableExecutable()
{
    delete[] DOSProgram;

    if (sections)
        for (int i = 0; i < fileHeader.NumberOfSections; i++)
                delete[] sections[i].Data;

    delete[] sectionHeaders;
    delete[] sections;

     if(file->isOpen())
        file->close();

    delete file;
}

PortableExecutable::PortableExecutable(const QString& filename)
{
    fileInfo = filename;
}

bool PortableExecutable::Open()
{
    if (file)
        this->~PortableExecutable();

    file = new QFile(fileInfo.filePath());

    if(!file->open(QIODevice::ReadWrite))
        return false;

    fileBuffer = file->readAll();

    file->seek(0);

    file->read((char*)&dosHeader, sizeof(EXECUTABLE_DOS_HEADER));

    DOSProgram = new unsigned char[dosHeader.AddressOfNewEXEHeader - sizeof(EXECUTABLE_DOS_HEADER)];

    file->read((char*)DOSProgram, dosHeader.AddressOfNewEXEHeader - sizeof(EXECUTABLE_DOS_HEADER));

    file->read((char*)&fileHeader, sizeof(EXECUTABLE_FILE_HEADER));

    file->read((char*)&optionalHeader, sizeof(EXECUTABLE_OPTIONAL_HEADER));

    sectionHeaders = new EXECUTABLE_SECTION_HEADER[fileHeader.NumberOfSections];

    for (int i = 0; i < fileHeader.NumberOfSections; i++)
        file->read((char*)&sectionHeaders[i], sizeof(EXECUTABLE_SECTION_HEADER));

    sections = new Section[fileHeader.NumberOfSections];

    for (int i = 0; i < fileHeader.NumberOfSections; i++)
    {
        sections[i].Data = new unsigned char[sectionHeaders[i].SizeOfRawData];
        sections[i].Length = sectionHeaders[i].SizeOfRawData;
        int j = 0;
        file->seek(sectionHeaders[i].PointerToRawData);

        while (file->pos() < sectionHeaders[i].PointerToRawData + sectionHeaders[i].SizeOfRawData)
            file->read((char*)&sections[i].Data[j++], sizeof(unsigned char));
    }

    return true;

}

int PortableExecutable::GetEntrySectionIndex()
{
    for (int i = 0; i < fileHeader.NumberOfSections; i++) {
        if ((sectionHeaders[i].VirtualAddress < optionalHeader.AddressOfEntryPoint) < (sectionHeaders[i].VirtualAddress + sectionHeaders[i].VirtualSize))
            return i;
    }

    throw;
}

unsigned long PortableExecutable::GetEntryPointOffset()
{
    for (int i = 0; i < fileHeader.NumberOfSections; i++) {
        if ((sectionHeaders[i].VirtualAddress < optionalHeader.AddressOfEntryPoint) < (sectionHeaders[i].VirtualAddress + sectionHeaders[i].VirtualSize)) {

            unsigned long delta = optionalHeader.AddressOfEntryPoint - sectionHeaders[i].VirtualAddress;
            return sectionHeaders[i].PointerToRawData + delta;
        }
    }

    throw;
}

unsigned long PortableExecutable::GetEntryPointVA()
{
    for (int i = 0; i < fileHeader.NumberOfSections; i++) {
        if ((sectionHeaders[i].VirtualAddress < optionalHeader.AddressOfEntryPoint) < (sectionHeaders[i].VirtualAddress + sectionHeaders[i].VirtualSize)) {

            unsigned long delta = GetEntryPointOffset() - sectionHeaders[i].PointerToRawData;
            return delta + optionalHeader.ImageBase + sectionHeaders[i].VirtualAddress;
        }
    }

    throw;
}

Section* PortableExecutable::GetSection(int sectionIndex)
{
    for (int i = 0; i < fileHeader.NumberOfSections; i++)
        if (string((char*)sectionHeaders[i].Name) == string((char*)sectionHeaders[sectionIndex].Name))
            return &sections[sectionIndex];

    throw;
}

unsigned char* PortableExecutable::GetEPFirstBytes()
{
    unsigned char* sectionData = (unsigned char*)fileBuffer.data() + GetEntryPointOffset();
    unsigned char* res = new unsigned char[4 + 1];

    for (int i = 0; i < 4; i++)
        res[i] = *(sectionData + 0 + i);

    res[4] = 0;

    return res;
}

QList<QStringList> PortableExecutable::FindCodeCaves(int minimumSize)
{
    QList<QStringList> Codecaves = {};
    for (int i = 0; i < fileHeader.NumberOfSections; i++) {
        if(sectionHeaders[i].SizeOfRawData != 0){
            int pos = 0, count = 0;

            file->seek(sectionHeaders[i].PointerToRawData);
            QByteArray data = file->read(sectionHeaders[i].SizeOfRawData);

            for (int x = 0; x < data.size(); x++) {
                pos++;

                if(data.at(x) == 0x00)
                    count++;
                else{
                    if(count > minimumSize){

                        unsigned long offset = sectionHeaders[i].PointerToRawData + (pos - count - 1);
                        Codecaves.append(QList<QString>{ QString((char *)sectionHeaders[i].Name), QString("%1").arg(count, 0, 10), QString("0x%2").arg(offset, 8, 16, QChar('0')) });
                    }
                    count = 0;
                }
            }

        }
    }

    return Codecaves;
}
