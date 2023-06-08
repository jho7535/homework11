/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13 /* prime number */
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);

int main()
{
	char command;		   // 명령어를 입력 받을 변수
	int *array = NULL;	   // 포인터 array 선언하고 NULL로 초기화
	int *hashtable = NULL; // 포인터 hashtable 선언하고 NULL로 초기화
	int key = -1;		   // key 값 -1로 초기화
	int index = -1;		   // index -1로 초기화

	srand(time(NULL)); // rand 시드값 초기화

	printf("[----- [Jeong Hanul] [2020039076] -----]\n\n");

	do
	{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 명령어를 입력받아 command에 저장

		switch (command)
		{
		case 'z':
		case 'Z': // z or Z 입력 시
			initialize(&array);
			break;
		case 'q':
		case 'Q': // q or Q 입력 시
			freeArray(array);
			break;
		case 's':
		case 'S': // s or S 입력 시
			selectionSort(array);
			break;
		case 'i':
		case 'I': // i or I 입력 시
			insertionSort(array);
			break;
		case 'b':
		case 'B': // b or B 입력 시
			bubbleSort(array);
			break;
		case 'l':
		case 'L': // l or L 입력 시
			shellSort(array);
			break;
		case 'k':
		case 'K': // k or K 입력 시
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h':
		case 'H': // h or H 입력 시
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e':
		case 'E': // e or E 입력 시
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p':
		case 'P': // p or P 입력 시
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q'); // command가 q or Q 아닌 동안 반복

	return 1;
}

int initialize(int **a)
{
	int *temp = NULL; // 포인터 temp 선언하고 NULL로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL)
	{
		temp = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE); // temp에 int 사이즈 * MAX_ARRAY_SIZE 만큼 동적 할당
		*a = temp;											/* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a; // temp에 a 대입

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		temp[i] = rand() % MAX_ARRAY_SIZE;	 // temp[i] 에 0~12 랜덤 값 대입

	return 0;
}

int freeArray(int *a) // 배열 메모리 해제하는 함수
{
	if (a != NULL) // a가 NULL이 아닌 경우
		free(a);   // a 메모리 해제제
	return 0;
}

void printArray(int *a) // 배열 출력하는 함수
{
	if (a == NULL) // a가 NULL일 경우
	{
		printf("nothing to print.\n"); // 출력 불가 메세지 출력
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		printf("a[%02d] ", i);				 // 배열의 index 출력
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		printf("%5d ", a[i]);				 // a[i] 값 출력
	printf("\n");
}

int selectionSort(int *a) // 배열을 선택 정렬하는 함수
{
	int min;	  // 최소값을 저장할 변수
	int minindex; // 최소값의 index를 저장할 변수
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
	{
		minindex = i;							 // minindex에 i 대입
		min = a[i];								 // min에 a[i] 대입
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++) // j가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		{
			if (min > a[j]) // min이 a[j]보다 큰 경우
			{
				min = a[j];	  // min에 a[j] 대입
				minindex = j; // minindex에 j 대입
			}
		}
		a[minindex] = a[i]; // a[minindex]에 a[i] 대입
		a[i] = min;			// a[i]에 min 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) // 배열을 삽입 정렬하는 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
	{
		t = a[i];					  // t에 a[i] 대입
		j = i;						  // j에 i 대입
		while (a[j - 1] > t && j > 0) // a[j - 1]가 t보다 크고 j가 0보다 큰 동안 반복
		{
			a[j] = a[j - 1]; // a[j]에 a[j - 1] 대입
			j--;			 // j에 -- 연산
		}
		a[j] = t; // a[j]에 t 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) // 배열을 버블 정렬하는 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) // j가 1부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		{
			if (a[j - 1] > a[j]) // a[j - 1]가 a[j]보다 큰 경우
			{
				t = a[j - 1];	 // t에 a[j - 1] 대입
				a[j - 1] = a[j]; // a[j - 1]에 a[j] 대입
				a[j] = t;		 // a[j]에 t 대입
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) // 배열을 셸 정렬하는 함수
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2) // h가 MAX_ARRAY_SIZE / 2 부터 0보다 큰 동안 2로 나누어 가며 반복
	{
		for (i = 0; i < h; i++) // i가 0부터 1씩 증가하면서 h보다 작을 동안 반복
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h) // j가 i + h부터 h씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
			{
				v = a[j];						  // v에 a[j] 대입
				k = j;							  // k에 j 대입
				while (k > h - 1 && a[k - h] > v) // k가 h - 1보다 크고 a[k - h]가 v보다 큰 경우
				{
					a[k] = a[k - h]; // a[k]에 a[k - h] 대입
					k -= h;			 // k에 k - h 대입
				}
				a[k] = v; // a[k]에 v 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) // 배열을 퀵 정렬하는 함수
{
	int v, t;
	int i, j;

	if (n > 1) // n이 1보다 큰 경우
	{
		v = a[n - 1]; // v에 a[n - 1] 대입
		i = -1;		  // i에 -1 대입
		j = n - 1;	  // j에 n - 1 대입

		while (1)
		{
			while (a[++i] < v) // a[i]가 v보다 작을 동안 i에 ++ 연산
				;
			while (a[--j] > v) // a[j]가 v보다 클 동안 i에 -- 연산
				;

			if (i >= j)	 // i가 j보다 크거나 같은 경우
				break;	 // 반복문 탈출
			t = a[i];	 // t에 a[i] 대입
			a[i] = a[j]; // a[i]에 a[j] 대입
			a[j] = t;	 // a[j]에 t 대입
		}
		t = a[i];		 // t에 a[i] 대입
		a[i] = a[n - 1]; // a[i]에 a[n - 1] 대입
		a[n - 1] = t;	 // a[n - 1]에 t 대입

		quickSort(a, i);				 // a, i를 매개변수로 하여 함수 재호출
		quickSort(a + i + 1, n - i - 1); // a + i + 1, n - i - 1를 매개변수로 하여 함수 재호출
	}

	return 0;
}

int hashCode(int key) // 해쉬 함수
{
	return key % MAX_HASH_TABLE_SIZE; // key에 MAX_HASH_TABLE_SIZE 모듈로 연산값 리턴
}

int hashing(int *a, int **ht) // 해싱하는 함수
{
	int *hashtable = NULL; // 포인터 hashtable를 선언하고 NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) // ht가 NULL인 경우
	{
		hashtable = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE); // hashtable에 int 사이즈 * MAX_ARRAY_SIZE 만큼 동적 할당
		*ht = hashtable;										 /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
	{
		hashtable = *ht; /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
		hashtable[i] = -1;						  // hashtable[i]에 -1 대입

	int key = -1;							 // 변수 key를 선언하고 -1 대입
	int hashcode = -1;						 // 변수 hashcode를 선언하고 -1 대입
	int index = -1;							 // 변수 index를 선언하고 -1 대입
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) // i가 0부터 1씩 증가하면서 MAX_ARRAY_SIZE보다 작을 동안 반복
	{
		key = a[i];				  // key에 a[i] 대입
		hashcode = hashCode(key); // hashcode에 매개변수를 key로 하는 해쉬 함수 값을 대입

		if (hashtable[hashcode] == -1) // hashtable[hashcode] -1과 같은 경우
		{
			hashtable[hashcode] = key; // hashtable[hashcode]에 key 대입
		}
		else
		{

			index = hashcode; // index에 hashcode 대입

			while (hashtable[index] != -1) // hashtable[index]가 -1이 아닌 동안 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; // index에 (index + 1) MAX_HASH_TABLE_SIZE 모듈로 연산값 대입
			}
			hashtable[index] = key; // hashtable[index]에 key 값 대입
		}
	}

	return 0;
}

int search(int *ht, int key) // 해시 테이블에서 key 값을 찾는 함수
{
	int index = hashCode(key); // index에 해쉬 코드 대입

	if (ht[index] == key) // ht[index]와 key 값과 다른 경우
		return index;	  // index 리턴

	while (ht[++index] != key) // index에 ++ 연산을 하고 ht[index]과 key가 다른 동안
	{
		index = index % MAX_HASH_TABLE_SIZE; // index에 index MAX_HASH_TABLE_SIZE 모듈로 연산값을 대입
	}
	return index; // index 리턴
}
