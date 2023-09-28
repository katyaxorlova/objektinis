#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <numeric>
#include <stdio.h>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::stoi;
using std::setw;
using std::fixed;
using std::sort;
using std::left;
using std::setprecision;

struct irasas
{
    string vardas;
    string pavarde;
    int paz[100];
    int egzas;
    float galut;
    int n;

};
void papildoma(irasas Stud[], int &st);
bool patvirtinimas();
bool vardInfo(string skai);
string vardIrasymas(string irasymas);
bool skaiInfo(string pazym);
bool skInfo(string pazym);
int skIrasymas(string irasymas, bool);
int suma(int paz[], int n);
float vidurkis(int paz[], int n);
float mediana(int paz[], int n);
float galutinis(float, int egzas);
int atsitiktiniai();
int pavardTvark(irasas Stud[], int st);
int vardTvark(irasas Stud[], int st);
void papildoma(irasas Stud[], int &st);
void spausdinimas(irasas Stud[], int st);

int main() 
{
    irasas Stud[100];
    int st;
    srand(time(0));
    papildoma(Stud, st);
    spausdinimas(Stud, st);
  
}
void papildoma(irasas Stud[], int &st)
{
    int n;
    do
    {
        Stud[st].vardas = vardIrasymas("Varda");
        Stud[st].pavarde = vardIrasymas("Pavarde");
        cout <<"Ar norite patys irasyti, jei ne bus sugeneruoti? (iveskite + jei norite, - jei ne) ";
        if(patvirtinimas())
        {
            cout <<"Norite irasyti kiek pazymiu bus? (iveskite + jei norite, - jei ne) ";
            if(patvirtinimas())
            {
                int n = skIrasymas(" kiek pazymiu", false);
                for(int j = 0; j < n; j++)
                    {
                        Stud[st].paz[j] = skIrasymas("pazymi", true);             
                    }
            }
            else
            {
                n = 0;
                do
                {
                    Stud[st].paz[n] = skIrasymas("pazymi", true);
                    cout << "Ar vesite dar pazymi? (iveskite + jei norite, - jei ne) ";
                    n++;
                } while(patvirtinimas());
            }
        }
        else
        {
            n = skIrasymas("kiek pazymiu", false);
            for (int j = 0; j <n; j++)  Stud[st].paz[j] =atsitiktiniai();
            cout << "Sugeneruoti: ";
            for (int j = 0; j < n-1; j++) cout << Stud[st].paz[j] <<",";
            cout <<  Stud[st].paz[n-1] << "." << endl;                  
        }
        cout << "Egzamino bala suvesite patys, jei ne bus sugeneruotas? (iveskite + jei norite, - jei ne) ";
        if(patvirtinimas())
        {
            Stud[st].egzas = skIrasymas("egzamino pazymi", true);         
        }
        else
        {
            Stud[st].egzas = atsitiktiniai ();
            cout << "Sugeneruotas egzamino balas: " <<Stud[st].egzas << endl;
        }
        Stud[st].galut = 0;
        Stud[st].n = n;
        cout <<"Ar vesite kito studento duomenis? (iveskite + jei norite, - jei ne) ";
        st++;
    } while(patvirtinimas());
    cout << "Ar norite skaiciuoti vidurki, jei ne bus suskaiciuota mediana? (iveskite + jei norite, - jei ne) ";
    if(patvirtinimas())
    {
        for(int j = 0; j < st; j++)
        {
            Stud[j].galut = galutinis(vidurkis(Stud[j].paz, Stud[j].n),Stud[j].egzas);           
        }
    }
    else
    {
        for(int j = 0; j < st; j++)
        {
            Stud[j].galut = galutinis(mediana(Stud[j].paz, Stud[j].n),Stud[j].egzas);
        }
    }  
} 
bool patvirtinimas()
{
    bool tiesa = true;
    bool pazym = true;
    string tn;
    
    do
    {
        cin >> tn;
        if(tn.length() == 1 && (tolower(tn[0]) =='+' || tolower(tn[0]) == '-'))
        { 
            pazym = true;
            if(tolower(tn[0]) =='+')
            tiesa = true;
            else tiesa = false;
        }
        else
        {
            cout << "Kazkas negerai, irasykite dar karta";
            pazym = false;
        }       
    } while (!pazym);
    return tiesa;   
}
bool vardInfo(string skai)
{
    bool teisingas = true;
    for (int i = 0; i< skai.length(); i++)
    {
        if (isalpha(skai[i]) == false)
        {
            teisingas = false;
            cout << "Neturi buti skaiciu" << endl;
            break;
        }
        else teisingas = true;        
    }
    return teisingas;   
}
string vardIrasymas(string irasymas)
{
    string skai;
    do
    {
        cout <<"Iveskite studento " <<irasymas << ":";
        cin >> skai;   
    } while (!vardInfo(skai));
    return skai;        
}
bool skaiInfo(string pazym)
{
    bool teisingas = true;
    for (int i = 0; i < pazym.length(); i++)
    {
        if (!isdigit(pazym[i]) || stoi(pazym) == 0 )
        {
            teisingas = false;
            cout << "turi buti daugiau uz 0"<<endl;
            break;
            }
    }
    return teisingas;
}
    bool skInfo(string pazym)
{
    bool teisingas = true;
    for (int i = 0; i < pazym.length(); i++)
    {
        if (!isdigit(pazym[i]))
        {
            teisingas = false;
            cout <<"Turi buti tik skaiciai" <<endl;
            break;
        }
        else if (teisingas == true && (stoi(pazym)<1 || stoi(pazym) >10))
        {
            teisingas = false;
            cout << "skaicius turi buti nuo 1 iki 10" << endl;
        }
    }
    return teisingas;    
}
int skIrasymas(string irasymas, bool negalut)
{
    string skai;
    bool pazym;
    do
    {
        cout << "Irasykite " << irasymas << ":";
        cin >> skai;
        if(negalut)pazym = skInfo(skai);
        else pazym = skaiInfo(skai);
    
    } while (!pazym);
    int skaicius = stoi(skai);
    return skaicius;
}
int suma(int paz[], int n)
{
    int sum = 0;
    for (int i = 0; i <n; i ++)
    {
        sum += paz[i];
    }
    return sum;
}
float vidurkis(int paz[], int n)
{
    float vid = suma(paz, n) / n;
    return vid;
}
float mediana(int paz[], int n)
{
    float median;
    sort(paz, paz + n);
    
    if(n / 2 == 0)
    median = (paz[n/2] + paz[n/2 +1])/2;
    else
    median = paz[n/2];
    return median;  
}
float galutinis(float sum, int egzas)
{
    float galut = float(0.4 * sum ) + 0.6 * egzas;
    return galut;
}
int atsitiktiniai()
{
    int p;
    p = 1 +rand()% ((10+1)-1);
    return p;   
}
int pavardTvark(irasas Stud[], int st)
{
    int max = 0;
    for(int i = 0; i < st; i++)
    {
        if(Stud[i].pavarde.length() > max)
        max = Stud[i].pavarde.length();
    }
    return max;   
}
int vardTvark(irasas Stud[], int st)
{
    int max = 0;
    for(int i = 0; i < st; i++)
    {
        if(Stud[i].vardas.length() > max)
        max = Stud[i].vardas.length();        
    }
    return max;
}
void spausdinimas(irasas Stud[], int st)
{
    string tva = "";
    int maxvardas = vardTvark(Stud, st);
    int maxpavarde = pavardTvark(Stud, st);
    tva.append(maxpavarde + maxvardas + 50, '-');
    cout << left << setw(maxvardas + 15) << "Vardas" << setw(maxpavarde + 15) << "Pavarde" << " Galutinis balas" << endl;
    cout << tva << endl;
    for(int i = 0; i < st; i++)
    {
        cout << left << setw(maxvardas + 15) << Stud[i].vardas << setw(maxpavarde + 15) << Stud[i].pavarde << fixed << setprecision(2) << Stud[i].galut <<endl;
    }
}
        
