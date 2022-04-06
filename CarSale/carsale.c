#define _CRT_SECURE_NO_WARNINGS

/*to use scanf() and printf() and any other functions*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
//#pragma warning(disable : 4996)
/*Constants*/
#define COMMUNAL_TAX 00.029f
#define CO2_EMISSION_TAX 00.10f
#define NHS_DISCOUNT 0.29f
#define FESTIVAL_DISCOUNT 0.10f
#define NEWSLETTER_SUBSCRIBER_DISCOUNT 0.05f
#define OPTION_A 'a'
#define OPTION_B 'b'
#define OPTION_C 'c'
#define EXIT 'x'
#define YES 'y'
#define NO 'n'


unsigned int carPricesList[12] = { 100000,80000,120000,100000,1000000,80000,90000,120000,25000,30000,22000,21000 };
char* carName[12] = { "Bentley","Ferrari","MCLaren","Maserati","Buggati","BMW","Audi","Mercedes-Benz","Hyundai","Toyota","Vauxhall","Suzuki" };
unsigned int carCountList[12] = { 5,8,10,3,0,10,15,12,13,6,20,25 }, totalCarCount = 0;
unsigned short carNumber = 0;
double userSelectedTotalCarPrice = 0;
char* userOldCarName = "\0";
unsigned int userOldCarMakeYear = 0;
unsigned short userOldCarOwnersCount = 0;
unsigned int festiveDate[] = {15,25,25};
unsigned int festiveMonth[] = {04,11,12};
char* festiveName[] = {"Good Friday","Black Friday","Christmas Day"};
SYSTEMTIME curDate;
short isDiscount = 0;
short nhsDiscount = 0;
short newsLetterDiscount = 0;
short festivalDiscount = 0;
unsigned int userNHSNumberInt = 0;
long long int userPhoneNumberInt = 0;
char* discountReason = "\0";




void fullscreen();
char userCharInput();
void viewCars();
void viewCarsDetails();
void viewOffers();
void carValuation();
void sortingByAvailCar();
void carSelection();
char conFromCapSmall(char userChoice);
char userOldCarDetails();
char userCarValuation();
void mainMenu();
void discountApplied();
unsigned int userIntInput(short inputLength);


char userCharInput()
{
	char userChoice="\0";
	userChoice = _getch();
	userChoice=conFromCapSmall(userChoice);
	printf("%c",userChoice);
	return userChoice;
}
 
unsigned int userIntInput(short inputLength)
{
	char userStrInput[10]="\0";
	userStrInput[0]= "0";

	short iteration = 0;
	int userIntConInput = 0;

	for (iteration = 0; iteration < inputLength; iteration++)
	{
		userStrInput[iteration]=_getch();
		printf("%c",userStrInput[iteration]);
	}
	userIntConInput = atoi(userStrInput);

	return userIntConInput;
}

void viewCarsDetails()
{
	unsigned int iteration = 0;
	printf("\n---------------------------------------------------\n");
	printf("|Index Car Name\t\tCar price   Cars Available|\n");
	printf("|-------------------------------------------------|\n");
	iteration = 0;
	for (iteration = 0; iteration < 12; iteration++)
	{
		printf("|%3d\t%-17s%-16d%-9d|\n",iteration+1, carName[iteration], carPricesList[iteration], carCountList[iteration]);
	}
	printf("---------------------------------------------------\n");
}

void sortingByAvailCar()
{
	unsigned int i, j;
	char* tempForString="\0";
	int tempForInt=0;
	for (i = 0; i < 12; i++)
	{
		for (j = i + 1; j < 12; j++)
		{
			if (carCountList[i] < carCountList[j])
			{
				tempForInt = carCountList[i];
				carCountList[i] = carCountList[j];
				carCountList[j] = tempForInt;
				tempForInt = 0;

				tempForInt = carPricesList[i];
				carPricesList[i] = carPricesList[j];
				carPricesList[j] = tempForInt;

				tempForString = carName[i];
				carName[i] = carName[j];
				carName[j] = tempForString;
			}
		}
	}
		
}
void carSelection()
{
	char userChoice="\0";
	
	printf("\n\nEnter Car Number Here:-");
	carNumber=userIntInput(2);
	carNumber--;
	if (carNumber <12 && carNumber >-1)
	{
		system("cls");
		printf("\nYou have selected %s car whose price is %d \n", carName[carNumber], carPricesList[carNumber]);
		printf("\nIf you want to confirm your booking for car Press Y for Yes and N for No\n");
		userChoice=userCharInput();
		switch(userChoice)
		{ 
		case 'y':
			printf("\nThanks for confirmation :)\n");
			printf("\nFor Discount Purposes We are going to ask some details about you.\n If you are agree to share details with us Press Y or else N. \n");
			userChoice=userCharInput();
			switch(userChoice)
			{
			case YES:
				while (userChoice != EXIT)
				{
					system("cls");
					printf("\nPress Y if you have any old car for exchange.");
					printf("\nPress N if you do not have an old car to exchange.");
					printf("\nPress x to Return to the Menu.\n");
					userChoice = userCharInput();
					switch (userChoice)
					{

					case YES:
						userOldCarDetails();
						printf("\n Do you agree to trade in your car with our specified price?\nEnter Y for Yes or N for No:-");
						userChoice = userCharInput();
						switch (userChoice)
						{
						case YES:
							viewOffers();/*if you work for nhs or any medical related companies */
							//discount code

						case NO:
							carValuation();
							//pricing calc code
						default:
							system("cls");
							printf("Wrong Input, PLease Try Again!!!\n");
							system("pause");
							break;
						}
					case NO:
						system("cls");
						viewOffers();

					case 'x':
						system("cls");
						mainMenu();

					default:
						system("cls");
						printf("Wrong Input, PLease Try Again!!!\n");
						system("pause");
						break;
					}
				}


			case NO:
				carValuation();
				break;
			default:
				break;
			}
			
		case 'n':
				system("cls");
				printf("\nAs per Your Input, We are again showing our cars list.\n");
				viewCarsDetails();
				carSelection();
				break;
				
		default :
				
				system("cls");
				printf("Wrong Input, PLease Try Again!!!\n");
				viewCarsDetails();
				carSelection();
				break;
		}
	}
	else
	{
		printf("\nWrong Input, try Again!!!!\n");
		system("pause");
		system("cls");
		viewCarsDetails();
		carSelection();
	}

}
void discountApplied()
{
	if (isDiscount == 1)
	{
		printf("Congrats You are getting %s of %d",discountReason);
	}
}
void carValuation()
{
	printf("\n Car Price: %5d ",carPricesList[carNumber]);
	printf("\n Communal Tax:%5f%",(COMMUNAL_TAX*100));
	printf("\nCO2 Emmission Tax:%5f%", (CO2_EMISSION_TAX * 100));
	userSelectedTotalCarPrice = (double)carPricesList[carNumber];
	userSelectedTotalCarPrice = userSelectedTotalCarPrice + (userSelectedTotalCarPrice * COMMUNAL_TAX) + (userSelectedTotalCarPrice * CO2_EMISSION_TAX);
	printf("\nTotal Price after Applying Taxes: %5lf", userSelectedTotalCarPrice);
	if (isDiscount == 1)
	{
		if (nhsDiscount == 1)
		{
			printf("\n %s Discount:%5f%", discountReason, (NHS_DISCOUNT * 100));
			userSelectedTotalCarPrice = userSelectedTotalCarPrice - (userSelectedTotalCarPrice * NHS_DISCOUNT);
		}
		else if (newsLetterDiscount == 1)
		{
			printf("\n %s Discount:%5f%", discountReason, (NEWSLETTER_SUBSCRIBER_DISCOUNT * 100));
			userSelectedTotalCarPrice = userSelectedTotalCarPrice - (userSelectedTotalCarPrice * NEWSLETTER_SUBSCRIBER_DISCOUNT);

		}
		else if (festivalDiscount == 1)
		{
			printf("\n %s Discount:%5f%", discountReason, (FESTIVAL_DISCOUNT * 100));
			userSelectedTotalCarPrice = userSelectedTotalCarPrice - (userSelectedTotalCarPrice * FESTIVAL_DISCOUNT);
		}
		printf("After Applying %s Discount Final Price: %5lf", discountReason, userSelectedTotalCarPrice);

	}
	else
		printf("NO Discount Applied, So Final Price: %5lf",userSelectedTotalCarPrice);
	system("pause");
	
}
void viewOffers()
{
	char userChoice = "\0";
	char userNHSNumberstr[7] = "\0";
	short userInputLen = 0;

	char userPhoneNumberstr [12]= "\0";
	
	printf("\nPress A if you work for NHS or any other Clinical Companies.");
	printf("\nPress B if you are subscriber of our News Letter.");
	printf("\nPress C if none of above option applies to you and still want to get some Discount.\n'Note : This discount only applied on Festival days.' ");
	printf("\nPress x to go back to Main Menu");
	userChoice = userCharInput();
	switch (userChoice)
	{
	case OPTION_A:

		system("cls");
		printf("'Your NHS Identification Card will be checked at delivery time, so Please Carry it with you.'");
		printf("\nPlaese Enter your NHS Identity Number:-");
		scanf("\n%[0-5] ", &userNHSNumberstr);
		userInputLen = strlen(userNHSNumberstr);
		
		while (userInputLen != 5)
		{
			system("cls");
			printf("\nOops!!!  Your NHS Number is Wrong, Please Re-Enter it:-");
			scanf("\n%[0-5] ", &userNHSNumberstr);
			userInputLen = strlen(userNHSNumberstr);
		}
		if (userInputLen == 5)
		{
			userNHSNumberInt = atoi(userNHSNumberstr);
			isDiscount = 1;
			nhsDiscount = 1;
			userInputLen = 0;
			discountReason = "NHS volunteer";
			
		}
		carValuation();
		break;
		
	case OPTION_B:
		system("cls");
		printf("\nPlaese Enter your Mobile-Phone Number for Verification (The one which gave you during subscribing our news letter)");
		printf("\n'''Please Enter it with adding 0 in starting of your Number.''' :-");
		scanf("\n%s ", &userPhoneNumberstr);
		userInputLen = strlen(userPhoneNumberstr);
		//verification logic

		while (userInputLen != 11)
		{
			system("cls");
			printf("\nOops!!!  Your Phone Number is Wrong, Please Re-Enter it");
			printf("\n'''Please Enter it with adding 0 in starting of your Number.''' :-");
			scanf("\n%s ", &userPhoneNumberstr);
			userInputLen = strlen(userPhoneNumberstr);
		}
		if (userInputLen == 11)
		{
			userPhoneNumberInt = atoll(userPhoneNumberstr);
			isDiscount = 1;
			newsLetterDiscount = 1;
			userInputLen = 0;
			discountReason = "News Letter Subscriber";
		}
		carValuation();
		break;

	case OPTION_C:
		for (short i = 0; i < 3; i++)
		{
			if (curDate.wDay == festiveDate[i] && curDate.wMonth == festiveMonth[i])
			{
				isDiscount = 1;
				discountReason = festiveName[i];
				festivalDiscount = 1;
			}
			carValuation();
		}
		break;

	case EXIT:
		break;

	default:
		break;
	}
	//if
	//GetSystemTime(&curDate);
}

char conFromCapSmall(char userChoice)
{
	if (userChoice < 97)
	{
		userChoice = userChoice + 32;
	}
	return userChoice;
}
void viewCars()
{
	short iteration = 0;
	printf("\n----------------------\n");
	printf("|Index  Car Name     |\n");
	printf("|--------------------|\n");
	for (iteration = 0; iteration < 12; iteration++)
	{
		printf("|%3d\t%-13s|\n", iteration + 1, carName[iteration]);
	}
	printf("----------------------\n");
}
char userOldCarDetails()
{
	unsigned short carNumber = 0;
	char userChoice="\0";
	viewCars();
	printf("\nEnter Your Old car Index Number From Shown List and If not Listed Enter 0 to go back to the Main Menu.\n");
	carNumber = (short)userIntInput(2);
	
	if (carNumber > 0)
	{
		char userChoice="\0";
		carNumber--;
		userOldCarName = carName[carNumber];
		printf("\nEnter Car make Year :-");
		userOldCarMakeYear = userIntInput(4);
		printf("\nIn past, how many person bought this car? :-");
		userOldCarOwnersCount=userIntInput(2);
		userCarValuation();
	}
	else
	{
		system("cls");
		mainMenu();
	}
}
char userCarValuation()
{
	int flag=0;
	char* fault="\0";
	
	char* lowPriceCarsList[4] = { "Hyundai","Toyota","Vauxhall","Suzuki" };
	unsigned int userOldCarPrice=0;
	unsigned short lowPriceConf = 1;
	for (unsigned short i = 0; i < 4; i++)
	{
		lowPriceConf = strcmp(lowPriceCarsList[i], userOldCarName);
		if (lowPriceConf == 0)
			break;
		printf("%d",lowPriceConf);
	}
	if (userOldCarMakeYear < 1999)
	{
		flag = 1;
		fault = "Your car is Very Old";
	}
	else if (userOldCarOwnersCount > 5)
	{
		flag = 1;
		fault = "Your car have too many previous owners";
	}
	else if (userOldCarMakeYear<2005 && lowPriceConf==0 )
	{
		userOldCarPrice = 2000;
	}
	else if (userOldCarMakeYear < 2010 && lowPriceConf == 0)
	{
		userOldCarPrice = 6000;
	}
	else if (userOldCarMakeYear < 2015 && lowPriceConf == 0)
	{
		userOldCarPrice = 14000;
	}
	else if (userOldCarMakeYear < 2021 && lowPriceConf == 0)
	{
		userOldCarPrice = 18000;
	}
	else if (userOldCarMakeYear > 2020 && lowPriceConf == 0)
	{
		userOldCarPrice = 20000;
	}
	else if (userOldCarMakeYear < 2005 && lowPriceConf == 1)
	{
		userOldCarPrice = 5000;
	}
	else if (userOldCarMakeYear < 2010 && lowPriceConf == 1)
	{
		userOldCarPrice = 10000;
	}
	else if (userOldCarMakeYear < 2015 && lowPriceConf == 1)
	{
		userOldCarPrice = 30000;
	}
	else if(userOldCarMakeYear < 2021 && lowPriceConf == 1)
	{
		userOldCarPrice = 45000;
	}
	else if (userOldCarMakeYear > 2020 && lowPriceConf == 1)
	{
		userOldCarPrice = 55000;
	}

	if (flag == 1)
	{
		system("cls");
		printf("\nSorry,We can not Accept Your car for exchange for listed below reason.\n");
		printf("%s",fault);
		system("pause");
	}
	else
	{
		system("cls");
		printf("\nYour car has qualified our check\n");
		printf("\nAs per our valuation system, Your %s's price is %d \n",userOldCarName,userOldCarPrice);
		system("pause");
	}

}
void mainMenu()
{
	char userChoice="\0";
	unsigned int iteration = 0;
	printf("Press a to see car's price, availability, etc.\n");
	printf("Press b to buy the car\n");
	printf("Press c to View Sales of cars\n");
	printf("Press x to Exit\n");

	//Using Function for users choicing
	userChoice = userCharInput();

	switch (userChoice)
	{
	case OPTION_A:
		system("cls");
		for (iteration = 0; iteration < 12; iteration++)
		{
			totalCarCount = totalCarCount + carCountList[iteration];
		}
		printf("Total %d cars available", totalCarCount);
		//sorting function
		sortingByAvailCar();
		viewCarsDetails();
		system("Pause");
		system("cls");
		mainMenu();
		break;

	case OPTION_B:
		system("cls");
		printf("You can select any car by typing number of the car \n");
		viewCarsDetails();
		carSelection();
		system("Pause");
		
		break;

	case OPTION_C:
		break;

	case EXIT:
		exit(0);

	default:
		printf("You have entered Wrong Input!!\n\n");
		system("Pause");
		system("cls");
		mainMenu();
		break;
	}
}
void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
void main()
{
	fullscreen();
	system("cls");
	printf("Welcome to Auxi car sales agency\n \n");
	mainMenu();
}