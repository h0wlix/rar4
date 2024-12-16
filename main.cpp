#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

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

    VolumeHeader* p_header = reinterpret_cast<VolumeHeader*>(&data[7]);
    cout << hex << int(p_header->header_size) << endl;
    int offset = 7+int(p_header->header_size);
    cout << hex << offset << endl;
    while (true){
    VolumeHeader* p_header = reinterpret_cast<VolumeHeader*>(&data[offset]); //перебор заголовков
    File_Head* f_header = reinterpret_cast<File_Head*>(&data[offset+7]);
    cout << hex << int(f_header->NameSize) << endl;
    uint16_t fileName = int(f_header->NameSize);

    cout << hex << offset << endl;
    uint16_t fileNameOffset = sizeof(struct File_Head) + offset + sizeof(struct VolumeHeader);
    cout << hex << fileNameOffset << endl;



    //cout << hex << int(f_header->PackSize) << endl;
    //offset = int(p_header->header_size)+int(f_header->PackSize);
    //cout << hex << offset << endl;
    break;
    }

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
        vector<char> rar_data(fileSize, 0);
        rar_file.read(rar_data.data(), fileSize);
        read_headers(rar_data);


    }
return 0;
}

