#include <stdio.h>
#include <stdint.h>
#include <windows.h>

void playMelody(int frequency[], int duration[], int melodyLenght)
{
    for (int i = 0; i < melodyLenght; i++)
        Beep(frequency[i], duration[i]);
}

int main()
{
    int sevenNationArmyFrequence[] = {
        220, 220, 262.6, 220, 196, 174.6, 164.8,
        220, 220, 262.6, 220, 196, 174.6, 196, 174.6, 164.8
    };

    int sevenNationArmyDuration[] = {
        750, 250, 333, 333, 333, 1000, 1000,
        750, 250, 333, 333, 333, 333, 333, 333, 1000
    };

    playMelody(sevenNationArmyFrequence, sevenNationArmyDuration,
        sizeof(sevenNationArmyFrequence) / sizeof(sevenNationArmyDuration[0]));


    return 0;
}
