#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//GLOBAL DATA

int map[10][2] = {{-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1},
                  {-1, -1}}; //map of booking IDs to indices .. -- matthew: i had to pre-fill due to return index find matches from old memory. -1 should never be used in code as this stands for error
int tables[2][3] = {};    //boolean list of tables
int partyIndex = -1;       //tells checkIn what index to insert at


//PARTY DATA - maximum 24 parties
char surname[24][127] = {};
int dateOfBirth[24][3] = {};
int guests[24][2]; //please don't put test values and then give the code and not remove them // array hold guest numbers
char boardType[24][2] = {};
int length[24] = {};
int dailyWakeUpCall[24] = {};
int roomsUsed[24][6] = {};


int digits_only(const char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i]) == 1) {
            return 1;
        }
    }
    return 0;
}


int returnIndex(reference) { //returns index from the map
    for (int i = 0; i < 18; i++) {
        if (map[i][0] == reference) {
            return map[i][1];
        }
    }
    return -1;
}

int TotalGuests(int index) { //totals adult and child guests
    return guests[index][0] + guests[index][1];
}

//for sanitation of inputs
int input_int(char *text) {
    int run = 1;
    int num = 0;
    while (run == 1) {
        printf("%s", text);
        int hold = scanf("%5d", &num);
        if (hold != 1) {
            fflush(stdin);
            fflush(stdout);
            printf("error input\n");
            num = 0;
        } else {
            fflush(stdin);
            fflush(stdout);
            run = 0;
        }
    }
    return num;
}

char *input_char(char *text) {
    fflush(stdin);
    char *string = malloc(25);
    printf("%s", text);
    fgets(string, 25, stdin);

    if (string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    }

    return string;
}


void BookTable() {

    char names[3][32] = {"Endor", "Naboo", "Tatooine"};

    int run = 0;
    char bookingId[256] = {};
    strcpy(bookingId, input_char("Enter your booking ID?"));

    // how do i put this this solution did not work at all probably because clion handles this type clever stuff different.
    //old solution:
    //int numbers = sscanf("%d",
    //                   bookingId + strlen(bookingId) - 4); //use pointer arithmetic to get the last three letters
    // of the string, use sscanf to convert last three digits to integer
    //new solution this saved me so many headaches
    char *p = bookingId;
    while (isalpha(*p)) ++p;
    int numbers = atoi(p);
    int index = returnIndex(numbers); //fetch the index for this booking ID

    if (index == -1) {
        printf("Invalid booking ID\n");
        return;
    }
    if (strcmp(boardType[index], "BB") == 0) {
        printf("Only full and half board can book dinner\n");
        return;
    }
    if (TotalGuests(index) > 4) {
        printf("Tables can only seat 4\n");
        return;
    }

    for (int setting = 0; setting < 2; ++setting) { //iterate through the two settings
        for (int i = 0; i < 3; ++i) { //iterate through the three tables
            if (tables[setting][i] == 0) { //if this table is available
                printf("Table %s is available at %d\n", names[i],
                       (setting * 2) + 7); //maths is to correctly convert from 0/1 to 7/9
            }
        }
        printf("\n");
    }

    int timeIn = 0;
    char table[64];

    int flag = 0;

    do { //validation - will loop until a table is successfully booked

        timeIn = input_int("What time do you want to book a table, 7 or 9?\n");

        if (timeIn != 7 && timeIn != 9) { //invalid id
            printf("Invalid time, try again\n");
            continue;
        }

        timeIn = timeIn / 9; //int division trick to get the times to 0 or 1:
        // 7/9 < 1 so it gets round down to 0, 9/9 = 1 so it stays as 1

        strcpy(table, input_char("What table would you like to book?\n"));

        switch (tolower(
                table[0])) {  //since we can't switch on a string, we use the 0th char as it is different for each table.

            case 'e':
                if (tables[timeIn][0] == 1) {
                    printf("This table is already booked\n");
                } else {
                    tables[timeIn][0] = 1;
                    flag = 1;
                }
                break;
                //fixed the lowercase case input thing you only had one working - matthew
            case 'n':
                if (tables[timeIn][1] == 1) {
                    printf("This table is already booked\n");
                } else {
                    tables[timeIn][1] = 1;
                    flag = 1;
                }
                break;

                //fixed the lowercase case input thing you only had one working - matthew
            case 't':
                if (tables[timeIn][2] == 1) {
                    printf("This table is already booked\n");
                } else {
                    tables[timeIn][2] = 1;
                    flag = 1;
                }
                break;

            default:
                printf("That table doesn't exist\n");
                break;
        }

    } while (flag == 0);

}

int boolCheck(char *string) {
    while (1) {
        char *getsp;
        char answer;
        getsp = input_char(string);
        answer = getsp[0];
        if (answer == 'Y' || answer == 'N') {
            if (answer == 'Y') {
                return 1;
            } else {
                return 0;
            }
        } else {
            printf("not valid\n");
        }
    }

}

void GenerateID() {
    srand(time(0));
    partyIndex++;
    int id = (rand() % (999 - 100 + 1)) + 100; //inclusive
    map[partyIndex][0] = id;
    map[partyIndex][1] = partyIndex; //set the second int to the index - this will be used for further lookup
}

int roomInUseCheckByIndex(int numRoom, int index) {
    if (roomsUsed[index][numRoom] != 1) {
        return 1;
    } else {
        return 0;
    }
}

int roomInUseCheckByID(int numRoom, int id) {
    if (roomsUsed[returnIndex(id)][numRoom] != 1) {
        return 1;
    } else {
        return 0;
    }
}

int IsLeapYear(int year) {
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

// returns 1 if given date is valid.
int IsValidDate() {
    int MAX_YR = 2004;
    int MIN_YR = 1900;
    //check range of year,month and day
    if (dateOfBirth[partyIndex][2] > MAX_YR || //check date of birth is in valid range
        dateOfBirth[partyIndex][2] < MIN_YR) {
        return 0;
    }
    if (dateOfBirth[partyIndex][1] < 1 || dateOfBirth[partyIndex][1] > 12) { //check year is valid
        return 0;
    }
    if (dateOfBirth[partyIndex][0] < 1 || dateOfBirth[partyIndex][0] > 31) { //check month is valid
        return 0;
    }
    //Handle feb days in leap year
    if (dateOfBirth[partyIndex][1] == 2) {
        if (IsLeapYear(dateOfBirth[partyIndex][2])) {
            return (dateOfBirth[partyIndex][0] <= 29);
        } else {
            return (dateOfBirth[partyIndex][0] <= 28);
        }
    }
    //handle months which has only 30 days
    if (dateOfBirth[partyIndex][1] == 4 || dateOfBirth[partyIndex][1] == 6 ||
        dateOfBirth[partyIndex][1] == 9 || dateOfBirth[partyIndex][1] == 11) {
        return (dateOfBirth[partyIndex][0] <= 30);
    } else {
        return 1;
    }
}


void checkin() {
    fflush(stdout);
    int numbers = -1;
    int numbers_child = -1;
    int time = -1;
    int numberOfRooms = -1;
    int run = 1;
    //generate_id();
    char *surinput;
    GenerateID();
    for (int i = 0; i < 7; i++) {
        roomsUsed[partyIndex][i] = 0;
    }
    //gets surname input
    do {
        surinput = input_char("what is your surname?");
    } while (digits_only(surinput) == 1);
    int len = strlen(surinput);
    if (surinput[len - 1] == '\n')
        surinput[len - 1] = '\0';
    //copies to surname
    strcpy(surname[partyIndex], surinput);
    //gets number of rooms
    do {
        printf("\nHow many rooms would you like to book? 1-6.");
        numberOfRooms = input_int("\n");

    } while (numberOfRooms >= 61 || numberOfRooms < 1);
    do {
        time = input_int("how many days are you here for?");
        if (time > 30 || time < 1){
            printf("\ntoo large or small time 1-30\n");
        }
    }while(time > 30 || time < 1 );
    printf("\n");
    int hold_int = numberOfRooms;
    for (int i = 0; i < hold_int; i++) {
        //checks for if the number lies between 1 & 6
        int whatRoom = input_int(
                "what room would you like prices are:\nRoom 1 & 2 = 100,\nRoom 3 = 85,\nRoom 4 & 5 = 75,\nRoom 6 = 50,\n?");
        if (whatRoom > 6 || whatRoom < 1) {
            printf("error\n");
            i--;
            continue;
        }
        if (roomInUseCheckByIndex(whatRoom, partyIndex) == 0) {
            printf("invalid room in already in use\n");
            i--;
            continue;
        } else if (roomInUseCheckByIndex(whatRoom, partyIndex) == 1) {
            roomsUsed[whatRoom][partyIndex] = 1;
        }

        do {
            //gets inputs for number of people and length of stay.
            numbers = input_int("how many adults are with you?");
            numbers_child = input_int("how many children are with you?");
        } while (time > 30 || time < 1 || numbers_child > 5 || numbers > 5 || numbers_child < 0 || numbers < 1);

        length[partyIndex] = time;
        guests[partyIndex][0] = guests[partyIndex][0] + numbers;
        guests[partyIndex][1] = guests[partyIndex][1] + numbers_child;
        roomsUsed[partyIndex][i] = whatRoom;
        printf("\n");
        dailyWakeUpCall[partyIndex] = boolCheck("do you want a daily wake up call?");
    }
    int dateCheck = 0;
    do {
        printf("\n\n");
        //gets date of birth
        dateOfBirth[partyIndex][0] = input_int("what is your date of birth DD?");
        dateOfBirth[partyIndex][1] = input_int("what is your date of birth MM?");
        dateOfBirth[partyIndex][2] = input_int("what is your date of birth YYYY?");
        dateCheck = IsValidDate();
        if (dateCheck == 0) {
            printf("\ninvalid date must be at least 16 years old.");
        }
    } while (dateCheck == 0);

    do{ //validation loop for taking in board type
        printf("\n\n");
        strcpy(boardType[partyIndex], input_char("Enter your board type, FB, HB or BB?\n"));
    }
    while( !( (boardType[partyIndex][0] == 'F' || boardType[partyIndex][0] == 'H' || boardType[partyIndex][0] == 'B') && boardType[partyIndex][1] == 'B') ); //not at all overcomplicated way to make sure it is FB, HB or BB


    printf("your booking ID is:\n%s%d\n", surname[partyIndex], map[partyIndex][0]);
    fflush(stdout);
}

int AgeDifference(const int date1[3], const int date2[3]) {
    int day1 = date1[0], mon1 = date1[1], year1 = date1[2];
    int day2 = date2[0], mon2 = date2[1], year2 = date2[2];

    int day_diff, mon_diff, year_diff;

    if (day2 < day1) {
        //borrow days from february
        if (mon2 == 3) {
            //check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) {
                day2 += 29;
            } else {
                day2 += 28;
            }
        }

            //borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) {
            day2 += 30;
        }

            //borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else {
            day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1) {
        mon2 += 12;
        year2 -= 1;
    }

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;
    printf("you are %d years old", year_diff);
    return year_diff;
}

int Checkout(int bookingID) {

    // Initialising all the variables
    float lengthCost = 0;
    float adultBoardRate = 0;
    float adultBoardCost = 0; //multiplying by 0.5f means theses must be floats
    float childBoardRate = 0;
    float childBoardCost = 0;
    float totalBoardCost = 0;
    float wakeUpCost = 0;
    float overallCost = 0;
    float rooms[6];

    int index = returnIndex(bookingID);

    int roomPrices[6][2] = {
            {1, 100},
            {2, 100},
            {3, 85},
            {4, 75},
            {5, 75},
            {6, 50}
    };

    // This loop is used to go through all data in the roomsUsed array to check which rooms are used
    for (int i = 0; i < 6; i++) {

        // This loops loops through the first column of the roomPrices array every time the
        // roomsUsed array goes to the next value. This way it checks every value in that array against the first column
        for (int j = 0; j < 6; j++) {

            // When the values are equal it will multiply the cost by the amount of days stayed to get the room price
            if (roomsUsed[index][i] == roomPrices[j][0]) {
                lengthCost = lengthCost + (roomPrices[j][1] * length[index]);
            }
        }
    }
    int current_time[3] = {14, 11, 2020};
    if (AgeDifference(dateOfBirth[index], current_time) > 65) {
        lengthCost = lengthCost * 0.9;
    }

    if (strcmp((const char *) boardType, "FB") == 0) {
        adultBoardRate = guests[index][0] * 20;
        adultBoardCost = adultBoardRate * length[index];
        childBoardRate = guests[index][1] * 20;
        childBoardCost = childBoardRate * length[index] * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    } else if (strcmp((const char *) boardType, "HB") == 0) {
        adultBoardRate = guests[index][0] * 15;
        adultBoardCost = adultBoardRate * length[index];
        childBoardRate = guests[index][1] * 15;
        childBoardCost = childBoardRate * length[index] * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    } else if (strcmp((const char *) boardType, "FB") == 0) {
        adultBoardRate = guests[index][0] * 5;
        adultBoardCost = adultBoardRate * length[index];
        childBoardRate = guests[index][1] * 5;
        childBoardCost = childBoardRate * length[index] * 0.5;
        totalBoardCost = adultBoardCost + childBoardCost;
    }

    if (dailyWakeUpCall[index] == 1) {
        wakeUpCost = 5;
    }

    printf("\nBILL FOR %s%d:", surname[partyIndex], map[partyIndex][0]);
    if (lengthCost > 0) {
        printf("\nTotal cost for rooms stayed in is: GBP%.2f", lengthCost);
    }

    if (totalBoardCost > 0) {
        printf("\nTotal cost for meals is: GBP%.2f", totalBoardCost);
        printf("\n\tCost for adults' meals was: GBP%.2f", adultBoardCost);
        printf("\n\tCost for children's meals was: GBP%.2f", childBoardCost);
    }

    if (wakeUpCost > 0) {
        printf("\nTotal cost for wake up calls is: GBP%.2f", wakeUpCost);
    }

    overallCost = lengthCost + totalBoardCost + wakeUpCost;
    printf("\n\nOverall cost for the stay is: GBP%.2f", overallCost);

    for (int i = 0; i < 6; i++) {
        roomsUsed[index][i] = 0;
    }
}


int main() {
    //gets tests
    char reference[8];
    char idChecked[26] = {"test"};
    int run = 1;
    while (run == 1) {
        //gets input and start switch case
        printf("\n");
        switch (input_int("\nwhat would you like to do?\n1.check in\n2.book a table\n3.check out\n?")) {
            case 1:
                //starts the checkin subroutine
                checkin();
                break;
            case 2:
                //starts the subroutine
                BookTable();
                break;
            case 3:
                //checks if contains numbers
                strcpy(idChecked, input_char("\nwhat is your bookingID?"));
                if (digits_only(idChecked) == 1) {
                    //all hall stackoverflow for this fix. It took some time
                    //gets numbers from string
                    char *p = idChecked;
                    while (isalpha(*p)) ++p;
                    int numbers = atoi(p);
                    int check = returnIndex(numbers);
                    if (returnIndex(numbers) != -1) { //fetch the index for this booking ID
                        //if yes then passes into sub routine.
                        Checkout(numbers);
                    } else {
                        //if no then returns a error
                        printf("\nerror invalid bookingID\n");
                    }
                } else {
                    //if no then the case and switch goes to start and return not valid
                    printf("\nnot valid\n");
                }
                break;
            case 4:
                //this stops the program
                run = 0;
                break;
            default:
                //input wasn't any of the cases
                printf("\nINPUT error.\n");
                break;


        }
    }
    fflush(stdout);
    return 0;
}