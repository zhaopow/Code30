/*Zhao Taylor
tz2857
*/

#include <stdio.h>
#include <math.h>
int AustinHr, IrishHr, Min; /*variables for Time*/
int Dollars, Cents;	/*Variables for Currency*/
double Euros;	/*Variables for Currency*/
double Celsius;	/*Units for Temperature*/
int Fahren;	/*Units for Temperature*/
int Pounds, Ounces;	/*Units for Weight*/
double Kilograms;	/*Units for Weight*/
double Miles, KM;	/*Units for Distance*/
const double DOLLAR_UNIT = 0.74;
const double EURO_UNIT = 1.36;
const double FREEZE_POINT = 32.0;
const double CEL_UNIT = 9.0 / 5.0;
const double FAH_UNIT = 5.0 / 9.0;
const double PD_UNIT = .45359237;
const double OZ_IN_PD = 16.0;
const double DIST_UNIT = 0.6213712;

int main(void)
{
	int control = 0;	/*control is used to exit the command menu loop*/
	
	while (control == 0){
		int command; /*The user input command*/
		printf("Enter a number from the menu (1-11) to select a specific conversion to perform or to quit: ");
		scanf_s("%d", &command);
		if (1 <= command && command <= 10){
			if (command == 1){
				/*Austin to Irish Time Conversion*/
				printf("Enter Austin time to be converted, expressed in hours and minutes: ");
				scanf("%d %d", &AustinHr, &Min);
				IrishHr = (AustinHr + 6) % 24;
				if (AustinHr >= 0 && AustinHr <= 17){
					printf("The time in Ireland equialent to %d %.2d in Austin is %d %.2d of the same day\n", AustinHr, Min, IrishHr, Min);
				}
				else{
					printf("The time in Ireland equialent to %d %.2d in Austin is %d %.2d of the next day\n", AustinHr, Min, IrishHr, Min);
				}
			}

			if (command == 2){
				/*Irish to Austin Time Conversion*/
				printf("Enter Irish time to be converted, expressed in hours and minutes: ");
				scanf("%d %d", &IrishHr, &Min);
				AustinHr = (IrishHr + 18) % 24;
				if (IrishHr >= 0 && IrishHr <= 5){
					printf("The time in Austin equivalent to %d %.2d in Ireland is %d %.2d the previous day\n", IrishHr, Min, AustinHr, Min);
				}
				else{
					printf("The time in Austin equivalent to %d %.2d in Ireland is %d %.2d the same day\n", IrishHr, Min, AustinHr, Min);
				}
			}

			if (command == 3){
				/*Dollar to Euro Conversion*/
				printf("Enter USD value: ");
				scanf("%d %d", &Dollars, &Cents);
				Euros = (Dollars + 0.01*Cents) * DOLLAR_UNIT;
				printf("EUR value is: %lf Euros\n", Euros);
			}

			if (command == 4){
				/*Euro to Dollar Conversion*/
				printf("Enter EUR value: ");
				scanf("%lf", &Euros);
				Dollars = Euros * EURO_UNIT;
				Cents = 100 * ((Euros * EURO_UNIT) - Dollars);
				printf("USD value is: $%d.%.2d\n", Dollars, Cents);
			}

			if (command == 5){
				/*Fahrenheit to Celsius Conversion*/
				printf("Enter temperature in Fahrenheit: ");
				scanf("%d", &Fahren);
				Celsius = FAH_UNIT * (Fahren - FREEZE_POINT);
				printf("Temperature in Celsius is: %lf\n", Celsius);
			}

			if (command == 6){
				/*Celsius to Fahrenheit Conversion*/
				printf("Enter temperature in Celsius: ");
				scanf("%lf", &Celsius);
				Fahren = CEL_UNIT * Celsius + FREEZE_POINT;
				printf("Temperature in Fahrenheit is: %d\n", Fahren);
			}

			if (command == 7){
				/*KG to Pound Conversion*/
				printf("Enter weight in kg: ");
				scanf("%lf", &Kilograms);
				Pounds = Kilograms / PD_UNIT;
				Ounces = (Kilograms / PD_UNIT - Pounds) * OZ_IN_PD;
				printf("Weight in pounds and ounces is: %d lb %d oz\n", Pounds, Ounces);
			}

			if (command == 8){
				/*Pound to KG Conversion*/
				printf("Enter weight in pounds and ounces: ");
				scanf("%d %d", &Pounds, &Ounces);
				Kilograms = Pounds * PD_UNIT + (Ounces / OZ_IN_PD) * PD_UNIT;
				printf("Weight in kg is: %lf\n", Kilograms);
			}

			if (command == 9){
				/*KM to Mi*/
				printf("Enter distances in km: ");
				scanf("%lf", &KM);
				Miles = KM * DIST_UNIT;
				printf("Distance in miles is: %lf mi\n", Miles);
			}

			if (command == 10){
				/*Mi to KM*/
				printf("Enter distance in miles: ");
				scanf("%lf", &Miles);
				KM = Miles / DIST_UNIT;
				printf("Distance in km is: %lf km\n", KM);
			}
		}
		else if (command == 11){
			control = 1;
		}
		else {
			printf("That is an incorrect input.\n");
			control = 1;
		}
	}
	
	printf("Goodbye");
	return 0;
}