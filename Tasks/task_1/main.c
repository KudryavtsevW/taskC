#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>


int MAX(int A, int B, int i, int j, int p[][20]);  //Нахождение минимального элемента
void OutputArr(int A[][20], int SIZE);             //Вывод массива
void CheckError(int error, FILE *in);              //Для ошибок
int CheckSymbol(FILE *in, int error);              //Проверка на символ
int CheckNum(FILE*in, int SIZE, int error);        //Проверка на количество чисел в файле
int ChekVoid(FILE*in, int error);                  //Проверка файла на пустоту

int main()
{
	FILE *in;
	int SIZE;                               //Размер массива
	int PrintArr[200];                      //Массив для вывода
	int i, j;                               //переменная для заполнения массива
	int m, n;                               // Для поиска минимального пути
	int SUMM = 0;                           // Сумма максимального пути
	int Flag;                               //|Флаг для заполнение выходного масс-
											//|ива путей
	int cls;
	int ArrA[20][20];
	int ArrB[20][20];
	int Arrp[20][20];

	int error = 0;                              //Ошибка


	setlocale(LC_ALL, "Rus");
	if ((in = fopen("Text.txt", "r")) == NULL)
	{
		error = 4;
		CheckError(error, in);
		system("pause");
		return -4;

	}


	if (CheckSymbol(in, error) == 6)   //Проверяем файл на запрещенные символы
	{
		system("pause");
		return -6;
	}
	if (fseek(in, 0, SEEK_SET) != 0)
	{
		error = 1;
		CheckError(error, in);
		system("pause");
		return -1;
	}
	if (ChekVoid(in, error) == 9)
	{
		system("pause");
		return -9;
	}
	if (fseek(in, 0, SEEK_SET) != 0)
	{
		error = 1;
		CheckError(error, in);
		system("pause");
		return -2;
	}

	printf("Введите размерность таблицы :");
	if (scanf("%d", &SIZE) != 1)
	{
		error = 2;
		CheckError(error, in);
		system("pause");
		return -10;

	}

	if (SIZE <= 0)
	{
		error = 7;
		CheckError(error, in);
		system("pause");
		return -7;
	}
	if (SIZE > 20)
	{
		error = 8;
		CheckError(error, in);
		system("pause");
		return -8;
	}
	if (CheckNum(in, SIZE, error) == 5)    //Проверка на количество чисел в файле
	{

		system("pause");
		return -5;
	}
	if (fseek(in, 0, SEEK_SET) != 0)
	{
		fclose(in);
		error = 1;
		CheckError(error, in);
		system("pause");
		return -3;
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			Arrp[i][j] = 0;
		}
	}


	for (i = 0; i < SIZE; i++)             //Считывание массива из файла
	{
		for (j = 0; j < SIZE; j++)
			fscanf(in, "%d", &ArrA[i][j]);

	}

	OutputArr(ArrA, SIZE);                       //Вывод таблицы
	ArrB[0][0] = ArrA[0][0];                     //|Первые элементы этих  
												 //|массивов должны быть
												 //|одинаковым

	for (i = 1; i < SIZE; i++)                     //|Заполняем первую 
	{                                              //|строку и первый стол-  
		ArrB[0][i] = ArrB[0][i - 1] + ArrA[0][i];  //|бец в массиве ArrB  
		ArrB[i][0] = ArrB[i - 1][0] + ArrA[i][0];


		Arrp[i][0] = 1;                            //|ArrP(первую строку и столбец)
	}


	for (i = 1; i < SIZE; i++)                     //|Заполнение массива ArrB  
												   //|суммы и массив Arrp
	{                                              //|путей
		for (j = 1; j < SIZE; j++)
		{
			ArrB[i][j] = ArrA[i][j] +
				MAX(ArrB[i - 1][j],
					ArrB[i][j - 1], i, j, Arrp);
		}
	}

	if (ArrB[SIZE - 1][SIZE - 2] == ArrB[SIZE - 2][SIZE - 1])
	{
		printf("В матрице больше одного пути\n");
		printf("1 - Вывести один путь \n");
		printf("0 - Завершение работы программы\n");
		scanf("%d", &cls);
		switch (cls)
		{
		case 1:
			break;
		case 0:
			fclose(in);
			system("pause");
			return -11;
		default:
			error = 3;
			CheckError(error, in);
			system("pause");
			return -12;

		}
	}
	
	m = SIZE - 1;
	n = SIZE - 1;

	for (i = 0, j = 0; i < 2 * SIZE-1; i++, j++)     //|Заполняем массив 
	{                 	                             //|PrintArr для того чтобы его
		Flag = 0;                                    //|потом вывести(Путь из 1,1 в n,n) 
		if (Arrp[m][n] == 0)
		{
			SUMM = SUMM + ArrA[m][n];
			PrintArr[j] = n + 1;
			j++;

			PrintArr[j] = m + 1;
		}
		if (Arrp[m][n] == 1)
		{
			SUMM = SUMM + ArrA[m][n];
			Flag = 1;
			PrintArr[j] = n + 1;
			j++;

			PrintArr[j] = m + 1;
		}
		if (Flag == 0)
		{
			n = n - 1;
		}
		else
		{
			m = m - 1;
		}
	}
	i = (SIZE * 4 - 3);

	for (i, j = 0; i > 2; i--, j++)               //Вывод пути из [1][1] в [n][n]
	{
		if (j % 11 == 0)
		{
			printf("\n");
		}
		printf("A[%d]", PrintArr[i]);
		i--;
		printf("[%d] -> ", PrintArr[i]);
	}
	printf("A[%d][%d]\n", SIZE, SIZE);
	printf("Максимальная сумма =%d \n", SUMM);



	fclose(in);
	//system("pause");
	return 0;
}



int MAX(int UP, int LEFT, int i, int j, int p[][20])
{
	int max;                          //|Функция возвращает

	if (UP > LEFT)                    //|значение максимального 
	{                                 //|элемента среди врехнего
		p[i][j] = 1;                  //|и левого
		max = UP;
	}
	else
		max = LEFT;
	return max;
}

int CheckSymbol(FILE *in, int error)  //|Проверка элементов
{                                     //|массива на то,
	char str[256];                    //|являются ли они
	int i;                            //|числами
	


	while (fgets(str, 256, in) != NULL)
	{

		for (i = 0; i < 256; i++)
		{

			if (str[i] == '\0' || str[i] == '\n')
				break;

			if ((isdigit((unsigned char)str[i]) + (isspace((unsigned char)str[i])) == 0))//|Является ли символ чем то кроме
			{                                                                            //|цифры или пробела 
				error = 6;
				CheckError(error, in);
				break;
			}


		}
		if (error == 6)
			break;
	}
	return error;
}


int CheckNum(FILE*in, int SIZE, int error)
{
	int count = 0;
	int Digit;

	while (fscanf(in, "%d", &Digit) != EOF)
	{                                                //|Считываем числа пока
													 //|не конец файла
		count++;

	}

	printf("Количество чисел в файле = %d\n", count);

	if (count != SIZE * SIZE)
	{                                                //|Совпадает ли количество чи-
		error = 5;                                   //|сел в файле с резмерностью таблицы
		CheckError(error, in);

	}

	return error;
}
int ChekVoid(FILE*in, int error)
{
	int Digit;

	int count = 0;
	while (fscanf(in, "%d", &Digit) != EOF)
	{                                                //|Считываем числа пока
													 //|не конец файла
		count++;

	}

	if (count == 0)
	{
		error = 9;
		CheckError(error, in);

	}
	return error;
}

void OutputArr(int A[][20], int SIZE)        //Вывод массива
{

	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("\t ");
			printf("%d", A[i][j]);
		}
		printf("\n");
	}
}
void CheckError(int error, FILE *in)                 //Вывод ошибок на экран
{
	switch (error)
	{
	case 1:
		fclose(in);
		printf("Не удалось вернуться в начало файлового потока !\n");
		break;

	case 2:
		fclose(in);
		printf("Введено не число !\n");
		break;

	case 3:
		fclose(in);
		printf("Введено неопознанное значение !\n");
		break;


	case 4:
		fclose(in);
		printf("Не удалось открыть файл Text.txt\n");
		break;

	case 5:
		fclose(in);
		printf("Количество чисел в файле не сопоставимо с размерностью таблицы\n");
		break;

	case 6:
		fclose(in);
		printf("Ошибка! В файле недопустимые символы\n");
		break;

	case 7:
		fclose(in);
		printf("Ошибка! Размерность таблицы не может быть меньшей или равной нулю\n");
		break;
	case 8:
		fclose(in);
		printf("Ошибка! По условию размерность таблицы не приевышает 20\n");
		break;
	case 9:
		fclose(in);
		printf("Ошибка! В файле нет чисел!\n");
		break;
	default:
		fclose(in);
		printf("Недопустимая команда!\n");
		break;

	}
}
