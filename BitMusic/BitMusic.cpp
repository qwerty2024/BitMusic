#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <time.h>

#define E 164.8
#define G 196
#define A 220
#define H 246.9
#define D 293.7

void playMelody(float freq[], int dur[], int length) 
{
    for (int i = 0; i < length; i++) 
    {
        Beep(freq[i], dur[i]);
    }
}

int main()
{
    // Массивы для хранения частот и длительностей нот
    float first_freq[] = { E / 2, G, A, H / 2, D };
    int first_dur[] = { 600, 600, 300, 300, 600 };


    float second_freq[] = { E / 2, G, E, D * 2, G * 2 };
    int second_dur[] = { 150, 300, 750, 600, 600 };

    float third_freq[] = { E / 2, G, G * 3, D / 2 };
    int third_dur[] = { 600, 750, 450, 600 };

    srand(time(NULL)); // текущее время в качестве начального значения
    while (1) 
    {
        int state = rand() % 3 + 1; //номер паттерна (1..3)
        switch (state) 
        {
        case 1:
            playMelody(first_freq, first_dur, sizeof(first_freq) / sizeof(first_freq[0]));
            break;
        case 2:
            playMelody(second_freq, second_dur, sizeof(second_freq) / sizeof(second_freq[0]));
            break;
        case 3:
            playMelody(third_freq, third_dur, sizeof(third_freq) / sizeof(third_freq[0]));
            break;
        }
    }
    return 0;
}
