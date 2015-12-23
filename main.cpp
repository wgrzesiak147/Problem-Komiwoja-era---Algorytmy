#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include "adjacencymatrix.h"
#include "route.h"
#include "ialgorithm.h"
#include "geneticalgorithm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    //----------------------------------------------------------------------------------------------------------------------
    //Test macierzy
    //AdjacencyMatrix(unsigned int size,QObject *parent = 0);
    //pierwszy parametr oznacza liczbę wierzchołków grafu, drugi zostawiacie pusty
    AdjacencyMatrix * matrix = new AdjacencyMatrix(3); //Tworzenie macierzy

    //bool addEdge(unsigned int startNode, unsigned int destinationNode, unsigned int distance, unsigned int time);
    //Argumenty funkcji kolejno: wierzchołek stratowy, wierzchołek docelowy, koszt przejścia pomiędzy wierzchołkami, czas przejścia między wierzchołkami (jeszcze nie jest użwany)
    qDebug() << "addEdge:" << matrix->addEdge(0,1,10,20); //Dodawanie krawędzi grafu
    qDebug() << "addEdge:" << matrix->addEdge(0,2,20,20); //Graf powinien być pełny - każda możliwa trasa powinna być dodana
    qDebug() << "addEdge:" << matrix->addEdge(1,0,30,20); //Oprócz tras które zaczynają się i kończą w tym samym wierzchołku
    qDebug() << "addEdge:" << matrix->addEdge(1,2,40,20); //Jeżeli uda się dodać krawędź zwraca true, jeśli nie to false
    qDebug() << "addEdge:" << matrix->addEdge(2,0,50,20); //Tutaj jest przykład dla macierzy 3 na 3
    qDebug() << "addEdge:" << matrix->addEdge(2,1,60,20); //Później dorobi się jakieś narzędzie do importu albo wprowadzania tej macierzy graficznie


    qDebug() << "isFull:" << matrix->isFull(); //Ta funkcja służy do sprawdzania czy macierz jest wypełniona prawidłowo tzn czy jest pełna

    qDebug() << "setTimeSlot:" << matrix->setTimeSlot(0,0,20); // Ta funkcja ustawia przedział czasowy dla danego węzła
    qDebug() << "setTimeSlot:" << matrix->setTimeSlot(1,25,30); // Czas liczymy w minutach od 0. 0 to start podróży komiwojażera
    qDebug() << "setTimeSlot:" << matrix->setTimeSlot(2,30,40); // Przedział czasowy podajemy w minutach od startu podróży

    Route route(3,matrix); //Tworzenie trasy Argumenty: ilość miejsc, wskaźnik do macierzy która przechowuje koszty (AdjacencyMatrix*)
    //ilość miejsc w trasie i liczba wierzchołków grafu muszą się zgadzać inaczej pewnie aplikacja się wywali

    route.insertNode(0,0); //Dodawanie kolejnych punktów na trasie
    route.insertNode(1,1); //Funkcja sprawdza czy wierzchołek który dodajecie już znajduje się na trasie
    route.insertNode(2,2); //Jeżeli się znajduje to wyświetli ostrzeżenie i doda wierzchołek
    //Argumenty: pozycja na trasie, numer wierzchołka
    //Poprawność trasy nie jest sprawdzana więc jak coś będzie nie tak to mogą się pojawiać dziwne błędy

    //route.clear(); //Czyszczenie trasy
    route.printRoute(); //Wyświetlanie trasy
    qDebug() << "getCost(WITHOUT_TIME):" << route.getCost(Route::WITHOUT_TIME); //Funkcja do sprawdzania kosztu trasy
    qDebug() << "getCost(WITH_TIME):" << route.getCost(Route::WITH_TIME); //Funkcja liczy koszt z uwzględnieniem przedziałów czasowych
    //Docelowo będzie obsługiwała dwa tryby liczenia trasy WITH_TIME i WITHOUT_TIME. Teraz działa tylko ten drugi.
    //Można używać bez agrumentu, wtedy jest liczony koszt bez uwzględniania czasu

    //Dany element trasy możecie sprawdzić funkcją
    //int at(unsigned int position)

    Route route2(3,matrix);
    route2.makeRandomRoute(0); //Losowanie trasy. Trzeba podać wierzchołek startowy. Brak zabezpieczenia przed podaniem wierzchołka przekraczającego zakres.
    route2.printRoute();
    qDebug() << "getCost(WITHOUT_TIME):" << route2.getCost(Route::WITHOUT_TIME); //Funkcja do sprawdzania kosztu trasy
    qDebug() << "getCost(WITH_TIME):" << route2.getCost(Route::WITH_TIME); //Funkcja liczy koszt z uwzględnieniem przedziałów czasowych



    //Test macierzy

    //Moje testy, nie zwarcać na nie uwagi - KW ;)
//    AdjacencyMatrix * adjMtrx = new AdjacencyMatrix(10);
//    qDebug() << "Test1:";

//    qDebug() << "Test2:";

//    qDebug() << "Test3:";
//    GeneticAlgorithm * genetic = new GeneticAlgorithm();
//    qDebug() << "Test4:";

//    for(int i = 0; i < 100000; i++)
//    {
//        Route * testRoute1 = new Route(10,adjMtrx);
//        Route * testRoute2 = new Route(10,adjMtrx);
//        testRoute1->makeRandomRoute(0);
//        testRoute2->makeRandomRoute(0);

//        qDebug() << "Route1:";
//        testRoute1->printRoute();
//        qDebug() << "Route2:";
//        testRoute2->printRoute();

//        qDebug() << "Result:";
//        Route * resultOfCrossbreed = genetic->crossbreedRoutes(testRoute1,testRoute2);
//        resultOfCrossbreed->printRoute();
//    }

//    qDebug() << "Koniec";

    //Moje testy, nie zwarcać na nie uwagi - KW ;)
    return a.exec();
}
