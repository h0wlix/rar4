#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <windows.h>

#pragma pack(push, 1)

using namespace std;

struct VolumeHeader {
uint16_t header_crc;
uint8_t header_type;
uint16_t header_flags;
uint16_t header_size;
};

struct File_Head {
uint32_t PackSize;
uint32_t UnpSize;
uint8_t HostOS;
uint32_t FileCRC;
uint32_t FileTime;
uint8_t UnpVer;
uint8_t Method;
uint16_t NameSize;
uint32_t FileAttr;
};

void read_headers(vector<char> data) {

    VolumeHeader* p_header = reinterpret_cast<VolumeHeader*>(&data[7]); //заполнили структуру начиная с седьмого байта

    int offset = 7+int(p_header->header_size); //пропускаем сигнатуру и перемещаемся на первый заголовок

    while (true){

        VolumeHeader* p_header = reinterpret_cast<VolumeHeader*>(&data[offset]); //перебор заголовков
        File_Head* f_header = reinterpret_cast<File_Head*>(&data[offset+7]); //начинаем считывать данные в структуру со второго заголовка
        if ((p_header->header_type) != 0x74){
            break;
        }

        uint16_t fileName = int(f_header->NameSize); //узнаём размер названия заголовка
        uint16_t fileNameOffset = sizeof(struct File_Head) + offset + sizeof(struct VolumeHeader); //отступ файл нейма
        const char* firstHeaderName = reinterpret_cast<const char*>(&data[fileNameOffset]); //создаёт указатель на смещение файл нейма
        string utf8line(firstHeaderName, fileName);
        vector<wchar_t> utf16content(fileName);
        int wideCharCount = MultiByteToWideChar(CP_UTF8, 0, utf8line.c_str(), fileName, utf16content.data(), utf16content.size());
        wstring hideName(utf16content.begin(), utf16content.end());
        wcout << "Hide content:" << hideName << endl;

        offset += int(p_header->header_size)+int(f_header->PackSize);

    }


};

#pragma pack(pop)

int main(){
    ifstream rar_file("D:\\dz\\rar4\\Example.rar", ios::binary); //открыли файл

    if (rar_file.is_open()){ //проверка открытия файла
        cout << "open ok" << endl;
        rar_file.seekg(0, ios::end); //переместились в конец
        int fileSize = rar_file.tellg(); //узнали текущее положение указателя
        cout << "File size: " << fileSize << endl;
        rar_file.seekg(0, ios::beg); //переместились в начало
        vector<char> rar_data(fileSize, 0); //создали буфер размера файла и заполнили нулями
        rar_file.read(rar_data.data(), fileSize); //заполняем буфер содержимым файла
        read_headers(rar_data); //вызываем функцию


    }
return 0;
}

