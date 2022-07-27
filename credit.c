#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define AMEX 0
#define MASTERCARD 1
#define VISA_16 2
#define VISA_13 3
#define NONE -1
#define cardType int

long getNumberFromUser();
int getDigit(long number, int digit);
cardType getCardType(long number);
int getNumberOfDigits(long number);
string getCardDescription(cardType type);
bool isCardNumberValid(long number);

int main(void)
{
    long cardNumber = getInputFromUser();
    if (isCardNumberValid(cardNumber))
    {
        cardType type = getCardType(cardNumber);
        printf("%s\n",getCardDescription(type));    
    }
    else
    {
        printf("INVALID\n");    
    }
}

long getInputFromUser()
{
    long number;
    do{
        number = get_long("Card number: ");
    } while( number <= 0 );
    return number;
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

int getNumberOfDigits(long number){
    cardType type = getCardType(number);
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
    int first_digit = getDigit(number,16);
    int second_digit = getDigit(number,15);
    int third_digit = getDigit(number,14);
    int fourth_digit = getDigit(number,13);

    if( first_digit > 0 ){
        if (first_digit==5 && second_digit>=1 && second_digit<=5){
            return MASTERCARD;
        }
        if (first_digit==4){
            return VISA_16;
        }
    }
    // It can be AMEX
    else if ( second_digit > 0 )
    {
        if (second_digit==3 && ( third_digit == 4 || third_digit == 7 )){
            return AMEX;
        }
    
    }
    // It can be VISA_13
    else if ( third_digit == 0 && fourth_digit == 4)
    {
        return VISA_13;
    }
    return NONE;
}

bool isCardNumberValid(long number){
    int numberOfDigits = getNumberOfDigits(number);
    
    if (numberOfDigits < 0)
    {
        return false;
    }
    int totalSum = 0;
    
    for (int digit=1; digit <= numberOfDigits; digit++){
        int digitValue = getDigit(number,digit);
        //If the digit represents an odd position
        if (digit % 2 != 0){
            totalSum += digitValue;
        }
        else
        {
            int product = digitValue * 2;
            int sum = product;
            if (sum >= 10){
                sum = getDigit(product,1) + getDigit(product,2);
            }
            totalSum += sum;
        }
    }
    return getDigit( totalSum, 1 ) == 0;
}