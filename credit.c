#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define AMEX 0
#define MASTERCARD 1
#define VISA_16 2
#define VISA_13 3
#define INVALID -1
#define cardType int

bool isNumberValid(long number);
long getNumberFromUser();
int getDigit(long number, int digit);
cardType getCardType(long number);
int getNumberOfDigits(cardType type);
string getCardDescription(cardType type);
bool isCardValid(long number);

int main(void)
{
    long number = getNumberFromUser();
    cardType type = getCardType(number);
    if (isCardValid(number))
    {
        printf("%s\n",getCardDescription(type));    
    }else
    {
        printf("INVALID\n");    
    }
}

long getNumberFromUser()
{
    long number;
    do{
        number = get_long("Card number: ");
    }while(!isNumberValid(number));
    return number;
}

bool isNumberValid(long number)
{
    // Greater than zero and at least the length of the smaller VISA pattern
    return number > 0;
}

int getDigit(long number, int digit)
{
    int index = digit - 1;
    long number_from_index_to_the_end = number / pow(10,index);
    if (number_from_index_to_the_end>0)
    {
        int digit_to_the_right = number_from_index_to_the_end % 10;
        return digit_to_the_right;
    }
    return -1;
}

string getCardDescription(cardType type){
    switch(type){
        case AMEX:
            return "AMEX";
        case MASTERCARD:
            return "MASTERCARD";
    }
    // If not, it is VISA
    return "VISA";    
}

int getNumberOfDigits(cardType type){
    switch(type){
        case AMEX:
            return 15;
        case MASTERCARD:
        case VISA_16:
            return 16;    
        case VISA_13:
            return 13;        
    }
    return -1;
}

cardType getCardType(long number){
    // It can be MASTERCARD or VISA_16
    if(number >= pow(10,15)){
        int first_digit = getDigit(number,16);
        int second_digit = getDigit(number,15);
        if (first_digit==5 && second_digit>=1 && second_digit<=5){
            return MASTERCARD;
        }
        if (first_digit==4){
            return VISA_16;
        }
    }
    // It can be AMEX
    else if (number >= pow(10,14))
    {
        int first_digit = getDigit(number,15);
        int second_digit = getDigit(number,14);
        if (first_digit==3 && ( second_digit == 4 || second_digit == 7 )){
            return AMEX;
        }
    // It can be VISA_13
    }else if (number >= pow(10,12)){
        int first_digit = getDigit(number,13);
        if (first_digit==4){
            return VISA_13;
        }
    }
    return INVALID;
}

bool isCardValid(long number){
    cardType type = getCardType(number);
    
    int numberOfDigits = getNumberOfDigits(type);
    if (numberOfDigits < 0){
        return false;
    }

    int sumOfDigitsMultipliedBy2 = 0;
    int sumOfOtherDigits = 0;

    for (int digit=1; digit <= numberOfDigits; digit++){
        int digitValue = getDigit(number,digit);
        if (digit % 2 != 0){
            sumOfOtherDigits += digitValue;
        }else{
            int product = digitValue * 2;
            int sum = product;
            if (sum >= 10){
                sum = getDigit(product,1) + getDigit(product,2);
            }
            sumOfDigitsMultipliedBy2 += sum;
        }
    }
    int totalSum = (sumOfOtherDigits + sumOfDigitsMultipliedBy2);
    return getDigit( totalSum, 1 ) == 0;

}