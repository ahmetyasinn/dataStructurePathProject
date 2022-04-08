#include <stdio.h>
#include <stdlib.h>

struct city{
 int relatedCityIndex;
 char *cityName;
 struct city *relatedCities[20];
};
typedef struct city City;
typedef struct city *CityPointer;
CityPointer createCity(char *cityName);
void setRoadMap();
void recursionSearchCitys(CityPointer *cityStack,char *destinationCity,char *previousCities[100],int previousCitiesIndex);
int searchInPreviousCities(char *previousCities[],char *searchingCity,int previousCitiesIndex);
void printPreviousCities(char *previousCities[],int previousCitiesIndex);
void connectCity( CityPointer *baseCity,CityPointer *otherCity );
void copyArrayToAnother(char *sourceArray[],char *destArray[],int length);
CityPointer cityPA;
CityPointer cityPB;
CityPointer cityPC;
CityPointer cityPD;
CityPointer cityPE;
CityPointer cityPF;
CityPointer cityPG;
CityPointer cityPH;
CityPointer cityPI;
CityPointer cityPJ;
char *mostLengthPaths [100];
int lengthOfPath;
int main(int argc, char *argv[]) {
	setRoadMap();
	char *previousCities [100];
	lengthOfPath = 0;
	recursionSearchCitys(&cityPA,"H",previousCities,0);//Search the available paths
	printf("-------------------Longest of paths-------------------\n");
	printPreviousCities(mostLengthPaths,lengthOfPath);
	return 0;
}
void setRoadMap()
{
    cityPA = createCity("A");
    cityPB = createCity("B");
    cityPC = createCity("C");
	cityPD = createCity("D");
	cityPE = createCity("E");
	cityPF = createCity("F");
	cityPG = createCity("G");
	cityPH = createCity("H");
	cityPI = createCity("I");
	cityPJ = createCity("J");
	connectCity(&cityPA,&cityPB);
	connectCity(&cityPA,&cityPC);
	connectCity(&cityPA,&cityPD);
	connectCity(&cityPA,&cityPE);
	connectCity(&cityPB,&cityPC);
	connectCity(&cityPB,&cityPH);
	connectCity(&cityPB,&cityPI);
	connectCity(&cityPC,&cityPF);
	connectCity(&cityPC,&cityPD);
	connectCity(&cityPC,&cityPI);
	connectCity(&cityPC,&cityPG);
	connectCity(&cityPG,&cityPJ);
	connectCity(&cityPG,&cityPH);
}
void connectCity( CityPointer *baseCity,CityPointer *otherCity ){
 int index = (*baseCity)->relatedCityIndex;
 (*baseCity)->relatedCities[index] = *otherCity;
 (*baseCity)->relatedCityIndex = index + 1;
 int relatedCityIndex = (*otherCity)->relatedCityIndex;
 (*otherCity) -> relatedCities[relatedCityIndex] = *baseCity;
 (*otherCity)->relatedCityIndex = relatedCityIndex + 1;
 //printf("MainCity : %s -----> RelatedCity : %s \n",(*cityStack)->cityName,(*cityStack)->relatedCities[index]->cityName);
 //printf("RelatedCity : %s -----> MainCity : %s \n",cityP->cityName,cityP->relatedCities[relatedCityIndex]->cityName);
}
CityPointer createCity(char *cityName)
{
	 CityPointer cityP = ( CityPointer )malloc( sizeof( City ) );
	 cityP->cityName = cityName;
	 cityP->relatedCityIndex = 0;
	 return cityP;
}
void recursionSearchCitys(CityPointer *cityStack,char *destinationCity,char *previousCities[],int previousCitiesIndex)
{
	int i = 0;
	for(i= 0;i<((*cityStack)->relatedCityIndex);i++)
	{
		if(searchInPreviousCities(previousCities,(*cityStack)->relatedCities[i]->cityName,previousCitiesIndex) == 1)
		{
			continue;
		}
		if(searchInPreviousCities(previousCities,(*cityStack)->cityName,previousCitiesIndex) == 0)
		{
			previousCities[previousCitiesIndex] = (*cityStack)->cityName;
			previousCitiesIndex = previousCitiesIndex + 1;
		}
		if((*cityStack)->relatedCities[i]->cityName == destinationCity)
		{
			previousCities[previousCitiesIndex] = destinationCity;
			previousCitiesIndex = previousCitiesIndex + 1;
			printPreviousCities(previousCities,previousCitiesIndex);
			if(lengthOfPath <= previousCitiesIndex)
			{
				lengthOfPath = previousCitiesIndex;
				copyArrayToAnother(previousCities,mostLengthPaths ,lengthOfPath);
			}
			previousCities[previousCitiesIndex] = "";
			previousCitiesIndex = previousCitiesIndex - 1;
			continue;
		}
		recursionSearchCitys(&((*cityStack)->relatedCities[i]),destinationCity,previousCities,previousCitiesIndex);
	}
}
int searchInPreviousCities(char *previousCities[],char *searchingCity,int previousCitiesIndex)
{
	int i = 0;
	for(i = 0; i < previousCitiesIndex; i++)
	{
		if(previousCities[i] == searchingCity)
		{
			return 1;
		}
	}
	return 0;
}
void copyArrayToAnother(char *sourceArray[],char *destArray[],int length)
{
	int i = 0;
	for(i = 0; i < length; i++)
	{
		destArray[i] = sourceArray[i];
	}
}
void printPreviousCities(char *previousCities[],int previousCitiesIndex)
{
	int i;
	char* firstCity = previousCities[0];
	printf("%s --> ",previousCities[0]);
	for(i = 1; i < previousCitiesIndex - 1; i++)
	{
		printf("%s --> ",previousCities[i]);
	}
	printf("%s \n",previousCities[previousCitiesIndex - 1]);
}