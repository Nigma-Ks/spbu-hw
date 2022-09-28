#include <stdio.h>
#define sumAmount 28

int main( )
{
    int sums[sumAmount] = {0};
    for (int fstNumber = 0; fstNumber <= 9; fstNumber++){
        for (int sndNumber = 0; sndNumber <= 9; sndNumber++){
            for (int thirdNumber = 0; thirdNumber <= 9; thirdNumber++){
                sums[fstNumber + sndNumber + thirdNumber]++;
            }
        }
    }
    int amountHappyTickets = 0;
    for (int i = 0; i < sumAmount; i++) {
        amountHappyTickets += sums[i] * sums[i];
    }
    printf("Amount of happy tickets: %d", amountHappyTickets);
    return 0;
}
