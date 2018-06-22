#include <iostream>
#include <fstream>

#define addr_3 ((addr >> 12) & 1)
#define addr_2 ((addr >> 8) & 15)
#define addr_1 ((addr >> 4) & 15)
#define addr_0 (addr & 15)

#define byte_1 ((byte >> 4) & 15)
#define byte_0 (byte & 15)

#define checksum_1 ((checksum >> 4) & 15)
#define checksum_0 (checksum & 15)

using namespace std;

void escreveHex(ofstream* arquivo, int addr, char byte)
{
    *arquivo << ":01"; // Quantidade de bytes
    *arquivo << hex << addr_3; // Escreve os endereços na memória
    *arquivo << hex << addr_2;
    *arquivo << hex << addr_1;
    *arquivo << hex << addr_0;
    *arquivo << 0;
    *arquivo << 0;
    *arquivo << hex << byte_1; // Escreve as informações a serem salvas
    *arquivo << hex << byte_0;

    int checksum = 1 + (addr_3 * 16) + addr_2 + (addr_1 * 16) + addr_0 + (byte_1 * 16) + byte_0;
    checksum = ~checksum;
    checksum += 1;

    *arquivo << hex << checksum_1;
    *arquivo << hex << checksum_0;
    *arquivo << endl;
}

int main()
{
    ofstream* arquivo = new ofstream;
    arquivo->open("saida.hex");

    escreveHex(arquivo, 580, 0b01101111);

    *arquivo << ":00000001FF" << endl;
    arquivo->close();

    return 0;
}