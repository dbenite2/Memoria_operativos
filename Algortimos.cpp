//Autores: David Alejandro Benitez Cuevas 
//         Efrain Gonzales Arias

#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;



int getOffSet(int tamPag){
  
  stringstream str;
  unsigned int log = 0;
  while(tamPag >>=1){
      log++;
  }
  return log;
}

bool potencia(int tamPag){
    if(tamPag % 1 == 0){
        return true;
    }else{
        return false;
    }
}

void optimo(int *marcos,vector<string>& paginas,int offSet,int frames){
    int pageFault = 0;
    for (int i = 0; i < paginas.size(); i++){
        stringstream str;
        str << paginas.at(i);
        int hexa;
        str >> hex >> hexa;
        int base = hexa >> offSet << offSet;
        int flag = 0;
        for(int j = 0; j < frames; j++){
            if(base == marcos[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            pageFault++;
            int menosUsado[2] = {-1,-1};
            for(int j = 0; j < frames; j++){
                int paginaLongeva = -1; //valor mas a futuro a cambiar
                for(int k = i; k < paginas.size(); k++){
                    stringstream stream;
                    stream << paginas.at(k);
                    int hexa2;
                    stream >> hex >> hexa2;
                    int paginaFutura = hexa2 >> offSet << offSet;
                    if (marcos[j] == paginaFutura){
                        paginaLongeva = k;
                    }
                }
                if(paginaLongeva == -1){
                    menosUsado[0] = j;
                    menosUsado[1] = -1;
                    if(marcos[j] == -1){
                        break;
                    }
                }else if(paginaLongeva > menosUsado[1] && menosUsado[1] != -1){
                    menosUsado[0] = j;
                    menosUsado[1] = paginaLongeva;
                }
                
            }
            marcos[menosUsado[0]] = base;
        }
        cout << "[ ";
        for(int k = 0; k< frames; k++){
            stringstream stream;
            stream << hex << marcos[k];
            cout << stream.str() << " ";
        }
        cout <<"]" << endl;
    }
    cout << "Page Faults: " << pageFault - frames << endl;
}


void fifo(int *marcos,vector<string>& paginas,int offSet,int frames){
    int cont = 0;
    int siguiente = 0;
    int pageFault = 0;
    for(int i = 0; i < paginas.size();i++){
        stringstream str;
        str << paginas.at(i);
        int hexa;
        str >> hex >> hexa;
        int base = hexa >> offSet << offSet;
        int j = 0;
        bool salir = false;
        if(cont == frames){
            while(j<frames && !salir){
                if (marcos[j] == base){
                    salir = true; 
                }
                j++;
            }
        
            //FIFO
            if(!salir){
                marcos[siguiente] = base;
                siguiente = (siguiente+1) % frames;
                pageFault++;
            }
        }else{
            
            while(j < cont && !salir){
                if(marcos[j] == base){
                    salir = true;
                }
                j++;
            }
                
            if(!salir){
                marcos[cont] = base;
                cont++;
            }
        }
        cout << "[ ";
        for(int k = 0; k< frames; k++){
            stringstream stream;
            stream << hex << marcos[k];
            cout << stream.str() << " ";
        }
        cout <<"]" << endl;
    }
    cout<<endl<<"Page Faults: "<<pageFault<<endl;
}

void LRU(int *marcos,vector<string>& paginas,int offSet,int frames){
    int cont = 0;
    int siguiente = 0;
    int pageFault = 0;
    int arrPeso[frames];
    int peso = frames;
    for(int j = 0;j < frames ;j++){
        arrPeso[j] = peso;
        peso--;
        cout << " arrPeso: " << arrPeso[j] << endl;
    }
    int arrLength(sizeof(arrPeso)/sizeof(arrPeso[0]));
    string dato;
    
    for (int i = 0; i < paginas.size();i++){ 
        stringstream str;
        str << paginas.at(i);
        int hexa;
        str >> hex >> hexa;
        int base = hexa >> offSet << offSet;
        int j = 0;
        bool salir = false;
        int *max = max_element(arrPeso,arrPeso+arrLength);
        int posMax = distance(arrPeso,find(arrPeso,arrPeso+arrLength,*max));
        if(cont == frames){
            while(j<frames && !salir){
                if (marcos[j] == base){
                    salir = true;
                    for(int k = 0; k< frames; k++){
                    arrPeso[k] +=1;                        }
                    arrPeso[posMax] = frames;
                }
                j++;
            }
        
            //LRU
            if(!salir){
                marcos[posMax] = base;
                for(int k = 0; k< frames; k++){
                    arrPeso[k] +=1;
                }
                arrPeso[posMax] = frames;
                pageFault++;
            }
            
        }else{
            
            while(j < cont && !salir){
                if(marcos[j] == base){
                    salir = true;
                }
                j++;
            }
                
            if(!salir){
                marcos[cont] = base;
                cont++;
            }
        }
        cout << "[ ";
        for(int k = 0; k< frames; k++){
            stringstream stream;
            stream << hex << marcos[k];
            cout << stream.str() << " ";
        }
        cout <<"]" << endl;            
    }
    cout<<endl<<"Page Faults: "<<pageFault<<endl;    
}

int main(int argc, char* argv[]){
    if(argc != 5) {
        cerr << "usage: <program_name> <bit_Address> <page_size> <frames> <algorithm>" << endl;
        return 1;
    }
    int bitAddress = atoi(argv[1]); 
    int tamPag = atoi(argv[2]); 
    int frames = atoi(argv[3]); 
    int algoritmo = atoi(argv[4]);
    if(algoritmo > 2){
        cerr << "0: FIFO  1: LRU  2: Optimo" << endl;
        return 1;
    }
    if(potencia(getOffSet(tamPag)) == false){
        cerr << "please provide a <page_size> power of 2" << endl;
        return 1;
    }
    int marcos [frames]; 
    string dato;
    int i = 0;
    vector<string>paginas;
    while(cin >> dato){
        paginas.push_back(dato);
    }
    for (int i = 0; i<frames;i++){
        marcos[i] = -1;
    }
    int offSet = getOffSet(tamPag);
    if(algoritmo == 0){
        fifo(marcos,paginas,offSet,frames);
    }else if (algoritmo == 1){
        LRU(marcos,paginas,offSet,frames);
    }else if (algoritmo ==2){
        optimo(marcos,paginas,offSet,frames);
    }
    return 0;
}