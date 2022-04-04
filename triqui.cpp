#include <iostream>
using namespace std;

void print();
void turno_person();
void turno_pc();
int prevent_p_win();
int possibly_win();
bool evaluate_winner();

char tablero[3][3] = {' ', ' ', ' ',
                      ' ', ' ', ' ',
                      ' ', ' ', ' '};

int main(int argc, char const *argv[])
{
    char aux;
    bool end_g;  //End_g : end of the game (fin del juego)
    do
    {
        turno_pc();
        end_g = evaluate_winner();
        if (end_g == false)
            turno_person();

    } while(end_g == false);
    system("color 0C");
    cout<<"\n\nDesea observar como quedo finalmente el tablero?";
    cout<<"\n\t1. Si";
    cout<<"\n\t2. No";
    cout<<"\nDigita tu opcion: ";
    cin>>aux;
    cout<<endl<<endl;
    switch (aux)
    {
    case '1':
        cout<<"\nFinalmente el tablero quedo asi: \n\n";
        print();
        break;
    case '2': cout<<"\nVale, ningun problema :D"; break;
    default: cout<<"\nDigito incorrecto."; break;
    }
    cout<<"\n\n\t---\tGRACIAS POR JUGAR. --- :D\n\t---\tMAS SUERTE LA PROXIMA VEZ! --- :D\n\n\n";
    return 0;
}

void print(){
    cout<<"     A      B      C  \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {            
            if (j == 0)
                cout<<i+1;
            
            cout<<"  [ "<<tablero[i][j]<<" ]";
        }
        cout<<endl;
    }
    cout<<"\nRecuerde que cada jugador esta representado asi en el tablero:";
    cout<<"\n\t - Xavi (PC): '"<<char(2)<<"'";
    cout<<"\n\t - Jugador: '"<<char(3)<<"'"<<endl;
}

void turno_person(){
    char x, y;
    int posx, posy;
    system("color 0E"); 
    cout<<"\n\n\t------- AHORA ES SU TURNO -------\n";
    do
    {
        cout<<"\nEn que posicion desea colocar su '"<<char(3)<<"'";
        cout<<"\nDigite la fila en la que que desea colocarlo (1 - 3): ";
        cin>>x;
        switch (x)
        {
            case '1': posx = 0; break;
            case '2': posx = 1; break;
            case '3': posx = 2; break;
            default: cout<<"\nDigito incorrecto, a continuacion debera intentarlo de nuevo.\n"; break;
        }
        cout<<"\nDigite la fila en la que que desea colocarlo (A - C): ";
        cin>>y;
        switch (y)
        {
            case 'A': posy = 0; break;
            case 'B': posy = 1; break;
            case 'C': posy = 2; break;
            default: cout<<"\nDigito incorrecto, a continuacion debera intentarlo de nuevo.\n"; break;
        }
    } while (tablero[posx][posy] != ' ');

    tablero[posx][posy] = 3;

    system("cls");
    cout<<"\nSu turno ha sido llevado a cabo con exito,\n\n";
    cout<<"Ahora el tablero de juego esta asi: \n\n";
    print(); 
    cout<<endl; system("pause");
}

void turno_pc(){
    system("cls");
    system("color 0A"); 
    int cont=0, aux, aux2;
    bool done=false;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ')
                cont++;
    
    cout<<"\n\n\t------- TURNO DE XAVI -------\n";
    do
    {  
        aux = possibly_win();
        if (aux == 1) //Primero se evalua si es posible ganar ya que si ya puede ganar con un solo movimiento no es necesario evitar que el rival gane en su proximo turno ya que no habra proximo xd
            aux2 = prevent_p_win();
        
        if (aux == 1 && aux2 == 1) // 1 Significa que no puso nada en la anterior funcion ya que no habia peligro de perder en el siguiente turno o posibilidad de ganar inmediatamente, 0 que sí lo hizo y por tanto ya realizo su turno.
        {
            if (cont == 9){ //Significa que es el primer turno.
                tablero[2][0] = 2;
                done = true;
            } else if(cont == 7){
                if (tablero[0][0] == 3 || tablero[1][1] == 3 || tablero[2][2] == 3)
                    tablero[0][2] = 2;
                else if(tablero[1][0] == 3)
                    tablero[2][2] = 2;
                else
                    tablero[0][0] = 2;
                done = true;
            } else if(cont == 5){
                if (tablero[1][0] == 3 && tablero[2][1] == ' ' && tablero[2][2] == ' ')
                    tablero[2][2] = 2;

                else if (tablero[2][1] == 3 && tablero[0][2] == ' ')
                    tablero[0][2] = 2;
                
                else if (tablero[1][0] == 3 && tablero[2][1] == 3)
                    tablero[0][2] = 2;
                    
                else
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            if (tablero[i][j] == ' '){
                                tablero[i][j] = 2;
                                i=3; j=3;
                            }
                     
                done = true;
            } else // No puse la posibilidad especifica del cuarto turno del pc (cont == 3), ya que con las funciones que se desarrollaron arriba ya es suficiente; a este punto el tablero ya esta casi lleno entonces, si ninguno tiene la posibilidad de ganar, que simplemente lo coloque en cualquier posicion.
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        if (tablero[i][j] == ' '){
                            tablero[i][j] = 2;
                            j=3; i=3;
                            done = true;
                        }
        } else
            done = true;        
                    
    } while (done == false);
    cout<<"\n\n Ya se ha llevado a cabo el turno de Xavi (PC). \n\n";
    cout<<"Ahora el tablero de juego esta asi: \n\n";
    print();
    cout<<endl; system("pause");
}

int prevent_p_win(){ 
    // La tercera fila y la primera columna, al igual que la diagonal de inf a sup NO se evaluan ya que es imposible que el rival vaya a ganar colocando un triqui ahi, ya que desde el inicio de la partida hay una "ficha" del pc ahi (pos 2,0).
    //PRIMERA FILA
    if (tablero[0][0] == 3 && tablero[0][1] == 3 && tablero[0][2] == ' ')
        tablero[0][2] = 2;
    else if (tablero[0][0] == 3 && tablero[0][2] == 3 && tablero[0][1] == ' ')
        tablero[0][1] = 2;
    else if (tablero[0][1] == 3 && tablero[0][2] == 3 && tablero[0][0] == ' ')
        tablero[0][0] = 2;

    //SEGUNDA FILA
    else if(tablero[1][0] == 3 && tablero[1][1] == 3 && tablero[1][2] == ' ')
        tablero[1][2] = 2;
    else if (tablero[1][0] == 3 && tablero[1][2] == 3 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if (tablero[1][1] == 3 && tablero[1][2] == 3 && tablero[1][0] == ' ')
        tablero[1][0] = 2;


    //SEGUNDA COLUMNA
    else if (tablero[0][1] == 3 && tablero[1][1] == 3 && tablero[2][1] == ' ')
        tablero[2][1] = 2;
    else if (tablero[0][1] == 3 && tablero[2][1] == 3 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if (tablero[1][1] == 3 && tablero[2][1] == 3 && tablero[0][1] == ' ')
        tablero[0][1] = 2;

    //TERCERA COLUMNA
    else if (tablero[0][2] == 3 && tablero[1][2] == 3 && tablero[2][2] == ' ')
        tablero[2][2] = 2;
    else if (tablero[0][2] == 3 && tablero[2][2] == 3 && tablero[1][2] == ' ')
        tablero[1][2] = 2;
    else if (tablero[1][2] == 3 && tablero[2][2] == 3 && tablero[0][2] == ' ')
        tablero[0][2] = 2;


    //DIAGONAL  SUP-INF
    else if(tablero[0][0] == 3 && tablero[1][1] == 3 && tablero[2][2] == ' ')
        tablero[2][2] = 2;
    else if(tablero[0][0] == 3 && tablero[2][2] == 3 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if(tablero[1][1] == 3 && tablero[2][2] == 3 && tablero[0][0] == ' ')
        tablero[0][0] = 2;
    
    //Si no se cumplio ninguna de las anteriores significa el rival aun no tuvo posibilidades de ganar en el siguiente turno.
    else
        return EXIT_FAILURE; //No fue necesario colocar en ninguna posicion ya que no tenia peligro inmeiato de perder.
    
    return EXIT_SUCCESS; //Sí tuvo que colocar su turno en alguna posicion especifica ya que de lo contrario se iba a perder. 
}

int possibly_win(){
    //PRIMERA FILA
    if (tablero[0][0] == 2 && tablero[0][1] == 2 && tablero[0][2] == ' ')
        tablero[0][2] = 2;
    else if (tablero[0][0] == 2 && tablero[0][2] == 2 && tablero[0][1] == ' ')
        tablero[0][1] = 2;
    else if (tablero[0][1] == 2 && tablero[0][2] == 2 && tablero[0][0] == ' ')
        tablero[0][0] = 2;

    //SEGUNDA FILA
    else if(tablero[1][0] == 2 && tablero[1][1] == 2 && tablero[1][2] == ' ')
        tablero[1][2] = 2;
    else if (tablero[1][0] == 2 && tablero[1][2] == 2 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if (tablero[1][1] == 2 && tablero[1][2] == 2 && tablero[1][0] == ' ')
        tablero[1][0] = 2;

    
    //SEGUNDA COLUMNA
    else if (tablero[0][1] == 2 && tablero[1][1] == 2 && tablero[2][1] == ' ')
        tablero[2][1] = 2;
    else if (tablero[0][1] == 2 && tablero[2][1] == 2 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if (tablero[1][1] == 2 && tablero[2][1] == 2 && tablero[0][1] == ' ')
        tablero[0][1] = 2;

    //TERCERA COLUMNA
    else if (tablero[0][2] == 2 && tablero[1][2] == 2 && tablero[2][2] == ' ')
        tablero[2][2] = 2;
    else if (tablero[0][2] == 2 && tablero[2][2] == 2 && tablero[1][2] == ' ')
        tablero[1][2] = 2;
    else if (tablero[1][2] == 2 && tablero[2][2] == 2 && tablero[0][2] == ' ')
        tablero[0][2] = 2;


    //DIAGONAL  SUP-INF
    else if(tablero[0][0] == 2 && tablero[1][1] == 2 && tablero[2][2] == ' ')
        tablero[2][2] = 2;
    else if(tablero[0][0] == 2 && tablero[2][2] == 2 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    else if(tablero[1][1] == 2 && tablero[2][2] == 2 && tablero[0][0] == ' ')
        tablero[0][0] = 2;

    //Estas solo se evaluan 2 de las 3 casillas por "opcion de triqui" ya que la casilla 2,0 ya esta ocupada desde el inicio.
    //PRIMERA COLUMNA
    else if(tablero[1][0] == 2 && tablero[2][0] == 2 && tablero[0][0] == ' ')
        tablero[0][0] = 2;
    else if(tablero[0][0] == 2 && tablero[2][0] == 2 && tablero[1][0] == ' ')
        tablero[1][0] = 2;

    //ULTIMA FILA
    else if(tablero[2][0] == 2 && tablero[2][1] == 2 && tablero[2][2] == ' ')
        tablero[2][2] = 2;
    else if(tablero[2][0] == 2 && tablero[2][2] == 2 && tablero[2][1] == ' ')
        tablero[2][1] = 2;

    //DIAGONAL INF-SUP
    else if(tablero[2][0] == 2 && tablero[1][1] == 2 && tablero[0][2] == ' ')
        tablero[0][2] = 2;
    else if(tablero[2][0] == 2 && tablero[0][2] == 2 && tablero[1][1] == ' ')
        tablero[1][1] = 2;
    
    //Si ninguna se cumplio significa que aun no hay una posibilidad clara de ganar.
    else
        return EXIT_FAILURE; //No fue necesario colocar en ninguna posicion ya que no tenia posibilidad inmediata de ganar.
    
    return EXIT_SUCCESS; //Sí coloco su turno en alguna posicion especifica ya que podia ganar de una vez. 
}

bool evaluate_winner(){
    int cont=0;
    if ((tablero[0][0] == 2 && tablero[1][0] == 2 && tablero && tablero[2][0] == 2) ||
    (tablero[0][1] == 2 && tablero[1][1] == 2 && tablero && tablero[2][1] == 2) ||
    (tablero[0][2] == 2 && tablero[1][2] == 2 && tablero && tablero[2][2] == 2) ||
    (tablero[0][0] == 2 && tablero[0][1] == 2 && tablero && tablero[0][2] == 2) ||
    (tablero[1][0] == 2 && tablero[1][1] == 2 && tablero && tablero[1][2] == 2) ||
    (tablero[2][0] == 2 && tablero[2][1] == 2 && tablero && tablero[2][2] == 2) ||
    (tablero[0][0] == 2 && tablero[1][1] == 2 && tablero && tablero[2][2] == 2) ||
    (tablero[0][2] == 2 && tablero[1][1] == 2 && tablero && tablero[2][0] == 2))
    {
        system("cls");
        cout<<"\n**************************************************\n";
        cout<<"\n LA XAVINETA LO HA VUELTO A HACER, HA GANADO XAVI!\n";
        cout<<"\n**************************************************\n";
        return true;
    } 
    else{
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (tablero[i][j] != ' ')
                    cont++;

        if (cont == 9)
        {
            system("cls");
            cout<<"\n\t**********************************\n";
            cout<<"\n\t    SE HA PRESENTADO UN EMPATE.\n";
            cout<<"\n\t**********************************\n";
            return true;
        } else
            return false;
    }
}
