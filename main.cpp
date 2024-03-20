#include<iostream>
#include<vector>
#include<string>
#include<random>


class Carte{
private:
    int valoareCarte;
    std::string culoareCarte;

public:
    // constructor initializare carte
    Carte(const int valoareCarte, const std::string &culoareCarte) : valoareCarte{valoareCarte}, culoareCarte{culoareCarte} {
//        std::cout<<"Initializare carte"<<std::endl;
    }
    // functii getter
    // std::string getCuloareCarte() const {return culoareCarte;}
    int getValoareCarte() const {return valoareCarte;}

    // operator << de afisare
    friend std::ostream& operator<<(std::ostream& os, const Carte& carte);

    // metode
    bool isTaietura(Carte& cartePrecedenta){
        if(this->valoareCarte == 7){
            return true;
        }
        if(this->valoareCarte == cartePrecedenta.getValoareCarte() ){
            return true;
        }
        return false;
    }

};

std::string schimbareValoare(int valoare){
    if(valoare == 11){
        return ("A");
    }
    if(valoare == 12){
        return ("J");
    }
    if(valoare == 13){
        return ("Q");
    }
    if(valoare == 14){
        return ("K");
    }
    return std::to_string(valoare);
}

std::ostream& operator<<(std::ostream& os, const Carte& carte){
    os << schimbareValoare(carte.valoareCarte)<<" de "<<carte.culoareCarte<<std::endl;
    return os;
};


class Dealer{
private:
    std::vector<Carte> pachet;  // pachetul de carti
    std::vector<Carte> masa;  // cartile care sunt pe masa
    int cartiPachet;  // numarul de carti din pachet - initial 32



public:
    Dealer(const std::vector<Carte>& pachet_, int cartiPachet_): pachet{pachet_}, cartiPachet{cartiPachet_}{  // constr initializare
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

    ~Dealer(){ // destructor
        std::cout<<"Destructor Dealer"<<std::endl;
    }

    // functii geter
    std::vector<Carte> get_pachet() {return pachet;}
    int get_cartiPachet() {return cartiPachet;}
    std::vector<Carte> get_masa(){return masa;}

    // functii setter
    void setCartiPachet(int cartiPachet_) {
        Dealer::cartiPachet = cartiPachet_;
    }

//    void setPachet(const std::vector<Carte> &pachet_) {
//        Dealer::pachet = pachet_;
//    }

    void setMasa(const std::vector<Carte> &masa_){
        Dealer::masa = masa_;
    }

    int randomIndexGenerator(int max){
        int randomIndex;

        std::random_device rd;
        std::mt19937 gen(rd());
        // distributie uniforma de la 0 (primul index al pachetului) pana la max (numarul de carti din pachet - 1)
        std::uniform_int_distribution<int> distribution(0,max);

        randomIndex = distribution(gen);
        return randomIndex;
    }



};

class Jucator{
private:
    std::vector<Carte> manaJucator;  // cartile din mana jucatorului
    int nrCartiJucator;  // - numarul de carti - maxim 4, minim 0
    bool randCurentJucator;
//    bool aInceputRandul; // decide daca jucatorul are sau nu prima mutare


//
//    void endTurn(){
//        // daca jucatorul a inceput randul si nu mai vrea sa il continue, il poate termina
//    };

public:
    Jucator(const std::vector<Carte>& manaJucator_, int nrCartiJucator_, bool randCurentJucator_): manaJucator{manaJucator_}, nrCartiJucator{nrCartiJucator_}, randCurentJucator(randCurentJucator_){
        std::cout<<"Ai primit 4 carti"<<std::endl; // constr initializare

    }
    Jucator(const Jucator& other): manaJucator{other.manaJucator}, nrCartiJucator{other.nrCartiJucator}, randCurentJucator{other.randCurentJucator}{
        std::cout<<"Constructor de copiere pentru Jucator"<<std::endl; // util pentru functia de restart cu acelasi pachet
    }
    ~Jucator(){ // destructor
        std::cout<<"Destructor Jucator"<<std::endl;
    }
    // functii getter
    std::vector<Carte> get_manaJucator(){return manaJucator;}
//    int get_cartiJucator(){return nrCartiJucator;}
//    bool const get_aInceputRandul(){return aInceputRandul;}
    bool get_randCurentJucator(){return randCurentJucator;}

    // functii setter
    void setRandCurentJucator(bool randCurentJucator_) {
        Jucator::randCurentJucator = randCurentJucator_;
    }

    // metode
    void turnJucator(std::vector<Carte>& masaJoc, int& cartiMasa){
        for (int i = 0; i < this->nrCartiJucator; i++) {
            std::cout << "Tasta " << i << " pentru a juca cartea " << this->manaJucator[i];
        }
        int indexCarte = -1;
        while(indexCarte < 0 || indexCarte > this->nrCartiJucator -1) {
            std::cin >> indexCarte;

            if (indexCarte < 0 || indexCarte > this->nrCartiJucator - 1) {
                std::cout << "Actiunea nu este posibila" << std::endl;
            }
        }
        masaJoc.push_back(this->manaJucator[indexCarte]);
        this->manaJucator.erase(this->manaJucator.begin() + indexCarte);

        cartiMasa++;
        this->nrCartiJucator--;

        std::cout<<"Cartea dvs."<<std::endl;
        std::cout << masaJoc[cartiMasa - 1] << std::endl;
    }
    

};

class Bot{
private:
    std::vector<Carte> manaBot; // cartile folosite de bot
    int nrCartiBot; // numarul de carti din mana bot-ului
//    bool aInceputRandul; // decide daca botul a avut sau nu prima mutare (opusul variabilei din Jucator)
//    void atac(int ultimaCarte){
//        // daca bot-ul are in pachet ultima carte de pe masa, o va folosi pentru a continua randul
//    };
//    void taiere(int nrPuncte, int ultimaCarte){
//        // daca bot-ul nu are in pachet ultima carte de pe masa, in randul respectiv a fost folosit cel putin un punct, iar bot-ul are in pachet o carte de 7
//        // atunci o va folosi pentru a continua randul
//    };
public:
    Bot(const std::vector<Carte>& manaBot_, int nrCartiBot_): manaBot{manaBot_}, nrCartiBot{nrCartiBot_}{
        std::cout<<"Adversarul a primit 4 carti!"<<std::endl;  // initializare
    }

    Bot(const Bot& other): manaBot{other.manaBot}, nrCartiBot{other.nrCartiBot}{
        std::cout<<"Constructor de copiere pentru Bot"<<std::endl;
    }
    ~Bot(){ // destructor
        std::cout<<"Destructor Bot"<<std::endl;
    }

    Bot& operator=(const Bot& other){  // operator= de copiere
        manaBot = other.manaBot;
        nrCartiBot = other.nrCartiBot;
        std::cout<<"operator= copiere Bot"<<std::endl;
        return *this;
    }

    // functii getter
    std::vector<Carte> get_manaBot(){return manaBot;}
    int get_cartiBot(){return nrCartiBot;}
    // bool get_aInceputRandulBot(){return aInceputRandul;}

    // metode
//    void turnBot(Dealer& pachetInitial, std::vector<Carte>& masaJoc, int& cartiMasa){
//        int indexCarte;
//        indexCarte = pachetInitial.randomIndexGenerator(this->nrCartiBot-1);
//        masaJoc.push_back(this->manaBot[indexCarte]);
//        this->manaBot.erase(this->manaBot.begin()+indexCarte);
//
//        cartiMasa++;
//        this->nrCartiBot--;
//
//        std::cout<<"Cartea adversarului"<<std::endl;
//        std::cout << masaJoc[cartiMasa - 1] << std::endl;
//    }
};


void turnBot(std::vector<Carte>& manaBot, int& nrCartiBot, std::vector<Carte>& masaJoc, int&cartiMasa, Dealer& pachetInitial){
    int indexCarte;
    indexCarte = pachetInitial.randomIndexGenerator(nrCartiBot-1);
    masaJoc.push_back(manaBot[indexCarte]);
    manaBot.erase(manaBot.begin()+indexCarte);

    cartiMasa++;
    nrCartiBot--;

    std::cout<<"Cartea adversarului"<<std::endl;
    std::cout << masaJoc[cartiMasa - 1] << std::endl;

}



//int isPunct(Carte& carteCurenta){
//    if(carteCurenta.getValoareCarte()==10 || carteCurenta.getValoareCarte()==11){
//        return true;
//    }
//    return false;
//}

//void endTurnJucator(std::vector<Carte>& manaJucator, int& nrCartiJucator, std::vector<Carte>& masaJoc, int& cartiMasa, Dealer& pachetInitial){
//        int tastatura;
//        std::cin>>tastatura;
//        std::cout<<"Tasta 1 pentru a incheia randul"<<std::endl;
//        if(tastatura==1){
//            std::cout<<"randul s-a incheiat"<<std::endl;
//            while(nrCartiJucator<4){
//                int randomIndex;
//                pachetInitial.randomIndexGenerator(cartiMasa-1);
//                manaJucator.push_back(masaJoc[randomIndex]);
//                masaJoc.erase(masaJoc.begin()+randomIndex);
//                nrCartiJucator++;
//                cartiMasa--;
//            }
//        }
//        else{
//            turnJucator(manaJucator,nrCartiJucator,masaJoc,cartiMasa);
//        }
//
//
//}
//
//void endTurnBot(std::vector<Carte>& manaBot, int& nrCartiBot, std::vector<Carte>& masaJoc, int& cartiMasa, Dealer& pachetInitial){
//    while(nrCartiBot<4){
//        int randomIndex;
//        pachetInitial.randomIndexGenerator(cartiMasa-1);
//        manaBot.push_back(masaJoc[randomIndex]);
//        nrCartiBot++;
//        cartiMasa--;
//    }
//}




int main(){
    std::vector<Carte> pachetC;

    // init Carte
    std::vector<std::string> culori = {"trefla", "romb", "inima rosie", "inima neagra"};
    for(int i = 7; i<= 14; i++){
        for(std::string const &culoare : culori){
            Carte carte = {i,culoare};
            pachetC.push_back(carte);
        }
    }

    // init Dealer
    Dealer pachetInitial{pachetC,32};


    // afisare carti din pachet
    std::cout<<"Pachetul contine cartile de la 7 la K."<<std::endl;
    for(Carte const &carte : pachetInitial.get_pachet()){
        std::cout<<carte;
    }
    std::cout<<std::endl;

    // mesaje tutorial
    std::cout<<"\nCartile cu valoarea 7 sunt considerate taieri universale";
    std::cout<<"\nCartile 10 si A valoreaza 1 punct. Scopul jocului este acumularea unui numar maxim de puncte!\n";

    // init Jucator
    std::vector<Carte> mana;

    std::vector<Carte> pachet = pachetInitial.get_pachet();
    // alocare carti pentru jucator
    for(int i = 0; i < 4; i++){
        int ceva_random = pachetInitial.randomIndexGenerator(pachetInitial.get_cartiPachet() - 1);
        mana.push_back(pachet[ceva_random]);
        pachet.erase(pachet.begin() + ceva_random);
        pachetInitial.setCartiPachet(pachetInitial.get_cartiPachet() - 1);
    }

    Jucator manaInitialaJucator{mana,4, false};

    std::cout<<"\nFiecare jucator primeste cate 4 carti.";

    // afisare carti din mana jucatorului
    std::cout<<"Pachetul tau contine: "<<std::endl;
    for(Carte const &carte : manaInitialaJucator.get_manaJucator()){
        std::cout<<carte;
    }

    std::cout<<std::endl;


    // init Bot
    std::vector<Carte> manaB;

    // alocare carti pentru bot
    for(int i = 0; i < 4; i++){
        int ceva_random = pachetInitial.randomIndexGenerator(pachetInitial.get_cartiPachet()-1);
        manaB.push_back(pachet[ceva_random]);
        pachet.erase(pachet.begin() + ceva_random);
        pachetInitial.setCartiPachet(pachetInitial.get_cartiPachet() - 1);
    }

    Bot manaInitialaBot{manaB,4};

//    // afisare mana bot, nu va ramane in codul final
//    std::cout<<"Bot-ul a primit "<<manaInitialaBot.get_cartiBot()<<" carti."<<std::endl;
//    std::cout<<"Pachetul bot-ului contine:"<<std::endl;
//    for(Carte const &carte : manaInitialaBot.get_manaBot()){
//        std::cout<<carte;
//    }
//
//    std::cout<<std::endl<<"In pachet au ramas urmatoarele carti:"<<std::endl;
//    // afisare carti ramase dupa alocare, nu va ramane in codul final
//    for(Carte const &carte : pachet){
//        std::cout<<carte;
//    }
//
//    std::cout<<std::endl;


    // copiere mana initiala Jucator
    Jucator manaInitialaJucatorCopie(manaInitialaJucator);

    // copiere mana initiala Bot
    Bot manaInitialaBotCopie(manaInitialaBot);
    manaInitialaBotCopie.operator=(manaInitialaBot);


    std::cout<<std::endl;

    // DE AICI INCEPE JOCUL //

//    pachetInitial.setPachet(copiePachet.get_pachet());
    std::cout<<"Press 1 to start"<<std::endl;

    int tastatura = 0;
    while(tastatura!=1) {
        std::cin >> tastatura;

        if (tastatura == 1) {
            std::cout << "Jocul a inceput" << std::endl << std::endl;
            manaInitialaJucator.setRandCurentJucator(true);
            pachetInitial.setMasa({});
        } else {
            std::cout << "Press 1 to start" << std::endl;
        }
    }
        int cartiMasa = 0;
        std::vector<Carte> masaJoc = pachetInitial.get_masa();
        bool randCurentJucator = manaInitialaJucator.get_randCurentJucator();

        int nrCartiBot = manaInitialaBot.get_cartiBot();

        std::vector<Carte> manaJucator = manaInitialaJucator.get_manaJucator();
        std::vector<Carte> manaBot = manaInitialaBot.get_manaBot();

        int puncteJucator=0, puncteBot=0, puncteJoc=0;

        bool taieturaCurentaJucator = true;

        for(int tura=0; tura<4; tura++) {
            bool randCurentBot;



            std::cout<<"Punctele dvs. "<<puncteJucator<<std::endl;
            std::cout<<"Punctele adversarului "<<puncteBot<<std::endl<<std::endl;


            while (randCurentJucator) {


                manaInitialaJucator.turnJucator(masaJoc, cartiMasa);

                taieturaCurentaJucator = masaJoc[cartiMasa-1].isTaietura(masaJoc[cartiMasa-2]);


                if(masaJoc[cartiMasa-1].getValoareCarte() == 10 || masaJoc[cartiMasa-1].getValoareCarte() == 11){
                    puncteJoc++;
                }
                randCurentJucator = false;

            }
            randCurentBot = true;
            while (randCurentBot && nrCartiBot > 0) {


                turnBot(manaBot,nrCartiBot,masaJoc,cartiMasa,pachetInitial);
//                manaInitialaBot.turnBot(pachetInitial, masaJoc, cartiMasa);

                taieturaCurentaJucator = !(masaJoc[cartiMasa-1].isTaietura(masaJoc[cartiMasa-2]));


                if(masaJoc[cartiMasa-1].getValoareCarte() == 10 || masaJoc[cartiMasa-1].getValoareCarte() == 11){
                    puncteJoc++;
                }

                randCurentBot = false;

            }

            if(taieturaCurentaJucator){
                std::cout<<"Aveti taietura"<<std::endl<<std::endl;
                puncteJucator += puncteJoc;
            }
            else{
                std::cout<<"Adversarul are taietura"<<std::endl<<std::endl;
                puncteBot+=puncteJoc;
            }
            taieturaCurentaJucator = !taieturaCurentaJucator;
            puncteJoc = 0;

            randCurentJucator = true;

        }

    std::cout<<"Punctele dvs. "<<puncteJucator<<std::endl;
    std::cout<<"Punctele adversarului "<<puncteBot<<std::endl<<std::endl;

    std::cout<<"Jocul s-a terminat!"<<std::endl<<std::endl;

    // afisare pachet initial Jucator
    std::cout<<"Pachetul tau initial continea:"<<std::endl;
    for(Carte const &carte : manaInitialaJucatorCopie.get_manaJucator()){
        std::cout<<carte;
    }

    std::cout<<std::endl;

    // afisare pachet initial Bot
    std::cout<<"Pachetul adversarului continea:"<<std::endl;
    for(Carte const &carte : manaInitialaBotCopie.get_manaBot()){
        std::cout<<carte;
    }

    std::cout<<std::endl;






    return 0;
}