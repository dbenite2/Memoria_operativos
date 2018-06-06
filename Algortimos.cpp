#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

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
  bitset<8> daniel(n);
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
  
  string direccion = daniel.to_string();
  cout << "base pagina: " << direccion << endl;
  int address = stoi(direccion.substr(0,numPag),0,2);
  return address;
}

int optimo(int bitAddress,int tamPag, int *marcos,int frames,int siguiente,int cont){
    // while(leerDireccion){
    //     sacarbase();
    //     arreglo.push base || meter la base(base)
    // }
    // for (i < base.size){
    //     i = 0
    //     salir = false;
    //     if(cont == frames){
    //         if y ciclonormal
    //     }
    // }
    string dato;
    int pageFault = 0;
    int nPagina = 0;
    vector<int>paginas;
    for (int i = 0; i<frames;i++){
        marcos[i] = -1;
    }
    int i,j,k,l;
    while(cin >> dato){
        if(dato == "exit"){break;}
        int base = sacarBase(dato,bitAddress,tamPag);
        paginas.push_back(base);
        cout << paginas.at(0) << endl;
    }


    
    for(i=0;i<nPagina;i++){
       int paginaPresente = 0;
          
        for(j=0;j<frames;j++){
            if(paginas.at(i) == marcos[j]){
                  paginaPresente = 1;
                    break;
            }
        }
        
          
        if(paginaPresente == 0){
            pageFault++;
          
            
             int isFrameEmpty = 0;
         
                 for(j=0;j<frames;j++){
                     if(marcos[j] == -1)
                        {  isFrameEmpty = 1;
                            break;
                        }
                }
      
            if(isFrameEmpty == 1)
                marcos[j] = paginas.at(i);
                 
             
            
            else {
             
             
            int temp[frames];
             
            
            for(k=0;k<frames;k++)
            {  temp[k]=-1;
               for(l=i+1;l<nPagina-1;l++)
                 {
                     if(marcos[k] == paginas.at(l))
                       {
                           temp[k] = l;
                           break;
                       }
                 }
            }
             
             
             
        
        int pos = -1;
        int flag=0;
        for(l=0;l<frames;l++)
        {
            if(temp[l]==-1)
              {
                  pos = l;
                  flag=1;
                  break;
              }
        }
          
        if(flag==1) 
        { marcos[pos] = paginas.at(i);
        }
         
        else{
            
          int max = temp[0];
          pos = 0;
            
          for(k=1;k<frames;k++)
          {
              if(max<temp[k])
              {
                  pos = k;
                  max=temp[k];
                    
              }
          }
            
          marcos[pos] = paginas.at(i);
            
        }
          
      }
       
    }
       
       
     for(j=0;j<frames;j++)
        {
            cout<<marcos[j]<<" ";
        }
          
          
          
    cout<<endl;
          
    } 

     cout << "direccion: " << dato;
        for(int i = 0; i< frames; i++){
            cout << "  f" << i << ": " << marcos[i];
        }
        cout << endl;  
    cout<<endl<<"Page Faults:"<<pageFault;
    return 0;    
          
}


int fifo(int bitAddress,int tamPag, int *marcos,int frames,int siguiente,int cont){
    string dato;
    int pageFault = 0;
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
                pageFault++;
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
        cout<<endl<<"Page Faults:"<<pageFault;            
        
        
    }
}

int LRU(int bitAddress,int tamPag, int *marcos,int frames,int siguiente,int cont){
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
    while (cin >> dato){
        int base = sacarBase(dato,bitAddress,tamPag);
        cout << "base: " << base << endl;
        int i = 0;
        bool salir = false;
        int *max = max_element(arrPeso,arrPeso+arrLength);
        int posMax = distance(arrPeso,find(arrPeso,arrPeso+arrLength,*max));
        if(cont == frames){
            while(i<frames && !salir){
                if (marcos[i] == base){
                    salir = true;
                    for(int k = 0; k< frames; k++){
                        arrPeso[k] +=1;
                    }
                arrPeso[posMax] = frames;
                }
                i++;
            }
        
            //LRU
            cout << "max: " << *max << endl;
            cout << "posMax: " << posMax << endl;
            if(!salir){
                marcos[posMax] = base;
                for(int k = 0; k< frames; k++){
                    arrPeso[k] +=1;
                }
                arrPeso[posMax] = frames;
                pageFault++;
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
        cout<<endl<<"Page Faults:"<<pageFault;
        
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
    int siguiente = 0;
    int cont = 0;
    int leerDireccion = 0;
    if(algoritmo == 0){
        fifo(bitAddress,tamPag,marcos,frames,siguiente,cont);
    }else if (algoritmo == 1){
        LRU(bitAddress,tamPag,marcos,frames,siguiente,cont);
    }else if (algoritmo ==2){
        optimo(bitAddress,tamPag,marcos,frames,siguiente,cont);
    }
    return 0;
}



       



