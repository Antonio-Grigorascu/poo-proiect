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
    int getValoareCarte() const {return valoareCarte;}

    std::string schimbareValoare() const {
        if(valoareCarte == 11){
            return ("A");
        }
        if(valoareCarte == 12){
            return ("J");
        }
        if(valoareCarte == 13){
            return ("Q");
        }
        if(valoareCarte == 14){
            return ("K");
        }
        return std::to_string(valoareCarte);
    }


    // operator << de afisare
    friend std::ostream& operator<<(std::ostream& os, const Carte& carte);

    // metode
    bool isTaietura (const Carte& cartePrecedenta){
        if(this->valoareCarte == 7){
            return true;
        }
        if(this->valoareCarte == cartePrecedenta.getValoareCarte() ){
            return true;
        }
        return false;
    }

    void afisareInimaRosie() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "   |\n|(\\/)|\n| \\/ |\n|   " + schimbareValoare() + "|\n";
    }

    void afisareRomb() const{
        std::cout<<" ____ \n|"+ schimbareValoare()+"   |\n| /\\ |\n| \\/ |\n|   "   +schimbareValoare() + "|\n";
    }

    void afisareInimaNeagra() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "   |\n| /\\ |\n|(__)|\n| /\\" + schimbareValoare() + "|\n";
    }

    void afisareTrefla() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "   |\n| &  |\n|&|& |\n|   " + schimbareValoare() + "|\n";
    }

    void afisareInimaRosieZ() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "  |\n|(\\/)|\n| \\/ |\n|  " + schimbareValoare() + "|\n";
    }

    void afisareRombZ() const{
        std::cout<<" ____ \n|"+ schimbareValoare()+"  |\n| /\\ |\n| \\/ |\n|  "   +schimbareValoare() + "|\n";
    }

    void afisareInimaNeagraZ() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "  |\n| /\\ |\n|(__)|\n| / " + schimbareValoare() + "|\n";
    }

    void afisareTreflaZ() const{
        std::cout<<" ____ \n|" + schimbareValoare() + "  |\n| &  |\n|&|& |\n|  " + schimbareValoare() + "|\n";
    }

    void afisareAsciiArt(){
        if(culoareCarte == "inima rosie"){
            if(valoareCarte == 10){
                afisareInimaRosieZ();
            }
            else{
                afisareInimaRosie();
            }

        }
        if(culoareCarte == "inima neagra"){
            if(valoareCarte == 10){
                afisareInimaNeagraZ();
            }
            else{
                afisareInimaNeagra();
            }
        }
        if(culoareCarte == "romb"){
            if(valoareCarte == 10){
                afisareRombZ();
            }
            else{
                afisareRomb();
            }
        }
        if(culoareCarte == "trefla"){
            if(valoareCarte == 10){
                afisareTreflaZ();
            }
            else{
                afisareTrefla();
            }
        }
    }
};



std::ostream& operator<<(std::ostream& os, const Carte& carte){
    os << carte.schimbareValoare()<<" de "<<carte.culoareCarte<<std::endl;
    return os;
};


class Joc{
public:
    int randomIndexGenerator(int max){
        int randomIndex;

        std::random_device rd;
        std::mt19937 gen(rd());
        // distributie uniforma de la 0 (primul index al pachetului) pana la max (numarul de carti din pachet - 1)
        std::uniform_int_distribution<int> distribution(0,max);

        randomIndex = distribution(gen);
        return randomIndex;
    }

    void aCastigatJocul(int puncteJucator, int puncteBot){
        if(puncteJucator>puncteBot){
            std::cout<<"Felicitari! Ati castigat jocul"<<std::endl;
        }
        if(puncteJucator<puncteBot){
            std::cout<<"Ati pierdut!"<<std::endl;
        }
        if(puncteJucator==puncteBot){
            std::cout<<"Egalitate!"<<std::endl;
        }
    }

    void initializarePachet(std::vector<Carte>& pachet){
        std::vector<std::string> culori = {"trefla", "romb", "inima rosie", "inima neagra"};
        for(int i = 7; i<= 14; i++){
            for(std::string const &culoare : culori){
                Carte carte = {i,culoare};
                pachet.push_back(carte);
            }
        }
    }
};



class Jucator{
private:
    std::vector<Carte> manaJucator;  // cartile din mana jucatorului
    int nrCartiJucator;  // - numarul de carti - maxim 4, minim 0
    bool randCurentJucator;
//    bool aInceputRandul; // decide daca jucatorul are sau nu prima mutare



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
    int get_cartiJucator(){return nrCartiJucator;}
//    bool const get_aInceputRandul(){return aInceputRandul;}
    bool get_randCurentJucator(){return randCurentJucator;}

    // functii setter
    void setRandCurentJucator(bool randCurentJucator_) {
        Jucator::randCurentJucator = randCurentJucator_;
    }
    void setManaJucator(const std::vector<Carte>& manaJucator_){
        Jucator::manaJucator = manaJucator_;
    }
    void setNrCartiJucator(int nrCartiJucator_){
        Jucator::nrCartiJucator = nrCartiJucator_;
    }

    // metode


    void turnJucator(std::vector<Carte>& masaJoc, int& cartiMasa){
        for (int i = 0; i < this->nrCartiJucator; i++) {
            std::cout << "Tasta " << i << " pentru a juca cartea " << this->manaJucator[i];
        }
        std::cout<<"----------------------------------------------------------------------"<<std::endl;
        std::string indexCarte = "x";
        while(indexCarte != "0" && indexCarte != "1" && indexCarte != "2" && indexCarte != "3" ) {
            std::cin >> indexCarte;

            if (indexCarte != "0" && indexCarte != "1" && indexCarte != "2" && indexCarte != "3" ) {
                std::cout << "Actiunea nu este posibila" << std::endl;
            }
        }
        masaJoc.push_back(this->manaJucator[std::stoi(indexCarte)]);
        this->manaJucator.erase(this->manaJucator.begin() + std::stoi(indexCarte));

        cartiMasa++;
        this->nrCartiJucator--;

        std::cout<<"Cartea dvs."<<std::endl;
        std::cout << masaJoc[cartiMasa - 1] << std::endl;
    }

    void afisareJucator(){
        for(Carte const &carte : this->manaJucator){
            std::cout<<carte;
        }
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

    // functii setter
    void setManaBot(const std::vector<Carte> &manaBot_) {
        Bot::manaBot = manaBot_;
    }

    void setNrCartiBot(int nrCartiBot_) {
        Bot::nrCartiBot = nrCartiBot_;
    }

    // metode

    void afisareBot(){
        for(Carte const &carte : manaBot){
            std::cout<<carte;
        }

    }

    int cautareSapte(){
        int indexTaiere = -1;
        for(int i = 0; i<this->nrCartiBot; i++){
            if(this->manaBot[i].getValoareCarte() == 7){
                indexTaiere = i;
            }
        }
        return indexTaiere;
    }


    int cautareTaiere(std::vector<Carte>& masaJoc, const int& cartiMasa){
        int indexTaiere = -1;
        for(int i = 0; i<this->nrCartiBot; i++){
            if(this->manaBot[i].getValoareCarte() == masaJoc[cartiMasa-1].getValoareCarte()){
                indexTaiere = i;
            }
        }
        return indexTaiere;
    }



    int cautarePuncte(const std::vector<Carte>& masaJoc, const int& cartiMasa){
        const Carte& ultimaCarte = masaJoc[cartiMasa-1];
        if(ultimaCarte.getValoareCarte() == 10 || ultimaCarte.getValoareCarte() == 11){
            return true;
        }
        return false;
    }

    void turnBot(std::vector<Carte>& masaJoc, int& cartiMasa, Joc& joc){
        int indexCarte;
        if(cautareTaiere(masaJoc,cartiMasa) != -1 && masaJoc[cartiMasa-1].getValoareCarte() != 7){  // daca are o taiere care nu este 7, o va juca mereu
            indexCarte = cautareTaiere(masaJoc,cartiMasa);
        }
        else{
            if(cautareSapte() != -1 && cautarePuncte(masaJoc, cartiMasa)){ // daca singura lui taiere este 7 si exista puncte in joc, o va juca (incearca mereu sa fure puncte)
                indexCarte = cautareSapte();
            }
            else{
                indexCarte = joc.randomIndexGenerator(this->nrCartiBot-1);  // daca nu are taieri sau nu exista puncte in joc, va cauta o carte random
                int incercari = 0; // botul va incerca mereu sa pastreze cartea 7, dar are o limita de 3 incercari
                while(cautareSapte() == indexCarte && incercari < 3) { // are la dispozitie 3 incercari sa gaseasca alta carte ( in cazul in care are doar carti de 7 va juca 7)
                    indexCarte = joc.randomIndexGenerator(this->nrCartiBot - 1);
                    incercari++;
                }
            }
        }



        masaJoc.push_back(this->manaBot[indexCarte]);
        this->manaBot.erase(this->manaBot.begin()+indexCarte);

        cartiMasa++;
        this->nrCartiBot--;

        std::cout<<"Cartea adversarului"<<std::endl;
        std::cout << masaJoc[cartiMasa - 1] << std::endl;

    }

};


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
//    std::vector<Carte> get_pachet() {return pachet;}
    int get_cartiPachet() {return cartiPachet;}
    std::vector<Carte> get_masa(){return masa;}

    // functii setter
//    void setCartiPachet(int cartiPachet_) {
//        Dealer::cartiPachet = cartiPachet_;
//    }

//    void setPachet(const std::vector<Carte> &pachet_) {
//        Dealer::pachet = pachet_;
//    }

    void setMasa(const std::vector<Carte> &masa_){
        Dealer::masa = masa_;
    }

    void initializareJucator(Joc& joc, std::vector<Carte>& mana) {
        for (int i = 0; i < 4; i++) {
            int ceva_random = joc.randomIndexGenerator(this->cartiPachet - 1);
            mana.push_back(this->pachet[ceva_random]);
            this->pachet.erase(this->pachet.begin() + ceva_random);
            this->cartiPachet--;
        }
    }

    void initializareBot(Joc& joc, std::vector<Carte>& manaB){
        for(int i = 0; i < 4; i++){
            int ceva_random = joc.randomIndexGenerator(this->cartiPachet-1);
            manaB.push_back(this->pachet[ceva_random]);
            this->pachet.erase(this->pachet.begin() + ceva_random);
            this->cartiPachet--;
        }
    }

    void afisarePachet(){
        std::cout<<"Pachetul contine cartile de la 7 la K."<<std::endl;
        for(Carte const &carte : this->pachet){
            std::cout<<carte;
        }
        std::cout<<std::endl;

    }

    void alocareCarteJucator(Jucator& manaInitialaJucator, Joc& joc){
        std::vector<Carte> manaJucator = manaInitialaJucator.get_manaJucator();
        int randomIndex = joc.randomIndexGenerator(this->cartiPachet -1);
        Carte carteAlocata = this->pachet[randomIndex];
        manaJucator.push_back(carteAlocata);
        this->pachet.erase(this->pachet.begin() + randomIndex);
        this->cartiPachet--;
        manaInitialaJucator.setManaJucator(manaJucator);
        manaInitialaJucator.setNrCartiJucator(4);
    }

    void alocareCarteBot(Bot& manaInitialaBot, Joc& joc){
        std::vector<Carte> manaBot = manaInitialaBot.get_manaBot();
        int randomIndex = joc.randomIndexGenerator(this->cartiPachet -1);
        Carte carteAlocata = this->pachet[randomIndex];
        manaBot.push_back(carteAlocata);
        this->pachet.erase(this->pachet.begin() + randomIndex);
        this->cartiPachet--;
        manaInitialaBot.setManaBot(manaBot);
        manaInitialaBot.setNrCartiBot(4);
    }


    void runda(Joc& joc,
               int& cartiMasa,
               std::vector<Carte>& masaJoc,
               bool& randCurentJucator,
               const int& nrCartiBot,
               int& puncteJucator,
               int& puncteBot,
               int& puncteJoc,
               bool& taieturaCurentaJucator,
               bool& randCurentBot,
               Jucator& manaInitialaJucator,
               Bot& manaInitialaBot) {

        std::cout << "----------------------------------------------------------------------" << std::endl;

        while (randCurentJucator) {

            manaInitialaJucator.turnJucator(masaJoc, cartiMasa);

            if (cartiMasa < 2) {
                taieturaCurentaJucator = true;
            } else {
                taieturaCurentaJucator = masaJoc[cartiMasa - 1].isTaietura(masaJoc[cartiMasa - 2]);
            }


            if (masaJoc[cartiMasa - 1].getValoareCarte() == 10 || masaJoc[cartiMasa - 1].getValoareCarte() == 11) {
                puncteJoc++;
            }
            randCurentJucator = false;

        }
        randCurentBot = true;
        while (randCurentBot && nrCartiBot > 0) {


            manaInitialaBot.turnBot(masaJoc, cartiMasa, joc);

            masaJoc[cartiMasa - 2].afisareAsciiArt();
            masaJoc[cartiMasa - 1].afisareAsciiArt();


            taieturaCurentaJucator = !(masaJoc[cartiMasa - 1].isTaietura(masaJoc[cartiMasa - 2]));


            if (masaJoc[cartiMasa - 1].getValoareCarte() == 10 || masaJoc[cartiMasa - 1].getValoareCarte() == 11) {
                puncteJoc++;
            }

            randCurentBot = false;

        }

        if (taieturaCurentaJucator) {
            std::cout << "Aveti taietura" << std::endl << std::endl;
            puncteJucator += puncteJoc;
            if(puncteJoc != 0){
                if(puncteJoc == 1){
                    std::cout<<"Ati furat un punct!"<<std::endl;
                }
                else{
                    std::cout<<"Ati furat "<<puncteJoc<<" puncte!"<<std::endl;
                }

            }
        } else {

            std::cout << "Adversarul are taietura" << std::endl << std::endl;
            puncteBot += puncteJoc;
            if(puncteJoc != 0){
                if(puncteJoc == 1){
                    std::cout<<"Adversarul a furat un punct!"<<std::endl;
                }
                else{
                    std::cout<<"Adversarul a furat "<<puncteJoc<<" puncte!"<<std::endl;
                }

            }
        }
        taieturaCurentaJucator = !taieturaCurentaJucator;
        puncteJoc = 0;

        randCurentJucator = true;


        std::cout << "----------------------------------------------------------------------" << std::endl;

    }

    void incepeJocul(std::string& tastatura, Jucator& manaInitialaJucator, Dealer& pachetInitial){
        std::cin >> tastatura;

        if (tastatura == "1") {
            std::cout << "Jocul a inceput" << std::endl << std::endl;
            manaInitialaJucator.setRandCurentJucator(true);
            pachetInitial.setMasa({});
        } else {
            std::cout << "Tasta 1 pentru a incepe jocul" << std::endl;
        }
    }


};




int main(){

    Joc joc;

    std::vector<Carte> pachetC;

    // init Pachet
    joc.initializarePachet(pachetC);
    Dealer pachetInitial{pachetC,32};

    // afisare carti din pachet
    pachetInitial.afisarePachet();

    // mesaje tutorial
    std::cout<<"\nCartile cu valoarea 7 sunt considerate taieri universale";
    std::cout<<"\nCartile 10 si A valoreaza 1 punct. Scopul jocului este acumularea unui numar maxim de puncte!\n";

    // init Jucator
    std::vector<Carte> mana;
//    std::vector<Carte> pachet = pachetInitial.get_pachet();

    pachetInitial.initializareJucator(joc, mana);
    Jucator manaInitialaJucator{mana,4, false};

    std::cout<<"\nFiecare jucator primeste cate 4 carti.";

    std::cout<<"Pachetul tau contine: "<<std::endl;
    manaInitialaJucator.afisareJucator();

    std::cout<<std::endl;


    // init Bot
    std::vector<Carte> manaB;

    pachetInitial.initializareBot(joc, manaB);
    Bot manaInitialaBot{manaB,4};


    // copiere mana initiala Jucator
    Jucator manaInitialaJucatorCopie(manaInitialaJucator);

    // copiere mana initiala Bot
    Bot manaInitialaBotCopie(manaInitialaBot);
    manaInitialaBotCopie.operator=(manaInitialaBot);


    std::cout<<std::endl;


    // DE AICI INCEPE JOCUL //


//    pachetInitial.setPachet(copiePachet.get_pachet());
    std::cout<<"Press 1 to start"<<std::endl;

    std::string tastatura = "0";
    while(tastatura!="1") {
        pachetInitial.incepeJocul(tastatura, manaInitialaJucator,pachetInitial);
    }

        int cartiMasa = 0;
        std::vector<Carte> masaJoc = pachetInitial.get_masa();
        bool randCurentJucator = manaInitialaJucator.get_randCurentJucator();
        int nrCartiBot = manaInitialaBot.get_cartiBot();
//        std::vector<Carte> manaBot = manaInitialaBot.get_manaBot();
        int puncteJucator=0, puncteBot=0, puncteJoc=0;
        bool taieturaCurentaJucator = true;

        int randuri = 0;

        while(manaInitialaJucator.get_cartiJucator() > 0 && manaInitialaBot.get_cartiBot() > 0) {
            bool randCurentBot;
            std::cout<<std::endl;
            std::cout<<"Punctele dvs. "<<puncteJucator<<std::endl;
            std::cout<<"Punctele adversarului "<<puncteBot<<std::endl<<std::endl;

            pachetInitial.runda(joc, cartiMasa, masaJoc, randCurentJucator, nrCartiBot,puncteJucator,puncteBot,puncteJoc, taieturaCurentaJucator, randCurentBot, manaInitialaJucator, manaInitialaBot);
//            manaInitialaBot.afisareBot();
            if(pachetInitial.get_cartiPachet() >=2){
                pachetInitial.alocareCarteJucator(manaInitialaJucator,joc);
                pachetInitial.alocareCarteBot(manaInitialaBot,joc);
            }
            if(pachetInitial.get_cartiPachet() == 0){
                std::cout<<"Pachetul nu mai are carti"<<std::endl;
            }
            randuri++;
        }

    // FINAL JOC
    std::cout<<std::endl;
    std::cout<<"Punctele dvs. "<<puncteJucator<<std::endl;
    std::cout<<"Punctele adversarului "<<puncteBot<<std::endl<<std::endl;

    std::cout<<"Jocul s-a terminat!"<<std::endl<<std::endl;

    joc.aCastigatJocul(puncteJucator,puncteBot);
    std::cout<<std::endl;


    std::cout << "----------------------------------------------------------------------" << std::endl;


    // afisare pachet initial Jucator
    std::cout<<"Pachetul tau initial continea:"<<std::endl;

    manaInitialaJucatorCopie.afisareJucator();

    std::cout<<std::endl;

    // afisare pachet initial Bot
    std::cout<<"Pachetul adversarului continea:"<<std::endl;

    manaInitialaBotCopie.afisareBot();

    std::cout<<std::endl;

    std::cout<<"S-au disputat "<<randuri<<" randuri"<<std::endl;
    std::cout<<"----------------------------------------------------------------------"<<std::endl;



    return 0;
}