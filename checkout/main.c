#include <stdio.h>

int checkout(){

    // Initialising all the variables
    int lengthCost = 0;
    int adultBoardRate = 0;
    int adultBoardCost = 0;
    int childBoardRate = 0;
    int childBoardCost = 0;
    int totalBoardCost = 0;
    int wakeUpCost = 0;
    int overallCost = 0;
    int rooms[6];

    for (int i=0 ; i<6 ; i++){
        if (roomsUsed[partyIndex][i] == 1)
        {
            rooms[i] = i+1;
        }
    }

    int roomPrices[6][2] = {
            {1, 100},
            {2, 100},
            {3, 85},
            {4, 75},
            {5, 75},
            {6, 50}
    };

    // This loop is used to go through all data in the roomsUsed array to check which rooms are used
    for (int i=0 ; i<6 ; i++){

        // This loops loops through the first column of the roomPrices array every time the
        // roomsUsed array goes to the next value. This way it checks every value in that array against the first column
        for (int j=0 ; j<6 ; j++) {

            // When the values are equal it will multiply the cost by the amount of days stayed to get the room price
            if (rooms[i] == roomPrices[j][0]) {
                lengthCost = lengthCost + (roomPrices[j][1] * length);
            }
        }
    }

    if (age > 65) {
        lengthCost = lengthCost * 0.9;
    }

    if (boardType == 'FB')
    {
        adultBoardRate = guests[partyIndex][0] * 20;
        adultBoardCost = adultBoardRate * length;
        childBoardRate = guests[partyIndex][1] * 20;
        childBoardCost = childBoardRate * length * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    }

    else if (boardType == 'HB')
    {
        adultBoardRate = guests[partyIndex][0] * 15;
        adultBoardCost = adultBoardRate * length;
        childBoardRate = guests[partyIndex][1] * 15;
        childBoardCost = childBoardRate * length * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    }

    else if (boardType == 'BB')
    {
        adultBoardRate = guests[partyIndex][0] * 5;
        adultBoardCost = adultBoardRate * length;
        childBoardRate = guests[partyIndex][1] * 5;
        childBoardCost = childBoardRate * length * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    }

    if(wakeUp[partyIndex][0] == 1){
        wakeUpCost = 5;
    }

    printf("\nBILL FOR %s%d:", surname[partyIndex], map[partyIndex][0])
    if (lengthCost > 0) {
        printf("\nTotal cost for rooms stayed in is: GBP%d", lengthCost);
    }

    if (totalBoardCost > 0) {
        printf("\nTotal cost for meals is: GBP%d", totalBoardCost);
        printf("\n\tCost for adults' meals was: GBP%d", adultBoardCost);
        printf("\n\tCost for children's meals was: GBP%d", childBoardCost);
    }

    if (wakeUpCost > 0) {
        printf("\nTotal cost for wake up calls is: GBP%d", wakeUpCost);
    }

    overallCost = lengthCost + totalBoardCost + wakeUpCost
    printf("\n\nOverall cost for the stay is: GBP%d", overallCost);

    for (int i=0 ; i<6 ; i++) {
        rooms[i] = 0;
    }


}