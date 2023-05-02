//Bartlomiej Pawelec
//Nr. Grupy: WCY21KY2S1
//Nr. Albumu: 80468
//Kodowanie CRC

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

string dzielenie(string wiad,string dziel,int n,int k,int p)
{
	int i=0,j;
	while (i<k)			
	{											
		for(j=0;j<p;j++)							
		{	
			if(wiad[i+j]==dziel[j])	
        	{
                wiad[i+j]='0';
			}
        	else
		 	{
       			wiad[i+j]='1';
			}			
		}
		while(i<n &&wiad[i]!='1')
		{
			i++; 
		}
	}
	return wiad;
}

int main(){
	int i,j;
	
	string wiadomosc,wielomian;
	
	fstream plik;					
	plik.open("wejscie.txt", ios::in);
	getline(plik,wiadomosc);
	getline(plik,wielomian);
	plik.close();
	
	// Dlugosc wiadomosci		
	int wiad_len=wiadomosc.size();
	// Dlugosc wielomianu
	int wiel_len=wielomian.size();
	// Dlugosc tablicy z dopisanym kodem CRC
	int n=wiad_len+wiel_len-1;

	// Kopiowanie wiadomosci do tablicy operacyjnej
	for(i=wiad_len;i<n;i++)
	{
		wiadomosc.push_back('0');
	}
	cout<<"-----------Wiadomosc przed dopisaniem CRC-----------"<<endl<<endl;
	cout<<wiadomosc<<endl<<endl;
	
	cout<<"-----------Wielomian generujacy-----------"<<endl<<endl;
	cout<<wielomian<<endl<<endl;
	
 	//XOR
    string wynik=dzielenie(wiadomosc,wielomian,n,wiad_len,wiel_len);
	// Dopisanie crc do wiadomosci
    for(j=wiad_len;j<n;j++)
    {
   		wiadomosc[j]=wynik[j];
    }
	wiad_len=wiadomosc.size();

	cout<<"-----------Wiadomosc po dopisaniu CRC-----------"<<endl<<endl;
	cout<<wiadomosc<<endl<<endl;
	
	// Sprawdzenie integralnosci danych
	cout<<"-----------Sprawdzenie integralnosci danych-----------"<<endl<<endl;
	string sprawdzenie=dzielenie(wiadomosc,wielomian,n,wiad_len,wiel_len);

	int count=0;
	
	// Sprawdzenie czy reszta jest rowna 0
 	for(j=wiad_len-wiel_len+1;j<wiad_len;j++)
    {
   		if(sprawdzenie[j]=='0')
   		{
   			count++;
		}
    }

    if(count==wiel_len-1)
    {
    	cout<<"Transmisja zostala wykonana poprawnie";
    	fstream plik;					
		plik.open("wyjscie.txt", ios::out);		// W przypadku poprawnej transmisji, zapisuje do pliku
		plik<<wiadomosc<<endl;
		plik<<wielomian<<endl;
	}
	else
    {
    	cout<<"Transmisja zostala wykonana niepoprawnie";
	}
 	
	return 0;
	
}



