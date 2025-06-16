#include <iostream>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <cstring>
#include <ctime>

using namespace std;

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

struct RubroArt {
    short codRubro;
    int posicionArt;
};


void EmitirUnArray(int id[],int n);

bool Abrir(ifstream &archArticulos, ifstream &archIndDescripArt, ifstream &archRubros, ifstream &archListaCompras);
void VolcarArchivos(Articulo Articulo[] ,DescripArt IndDescripArt[], Rubro Rubros[], ListaCompras ListaCompras[],int &nArticulos, int &nDescripArt, int &nRubros, int &nListaCompras,ifstream &archArticulos, ifstream &archIndDescripArt, ifstream &archRubros, ifstream &archListaCompras);
bool LeerArticulos(ifstream &arch, Articulo &articulo);
bool LeerRubros(ifstream &arch, Rubro &rubro);
bool LeerListaCompras(ifstream &arch, ListaCompras &compra);
bool LeerDescripArts(ifstream &arch, DescripArt &desc);
void ProcCompras(ifstream archArticulos,ListaCompras ListaCompras[], DescripArt IndDescripArt[], Articulo Articulos[], int nArticulos, int nDescripArt, int nRubros, int nListaCompras);
void CrearTablaRubroArt(Articulo Articulos[], int nArticulos, RubroArt tablaRubroArt[], int &nRubroArt);
void OrdxBur(RubroArt tabla[], int n);
void IntCmb(RubroArt &a, RubroArt &b);
long GetTime(int &hh, int &mm, int &ss);
long GetDate(int &year, int &mes, int &dia, int &ds);
void EmitirTicket(ListaCompras ListaCompras[], DescripArt IndDescripArt[], Articulo Articulos[], int nListaCompras, int nDescripArt);

int main()
{
    ifstream archArticulos, archIndDescripArt, archRubros, archListaCompras;
    Articulo Articulos[10000];
    DescripArt IndDescripArt[10000];
    Rubro Rubros[1000];
    ListaCompras ListaCompras[10000];
    RubroArt tablaRubroArt[10000];
    int nArticulos = 0;
    int nDescripArt = 0;
    int nRubros = 0;
    int nListaCompras = 0;
    int nRubroArt = 0;


    Abrir(archArticulos, archIndDescripArt, archRubros, archListaCompras);
    VolcarArchivos(Articulos,IndDescripArt,Rubros,ListaCompras,nArticulos,nDescripArt,nRubros,nListaCompras,archArticulos, archIndDescripArt, archRubros, archListaCompras);
    ProcCompras(ListaCompras,IndDescripArt,Articulos, nArticulos, nDescripArt, nRubros, nListaCompras);
    for (int i = 0; i < nListaCompras; i++)
    {
        cout << ListaCompras[i].descripcionArt << " " << ListaCompras[i].cantRequerida << endl;
    }
    EmitirTicket(ListaCompras,IndDescripArt,Articulos,nListaCompras,nDescripArt);
    //   EmitirArt_x_Rubro(/*lista de parámetros que correspondan*/);
    //   Cerrar (/*Articulos,IndDescripArt,Rubros,ListaCompras*/);
    //   return 0;
}

void EmitirUnArray(int id[], int n) {
    for (int i = 0; i < n; i++) {
        cout << id[i] << " ";
    }
}




bool Abrir(ifstream &archArticulos, ifstream &archIndDescripArt, ifstream &archRubros, ifstream &archListaCompras) {
    archArticulos.open("../Articulos.txt");
    archIndDescripArt.open("../IndDescripArt.txt");
    archRubros.open("./Rubros.txt");
    archListaCompras.open("./ListaCompras.txt");

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

    return true;

}

void VolcarArchivos(Articulo Articulo[] ,DescripArt IndDescripArt[], Rubro Rubros[], ListaCompras ListaCompras[], int &nArticulos, int &nDescripArt, int &nRubros, int &nListaCompras,ifstream &archArticulos, ifstream &archIndDescripArt, ifstream &archRubros, ifstream &archListaCompras) {
    int i = 0;
    while (LeerArticulos(archArticulos, Articulo[i])) {

    i++;
    }
    nArticulos = i;
    i = 0;
    while (LeerDescripArts(archIndDescripArt, IndDescripArt[i])) {
        i++;
    }
    nDescripArt = i;
    i = 0;
    while (LeerRubros(archRubros, Rubros[i])) {
        i++;
    }
    nRubros = i;
    i = 0;
    while (LeerListaCompras(archListaCompras, ListaCompras[i])) {
        i++;
    }
    nListaCompras = i;
 }

void ProcCompras(ifstream archArticulos,ListaCompras ListaCompras[], DescripArt IndDescripArt[], Articulo Articulos[], int nArticulos, int nDescripArt, int nRubros, int nListaCompras) {
    for (int i = 0; i < nListaCompras; i++)
    {
        cout << "ProcCompras " << ListaCompras[i].descripcionArt << " " << ListaCompras[i].cantRequerida << endl;
    }
    for (int i = 0; i < nListaCompras; i++)
     {
      int j = 0;
        while (ListaCompras[i].descripcionArt != IndDescripArt[j].descripcionArt) {
        j++;
      }
      if(IndDescripArt[j].estado) {
        int stockViejo = Articulos[IndDescripArt[j].posicionArt].stockActual;
        if (Articulos[IndDescripArt[j].posicionArt].stockActual >= ListaCompras[i].cantRequerida) {
            Articulos[IndDescripArt[j].posicionArt].stockActual -= ListaCompras[i].cantRequerida;
        }
        else {
            ListaCompras[i].cantRequerida = Articulos[IndDescripArt[j].posicionArt].stockActual;
            Articulos[IndDescripArt[j].posicionArt].stockActual = 0;
        }
        archArticulos.seekg(0);
        if (!archArticulos) {
            cout << "No se pudo abrir el archivo.\n";
        }
        string linea;
        while (getline(archArticulos, linea)) {

        if (linea.find(Articulos[IndDescripArt[j].posicionArt].codArt) != string::npos) {
            linea.replace(linea.find(to_string(stockViejo)),to_string(stockViejo).length() , to_string(Articulos[IndDescripArt[j].posicionArt].stockActual));
        }
    }
      }
      else {
        ListaCompras[i].cantRequerida = 0;
      }
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

void CrearTablaRubroArt(Articulo Articulos[], int nArticulos, RubroArt tablaRubroArt[], int &nRubroArt) {
    for (int i = 0; i < nArticulos; i++) {
        tablaRubroArt[i].codRubro = Articulos[i].codRubro;
        tablaRubroArt[i].posicionArt = i;
    }
    nRubroArt = nArticulos;
    OrdxBur(tablaRubroArt, nRubroArt);
}

void OrdxBur(RubroArt tabla[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tabla[j].codRubro > tabla[j + 1].codRubro) {
                IntCmb(tabla[j], tabla[j + 1]);
            }
        }
    }
}

void IntCmb(RubroArt &a, RubroArt &b) {
    RubroArt aux = a;
    a = b;
    b = aux;
}

void EmitirTicket(ListaCompras ListaCompras[], DescripArt IndDescripArt[], Articulo Articulos[], int nListaCompras, int nDescripArt) {

    freopen("../Ticket.txt", "w", stdout); // Redirige cout al archivo

    cout << "K O T T O\nYo te reconozco\nSUC 170\nXXXXXXXXX 9999\nC.U.I.T. 99-99999999-9\n";
    cout << "Fecha: ";
    int y, m, d, ds;
    GetDate(y, m, d, ds);
    cout << d << "/" << m << "/" << y << "\n";
    int h, mi, s;
    GetTime(h, mi, s);
    cout << "Hora: " << h << ":" << mi << ":" << s << "\n";
    cout << "Nro. Ticket: 0001-00000001\nNro. Caja: 0001\n";
    cout << "----------------------------------------\nF A C T U R A - B\nORIGINAL\n----------------------------------------\n";

    float totalSinDescuentos = 0, totalDescuentos = 0;

    for (int i = 0; i < nListaCompras; i++) {
        // Buscar artículo
        for (int j = 0; j < nDescripArt; j++) {
            if (strcmp(ListaCompras[i].descripcionArt, IndDescripArt[j].descripcionArt) == 0) {
                if (IndDescripArt[j].estado == false || ListaCompras[i].cantRequerida == 0) continue;

                Articulo &art = Articulos[IndDescripArt[j].posicionArt];
                float subtotal = ListaCompras[i].cantRequerida * art.precioUnitario;
                float descuento = 0.0;

                // Supongamos: primer promoción válida si existe
                if (art.porcOfertas[0] != 0) {
                    descuento = subtotal * (art.porcOfertas[1] / 100.0f);
                }

                totalSinDescuentos += subtotal;
                totalDescuentos += descuento;

                // Cuerpo del ticket
                cout << ListaCompras[i].cantRequerida << " x $ " << art.precioUnitario << endl;
                cout << art.descripcionArt << " \t " << art.unidadMedida << endl;
                cout << art.codArt << "\t\t\t\t$ " << subtotal << endl;
                if (descuento > 0)
                    cout << "Promo\t\t\t\t\t$ -" << descuento << endl;
                cout << "\n";
                break;
            }
        }
    }

    float totalFinal = totalSinDescuentos - totalDescuentos;

    // Totales
    cout << "SubTot. sin descuentos....:         $ " << totalSinDescuentos << endl;
    cout << "Descuentos por promociones:         $ -" << totalDescuentos << endl;
    cout << "========================================\n";
    cout << "T O T A L                            $ " << totalFinal << endl;
    cout << "========================================\n";
    cout << "Su pago con Tipo Pago:              $ " << totalFinal << endl;
    cout << "Su vuelto:                          $ 0.00\n";
    cout << "G R A C I A S  P O R  S U  C O M P R A\n";
    cout << "Para consultas: infoKotto.com.ar\n";

    fclose(stdout); // Cierra la redirección de salida
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
long GetDate(int &year, int &mes, int &dia, int &ds) {
   time_t     rawtime;
   struct tm *timeinfo;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   year = 1900 + timeinfo->tm_year;
   mes  = 1 + timeinfo->tm_mon;
   dia  = timeinfo->tm_mday;
   ds   = 1 + timeinfo->tm_wday;
   return (1900 + timeinfo->tm_year) * 10000 + (1 + timeinfo->tm_mon) * 100 + timeinfo->tm_mday;
 }
long GetTime(int &hh, int &mm, int &ss) {
   time_t     rawtime;
   struct tm *timeinfo;

   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   hh = timeinfo->tm_hour;
   mm = timeinfo->tm_min;
   ss = timeinfo->tm_sec;
   return timeinfo->tm_hour * 10000 + timeinfo->tm_min * 100 + timeinfo->tm_sec;
 }