#include<iostream>
using namespace std;

void ssort(int arr[], int n){                         //ѡ������

	for (int i = 0; i < n; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min]) swap(arr[j], arr[min]);
		}

	}
}

void midx(int arr[], int n, int x, int m) {                 //���ַ�����

	int mid = x / 2;
	if (arr[mid] > m) midx(arr, n,mid ,m);
	if (arr[mid] < m) midx(arr, mid+1,x, m);
	if (arr[mid] == m) { cout << mid;}

   
	
	
}
   template <typename T>
int partition(T arr[], int n, int m){
	T v = arr[n];
	int j = n;
	for (int i = n + 1; i <= m; i++){

		if (arr[i] < v){ swap(arr[i], arr[j + 1]); j++; }
	}
	swap(arr[n], arr[j]);
	return j;

}



template <typename T>
void quicksort(T arr[], int l, int r){          //��������
	if (l >= r) return;
	int p;
	p = partition(arr, l, r);

	quicksort(arr, l, p);

	quicksort(arr, p + 1, r);
}

int main(){
	int a;
	int ar[10] = { 65, 92, 66, 16, 39, 21, 40, 71, 89, 0 }; //���������
	    ssort(ar, 10);                     //����
		for (int i = 0; i < 10; i++)
		{
			cout << ar[i] <<" ";
		}
		cin >> a;
		midx(ar, 0,10, a);                    //�������飬���鷶Χ��������






}