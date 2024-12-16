#include <iostream>
#include <fstream>
#include <cstdint>

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

void read_headers() {

};



#pragma pack(pop)

int main(){
    ifstream rar_file("D:\\dz\\rar4\\Example.rar", ios::binary);

    if (rar_file.is_open()){
        cout << "open ok" << endl;
        rar_file.seekg(0, ios::end);
        int fileSize = rar_file.tellg();
        cout << "File size: " << fileSize << endl;
        rar_file.seekg(0, ios::beg);

    }
return 0;
}

