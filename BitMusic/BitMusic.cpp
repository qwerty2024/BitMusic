#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>

#define _USE_MATH_DEFINES   // для использования M_PI, перед #include <math.h>
#include <math.h>

#define DURATION    10      //длительность мелодии в секундах
#define SAMPLE_RATE 9000    //Частота дискретизации
#define FILENAME "melody.wav"

//структура для заголовка WAV файла
struct WavHeader 
{
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2Id[4];
    uint32_t subchunk2Size;
};


void generate_sound_data(std::ofstream &out, const WavHeader &h) {

    //массив для хранения семплов (частей аудиосигнала)
    uint8_t *buffer = new uint8_t[DURATION * SAMPLE_RATE];
    uint8_t output = 0;
    uint32_t t = 0, current_sample = 0;

    for (;; t++) {
        output = t * (0xCA98 >> (t >> 9 & 14) & 15) | t >> 8;
        //printf("%d ", output);

        //формируем массив алгоритмом bytebeat
        buffer[current_sample++] = output;

        if (current_sample == DURATION * SAMPLE_RATE - 1) break;
    }

    //записываем семплы в файл
    out.write((char*)buffer, DURATION * SAMPLE_RATE);
}

using std::ios;

int main() {
    //открываем файл для записи в бинарном режиме
    std::ofstream out(FILENAME, ios::out | ios::binary);

    //заполняем заголовок WAV файла
    WavHeader header;
    header.chunkId[0] = 'R';
    header.chunkId[1] = 'I';
    header.chunkId[2] = 'F';
    header.chunkId[3] = 'F';
    header.chunkSize = 36 + SAMPLE_RATE * DURATION; //размер файла - 36 байт + размер данных
    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';
    header.subchunk1Id[0] = 'f';
    header.subchunk1Id[1] = 'm';
    header.subchunk1Id[2] = 't';
    header.subchunk1Id[3] = ' ';
    header.subchunk1Size = 16;         //размер подчиненного блока
    header.audioFormat = (short)1;            //формат аудио (PCM)
    header.numChannels = (short)1;            //количество каналов (моно)
    header.sampleRate = SAMPLE_RATE;   //частота дискретизации
    header.byteRate = SAMPLE_RATE * 2; //байт в секунду (SAMPLE_RATE * numChannels * bitsPerSample / 8)
    header.blockAlign = (short)1;             //байт на сэмпл (numChannels * bitsPerSample / 8)
    header.bitsPerSample = (short)8;         //бит на сэмпл
    header.subchunk2Id[0] = 'd';
    header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';
        // Размер данных - SAMPLE_RATE * DURATION * numChannels * bitsPerSample / 8
    header.subchunk2Size = SAMPLE_RATE * DURATION;
        

    //записываем заголовок в файл
    out.write((char*)&header, sizeof(header));

    generate_sound_data(out, header);

    //закрываем файл
    out.close();

    PlaySound(L"melody.wav", NULL, SND_FILENAME | SND_SYNC);

    return 0;
}