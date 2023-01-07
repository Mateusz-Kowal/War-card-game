#include <iostream>
#include <string.h>													// stringi [LennyFace]
#include <windows.h>												// Sleep([czas]) oraz key inputs
#include <stdlib.h>													// system("cls")
#include <time.h>													// srand(time(NULL));
#include <fstream>													// tylko do obslugi plikow	

using namespace std;												

int nrwojny;														// zmienne do pojedynczej gry
int IloscWojen=0, IloscAsow=0, WojnyAsow=0;
int Wojny1=0, Wojny2=0, Wojny3=0, Wojny4=0, Wojny5=0;
int oneJ=0;
int oneQ=0;
int oneK=0;
int oneA=0;
int twoJ=0;
int twoQ=0;
int twoK=0;
int twoA=0;
string PotasowaneKarty;

int IloscRuchow=0, WynikPorownania=0, IloscPrzelaman=-1, przewaga1=0, przewaga2=0, remis=0, PrzewagaPrzedtem=0, PrzewagaTeraz=0, WygranaRundy1=0, WygranaRundy2=0;
//	wyzej zmienne wziete z funkcji "rozgrywka"

																	// zmienne do ogolnych statystyk
int IloscGier, BierzacaGra;											// ilosc gier w sumie, nr gry bierzacej
int SumaWojen=0, SumaAsow=0, SumaWojenAsow=0;
float SredniaWojen=0, SredniaSumyAsow=0, SredniaWojenAsow=0;
int SumaWojen1=0, SumaWojen2=0, SumaWojen3=0, SumaWojen4=0, SumaWojen5=0;
float SredniaWojen1=0, SredniaWojen2=0, SredniaWojen3=0, SredniaWojen4=0, SredniaWojen5=0;
int SumaKolejek=0;
float SredniaKolejek=0;
int wygrane1=0, wygrane2=0;											// ilosc wygranych poszczegolnych graczy
int SumaPrzelaman=0;
float SredniaPrzelaman=0;

int MaxRuchow=0, MinRuchow=2000;									// maksymalna i minimalna ilosc kolejek w jakiejs grze z wielu
int Wygrane0Asow=0, Wygrane1As=0, Wygrane2Asy=0, Wygrane3Asy=0, Wygrane4Asy=0;	// ilosc wygranych gier przy x asow na poczatku
int Ilosc0Asow=0, Ilosc1Asa=0, Ilosc2Asow=0, Ilosc3Asow=0, Ilosc4Asow=0;		// ilosc gier gdzie gracz mial x asow na poczatku


typedef struct														// definiowanie struktury Gracz
{
//	string Nazwa;
	int IloscKart;
	char Karta[52];
} Gracz;



string tasuj()														// tasowanie kart
{
	int i, pozycja1, pozycja2;
	char k;
	string tab="22223333444455556666777788889999DDDDJJJJQQQQKKKKAAAA";		// 111111111111111111111111AAAAAAAAAAAAAAAAAAAAAAAA11AA
																			// 22223333444455556666777788889999DDDDJJJJQQQQKKKKAAAA
	for (i=0; i<1000000; i++)
	{
		pozycja1=rand()%52;
		pozycja2=rand()%52;
		k=tab[pozycja1];
		tab[pozycja1]=tab[pozycja2];
		tab[pozycja2]=k;
	}
	return tab;
}

void rozdajKarty(Gracz *gracz1, Gracz *gracz2)						// rozdawanie kart graczom na poczatku
{				
	PotasowaneKarty=tasuj();
	int i, j1=0, j2=0;
	for (i=0; i<52; i++)
	{
		gracz1->Karta[j1]=PotasowaneKarty[i];
		j1++;
		i++;
		gracz2->Karta[j2]=PotasowaneKarty[i];
		j2++;
	}
}



int wojna (Gracz *gracz1, Gracz *gracz2)							// przeprowadza wojne
{
	nrwojny++;
	int karta1, karta2;
	switch (gracz1->Karta[2*nrwojny])										// okreslenie 1. karty
	{
		case 65:
		{
			karta1=14;
			break;
		}
		case 75:
		{
			karta1=13;
			break;
		}
		case 81:
		{
			karta1=12;
			break;
		}
		case 74:
		{
			karta1=11;
			break;
		}
		case 68:
		{
			karta1=10;
			break;
		}
		default:
		{
			karta1=gracz1->Karta[2*nrwojny]-48;
		}
	}
	
	switch (gracz2->Karta[2*nrwojny])										// okreslenie 2. karty
	{
		case 65:
		{
			karta2=14;
			break;
		}
		case 75:
		{
			karta2=13;
			break;
		}
		case 81:
		{
			karta2=12;
			break;
		}
		case 74:
		{
			karta2=11;
			break;
		}
		case 68:
		{
			karta2=10;
			break;
		}
		default:
		{
			karta2=gracz2->Karta[2*nrwojny]-48;
		}
	}
	
	if (gracz1->Karta[2*nrwojny-2]==65 && gracz2->Karta[2*nrwojny-2]==65)		// warunek na wojne asow
	{
		WojnyAsow++;
	}
																	// sprawdza kto wygral wojne
	if (karta1>karta2)												
	{
		if (gracz2->Karta[2*nrwojny-1]==65)
		{
			IloscAsow++;
		}
		return 1;
	}
	else if (karta2>karta1)
	{
		if (gracz1->Karta[2*nrwojny-1]==65)
		{
			IloscAsow++;
		}
		return 2;
	}
	else															
	{
		if (gracz1->Karta[2*nrwojny-1]==65 || gracz2->Karta[2*nrwojny-1]==65)		// warunek na wygranie asa
		{
			IloscAsow++;
		}
		
		if (gracz2->IloscKart<2*nrwojny+1)
		{
			return 1;
		}
		else if (gracz1->IloscKart<2*nrwojny+1)
		{
			return 2;
		}
		else
		{
			return wojna(gracz1, gracz2);
		}
	}
}



int porownanie (Gracz *gracz1, Gracz *gracz2)						// porownuje karty obu graczy w celu okreslenia kto wygral
{
	int karta1, karta2;
	switch (gracz1->Karta[0])										// okreslenie 1. karty
	{
		case 65:
		{
			karta1=14;
			break;
		}
		case 75:
		{
			karta1=13;
			break;
		}
		case 81:
		{
			karta1=12;
			break;
		}
		case 74:
		{
			karta1=11;
			break;
		}
		case 68:
		{
			karta1=10;
			break;
		}
		default:
		{
			karta1=gracz1->Karta[0]-48;
		}
	}
	
	switch (gracz2->Karta[0])										// okreslenie 2. karty
	{
		case 65:
		{
			karta2=14;
			break;
		}
		case 75:
		{
			karta2=13;
			break;
		}
		case 81:
		{
			karta2=12;
			break;
		}
		case 74:
		{
			karta2=11;
			break;
		}
		case 68:
		{
			karta2=10;
			break;
		}
		default:
		{
			karta2=gracz2->Karta[0]-48;
		}
	}
	
	if (karta1>karta2)
	{
		return 1;
	}
	else if (karta2>karta1)
	{
		return 2;
	}
	else
	{
		if (gracz2->IloscKart<3)
		{
			return 1;
		}
		else if (gracz1->IloscKart<3)
		{
			return 2;
		}
		else
		{	
		return wojna(gracz1, gracz2);
		}	
	}
}


void dolacz (Gracz *gracz1, Gracz *gracz2, int zwyciezca)			// dolacza karty ktore byly w grze do talii gracza ktory wygral
{
	char bufor[60]={'#'};
	int i=0;
	if (zwyciezca==1)
	{
		for (i=0; i<2*nrwojny+1; i++)
		{
			gracz1->Karta[gracz1->IloscKart+i]=gracz2->Karta[i];					// przeklada pierwsze karty od gracza ktory przegral na koniec talii gracza ktory wygral
			bufor[i]=gracz1->Karta[i];												// kopiuje pierwsze karty gracza ktory wygral do bufora		
		}
		for (i=0; i<gracz2->IloscKart-2*nrwojny-1; i++)
		{
			gracz2->Karta[i]=gracz2->Karta[2*nrwojny+1+i];							// przesuwa karty gracza ktory przegral na poczatek talii
		}
		gracz2->IloscKart-=2*nrwojny+1;
																					
		for (i=0; i<gracz1->IloscKart; i++)
		{
			gracz1->Karta[i]=gracz1->Karta[2*nrwojny+1+i];							// przesuwa karty gracza ktory wygral na poczatek talii
		}
		for (i=0; i<2*nrwojny+1; i++)
		{
			gracz1->Karta[gracz1->IloscKart+i]=bufor[i];							// dopisuje bufor na koniec talii
		}
		gracz1->IloscKart+=2*nrwojny+1;
	}
	else if (zwyciezca==2)
	{
		for (i=0; i<2*nrwojny+1; i++)
		{
			gracz2->Karta[gracz2->IloscKart+i]=gracz1->Karta[i];
			bufor[i]=gracz2->Karta[i];	
		}
		for (i=0; i<gracz1->IloscKart-2*nrwojny-1; i++)
		{
			gracz1->Karta[i]=gracz1->Karta[2*nrwojny+1+i];
		}
		gracz1->IloscKart-=2*nrwojny+1;
		
		for (i=0; i<gracz2->IloscKart; i++)
		{
			gracz2->Karta[i]=gracz2->Karta[2*nrwojny+1+i];						
		}
		for (i=0; i<2*nrwojny+1; i++)
		{
			gracz2->Karta[gracz2->IloscKart+i]=bufor[i];						
		}
		gracz2->IloscKart+=2*nrwojny+1;
	}
	else
	{
		cout << "\n\nZly zwyciezca!!!\n\n";
	}
}



void zliczanie (Gracz *gracz1, Gracz *gracz2)						// zlicza ilosc waletow, dam, kroli i asow na poczatku
{
	int i=0;
	oneJ=0;
	oneQ=0;
	oneK=0;
	oneA=0;
	twoJ=0;
	twoQ=0;
	twoK=0;
	twoA=0;
	for (i=0; i<26; i++)
	{
		if (gracz1->Karta[i]=='J')
		{
			oneJ++;
		}
		if (gracz2->Karta[i]=='J')
		{
			twoJ++;
		}
		if (gracz1->Karta[i]=='Q')
		{
			oneQ++;
		}
		if (gracz2->Karta[i]=='Q')
		{
			twoQ++;
		}
		if (gracz1->Karta[i]=='K')
		{
			oneK++;
		}
		if (gracz2->Karta[i]=='K')
		{
			twoK++;
		}
		if (gracz1->Karta[i]=='A')
		{
			oneA++;
		}
		if (gracz2->Karta[i]=='A')
		{
			twoA++;
		}
	}
//	cout << "\n\n\tIlosc asow: " << oneA << "\t\t\t\tIlosc asow: " << twoA << endl;
//	cout << "\tIlosc kroli: " << oneK << "\t\t\t\tIlosc kroli: " << twoK << endl;
//	cout << "\tIlosc dam: " << oneQ << "\t\t\t\tIlosc dam: " << twoQ << endl;
//	cout << "\tIlosc waletow: " << oneJ << "\t\t\tIlosc waletow: " << twoJ << endl;
}



void zapisz (string NazwaPliku)
{
	const char *NazwaPlikuChar=NazwaPliku.c_str();					// zmienianie typu ze string na char[], potrzebne do obslugi plikow
	const char *PotasowaneKartyChar=PotasowaneKarty.c_str();
	FILE *ZapisywanieKart=fopen(NazwaPlikuChar, "w");
	fprintf(ZapisywanieKart, PotasowaneKartyChar);	
}



int rozgrywka (Gracz *gracz1, Gracz *gracz2)
{
	gracz1->IloscKart=26;
	gracz2->IloscKart=26;
	string NazwaPliku;
	IloscWojen=0, IloscAsow=0, WojnyAsow=0;								// resetowanie wszystkich globalnych licznikow przed kolejna gra
	Wojny1=0, Wojny2=0, Wojny3=0, Wojny4=0, Wojny5=0;
	IloscRuchow=0, WynikPorownania=0, IloscPrzelaman=-1, przewaga1=0, przewaga2=0, remis=0, PrzewagaPrzedtem=0, PrzewagaTeraz=0, WygranaRundy1=0, WygranaRundy2=0;
	bool kontynuuj=true;
	rozdajKarty(gracz1, gracz2);
//	wypisz(gracz1, gracz2);
	zliczanie(gracz1, gracz2);
//	system("cls");
//	cin >> czekaj;
	while (kontynuuj)
	{
//		wypisz(gracz1, gracz2);
		nrwojny=0;
		WynikPorownania=porownanie(gracz1, gracz2);
		if (WynikPorownania==1)										// porownuje karty i okresla kto wygral runde
		{
			WygranaRundy1++;
			if (nrwojny==1)
			{
				Wojny1++;
				IloscWojen++;
			}
			else if (nrwojny==2)
			{
				Wojny2++;
				IloscWojen++;
			}
			else if (nrwojny==3)
			{
				Wojny3++;
				IloscWojen++;
			}
			else if (nrwojny==4)
			{
				Wojny4++;
				IloscWojen++;		
			}
			else if (nrwojny>4)
			{
				Wojny5++;
				IloscWojen++;		
			}
			if (gracz2->IloscKart>2*nrwojny)						// sprawdzanie czy gracz przegrany ma wystarczajaco duzo kart zeby mu je zabrac
			{
				dolacz(gracz1, gracz2, 1);
			}
			else
			{
				break;												// od razu warunek zakonczenia gry
			}
		}
		else if (WynikPorownania==2)
		{
			WygranaRundy2++;
			
			if (nrwojny==1)
			{
				Wojny1++;
				IloscWojen++;
			}
			else if (nrwojny==2)
			{
				Wojny2++;
				IloscWojen++;			
			}
			else if (nrwojny==3)
			{
				Wojny3++;
				IloscWojen++;		
			}
			else if (nrwojny==4)
			{
				Wojny4++;
				IloscWojen++;		
			}
			else if (nrwojny>4)
			{
				Wojny5++;
				IloscWojen++;		
			}	
			if (gracz1->IloscKart>2*nrwojny)						// sprawdzanie czy gracz przegrany ma wystarczajaco duzo kart zeby mu je zabrac
			{
				dolacz(gracz1, gracz2, 2);
			}
			else
			{					
				break;												// od razu warunek zakonczenia gry
			}
		}
		else
		{
			cout << "\nEee cos sie zepsulo :/" << endl;
		}
		
		IloscRuchow++;
		
		
		
		
		if (gracz1->IloscKart>30)									// warunek na przelamanie
		{
			PrzewagaTeraz=1;
		}
		else if (gracz2->IloscKart>30)
		{
			PrzewagaTeraz=2;
		}	
		if (PrzewagaTeraz!=PrzewagaPrzedtem)					// jezeli gracz majacy przewage sie zmienil, to nastepuje przelamanie
		{
			IloscPrzelaman++;
		}
		PrzewagaPrzedtem=PrzewagaTeraz;							// przygotowuje na nastepna kolejke
		
		
		
		if (gracz1->IloscKart>30)									// warunek dla przewagi gracza1
		{
			przewaga1++;
		}
		else if (gracz2->IloscKart>30)								// warunek dla przewagi gracza2
		{
			przewaga2++;
		}
		else														// w innym wypadku jest "remis"
		{
			remis++;
		}
								
																	// statystyki biezace
																	
		cout << "\r" << BierzacaGra+1 << ":\t";						// numer gry
		cout << IloscRuchow << "\t";
		cout << gracz1->IloscKart << "\t";
		cout << gracz2->IloscKart << "\t";
		cout << przewaga1 << "\t";
		cout << remis << "\t";
		cout << przewaga2 << "\t";
		cout << IloscWojen << "\t";
		cout << WojnyAsow << "\t";
		cout << IloscAsow << "\t";		
		if (IloscPrzelaman!=-1)										// zeby nie bylo "Licznik przelaman: -1"
		{
			cout << IloscPrzelaman;
		}
		else
		{
			cout << "0";
		}														
		
	
//		system("PAUSE");											// czy gra przewija sie na trzymanie klawisza											
//		cin >> kontynuuj;											// czy gra przewija sie krok po kroku po potwierdzeniu (wpisaniu "1")
//		system("cls");												// czysci ekran
	}
	
	
																	// nizej czesc podsumowujaca jesli gra sie skonczyla
	

		cout << "\r" << BierzacaGra+1 << ":\t";		//jeszcze nie	// to samo co zawsze, z tym, ze jest nazwa gracza zamiast kart
		cout << IloscRuchow << "\t";
		cout << gracz1->IloscKart << "\t";
		cout << gracz2->IloscKart << "\t";
		cout << przewaga1 << "\t";
		cout << remis << "\t";
		cout << przewaga2 << "\t";
		cout << IloscWojen << "\t";
		cout << WojnyAsow << "\t";
		cout << IloscAsow << "\t";		
		if (IloscPrzelaman!=-1)									// zeby nie bylo "Licznik przelaman: -1"
		{
			cout << IloscPrzelaman << endl;
		}
		else
		{
			cout << "0\n";
		}
																// nizej zliczanie szans na wygranie z dana iloscia asow
		switch (oneA)												// ile razy przy x asach na poczatku gracz1 wygral
		{
			case 0:
			{
				Ilosc0Asow++;
				if (gracz2->IloscKart<nrwojny*2+1)
				{
					wygrane1++;
					Wygrane0Asow++;
				}
				break;
			}
			case 1:
			{
				Ilosc1Asa++;
				if (gracz2->IloscKart<nrwojny*2+1)
				{
					wygrane1++;
					Wygrane1As++;
				}
				break;
			}
			case 2:
			{
				Ilosc2Asow++;
				if (gracz2->IloscKart<nrwojny*2+1)
				{
					wygrane1++;
					Wygrane2Asy++;
				}
				break;
			}
			case 3:
			{
				Ilosc3Asow++;
				if (gracz2->IloscKart<nrwojny*2+1)
				{
					wygrane1++;
					Wygrane3Asy++;
				}
				break;
			}
			case 4:
			{
				Ilosc4Asow++;
				if (gracz2->IloscKart<nrwojny*2+1)
				{
					wygrane1++;
					Wygrane4Asy++;
				}
				break;
			}
			default:
			{
				cout << "\nZLE ASY\n";
				break;
			}
		}
		switch (twoA)												// ile razy przy x asach na poczatku gracz1 wygral
		{
			case 0:
			{
				Ilosc0Asow++;
				if (gracz1->IloscKart<nrwojny*2+1)
				{
					wygrane2++;
					Wygrane0Asow++;
				}
				break;
			}
			case 1:
			{
				Ilosc1Asa++;
				if (gracz1->IloscKart<nrwojny*2+1)
				{
					wygrane2++;
					Wygrane1As++;
				}
				break;
			}
			case 2:
			{
				Ilosc2Asow++;
				if (gracz1->IloscKart<nrwojny*2+1)
				{
					wygrane2++;
					Wygrane2Asy++;
				}
				break;
			}
			case 3:
			{
				Ilosc3Asow++;
				if (gracz1->IloscKart<nrwojny*2+1)
				{
					wygrane2++;
					Wygrane3Asy++;
				}
				break;
			}
			case 4:
			{
				Ilosc4Asow++;
				if (gracz1->IloscKart<nrwojny*2+1)
				{
					wygrane2++;
					Wygrane4Asy++;
				}
				break;
			}
			default:
			{
				cout << "\nZLE ASY\n";
				break;
			}
		}
		
		SumaKolejek+=IloscRuchow;
		SumaWojen+=IloscWojen;
		SumaWojen1+=Wojny1;
		SumaWojen2+=Wojny2;
		SumaWojen3+=Wojny3;
		SumaWojen4+=Wojny4;
		SumaWojen5+=Wojny5;
		SumaPrzelaman+=IloscPrzelaman;
		SumaAsow+=IloscAsow;
		SumaWojenAsow+=WojnyAsow;
																// sprawdzanie ekstremow i zapisywanie do plikow
		if (IloscRuchow>MaxRuchow)
		{
			zapisz("MaxRuchow.txt");
			MaxRuchow=IloscRuchow;
		}
		if (IloscRuchow<MinRuchow)
		{
			zapisz("MinRuchow.txt");
			MinRuchow=IloscRuchow;
		}
		if (Wojny5>0)
		{
			zapisz("Wojny5.txt");
		}
															
		return 0;
}



int main()
{
	srand(time(NULL));
	Gracz gracz1, gracz2;
	cin >> IloscGier;
	cout << "Nr gry\tRuchy\tKarty1\tKarty2\tP1\tRemis\tP2\tWojny\tWasow\tAsy\tPrzel" << endl;
	for (BierzacaGra=0; BierzacaGra<IloscGier; BierzacaGra++)
	{
		rozgrywka(&gracz1, &gracz2);
	}
	cout << "\n\n\nKoncowe statystyki:";
	cout.precision(5);
	cout << endl << endl << "Gracz1 wygral " << wygrane1 << " razy, Gracz2 wygral " << wygrane2 << " razy.\n\n";
	cout << "\t\tw sumie\t\tna 1 gre\tco ile gier\tco ile kolejek" << endl;
	cout << "Kolejki\t\t" << SumaKolejek << "\t\t" << (float)SumaKolejek/IloscGier << endl;
	cout << "Wojny\t\t" << SumaWojen << "\t\t" << (float)SumaWojen/IloscGier  << "\t\t\t\t" << (float)SumaKolejek/SumaWojen << endl;
	cout << "1x Wojny\t" << SumaWojen1 << "\t\t" << (float)SumaWojen1/IloscGier  << "\t\t\t\t" << (float)SumaKolejek/SumaWojen1 << endl;
	cout << "2x Wojny\t" << SumaWojen2 << "\t\t" << (float)SumaWojen2/IloscGier  << "\t\t" << (float)IloscGier/SumaWojen2 << "\t\t" << (float)SumaKolejek/SumaWojen2 << endl;
	cout << "3x Wojny\t" << SumaWojen3 << "\t\t" << (float)SumaWojen3/IloscGier  << "\t\t" << (float)IloscGier/SumaWojen3 << "\t\t" << (float)SumaKolejek/SumaWojen3 << endl;
	cout << "4x Wojny\t" << SumaWojen4 << "\t\t" << (float)SumaWojen4/IloscGier  << "\t\t" << (float)IloscGier/SumaWojen4 << "\t\t" << (float)SumaKolejek/SumaWojen4 << endl;
	cout << "(5+)x Wojny\t" << SumaWojen5 << "\t\t" << (float)SumaWojen5/IloscGier  << "\t\t" << (float)IloscGier/SumaWojen5 << "\t\t" << (float)SumaKolejek/SumaWojen5 << endl;
	cout << "Asy w wojnie\t" << SumaAsow << "\t\t" << (float)SumaAsow/IloscGier << "\t\t" << (float)IloscGier/SumaAsow << "\t\t" << (float)SumaKolejek/SumaAsow << endl;
	cout << "Wojny asow\t" << SumaWojenAsow << "\t\t" << (float)SumaWojenAsow/IloscGier << "\t\t" << (float)IloscGier/SumaWojenAsow << "\t\t" << (float)SumaKolejek/SumaWojenAsow << endl;
	cout << "Przelamania\t" << SumaPrzelaman << "\t\t" << (float)SumaPrzelaman/IloscGier  << "\t\t\t\t" << (float)SumaKolejek/SumaPrzelaman << endl << endl;
	
	cout << "Max Kolejek: " << MaxRuchow << "\tMin Kolejek: " << MinRuchow << endl;
	
	cout << "Szanse na wygranie z 0 asami: " << (float)Wygrane0Asow*100/Ilosc0Asow << "%\n";
	cout << "Szanse na wygranie z 1 asem: " << (float)Wygrane1As*100/Ilosc1Asa << "%\n";
	cout << "Szanse na wygranie z 2 asami: " << (float)Wygrane2Asy*100/Ilosc2Asow << "%\n";
	cout << "Szanse na wygranie z 3 asami: " << (float)Wygrane3Asy*100/Ilosc3Asow << "%\n";
	cout << "Szanse na wygranie z 4 asami: " << (float)Wygrane4Asy*100/Ilosc4Asow << "%\n";
	
//	system ("PAUSE");
	return 0;
}
