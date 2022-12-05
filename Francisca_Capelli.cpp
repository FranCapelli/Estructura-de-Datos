#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Pueblo{
    string nombre;
    float distancia;
    Pueblo* next=NULL;
};

Pueblo addPueblo(Pueblo Inicial,string nombre,string nombreAnterior,int distancia){
    Pueblo* aux = new Pueblo();
    Pueblo* aux1 = new Pueblo();
    Pueblo* aux2 = new Pueblo();
    int distNew;

    if(nombreAnterior == Inicial.nombre && Inicial.next == NULL){
        aux2->nombre = nombre;
        aux2->distancia = distancia;
        Inicial.next = aux2;
    }

    else if(nombreAnterior == Inicial.nombre && Inicial.next != NULL){
        cout<<"Ingrese  distancia que hay en [Km] entre este nuevo pueblo y el que lo sucede: "; cin>>distNew;
        Inicial.next->distancia = distNew;
        aux = Inicial.next;
        aux2->nombre = nombre;
        aux2->distancia = distancia;
        Inicial.next = aux2;
        Inicial.next->next = aux;
    }

    else if(nombreAnterior != Inicial.nombre){
        aux = Inicial.next;
        while(aux->nombre != nombreAnterior){
            aux = aux->next;
        }
        if(aux->next == NULL){
            aux2->nombre = nombre;
            aux2->distancia = distancia;
            aux->next = aux2;
        }
        else{
            cout<<"Ingrese  distancia que hay en [Km] entre este nuevo pueblo y el que lo sucede: "; cin>>distNew;
            aux->next->distancia = distNew;
            aux1 = aux->next;
            aux2->nombre = nombre;
            aux2->distancia = distancia;
            aux->next = aux2;
            aux->next->next = aux1;
        }
    }
    return Inicial;
    
}

bool existePueblo(Pueblo Inicial,string nombreAnterior){
    Pueblo* aux = new Pueblo();
    aux = Inicial.next;

    if(nombreAnterior == "ROMA"){
        return true;
    }

    else if(nombreAnterior != Inicial.nombre && Inicial.next != NULL){

        if(nombreAnterior == Inicial.next->nombre){
            return true;
        }

        else if(nombreAnterior != aux->nombre && aux->next != NULL){
            while(aux->nombre != nombreAnterior && aux->next != NULL) aux = aux->next;
            if(aux->nombre == nombreAnterior){
                return true;
            }
        }

    }

    return false;
}

int main(void){
    Pueblo* aux = new Pueblo();
    Pueblo Roma[5];
    
    for (int i = 0; i < 5; ++i) {
        Roma[i].nombre = "ROMA";
        Roma[i].distancia = 0;
    }
    
    string namePueblo,namePuebloAnt;
    string puebloDist = "ROMA";
    int numCamino,opcion;
    float maxDist = 0,distActualAnterior,contDist;
    
    system("cls");
    cout<<"Bienvenidos a Roma! \nRoma esta conectada por 5 caminos, cada uno de ellos está enumerado del 1 al 5 \nEl primer pueblo de cada camino es el mismo Roma";
    cout<<"Usted aqui puede agregar pueblos en los caminos que conectan Roma, mostrar los caminos que agrego, \nCalcular la distancia entre caminos que agrego entre ellos y mostar el pueblo mas distante de Roma \n";
    system("pause");

    while(opcion != 5){
        system("cls");
        
        cout << "                  M  E  N  U                 " << endl;
        cout << "----------------------------------------------" << endl;
        cout << "1. Agregar Pueblo." << endl;
        cout << "2. Mostrar Pueblos por Camino." << endl;  
        cout << "3. Conocer el pueblo mas distante de Roma." << endl;    
        cout << "4. Conocer la distancia entre 2 Pueblos."<< endl;
        cout << "5. Finalizar."<< endl; 
        cout << "----------------------------------------------" << endl;
        cout << "Elija una opcion: "; 
        cin  >> opcion;
        
        switch (opcion){
            case 1:
                
                cout<<"Ingrese el nombre del nuevo pueblo que desea agregar: ";cin>>namePueblo;
                cout<<"Indique el camino por donde quiere agregar el pueblo nuevo: ";cin>>numCamino;
                numCamino -= 1;
                cout<<"Ingrese el nombre del pueblo que lo precede: "; cin>>namePuebloAnt;
                if(namePuebloAnt=="Roma"|| namePuebloAnt=="roma")namePuebloAnt="ROMA";
                if(existePueblo(Roma[numCamino], namePuebloAnt)){
                    cout<<"Ingrese  distancia que hay en [Km] entre este nuevo pueblo y el que lo precede: "; cin>>distActualAnterior;
                    Roma[numCamino] = addPueblo(Roma[numCamino],namePueblo,namePuebloAnt,distActualAnterior);
                    cout<<"Se ha agregado el nuevo pueblo con exito.\n";
                    cout<<endl;
                }
                else{
                    cout<<"El pueblo indicado no existe o no se encuentra en este camino\n";
                }

                break;
                
            case 2:
                cout<<"Indique el camino que quiere mostrar: ";cin>>numCamino;
                cout<<endl;
                numCamino -= 1;
                cout<<Roma[numCamino].nombre;
                aux = Roma[numCamino].next;
                if(Roma[numCamino].next != NULL){
                    cout<<"->"<<aux->nombre;
                    while(aux->next != NULL){
                        aux = aux->next;
                        cout<<"->"<<aux->nombre;
                    }
                }
                cout<<endl;
                break;

            case 3:
                maxDist = 0;
                for(int i = 0;i<5;i++){
                    contDist = 0;
                    if(Roma[i].next != NULL){
                        aux = Roma[i].next;
                        contDist += aux->distancia;
                        puebloDist = aux->nombre;
                        while(aux->next != NULL){
                            aux = aux->next;
                            contDist += aux->distancia;
                            puebloDist = aux->nombre;   
                        }
                    }
                    if(contDist>maxDist){
                        maxDist = contDist;
                    }
                }
                cout<<puebloDist<<" es el pueblo mas distante de Roma, con una distancia de "<<maxDist<<"[km]"<<endl;
                break;

            case 4:
                cout<<"La comparación de los pueblos es en orden, el primer pueblo se compara con el segundo. \n";
                cout<<"Indique el camino de los pueblos: ";cin>>numCamino;
                numCamino -= 1;
                cout<<"Indique el primer pueblo: ";cin>>namePuebloAnt;
                if(namePuebloAnt=="Roma"|| namePuebloAnt=="roma")namePuebloAnt="ROMA";
                cout<<"Indique el segundo pueblo: ";cin>>namePueblo;
                if(existePueblo(Roma[numCamino], namePuebloAnt) && existePueblo(Roma[numCamino], namePueblo)){
                    if(namePuebloAnt == Roma[numCamino].nombre){
                        aux = Roma[numCamino].next;
                        while(aux->nombre != namePueblo){
                            aux = aux->next;
                        }
                        maxDist = aux->distancia;
                        cout<<"La distancia entre Roma y "<<namePueblo<<" es "<<maxDist<<"[km]"<<endl;
                    }
                    else{
                        aux = Roma[numCamino].next;
                        while(aux->nombre != namePuebloAnt){
                            aux = aux->next;
                        }
                        contDist = aux->distancia;
                        while(aux->nombre != namePueblo){
                            aux = aux->next;
                        }
                        maxDist = aux->distancia;
                        maxDist -= contDist;
                        cout<<"La distancia entre "<<namePuebloAnt<<" y "<<namePueblo<<" es "<<maxDist<<"[km]"<<endl;
                    }
                }
                else{
                    cout<<"Uno de los pueblos no existe o no se encuentra en el camino"<<endl;
                }
                break;    

            case 5:
                cout<<"Se cerrara este programa. \n";
                break;

            default:
                cout<<"la opcion que eligio no es correcta, intente nuevamente"<<endl;
                break;

        }
        //while
        system("pause");
    }
    //main
}