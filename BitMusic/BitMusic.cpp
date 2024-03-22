#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <time.h>

//void playMelody(int frequency[], int duration[], int melodyLenght)
//{
//    for (int i = 0; i < melodyLenght; i++)
//        Beep(frequency[i], duration[i]);
//}

int main()
{
    float frequency[] = { 130.8, 146.8, 164.8, 174.6, 196, 220, 246.9 }; // гамма до-мажор
    int duration[] = { 60, 90, 120, 180, 240, 360, 480 };

    srand(time(NULL)); // текущее время в качестве начального значения
    while (1) {
        //генерация псевдослучайных чисел
        int i = rand() % 7; // номер элемента для частоты (0..6)
        int j = rand() % 7; // номер элемента для длительности (0..6)
        int k = rand() % 6 + 1; // коэффициент для частоты от (1..6)
        int g = rand() % 2 + 1; // коэффициент для длительности (1..2)
        system("cls");
        printf("frequency: %.2f\tduration: %d", frequency[i] * k, duration[j] * g);
        Beep(frequency[i] * k, duration[j] * g);
    }
    return 0;
}
