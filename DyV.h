#include<vector>
using namespace std;
void busquedaBinaria(int x, arr[] , int ini, int fin){
	if (ini>fin){
		throw out_of_range("ini esta fuera de rango");	
	}
	int medio = (ini + fin) / 2;
	if(arr[medio] == x){
		return medio;
	}
	else if (arr[medio] > x){
		return busquedaBinaria(x, arr, ini, medio -1);
	}
	else{
		return busquedaBinaria(x, arr, medio + 1, fin);
	}

}
