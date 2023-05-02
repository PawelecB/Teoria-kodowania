//Bartlomiej Pawelec
//Nr. Grupy: WCY21KY2S1
//Nr. Albumu: 80468
//Koder i dekoder

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;

// Zmienne globalne uzywane do odczytu/kodowania/dekodowania
int n;
int znaki;  //ilosc znakow do zakodowania
int dl_slownik;  //dlugosc slownika

struct Node  //struktura listy do przechowywania wynikow kodowania
{
    char znak;
	int index;
	int dlugosc;
    struct Node *next;
};

//Dodawanie do konca listy
void addEnd(struct Node** head, char znak, int index, int dlg)
{
	struct Node* newNode= (Node*) malloc(sizeof(Node)); //dynamiczne rezerwowanie pamieci
	struct Node *current = *head;
	
	newNode->znak = znak;
	newNode->index = index;
	newNode->dlugosc = dlg;
	newNode->next = NULL;
	
	if (*head == NULL) //gdy nie ma zadnego elementu w liscie
	{
		(*head) = newNode;
		return;
	}
	
	while (current->next != NULL)  //przejscie na koniec listy
	current = current->next;
	
	current->next = newNode;  //dodanie elementu na koniec listy
	return;
}


void print_list(Node *head)
{
    Node* current = head;
    while(current!=NULL)
	{
        cout<<"<"<<current->index<<","<<current->dlugosc<<","<<current->znak<<">";
        current = current->next;
    }
    if(current==NULL) 
	{
        return;
    }
}

void koder(char *bufor, struct Node** head)
{
	std::fstream plik;	
	plik.open("wyjscie.txt", ios::out);
	int curr_i;			// Zmienna poszukujaca indeksu w 
	int curr_slown = 0;		// Indeks dzialania na slowniku
	int curr_sekw = 0;		// Zmienna poszukujaca najdluzsza sekwencje znakow w iteracji
	int indeks = 0;				// Indeks 
	int sekw = 0;				// Najdluzsza wynikowa sekwencja 
	
	char nastepny_znak = bufor[dl_slownik - 1];		// Pobranie pierwszego znaku
	plik<<0<<","<<0<<","<<nastepny_znak;
	cout<<"<"<<0<<","<<0<<","<<nastepny_znak<<">"<<endl;
	addEnd(&(*head), nastepny_znak, 0, 0);

    for (int i = 0; bufor[i] == '0'; i++)     
    {
        bufor[i] = nastepny_znak;		// Wypelnienie pierwszym znakiem
    }

    nastepny_znak = bufor[dl_slownik + 1];
     
    while (nastepny_znak != '\0')
    {
        sekw = 0;		
        indeks = 0;
        
        // Poszukiwanie najdluzszej sekwencji 
        for (int i = 0; i < dl_slownik; i++)
        {
            curr_sekw = 0;			// Wyzerowanie licznika sekwencji w iteracji przy nowej iteracji
            if (bufor[curr_slown + i] == bufor[curr_slown + dl_slownik])           // Porownanie pierwszych znakow indeksu i slownika
            {
                curr_sekw = 1;
                // Sprawdzamy sekwencje 
                while(bufor[curr_slown + i + curr_sekw] == bufor[curr_slown + dl_slownik + curr_sekw] && curr_sekw < dl_slownik - 1 && bufor[(dl_slownik-1)] != NULL)
                {
                	curr_sekw++;
                }
                if (curr_sekw > sekw) 		// Jezeli wyszukana sekwencja jest dluzsza niz znaleziona w poprzedniej iteracji
                {
                	sekw = curr_sekw;
                	indeks = i;
                }
                i = i + dl_slownik - 1;
            }
        }
        nastepny_znak = bufor[curr_slown + dl_slownik + sekw];

        cout<<"<"<<indeks<<","<<sekw<<","<<nastepny_znak<<">"<<endl;
        plik<<indeks<<","<<sekw<<","<<nastepny_znak;	// Plik nie zawiera '<' '>' aby zaoszczedzic wage
        addEnd(&(*head), nastepny_znak, indeks, sekw);		// Zapisanie zakodowanego ciagu

        curr_slown = curr_slown + sekw + 1;		// Indeks na nastepny element slownika
    }
	plik.close();
	free(bufor);	
}


void dekoder(struct Node *node)
{
// Deklaracja tablicy w ktorej bedzie zdekodowana wiadomosc
	char wiad[znaki];  
	
	int i=0;
	
	while (node !=NULL)
	{
	    if(node->dlugosc == 0 && node->znak != '\n' ) 
	    {
	        wiad[i]=node->znak;		// Przepisuje znak jesli dlugosc ciagu jest rowna 0 lub jest to endline
	        i++;
	    }
	    else if(node->dlugosc > 0)  // Odkodowywanie ciagow
	    {
	    	// Odszukiwanie odpowiedniego miejsca w tabeli 
	        int tmp=0;
	        tmp=i-dl_slownik;
	        tmp += node->index;  
	        if(tmp<0)
	        {
	            tmp=0;
	        }
			
			// Przepisanie sekwencji
			int z;
	        for(z=0; z<(node->dlugosc) ;z++ ) 
	        {
	            wiad[i]=wiad[tmp];
	            i++;
	            tmp++;
	        }
	        wiad[i]=node->znak;
	        i++;
	    }
		node = node->next;
	}
	std::fstream plik;	
	plik.open("kopia.txt", ios::out);
	// Zapisanie zdekodowanej kopii
	for(i=0;i<znaki;i++)
	{
	    cout<<wiad[i];
		plik<<wiad[i]; 
	}
	plik.close();
}

int main()
{
	struct Node* head = NULL;  //utworzenie poczatku listy
	
	ifstream plik("wejscie.txt");
	char ch;
	
	// Zliczenie znakow w pliku do utworzenia tablicy bufora
	while(plik.get(ch)) 
	{
		n++;
	}
	znaki=n;
	
    cout<<"Podaj rozmiar slownika: "<<endl;
    cin>>dl_slownik;
    cout<<endl;

    n += dl_slownik;
	char* bufor=(char*)malloc((n)*sizeof(char));		

    for (int i = 0; i < dl_slownik - 1; i++)//uzupelnij tablice zerami
    {
       bufor[i] = '0';
    }

	plik.clear();
	plik.seekg(0);

	cout<<"------------SLOWO KODOWE--------------"<<endl<<endl;
    for (int i = dl_slownik - 1; i < n - 1; i++)
    {
		plik.get(bufor[i]);
		cout<<bufor[i];
    }
    bufor[n - 1] = '\0';
    cout<<endl<<endl;
	
	cout<<"------------FAZA KODOWANIA--------------"<<endl<<endl;
	koder(bufor, &head);
	
	cout<<"------------FAZA DEKODOWANIA--------------"<<endl<<endl;
	dekoder(head);
	
	free(head);
	
	return 0;
}
