#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <fstream>

using namespace std;

class Interfata{
public:
    virtual istream& citire(istream&) = 0;
    virtual ostream& afisare(ostream&) const =0;
};
class Carte:public Interfata {
protected:
    string titlu;
    string autor;
    string editura;
    int anPublicare;
public:

    Carte();
    Carte& operator =(const Carte&);
    Carte(string,string,string,int);
    Carte(const Carte&);
    friend istream& operator >> (istream&,Carte&);
    friend ostream& operator << (ostream&,const Carte&);
    istream& citire(istream& in){
    cout<<"Introduceti titlu:";
    in >> this->titlu;
    cout<<"Introduceti autor:";
    in >> this->autor;
    cout<<"Introduceti editura:";
    in >> this->editura;
    cout<<"Anul publicarii:";
    in >> this->anPublicare;

    }


    ostream& afisare(ostream& os) const{
    os<<"Titlu"<< this->titlu<<endl;
    os<<"Autor"<< this->autor<<endl;
    os<<"Editura:" <<this->editura<<endl;
    os<<"An Pub:" <<this->anPublicare<<endl;

    }



    virtual ~Carte() {} // Destructor
    virtual void importData(const string& fileName) = 0;
    virtual void exportData(const string& fileName) = 0;
    virtual void afisareCarte() = 0;
    string getTitlu() const { return titlu; }


    int getAnPublicare() const {
        return anPublicare;
    }
   void setAnPublicare(int an) {
        if (getAnPublicare() > 2023 || getAnPublicare() < 1400) {
            throw std::out_of_range("Anul publicarii nu este valid");
        }
        anPublicare = an;
    }




};
Carte::Carte(){
    this->titlu='Privat';
    this->autor='Anonim';
    this->editura='Anonim';
    this->anPublicare=0;

}

Carte::Carte(string titlu,string autor,string editura,int anPublicare){
    this->titlu=titlu;
    this->autor=autor;
    this->editura=editura;
    this->anPublicare=anPublicare;
}
Carte::Carte(const Carte& obj){
    this->titlu=obj.titlu;
    this->autor=obj.autor;
    this->editura=obj.editura;
    this->anPublicare=obj.anPublicare;
}


Carte& Carte::operator=(const Carte& obj){
  if(this != &obj){
    this->titlu=obj.titlu;
    this->autor=obj.autor;
    this->editura=obj.editura;
    this->anPublicare=obj.anPublicare;
    }
    return *this;
}


istream& operator >>(istream& in,Carte& obj){
return obj.citire(in);

}


ostream& operator<<(ostream& os,const Carte& obj){
return obj.afisare(os);

}


class Autor : public Carte {
private:
    string numeAutor;
    vector<string> cartiPublicate;
public:
    Autor();
    Autor(const string& titlu, const string& autor, const string& editura, int anPublicare,
          const string& numeAutor, const vector<string>& cartiPublicate);
    Autor(const Autor& other);
    Autor& operator=(const Autor& other);
    istream& citire(istream& in) override;
    ostream& afisare(ostream& os) const override;
    virtual ~Autor() {}

    void importData(const string& fileName) override {
        // Implementare importData pentru clasa Autor
        cout << "Importing data for Autor: " << getTitlu() << endl;
    }

    void exportData(const string& fileName) override {
        // Implementare exportData pentru clasa Autor
        cout << "Exporting data for Autor: " << getTitlu() << endl;
    }

    void afisareCarte() override {
        // Implementare afisareCarte pentru clasa Autor
        cout << "Afisare carte pentru Autor: " << getTitlu() << endl;
    }
};

Autor::Autor() : Carte(), numeAutor("Necunoscut") {}

Autor::Autor(const string& titlu, const string& autor, const string& editura, int anPublicare,
             const string& numeAutor, const vector<string>& cartiPublicate)
    : Carte(titlu, autor, editura, anPublicare), numeAutor(numeAutor), cartiPublicate(cartiPublicate) {}



Autor::Autor(const Autor& other)
    : Carte(other), numeAutor(other.numeAutor), cartiPublicate(other.cartiPublicate) {}

Autor& Autor::operator=(const Autor& other) {
    if (this != &other) {
        Carte::operator=(other);
        numeAutor = other.numeAutor;
        cartiPublicate = other.cartiPublicate;
    }
    return *this;
}

istream& Autor::citire(istream& in) {
    Carte::citire(in);

    cout << "Introduceti numele autorului: ";
    in >> numeAutor;

    cout << "Introduceti numarul de carti publicate: ";
    int numarCarti;
    in >> numarCarti;

    cout << "Introduceti denumirile cartilor publicate: ";
    cartiPublicate.clear();
    for (int i = 0; i < numarCarti; ++i) {
        string denumireCarte;
        in >> denumireCarte;
        cartiPublicate.push_back(denumireCarte);
    }

    return in;
}

ostream& Autor::afisare(ostream& os) const {
    Carte::afisare(os);

    os << "Nume autor: " << numeAutor << endl;

    os << "Carti publicate: ";
    for (const string& denumireCarte : cartiPublicate) {
        os << denumireCarte << ", ";
    }
    os << endl;

    return os;
}


// Clasa Cititor mosteneste Autor
class Cititor : public Autor {
private:
    map<string, bool> cartiImprumutate;
public:
    Cititor();
    Cititor(const string& numeAutor, const vector<string>& cartiPublicate, const map<string, bool>& cartiImprumutate);
    Cititor(const Cititor& other);
    Cititor& operator=(const Cititor& other);
    istream& citire(istream& in) override;
    ostream& afisare(ostream& os) const override;
    virtual ~Cititor() {}

    virtual void importData(const string& fileName) = 0;
    virtual void exportData(const string& fileName) = 0;
    virtual void afisareCarte() = 0;
};

Cititor::Cititor() {}

Cititor::Cititor(const string& numeAutor, const vector<string>& cartiPublicate, const map<string, bool>& cartiImprumutate)
    : Autor("", "", "", 0, numeAutor, cartiPublicate), cartiImprumutate(cartiImprumutate) {}


Cititor::Cititor(const Cititor& other) : Autor(other), cartiImprumutate(other.cartiImprumutate) {}

Cititor& Cititor::operator=(const Cititor& other) {
    if (this != &other) {
        Autor::operator=(other);
        cartiImprumutate = other.cartiImprumutate;
    }
    return *this;
}

istream& Cititor::citire(istream& in) {
    Autor::citire(in);

    cout << "Introduceti numarul de carti imprumutate: ";
    int numarCarti;
    in >> numarCarti;

    cout << "Introduceti denumirile cartilor imprumutate si starea lor (0 pentru disponibile, 1 pentru imprumutate): " << endl;
    cartiImprumutate.clear();
    for (int i = 0; i < numarCarti; ++i) {
        string denumireCarte;
        bool imprumutata;
        in >> denumireCarte >> imprumutata;
        cartiImprumutate[denumireCarte] = imprumutata;
    }

    return in;
}

ostream& Cititor::afisare(ostream& os) const {
    Autor::afisare(os);

    os << "Carti imprumutate: " << endl;
    for (const auto& pair : cartiImprumutate) {
        os << "Denumire: " << pair.first << ", Stare: " << (pair.second ? "Imprumutata" : "Disponibila") << endl;
    }

    return os;
}

istream& operator>>(istream& in, Cititor& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& os, const Cititor& obj) {
    return obj.afisare(os);
}


// Singleton pentru meniul aplicatiei
// Singleton pentru meniul aplicatiei
class Meniu {
private:
    static Meniu* instance;
    map<string, Carte*> biblioteca; // Pentru a stoca cartile din biblioteca

    Meniu() {}; // Constructor privat pentru a preveni crearea mai multor instante
public:
    static Meniu* getInstance();
    void displayMenu();
    void addBook();
    void displayBooks();
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);



};


Meniu* Meniu::getInstance() {
    if (instance == nullptr) {
        instance = new Meniu();
    }
    return instance;
}



void Meniu::displayMenu() {
    int option;
cin >> option;
if (option < 1 || option > 5) throw invalid_argument("Invalid option. Please try again.");

    do {
        cout << "1. Add book\n2. Display books\n3. Save to file\n4. Load from file\n5. Quit\n";
        cout << "Please choose an option: ";
        cin >> option;

        switch(option) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                saveToFile("books.txt");
                break;
            case 4:
                loadFromFile("books.txt");
                break;
            case 5:
                cout << "Quitting program...\n";
                return; // Adăugăm instrucțiunea 'return' pentru a ieși din funcție și a opri programul
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (true); // Modificăm condiția buclei astfel încât să ruleze în mod continuu până la selectarea opțiunii "Quit"
}


void Meniu::addBook() {
    string titlu;
    cout << "Enter book title: ";
    cin >> titlu;
    if (biblioteca.find(titlu) != biblioteca.end()) {
        throw std::runtime_error("Cartea exista deja in biblioteca");
    }

    biblioteca[titlu] = new Autor();
    biblioteca[titlu]->citire(cin);
}


void Meniu::displayBooks() {
    for (const auto& pereche : biblioteca) {
        pereche.second->afisareCarte();
    }
}

void Meniu::saveToFile(const string& filename) {
    ofstream out(filename);
    for (const auto& pereche : biblioteca) {
        out << pereche.first << "\n"; // Scriem doar titlul, completeaza cu restul informatiilor
    }
    out.close();
}

void Meniu::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    string titlu;
    while (getline(in, titlu)) {
        biblioteca[titlu] = new Autor();
        biblioteca[titlu]->citire(cin);
    }
    in.close();
}



// Instantierea pointerului static
Meniu* Meniu::instance = nullptr;

void testMemoryAllocation() {
    try {
        int* myArray = new int[1000000000];  // O cantitate mare de memorie
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
    }
}




int main() {
    try {
        Meniu* meniu = Meniu::getInstance();
        meniu->displayMenu();
    } catch (const exception& e) {
        cerr << "A aparut o exceptie: " << e.what() << '\n';
    }
    testMemoryAllocation();



    return 0;
}

