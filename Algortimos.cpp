#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <cmath>
#include <vector>

using namespace std;



int sacarBase(string dato,int bitAddress,int tamPag){
  
  //string s = "0xFF";
  double desplazamiento = log2(tamPag);
  int numPag = bitAddress - desplazamiento;
  stringstream ss;
  ss << hex << dato;
  unsigned n;
  ss >> n;
  bitset<8> b(n);
  string direccion = b.to_string();
  int address = stoi(direccion.substr(0,numPag),0,2);
  return address;
}

int main(){
    int bitAddress = 0; //8
    int tamPag = 0; //32
    size_t frames = 0; //3
    int algoritmo = 0; //0
    cout << "ingrese parametros" << endl;
    cin >> bitAddress >> tamPag >> frames >> algoritmo;
    int marcos [frames]; //frames
    unsigned int marcos_Length(sizeof(marcos)/sizeof(marcos[0]));
    for (int i  = 0;i<marcos_Length;i++){
        marcos[i] = -1;
        cout << marcos[i] << endl;
    }
    int siguiente = -1;
    int cont = 0;
    int leerDireccion = 0;
    string dato;

    while (cin >> dato){
        for(int i = 0; i< bitAddress; i++){
            int base = sacarBase(dato,bitAddress,tamPag);
            
            int flag = 0;
            for(int j = 0; j < marcos_Length;j++){
                if (base == marcos[j]){
                flag = 1;
                
                break;
                }
            }
            if(flag == 0){
                siguiente = (siguiente + 1 ) % frames;
                marcos[siguiente] = base;
                cout << "dato: " << dato << " " << "f" << marcos[0] << " f2: " << marcos[1] << " f3: " << marcos[2] << endl;
            }else{
                cout << "dato: " << dato << " " << "f" << marcos[0] << " f2: " << marcos[1] << " f3: " << marcos[2] << endl;
            }
        }
    //     int base = sacarBase(dato,bitAddress,tamPag);
    //     int i = 0;
    //     bool salir;
    //     cout << "entrando" << endl;
    //     if(cont == frames -1){
    //         cout << "entro 1" << endl;
    //         salir = false;
    //         while(i<frames && !salir){
    //             if (marcos[i] == base){
    //                 salir = true; 
    //             }
    //             i++;
    //         }
        
    //         //FIFO
    //         if(!salir){
    //             marcos[siguiente] = base;
    //             cout << "siguiente " << siguiente << " " << "dato: " << dato << " " << "f1 " << marcos[0] << " f2 " << marcos[1] << " f3 " << marcos[2] << endl;   
    //             siguiente++;
    //             siguiente = siguiente % frames;
            
    //         }
    //     }else{
            
    //         while(i < frames){
    //             cout << "entro 2" << endl;
    //             if(marcos[i] == base){
    //                 salir = true;
    //             }
    //             i++;
    //             if(!salir){
    //                 marcos[cont] = base;
    //             }
    //             cont++;
        
    //         }    
    //     }
        
     }
        return 0;
}


       



