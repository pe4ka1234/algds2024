#pragma warning (disable:4996)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>


#define N 9
#define PI 3.14159265358979


typedef enum
{
	circle,
	Rectangle,
	POLIGON


}tip;

typedef enum
{
	RED,
	GREEN,
	BLUE


}Svet;

typedef struct
{
	float dlina;
	float shirina;



}dlinipr;
typedef struct
{
	int a;
	float b;



}dlini;

typedef union
{
	float radiys;
	dlinipr pr;
	dlini lengthfigure;
}razmeri;


typedef struct 
{
	tip tipfig;
	Svet color;
	razmeri f;

}figura;


figura* ReadBinary(char const* filename, int* size)
{
	FILE* fp;
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("Файл не найден.");
		return 0;
	}
	fseek(fp, 0, SEEK_END); 
	int length = (int)(ftell(fp) / sizeof(figura)); 
	fseek(fp, 0, SEEK_SET); 

	figura* Arr = malloc(length * sizeof(figura));
	if (Arr ==0)
	{
			printf("Память не найдена ");
			fclose(fp);
			return 0;
			
	}

	fread(Arr, sizeof(figura), length, fp);
	fclose(fp);
	*size = length;
	return Arr;
}
int kolvofig (figura arr[], int* kr, int* pr, int* mn, int size)
{
	int i=0;
	int count = 0;
	for (i = 0; i < size; i++) 
	{

		if (arr[i].tipfig == 0)
		{
			*kr=*kr+1;
		}
		else 
		{

			if (arr[i].tipfig == 1)
			{

				*pr=*pr+1;
			}
			else
			{
				*mn=*mn+1;

			}
		}
	}


}

int kolvozv(figura arr[], int* kr, int* pr, int* mn, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{

		if (arr[i].color == 0)
		{
			*kr = *kr + 1;
		}
		else
		{

			if (arr[i].color == 1)
			{

				*pr = *pr + 1;
			}
			else
			{
				*mn = *mn + 1;

			}
		}
	}


}
float sumploshad(figura arr[], int size)
{
	int i = 0;
	float sum = 0;
	float x;
	for (i = 0; i < size; i++)
	{

		if (arr[i].tipfig == 0)
		{
			sum = sum + arr[i].f.radiys * arr[i].f.radiys * PI;
		}
		else
		{

			if (arr[i].tipfig == 1)
			{

				sum = sum + arr[i].f.pr.dlina * arr[i].f.pr.shirina ;
			}
			else
			{
				x = arr[i].f.lengthfigure.a;
				x = tan(PI / arr[i].f.lengthfigure.a) * 4;
				sum = sum + (arr[i].f.lengthfigure.b * arr[i].f.lengthfigure.b) * (arr[i].f.lengthfigure.a) / x;
			}
		}
	}
	printf("Площадь: %f", sum);
		return(0);
}

int main() 
{
	setlocale(LC_CTYPE, "Russian");
	figura* arr;
	int kr = 0;
	int pr = 0;
	int mn = 0;
	int size1 = 0;
	int size = 0;
	arr=ReadBinary("uni_shapes2023.bin", &size);
	printf("%i", size);
	kolvofig(arr, &kr, &pr, &mn, size);
	printf("\nКругов: %i \nПрямоугольников: %i  \nМногоугольников: %i  ", kr, pr, mn);
	kr = 0;
	pr = 0;
	mn = 0;
	kolvozv(arr, &kr, &pr, &mn, size);
	printf("\nКрасных: %i \nЗелёных: %i  \nГолубых: %i  \n", kr, pr, mn);
	sumploshad(arr, size);
	free(arr);
	return(0);
}