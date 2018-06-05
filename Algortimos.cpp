#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <cmath>
#include <vector>

using namespace std;



int sacarBase(string dato,int bitAddress,int tamPag){
  
  double desplazamiento = log2(tamPag);
  int numPag = 0;
  cout << "desplazamiento: " << desplazamiento << endl;
    numPag = bitAddress - desplazamiento;
    

  cout << "numPag: " << numPag << endl;
  stringstream ss;
  ss << hex << dato;
  unsigned n;
  ss >> n;
  bitset<8> b(n);
//   if(bitAddress%2 == 0){
//     if(bitAddress == 2){
//         bitset<2> b(n);
//     }else if(bitAddress == 4){
//         bitset<4> b(n);
//     }else if(bitAddress == 8){
//         bitset<8> b(n);
//     }else if(bitAddress == 16){
//         bitset<16> b(n);
//     }else if(bitAddress == 32){
//         bitset<32> b(n);
//     }else if(bitAddress == 64){
//         bitset<64> b(n);
//     }else{
//         bitset<128> b(n);
//     }
  
  string direccion = b.to_string();
  cout << "base pagina: " << direccion << endl;
  int address = stoi(direccion.substr(0,numPag),0,2);
  return address;
}

int fifo(int bitAddress,int tamPag, int *marcos,int frames,int siguiente,int cont){
    string dato;
    while (cin >> dato){
        int base = sacarBase(dato,bitAddress,tamPag);
        cout << "base: " << base << endl;
        int i = 0;
        bool salir = false;
        if(cont == frames){
            while(i<frames && !salir){
                if (marcos[i] == base){
                    salir = true; 
                }
                i++;
            }
        
            //FIFO
            if(!salir){
                marcos[siguiente] = base;
                siguiente = (siguiente+1) % frames;
            
            }
        }else{
            
            while(i < cont && !salir){
                if(marcos[i] == base){
                    salir = true;
                }
                i++;
            }
                
            if(!salir){
                marcos[cont] = base;
                cont++;
            }
        }
        cout << "direccion: " << dato;
        for(int i = 0; i< frames; i++){
            cout << "  f" << i << ": " << marcos[i];
        }
        cout << endl;    
        
        
    }
}

int main(){
    int bitAddress; //8
    int tamPag = 0; //32
    int frames = 0; //3
    int algoritmo = 0; //0
    cout << "ingrese parametros" << endl;
    cin >> bitAddress >> tamPag >> frames >> algoritmo;
    int marcos [frames]; //frames
    // unsigned int marcos_Length(sizeof(marcos)/sizeof(marcos[0]));
    // for (int i  = 0;i<marcos_Length;i++){
    //     marcos[i] = -1;
    //     cout << marcos[i] << endl;
    // }
    int siguiente = 0;
    int cont = 0;
    int leerDireccion = 0;
    if(algoritmo == 0){
    fifo(bitAddress,tamPag,marcos,frames,siguiente,cont);
    }
    return 0;
}



       



