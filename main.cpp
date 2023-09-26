#include <iostream>
#include <string>
#include <limits>

int main() {
    std::string vardas, pavarde;
    int n;
    double nd, egz, rez;
    double vid;
    double suma = 0;

    std::cout << "Įrašyk namų darbų kiekį: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Netinkamas įrašas. Įveskite skaičių kuris priklauso intervalui [0;10]: ";
    }

    int i = 1;
    while (i <= n) {
        std::cout << "Įrašyk " << i << " namų darbų rezultatą: ";


        if (std::cin >> nd) {
            if (nd >= 0 && nd <= 10) {
                suma += nd;
                i++;
            } else {
                std::cout << "Netinkamas įrašas. Rezultatas turi būti tarp 0 ir 10." << std::endl;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Netinkamas įrašas. Bandyk dar kartą." << std::endl;
        }
    }

    
    std::cout << "Įrašyk egzamino rezultatą: ";
    while (!(std::cin >> egz) || egz < 0 || egz > 10) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Netinkamas įrašas. Rezultatas turi būti tarp 0 ir 10. Bandyk dar kartą: ";
    }

    vid = suma / n;
    rez = 0.4 * vid + 0.6 * egz;
    std::cout << "Galutinis rezultatas: " << rez << std::endl;

    return 0;
}

