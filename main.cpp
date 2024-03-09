#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cstdlib>

class Carte{
private:
    int valoareCarte;
    std::string culoareCarte;

public:
    // constructor initializare carte
    Carte(int valoareCarte, const std::string &culoareCarte) : valoareCarte{valoareCarte}, culoareCarte{culoareCarte} {
//        std::cout<<"Initializare carte"<<std::endl;
    }

    std::string getCuloareCarte() const {return culoareCarte;}
    int getValoareCarte() const {return valoareCarte;}
    friend std::ostream& operator<<(std::ostream& os, const Carte& carte);
};

std::ostream& operator<<(std::ostream& os, const Carte& carte){
    os << carte.valoareCarte<<" de "<<carte.culoareCarte<<"\n";
    return os;
};


class Dealer{
private:
    std::vector<Carte> pachet;  // pachetul de carti
    std::vector<int> masa;  // cartile care sunt pe masa
    int cartiPachet;  // numarul de carti din pachet - initial 32

    void afisareUltimaCarte(){
        std::cout<<masa[masa.size()-1];
    };

    int numarPuncteRand(int nrPuncte = 0){  // numara numarul de puncte din randul respectiv
        if(masa[masa.size()-1] == 10 || masa[masa.size()-1] == 11){
            nrPuncte++;
        }
        return nrPuncte;
    }
    int randomIndexGenerator(){
        int randomIndex, max = pachet.size();
        srand(time(0));
        randomIndex = (rand() % max) + 1;
        return randomIndex;
    }

public:
    Dealer(std::vector<Carte> pachet_, int cartiPachet_): pachet{pachet_}, cartiPachet{cartiPachet_}{  // constr initializare
        std::cout<<"Pachetul a fost initializat cu succes!"<<std::endl;
    }
    Dealer(const Dealer& other): pachet{other.pachet}, masa{other.masa}, cartiPachet{other.cartiPachet}{
        std::cout<<"Constructor de copiere pentru Dealer"<<std::endl;  // util pentru functia de restart
    }
    Dealer& operator=(const Dealer& other){  // operator= de copiere
        pachet = other.pachet;
        masa = other.masa;
        cartiPachet = other.cartiPachet;
        std::cout<<"operator= copiere Dealer"<<std::endl;
        return *this;
    }
    // functii geter
    std::vector<Carte> get_pachet() {return pachet;}
    int get_cartiPachet() {return cartiPachet;}



};

class Jucator{
private:
    std::vector<Carte> manaJucator;  // cartile din mana jucatorului
    int nrCartiJucator;  // - numarul de carti - maxim 4, minim 0
    bool aInceputRandul; // decide daca jucatorul are sau nu prima mutare


    void joacaCarte(int indice){
        // masa.push_back(manaJucator[indice]);
    };

    void endTurn(){
        // daca jucatorul a inceput randul si nu mai vrea sa il continue, il poate termina
    };

public:
    Jucator(std::vector<Carte> manaJucator_, int nrCartiJucator_, bool aInceputRandul_): manaJucator{manaJucator_}, nrCartiJucator{nrCartiJucator_}, aInceputRandul{aInceputRandul_}{
        std::cout<<"Ai primit 4 carti"<<std::endl; // constr initializare

    }
    Jucator(const Jucator& other): manaJucator{other.manaJucator}, nrCartiJucator{other.nrCartiJucator}, aInceputRandul{other.aInceputRandul}{
        std::cout<<"Constructor de copiere pentru Jucator"<<std::endl; // util pentru functia de restart cu acelasi pachet
    }
    ~Jucator(){ // destructor
        std::cout<<"Destructor Jucator"<<std::endl;
    }
    // functii getter
    std::vector<Carte> get_manaJucator(){return manaJucator;}
    int get_cartiJucator(){return nrCartiJucator;}
    bool get_aInceputRandul(){return aInceputRandul;}

};

class Bot{
private:
    std::vector<Carte> manaBot; // cartile folosite de bot
    int nrCartiBot; // numarul de carti din mana bot-ului
    bool aInceputRandul; // decide daca botul a avut sau nu prima mutare (opusul variabilei din Jucator)
    void atac(int ultimaCarte){
        // daca bot-ul are in pachet ultima carte de pe masa, o va folosi pentru a continua randul
    };
    void taiere(int nrPuncte, int ultimaCarte){
        // daca bot-ul nu are in pachet ultima carte de pe masa, in randul respectiv a fost folosit cel putin un punct, iar bot-ul are in pachet o carte de 7
        // atunci o va folosi pentru a continua randul
    };
public:
    Bot(std::vector<Carte> manaBot_, int nrCartiBot_, bool aInceputRandul_): manaBot{manaBot_}, nrCartiBot{nrCartiBot_}, aInceputRandul{aInceputRandul_}{
        std::cout<<"Initializare Bot"<<std::endl;  // initializare
    }
    // functii getter
    std::vector<Carte> get_manaBot(){return manaBot;}
    int get_cartiBot(){return nrCartiBot;}
    bool get_aInceputRandulBot(){return aInceputRandul;}
};


int main(){
    std::vector<Carte> pachetC;

    // init Carte
    std::vector<std::string> culori = {"trefla", "romb", "inima rosie", "inima neagra"};
    for(int i = 7; i<= 14; i++){
        for(std::string culoare : culori){
            Carte carte = {i,culoare};
            pachetC.push_back(carte);
        }
    }

    // init Dealer
    Dealer pachetInitial{pachetC,32};

    // operator= de copiere
    Dealer copiePachet = pachetInitial;
    std::cout<<std::endl;


    // afisare carti din pachet
    std::cout<<"Pachetul contine urmatoarele carti"<<std::endl;
    for(Carte carte : pachetInitial.get_pachet()){
        std::cout<<carte;
    }
    std::cout<<std::endl;

    // init Jucator
    std::vector<Carte> mana;
    bool inceputRandJucator = true;

    std::vector<Carte> pachet = pachetInitial.get_pachet();
    // alocare carti pentru jucator
    for(int i = 0; i < 4; i++){
        int ceva_random = 5;  // se va defini o functie care alege un numar random, 5 este placeholder
        mana.push_back(pachet[ceva_random]);
        pachet.erase(pachet.begin() + ceva_random);
    }

    Jucator manaInitialaJucator{mana,4,inceputRandJucator};

    // afisare carti din mana jucatorului
    if(manaInitialaJucator.get_aInceputRandul()){
        std::cout<<"Pachetul tau contine: "<<std::endl;
        for(Carte carte : manaInitialaJucator.get_manaJucator()){
            std::cout<<carte;
        }
    }
    std::cout<<std::endl;


    // init Bot
    std::vector<Carte> manaB;
    bool inceputRandBot = !inceputRandJucator;

    // alocare carti pentru bot
    for(int i = 0; i < 4; i++){
        int ceva_random = 7;  // se va defini o functie care alege un numar random, 5 este placeholder
        manaB.push_back(pachet[ceva_random]);
        pachet.erase(pachet.begin() + ceva_random);
    }

    Bot manaInitialaBot{manaB,4,inceputRandBot};

    // afisare mana bot, nu va ramane in codul final
    std::cout<<"Pachetul bot-ului contine:"<<std::endl;
    for(Carte carte : manaInitialaBot.get_manaBot()){
        std::cout<<carte;
    }

    std::cout<<std::endl<<"In pachet au ramas urmatoarele carti:"<<std::endl;
    // afisare carti ramase dupa alocare, nu va ramane in codul final
    for(Carte carte : pachet){
        std::cout<<carte;
    }

    std::cout<<std::endl;

    // copiere mana initiala
    Jucator manaInitialaJucatorCopie(manaInitialaJucator);

    // afisare pachet initial
    std::cout<<"Pachetul tau initial continea:"<<std::endl;
    for(Carte carte : manaInitialaJucatorCopie.get_manaJucator()){
        std::cout<<carte;
    }

    std::cout<<std::endl;

    return 0;
}
