#include <iostream>
#include <fstream>
#include <iostream>
#include <direct.h>

using namespace std;
// template <typename Generico>


typedef char str30[31];
typedef char str10[11];
typedef char str20[21];
typedef unsigned ushort;

struct Articulo {
  int codArt;
  short codRubro;
  str30 descripcionArt;
  ushort stockActual;
  float precioUnitario;
  str10 unidadMedida;
  short porcOfertas[14];
};
 
struct DescripArt {
  str30 descripcionArt;
  int posicionArt;
  bool estado;
};

struct Rubro {
  short codRubro;
  str20 descripcionRubro;
};

struct ListaCompras {
  str30 descripcionArt;
  short cantRequerida;
};   

void EmitirUnArray(int id[],int n);

bool Abrir(Articulo Articulo[] ,DescripArt IndDescripArt[], Rubro Rubros[], ListaCompras ListaCompras[]);
bool LeerArticulos(ifstream &arch, Articulo &articulo);
bool LeerRubros(ifstream &arch, Rubro &rubro);
bool LeerListaCompras(ifstream &arch, ListaCompras &compra);
bool LeerDescripArts(ifstream &arch, DescripArt &desc);

int main()   
{   
      Articulo Articulos[10000];
      DescripArt IndDescripArt[10000];
      Rubro Rubros[1000];
      ListaCompras ListaCompras[10000];
      int nArticulos = 0;
      int nDescripArt = 0;
      int nRubros = 0;
      int nListaCompras = 0;
      
      Abrir (Articulos,IndDescripArt,Rubros,ListaCompras);

    //   VolcarArchivos(/*lista de parámetros que correspondan*/); // indicados por el grupo de trabajo.
    ProcCompras(ListaCompras,IndDescripArt);              
    //   EmitirTicket(/*lista de parámetros que correspondan*/);
    //   EmitirArt_x_Rubro(/*lista de parámetros que correspondan*/);
    //   Cerrar (/*Articulos,IndDescripArt,Rubros,ListaCompras*/);
    //   return 0;
}

void EmitirUnArray(int id[], int n) {
    for (int i = 0; i < n; i++) {
        cout << id[i] << " ";
    }
}




bool Abrir(Articulo Articulo[] ,DescripArt IndDescripArt[], Rubro Rubros[], ListaCompras ListaCompras[]) {
    ifstream archArticulos("../Articulos.txt");
    ifstream archIndDescripArt("../IndDescripArt.txt");
    ifstream archRubros("../Rubros.txt");
    ifstream archListaCompras("../ListaCompras.txt");

    if (!archArticulos) {
        cout << "Error al abrir el archivo Articulos.txt.";
        return false;
    }
    if (!archIndDescripArt) {
        cout << "Error al abrir el archivo Ind.";
        return false;
    }
    if (!archRubros) {
        cout << "Error al abrir rubros.";
        return false;
    }   
    if (!archListaCompras) {
        cout << "Error al abrir ListaCompras.txt.";
        return false;
    }
    
    int i = 0;
    while (LeerArticulos(archArticulos, Articulo[i])) {

    i++;
}
    i = 0;
    while (LeerDescripArts(archIndDescripArt, IndDescripArt[i])) {
        i++;
    }

    i = 0;
    while (LeerRubros(archRubros, Rubros[i])) {
        i++;
    }

    i = 0;
    while (LeerListaCompras(archListaCompras, ListaCompras[i])) {
        i++;
    }
    return true;
}

void VolcarArchivos(Articulo Articulo[] ,DescripArt IndDescripArt[], Rubro Rubros[], ListaCompras ListaCompras[]) {
    
 }

 void ProcCompras(ListaCompras ListaCompras[], DescripArt IndDescripArt[]) {
     for (int i = 0; i < sizeof(IndDescripArt) / sizeof(IndDescripArt[0]); i++)
     {
      /* code */
     }
     
 }

// void EmitirTicket(/* lista de parámetros que correspondan */) {
//     // Implementación de la emisión del ticket
// }

// void EmitirArt_x_Rubro(/* lista de parámetros que correspondan */) {
//     // Implementación de la emisión de artículos por rubro
// }

// void Cerrar(/*Articulos,IndDescripArt,Rubros,ListaCompras*/) {
//     // Implementación del cierre de archivos
// }

bool LeerArticulos(ifstream &arch, Articulo &articulo) {
 if (!(arch >> articulo.codArt >> articulo.codRubro))
        return false;

    arch.ignore(); 
    arch.get(articulo.descripcionArt, 31); 
    arch >> articulo.stockActual >> articulo.precioUnitario;
    arch.ignore();
    arch.get(articulo.unidadMedida, 11); 

    for (int i = 0; i < 14; i++) {
        arch >> articulo.porcOfertas[i];
    }

    arch.ignore(1000, '\n'); 
    return true;
}

bool LeerRubros(ifstream &arch, Rubro &rubro) {
    if (!(arch >> rubro.codRubro))
        return false;

    arch.ignore(); 
    arch.get(rubro.descripcionRubro, 21); 
    arch.ignore(1000, '\n'); 
    return true;
}


bool LeerListaCompras(ifstream &arch, ListaCompras &compra) {
    if (!arch.get(compra.descripcionArt, 31)) 
        return false;

    arch >> compra.cantRequerida; 
    arch.ignore(1000, '\n');
    return true;
}

bool LeerDescripArts(ifstream &arch, DescripArt &desc) {
    if (!arch.get(desc.descripcionArt, 31)) 
        return false;

    arch >> desc.posicionArt >> desc.estado; 
    arch.ignore(1000, '\n');
    return true;
}


// void CabeceraTicket(int &ds){

// }
// void PieTicket(int &ds){

// }
// void OrdxBur(tid tbl, tid card){

// }

// template <typename id>
// void IntCmb(id &elem1,id &elem2) {
//     id aux = a;
//     a = b;
//     b = aux;
// }

// void ActLinea(modo &id, sid id){

// }
// int BusBinVec(tbl id, tid clv, tid ult){
  
// }
// string Replicate(char car, unsigned n){

// }
// long GetDate(int &year, int &mes, int &dia, int &ds) {
//   time_t     rawtime;
//   struct tm *timeinfo;

//   time ( &rawtime );
//   timeinfo = localtime ( &rawtime );
//   year = 1900 + timeinfo->tm_year;
//   mes  = 1 + timeinfo->tm_mon;
//   dia  = timeinfo->tm_mday;
//   ds   = 1 + timeinfo->tm_wday;
//   return (1900 + timeinfo->tm_year) * 10000 + (1 + timeinfo->tm_mon) * 100 + timeinfo->tm_mday;
// }
// long GetTime(int &hh, int &mm, int &ss) {
//   time_t     rawtime;
//   struct tm *timeinfo;

//   time ( &rawtime );
//   timeinfo = localtime ( &rawtime );
//   hh = timeinfo->tm_hour;
//   mm = timeinfo->tm_min;
//   ss = timeinfo->tm_sec;
//   return timeinfo->tm_hour * 10000 + timeinfo->tm_min * 100 + timeinfo->tm_sec;
// }
