#include <iostream>
#include <fstream>
#include <bitset>

#define addr_3 ((addr >> 12) & 1)
#define addr_2 ((addr >> 8) & 15)
#define addr_1 ((addr >> 4) & 15)
#define addr_0 (addr & 15)

#define byte_1 ((byte >> 4) & 15)
#define byte_0 (byte & 15)

#define checksum_1 ((checksum >> 4) & 15)
#define checksum_0 (checksum & 15)

 //Saidas da maquina de estados
 #define LED_1 1<<3
 #define LED_2 1<<4
 #define LED_3 1<<5
 #define RESET_PLACAR 1<<6
 #define ADD_PONTO 1<<7

//Estados da maquina de estados
enum{INICIAL, ESPERA_BOTAO, SORTEIA, BURACO_1, BURACO_2, BURACO_3, AUMENTA_CONTADOR, ZERA_PLACAR};

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

char maquinaEstados (int entrada)
{
    int estado_atual = entrada&(7);
    int botao = entrada&(1<<3);
    int sensorB_1 = entrada&(1<<4);
    int sensorB_2 = entrada&(1<<5);
    int sensorB_3 = entrada&(1<<6);
    int sensor_de_volta = entrada&(1<<7);
    int timer = entrada&(1<<8);
    int aleatorio = (entrada&(3<<9))>>9;

    if(timer)
        return INICIAL
    if(botao && estado_atual == INICIAL)
        return ESPERA_BOTAO;
    if(!botao && estado_atual == ESPERA_BOTAO)
        return SORTEIA | RESET_PLACAR;
    if(aleatorio == 1 && estado_atual == SORTEIA)
        return BURACO_1 | LED_1;
    if(aleatorio == 2 && estado_atual == SORTEIA)
        return BURACO_2 | LED_2;
    if(aleatorio == 3 && estado_atual == SORTEIA)
        return BURACO_3 | LED_3;
    if(sensorB_1 && estado_atual == BURACO_1)
        return AUMENTA_CONTADOR | ADD_PONTO;
    if( (sensorB_2 || sensorB_3) && estado_atual == BURACO_1)
        return ZERA_PLACAR | RESET_PLACAR;
    if(sensorB_2 && estado_atual == BURACO_2)
        return AUMENTA_CONTADOR | ADD_PONTO;
    if( (sensorB_1 || sensorB_3) && estado_atual == BURACO_2)
        return ZERA_PLACAR | RESET_PLACAR;
    if(sensorB_3 && estado_atual == BURACO_3)
        return AUMENTA_CONTADOR | ADD_PONTO;
    if( (sensorB_1 || sensorB_2) && estado_atual == BURACO_3)
        return ZERA_PLACAR | RESET_PLACAR;
    if(sensor_de_volta && estado_atual == AUMENTA_CONTADOR)
        return SORTEIA | RESET_PLACAR;
    if(sensor_de_volta && estado_atual == AUMENTA_CONTADOR)
        return SORTEIA | RESET_PLACAR;

    return 8191;
}

int main()
{
    /*Grava arquivo .hex
    ofstream* arquivo = new ofstream;
    arquivo->open("saida.hex");

    escreveHex(arquivo, 580, 0b01101111);

    *arquivo << ":00000001FF" << endl;
    arquivo->close();*/

    for(int i =0; i < 8192; i++)
    {
        maquinaEstados(8192);
    }

    int teste = (3<<9)>>9;
    bitset<16> x((3<<9)>>9);
    cout << ADD_PONTO << endl;

    return 0;
}
