#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::cin;
using std::vector;
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
  vector <int> paz;
  int egzas;
  float galut;
};
bool vardInfo(string skai);
string vardIrasymas(string irasymas);
bool skaiInfo(string pazym);
bool skInfo(string pazym);
int skIrasymas(string irasymas, bool);
int suma(vector <int> paz);
float vidurkis(vector <int> paz);
float mediana(vector <int> paz);
float galutinis(float, int egzas);
int atsitiktiniai();
int pavardTvarka(vector <irasas> Stud);
int vardTvarka(vector <irasas> Stud);
void spausdinimas(vector <irasas> Stud);
void papildoma(vector <irasas> &Stud);
bool patvirtinimas();

int main() 
{
  vector <irasas> Stud;
  srand(time(0));
  papildoma(Stud);
  spausdinimas(Stud);
  Stud.clear();
}
void papildoma(vector <irasas> &Stud)
{
  irasas St;

  do
  {
    St.vardas = vardIrasymas("Varda");
    St.pavarde = vardIrasymas("Pavarde");
    cout <<"Ar norite patys irasyti, jei ne bus sugeneruoti? (iveskite + jei norite, - jei ne) ";
    if(patvirtinimas())
    {
      cout <<"Norite irasyti kiek pazymiu bus? (iveskite + jei norite, - jei ne) ";
      if(patvirtinimas())
      {
        int n = skIrasymas(" kiek pazymiu", false);
        for(int j = 0; j < n; j++)
          {
            St.paz.push_back(skIrasymas("pazymi", true));              
          }           
      }
      else
      {
        do
        {
          St.paz.push_back(skIrasymas("pazymi", true));
          cout << "Ar vesite dar pazymi? (iveskite + jei norite, - jei ne) ";              
        } while(patvirtinimas());          
      }
    }
    else
    { 
      int n = skIrasymas("kiek pazymiu", false);
      for (int j = 0; j <n; j++) St.paz.push_back(atsitiktiniai());
      cout << "Sugeneruoti: ";
      for (int j = 0; j < n-1; j++) cout <<St.paz[j] <<",";
      cout << St.paz[n-1] << "." << endl;         
    }
    cout << "Egzamino bala suvesite patys, jei ne bus sugeneruotas? (iveskite + jei norite, - jei ne) ";
    if(patvirtinimas())
    {
      St.egzas = skIrasymas("egzamino pazymi", true);          
    }
    else
    {
      St.egzas = atsitiktiniai ();
      cout << "Sugeneruotas egzamino balas: " <<St.egzas << endl;
    }
    St.galut = 0;
    Stud.push_back(St);
    St.paz.clear();
    cout <<"Ar vesie dar studento duomenu? (iveskite + jei norite, - jei ne) ";
        
  } while(patvirtinimas());
  cout << "Ar norite skaiciuoti vidurki, jei ne bus suskaiciuota mediana? (iveskite + jei norite, - jei ne) ";
  if(patvirtinimas())
  {
    for(int j = 0; j < Stud.size(); j++)
    {
      Stud[j].galut = galutinis(vidurkis(Stud[j].paz), Stud[j].egzas);
    }
  }
  else
  {
    for(int j = 0; j < Stud.size(); j++)
    {
      Stud[j].galut = galutinis(mediana(Stud[j].paz),Stud[j].egzas);
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
      cout << "Irasykite dar karta ";
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
      cout << "Neturi buti skaiciu " << endl;
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
      cout << "turi buti daugiau uz 0 "<<endl;
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
      cout <<"Turi buti tik skaiciai " <<endl;
      break;
    }
    else if (teisingas == true && (stoi(pazym)<1 || stoi(pazym) >10))
    {
      teisingas = false;
      cout << "skaicius turi buti nuo 1 iki 10 " << endl;          
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
int suma(vector <int> paz)
{
  return accumulate(paz.begin(), paz.end(), 0);
}
float vidurkis(vector <int> paz)
{
  int n = paz.size();
  float vid = suma(paz) / n;
  return vid;
}
float mediana(vector <int> paz)
{
  float median;
  int n = paz.size();
    
  sort(paz.begin(), paz.end());
    
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
int pavardTvark(vector <irasas> Stud)
{
  int max = 0;
  int t = Stud.size();
  for(int i = 0; i < t; i++)
  {
    if(Stud[i].pavarde.length() > max)
    max = Stud[i].pavarde.length(); 
  }
  return max;
}
int vardTvark(vector<irasas> Stud)
{
  int max = 0;
  int t = Stud.size();
  for(int i = 0; i < t; i++)
  {
    if(Stud[i].vardas.length() > max)
    max = Stud[i].vardas.length();
  }
  return max;
}
void spausdinimas(vector <irasas> Stud)
{
  int t = Stud.size();
  string pnktr = "";
  int maxvardas = vardTvark(Stud);
  int maxpavarde = pavardTvark(Stud);
  pnktr.append(maxpavarde + maxvardas + 50, '-');
  cout << left << setw(maxvardas + 15) << "Vardas" << setw(maxpavarde + 15) << "Pavarde" << " Galutinis balas" << endl;
  cout << pnktr << endl;
  for(int i = 0; i < t; i++)
  {
    cout << left << setw(maxvardas + 15) << Stud[i].vardas << setw(maxpavarde + 15) << Stud[i].pavarde << fixed << setprecision(2) << Stud[i].galut <<endl;        
  }
}
