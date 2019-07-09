//
//  mainwindow.cpp
//
//
//  Created by Yingchun Wang on 2018/9/27.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <climits>
#include <fstream>
#include <unistd.h>     /* find current location */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <string.h>     /* strcat */
#include <math.h>       /* math calc */
#include <QCloseEvent>
#include <QWidget>
#include <QPainter>
#include <QtGui>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFileDialog>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

#define square(A) ((A) * (A))

typedef int City[2];

City shortestTour[MAX_ANTS+1];
float shortestTourLength;

typedef vector<pair<int, int> > vCoordinate; //x,y

int NumberOfCities=8;
int NumberOfAnts=5;
int IterMax=5;
double Alpha=1.0;
double Beta=5.0;
double Rho=0.95;
double Q=100.0;
double MaxPheromone=2.0;

int StartCity=0;
double BestRouteLength = double (INT_MAX);

int ROUTES[MAX_ANTS+1][MAX_ANTS+1];
int GRAPH[MAX_ANTS+1][MAX_ANTS+1];
double PHEROMONES[MAX_ANTS+1][MAX_ANTS+1];
double DELTAPHEROMONES[MAX_ANTS+1][MAX_ANTS+1];
float CITIES[MAX_ANTS+1][2];
double PROBS[MAX_ANTS+1][2];
int BESTROUTE[MAX_ANTS+1];

bool is_init;
int isDisplay=1;
int isACO = 1;
int isBF = 0;
int total_no_of_input=0;

QGraphicsScene *scene;
QGraphicsView *view;

QGraphicsScene *scene1;
QGraphicsView *view1;

/*
Parameter initialization:
The number of ants is m
The number of cities is n
The quantity of the pheromone one ant released in a cycle is Q
The pheromone’s volatilization parameter is Rho
The pheromone affects ants’ path selection in a degree, this degree can be expressed by α
The affection degree of path’s length to the ants’ path selection can be expressed by β
IterMax represents the max iteration times
*/

void Read (string filename);
void initalize ();
void init_values ();
void re_init (int reset_city);
void init_CITIES (int cityi, int cityj);
void setCITYPOSITION (int city, int x, int y);
bool exists (int cityi, int cityc);
void printPHEROMONES (int iterations);
double calc_distance (int cityi, int cityj);
bool vizited (int antk, int c);
double PHI (int cityi, int cityj, int antk);
double ant_length (int antk);
int city ();
void route (int antk);
int valid (int antk); //, int iteration);
void printGRAPH ();
void printRESULTS ();
void updatePHEROMONES ();
void optimize (int Iter);
float ran1(double *idum);
double Uniforme();
void DisplayMsg(QString msg);
void CalcBestRouteLength();

float distance(City city1, City city2);                        //Find Distance between 2 city
void copy_tour(City citiesDest[], City citiesSource[]);        //Copy toured cities
void copy_City(City dest, City source);                        //Copy one city to another
void swap_cities(City city1, City city2);                      //Swap 2 city
void circ_perm(City cities[], int numCities);                  //Put all elements in pivot - before starting a new itaration
void scramble(City cities[], City *pivot, int numCities);      //Generate all combination by brute force approach
void target_function(City cities[]);                           //Get final smallest value by comparison
float tour_length(City cities[]);                              //Get total tour length

#define   IA 16807
#define   IM 2147483647
#define   AM (1.0/IM)
#define   IQ 127773
#define   IR 2836
#define   NTAB 32
#define   NDIV (1+(IM-1)/NTAB)
#define   EPS 1.2e-7
#define   RNMX (1.0-EPS)

double xpto = 21;

float ran1(double *idum)
{
    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    float temp;
    if (*idum <= 0 || !iy) {           // Initialize.
        if (-(*idum) < 1) *idum=1;     // Be sure to prevent idum = 0.
        else *idum = -(*idum);
        for (j=int (NTAB+7);j>=0;j--) {// Load the shuffle table (after 8 warm-ups).
            k=long ((*idum)/IQ);
            *idum=IA*(*idum-k*IQ)-IR*k;
            if (*idum < 0) *idum += IM;
            if (j < NTAB) iv[j] = long (*idum);
        }
        iy=iv[0];
    }
    k= long ((*idum)/IQ);             // Start here when not initializing.
    *idum=IA*(*idum-k*IQ)-IR*k;       // Compute idum=(IA*idum) % IM without over-
    if (*idum < 0) *idum += IM;       // flows by Schrage's method.
    j=int (iy/NDIV);                  // Will be in the range 0..NTAB-1.
    iy=iv[j];                         // Output previously stored value and refill the
    iv[j] = long (*idum);             // shuffle table.
    if ((temp=float (AM*iy) ) > float (RNMX) )
        return float (RNMX);          // Because users don't expect endpoint values.
    else
        return temp;
}

double Uniforme()
{
    return double (ran1(&xpto));
}

float tour_length(City cities[])
{
    int i;
    float length = 0.0;
    for(i = 0; i < total_no_of_input - 1; i++)
        length += distance(cities[i], cities[i+1]);
    length += distance(cities[total_no_of_input - 1], cities[0]);
    return length;
}

void target_function(City cities[])
{
    float length;
    length = tour_length(cities);
    if (length < shortestTourLength)
    {
        shortestTourLength = length;
        copy_tour(shortestTour, cities);
    }
}

void scramble(City cities[], City *pivot, int numCities)
{
    int i;
    City *newPivot;
    if (numCities <= 1)
    { //Scrambled! Call the target function
        target_function(cities);
        return;
    }
    for (i = 0; i < numCities; i++)
    {
        newPivot = &pivot[1];
        scramble(cities, newPivot, numCities - 1);
        circ_perm(pivot, numCities);
    }
}

void circ_perm(City cities[], int numCities)
{
    int i;
    City tmp;
    copy_City(tmp, cities[0]);
    for (i = 0; i < numCities - 1; i++)
        copy_City(cities[i], cities[i + 1]);
    copy_City(cities[numCities - 1], tmp);
}

void copy_tour(City citiesDest[], City citiesSource[])
{
    int i;
    for (i = 0; i < NumberOfCities; i++)
        copy_City(citiesDest[i], citiesSource[i]);
}

void copy_City(City dest, City source)
{
    dest[0] = source[0];
    dest[1] = source[1];
}

void swap_cities(City city1, City city2)
{
    City tmp;
    copy_City(tmp, city1);
    copy_City(city1, city2);
    copy_City(city2, tmp);
}

float distance(City city1, City city2)
{
    float result;
    result = sqrtf(float(square(city2[0] - city1[0])) +
                   float(square(city2[1] - city1[1])));
    return result;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    ui->lcdNumber_ant->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_ant->display(NumberOfAnts);
    ui->horizontalScrollBar_ant->setValue(NumberOfAnts);

    ui->lcdNumber_city->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_city->display(NumberOfCities);
    ui->horizontalScrollBar_city->setValue(NumberOfCities);

    ui->lcdNumber_iter->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_iter->display(IterMax);
    ui->horizontalScrollBar_iter->setValue(IterMax);

    ui->doubleSpinBox_alpha->setValue(Alpha);
    ui->doubleSpinBox_beta->setValue(Beta);
    ui->doubleSpinBox_rho->setValue(Rho);
    srand(unsigned (time(nullptr)));

}

void MainWindow::on_horizontalScrollBar_ant_valueChanged(int value)
{
    ui->lcdNumber_ant->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_ant->display(value);
    NumberOfAnts = value;
}


void MainWindow::on_horizontalScrollBar_city_valueChanged(int value)
{   ui->pushButton_start->setEnabled(false);
    ui->lcdNumber_city->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_city->display(value);
    NumberOfCities = value;
}

void MainWindow::on_horizontalScrollBar_iter_valueChanged(int value)
{
    ui->lcdNumber_iter->setSegmentStyle(QLCDNumber::Filled);
    ui->lcdNumber_iter->display(value);
    IterMax = value;
}

void MainWindow::on_doubleSpinBox_alpha_valueChanged(double arg1)
{
    Alpha = arg1;
}

void MainWindow::on_doubleSpinBox_beta_valueChanged(double arg1)
{
    Beta = arg1;
}

void MainWindow::on_doubleSpinBox_rho_valueChanged(double arg1)
{
    Rho = arg1;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    isDisplay = arg1;
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    isACO = arg1;
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    isBF = arg1;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "ACO",
                         tr("Are you sure to exit?\n"),
                         QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        delete scene;
        delete scene1;
        delete view;
        delete view1;
        event->accept();
    }
}

void MainWindow::on_pushButton_initial_clicked()
{
    if ((ui->checkBox_3->checkState()==Qt::Checked)&&(NumberOfCities>=11)) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Brute Force",
                    tr("The number of  cities is larger than 10\nAre you sure to perform Brute Force algorithm?\n"),
                    QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
        if (resBtn != QMessageBox::Yes) {
            return;
        }
    }
    initalize();
    is_init = true;
    DisplayMsg("Initialization done!");
    ui->pushButton_start->setEnabled(true);
}

void MainWindow::on_pushButton_start_clicked()
{
    ui->plainTextEdit_start->setPlainText("");

    re_init();

    if (isDisplay) printGRAPH ();

    if (isDisplay) printPHEROMONES (0);

    optimize (IterMax);

    printRESULTS ();
}

//user define functions
void MainWindow::init_values () {
    for(int i=0; i<NumberOfCities; i++) {
        for (int j=0; j<2; j++) {
            CITIES[i][j] = -1.0;
            PROBS[i][j]  = -1.0;
        }
        for (int j=0; j<NumberOfCities; j++) {
            GRAPH[i][j]             = 0;
            PHEROMONES[i][j]         = 0.0;
            DELTAPHEROMONES[i][j]     = 0.0;
        }
    }

    for (int i=0; i<NumberOfAnts; i++) {
        for (int j=0; j<NumberOfCities; j++) {
            ROUTES[i][j] = -1;
        }
    }

    for (int i=0; i<NumberOfCities; i++) {
        BESTROUTE[i] = -1;
    }
}

void MainWindow::re_init() {
    for(int i=0; i<NumberOfCities; i++) {
        for (int j=0; j<2; j++) {
            PROBS[i][j]  = -1.0;
        }
        for (int j=0; j<NumberOfCities; j++) {
            GRAPH[i][j]             = 0;
            PHEROMONES[i][j]         = 0.0;
            DELTAPHEROMONES[i][j]     = 0.0;
        }
    }

    for (int i=0; i<NumberOfAnts; i++) {
        for (int j=0; j<NumberOfCities; j++) {
            ROUTES[i][j] = -1;
        }
    }

    for (int i=0; i<NumberOfCities; i++) {
        BESTROUTE[i] = -1;
    }

    for (int i=0; i<NumberOfCities; i++){
        for (int j=0; j<NumberOfCities; j++) {
            if (j>i) init_CITIES(i,j);
        }
    }
}

void MainWindow::initalize () {
    init_values();

    City cities[301];
    City backupcities[301];
    vCoordinate vCity;

    for (int i=1; i<=X; i++) {
       for (int j=1; j<=Y; j++) {
          vCity.push_back(vCoordinate::value_type(i, j));
        }
     }

    int chosenpos[100];
    for(int i=0;i<100;i++) chosenpos[i] = 0;

    //create input.txt for later use, marked

    stringstream ss;
    time_t t = time(nullptr);   // get time now
    struct tm * now = localtime( & t );

    ss << NumberOfCities <<"_city_"
       << (now->tm_year + 1900) << '_'
       << (now->tm_mon + 1) << '_'
       <<  now->tm_mday << '_'
       <<  now->tm_hour << '_'
       <<  now->tm_min << '_'
       <<  now->tm_sec
       << ".txt";

    ofstream file;
    file.open (ss.str());

    for (int i=0; i<NumberOfCities; i++) {
        int choice;
        again:
        choice = rand() % (X*Y); //random create city location
        //chech if choice is chosen already
        for (int j=0; j<100; j++) {
            if (chosenpos[j] == choice) goto again;
        }
        vCoordinate::iterator it1 = vCity.begin();
        std::advance(it1, choice);
        int x=it1->first;
        int y=it1->second;
        setCITYPOSITION(i, x, y); //set position info
        cities[i][0] = x;
        cities[i][1] = y;
        backupcities[i][0] = x;
        backupcities[i][1] = y;
        char ss[80];
        sprintf(ss,"%d %d\n",x,y);
        file << ss;
        chosenpos[i] = choice;
    }
    file.close();
    //mark city dots on screen according chosenpos and vCity
    delete scene;
    delete view;
    scene = new QGraphicsScene();

    view = new QGraphicsView(scene);

    QPainterPath path;
    QFont font;
    QString pos;
    double paraX = 600.00 / X;
    double paraY = 600.00 / Y;
    for (int i=0; i<NumberOfCities; i++) {
        vCoordinate::iterator it2 = vCity.begin();
        std::advance(it2, chosenpos[i]);
        int x1=it2->first;
        int y1=it2->second;
        if (i==0)
            scene->addEllipse(x1*paraX-3, 600-(y1*paraY-3), 6, 6,QPen(QBrush(Qt::red), 1), QBrush(Qt::red));
        else
            scene->addEllipse(x1*paraX-3, 600-(y1*paraY-3), 6, 6,QPen(QBrush(Qt::black), 1), QBrush(Qt::black));
        //show city positions
        //pos.sprintf("%d(%d,%d)",i,x1,y1);
        //font.setPixelSize(13);
        //font.setBold(false);
        //font.setFamily("Calibri");
        //path.addText(x1*paraX-20, 600-(y1*paraY), font,  pos);
        //scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));
    }

    total_no_of_input=NumberOfCities;
    if (isBF) {
        //Time calculation Start
        clock_t t;
        t = clock();
        shortestTourLength = tour_length(cities);        //Generate initial value - not final
        copy_tour(shortestTour, cities);
        scramble(cities, cities, total_no_of_input);

        //show city in numbers
        pos.clear();
        pos.append("Route:");
        int startpoint = 0;
        for (int i=0; i<NumberOfCities; i++) {
            if ((backupcities[0][0]==shortestTour[i][0])&&(backupcities[0][1]==shortestTour[i][1])) {
                startpoint = i;
                break;
            }
        }
        for (int i=0; i<NumberOfCities; i++) {
            if ((startpoint+i)>=NumberOfCities) {
                startpoint = startpoint - NumberOfCities;
            }
            for (int j=0; j<NumberOfCities; j++) {
                if ((shortestTour[startpoint+i][0]==backupcities[j][0])&&(shortestTour[startpoint+i][1]==backupcities[j][1])) {
                    pos.append(QString::number(j));
                    if (i!=(NumberOfCities-1)) pos.append("->");
                    break;
                }
            }
        }
        path.addText(0, 600+80, font,  pos);
        scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //show city position sequence
        startpoint = 0;
        for (int i=0; i<NumberOfCities; i++) {
            if ((backupcities[0][0]==shortestTour[i][0])&&(backupcities[0][1]==shortestTour[i][1])) {
                startpoint = i;
                break;
            }
        }
        QString tmp2;
        pos.clear();
        pos.append("Route:");
        for (int i = 0; i < total_no_of_input; i++) {
            if ((startpoint+i)>=NumberOfCities) {
                startpoint = startpoint - NumberOfCities;
            }
            tmp2.sprintf("(%d,%d)", shortestTour[startpoint+i][0], shortestTour[startpoint+i][1]);
            pos.append(tmp2);
            if (i < total_no_of_input - 1) {
                pos.append(" , ");
            }
        }
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+60, font,  pos);
        scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //show length
        pos.sprintf("Shortest route %f", double (shortestTourLength));
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+40, font,  pos);
        scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //Time calculation End
        t = clock() - t;

        //show time
        pos.sprintf("Running time %f seconds.",(double(t)/CLOCKS_PER_SEC));
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+20, font,  pos);
        scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //show all lines
        for (int i=0; i<NumberOfCities;i++) {
            int x1,y1,x2,y2;
            x1 = int (shortestTour[i][0]*paraX);
            y1 = 600 - int (shortestTour[i][1]*paraY);
            if (i==(NumberOfCities-1)) {
                x2 = int (shortestTour[0][0]*paraX);
                y2 = 600 - int (shortestTour[0][1]*paraY);
            }
            else {
                x2 = int (shortestTour[i+1][0]*paraX);
                y2 = 600 - int (shortestTour[i+1][1]*paraY);
            }
            scene->addLine(x1,y1,x2,y2,Qt::DashLine);
        }
    }
    if (isBF) {
        view->resize(700,700);
        view->setWindowTitle("Brute Force Algorithm");
        view->show();
    }
}

void MainWindow::DisplayMsg(QString msg) {
    ui->plainTextEdit_start->appendPlainText(msg);
    QCoreApplication::processEvents();
}

void MainWindow::DisplayMsg1(QString msg) {
    ui->plainTextEdit_it->setPlainText(msg);
    QCoreApplication::processEvents();
}

void MainWindow::DisplayMsg2(QString msg) {
    ui->plainTextEdit_time->setPlainText(msg);
    QCoreApplication::processEvents();
}

void MainWindow::printGRAPH () {
    QString msg, msg2;
    msg.append("GRAPH: \n  | ");

    for( int i=0; i<NumberOfCities; i++) {
        msg2.sprintf("%02d",i);
        msg.append(msg2);
        msg.append(" ");
    }
    msg.append("\n--| ");
    for (int i=0; i<NumberOfCities; i++) {
        msg.append("-- ");
    }
    msg.append("\n");
    int count = 0;
    for (int i=0; i<NumberOfCities; i++) {
        msg2.sprintf("%02d",i);
        msg.append(msg2);
        msg.append("| ");
        for (int j=0; j<NumberOfCities; j++) {
            if(i == j) {
                msg.append(" x ");
            }
            else {
                msg.append(" ");
                msg.append(QString::number(GRAPH[i][j]));
                msg.append(" ");
            }
            if (GRAPH[i][j] == 1) {
                count++;
            }
        }
        msg.append("\n");
    }
    msg.append("\nNumber of connections: ");
    msg.append(QString::number(count));
    msg.append("\n\n");
    DisplayMsg(msg);
}

void MainWindow::printPHEROMONES (int iterations) {
    QString msg, msg2;

    msg.append(" PHEROMONES at iteration : ");
    msg.append(QString::number(iterations));
    msg.append("\n  | ");

    for (int i=0; i<NumberOfCities; i++) {
        msg2.sprintf("%5d   ", i);
        msg.append(msg2);
    }
    msg.append("\n- | ");
    for (int i=0; i<NumberOfCities; i++) {
        msg.append("--------");
    }
    msg.append("\n");
    for (int i=0; i<NumberOfCities; i++) {
        msg2.sprintf("%d | ", i);
        msg.append(msg2);
        for (int j=0; j<NumberOfCities; j++) {
            if (i == j) {
                msg2.sprintf("%5s   ","x");
                msg.append(msg2);
                continue;
            }
            if (exists(i, j)) {
                msg2.sprintf("%7.3f ", PHEROMONES[i][j]);
                msg.append(msg2);
            }
            else {
                if(PHEROMONES[i][j] == 0.0) {
                    msg2.sprintf("%5.0f   ", PHEROMONES[i][j]);
                    msg.append(msg2);
                }
                else {
                    msg2.sprintf("%7.3f ", PHEROMONES[i][j]);
                    msg.append(msg2);
                }
            }
        }
        msg.append("\n");
    }
    msg.append("\n");
    DisplayMsg(msg);
}

void MainWindow::printRESULTS () {
    QString msg;
    if (BESTROUTE[0]==-1) {
        DisplayMsg("Found nothing");
        return;
    }
    CalcBestRouteLength();
    msg.append(" Best calculated route:\n ");
    for (int i=0; i<NumberOfCities; i++) {
        msg.append(QString::number(BESTROUTE[i]));
        if (i!=(NumberOfCities-1)) msg.append("->");
    }
    DisplayMsg(msg);
    //show the same path the otherway round
    msg.clear();
    msg.append(" Or vise versa route:\n ");
    msg.append(QString::number(BESTROUTE[0]));
    msg.append("->");
    for (int i=NumberOfCities-1;i>0; i--) {
        msg.append(QString::number(BESTROUTE[i]));
        if (i!=1) msg.append("->");
    }
    DisplayMsg(msg);
    msg.sprintf(" Optimized route length:  %.3f", BestRouteLength);
    DisplayMsg(msg);
}

void MainWindow::init_CITIES (int cityi, int cityj) {
    GRAPH[cityi][cityj] = 1;
    PHEROMONES[cityi][cityj] = Uniforme() * MaxPheromone;
    GRAPH[cityj][cityi] = 1;
    PHEROMONES[cityj][cityi] = PHEROMONES[cityi][cityj];
}

void MainWindow::setCITYPOSITION (int city, int x, int y) {
    CITIES[city][0] = x;
    CITIES[city][1] = y;
}

bool MainWindow::exists (int cityi, int cityc) {
    return (GRAPH[cityi][cityc] == 1);
}

bool MainWindow::vizited (int antk, int city) {
    for (int l=0; l<NumberOfCities; l++) {
        if (ROUTES[antk][l] == -1) {
            break;
        }
        if (ROUTES[antk][l] == city) {
            return true;
        }
    }
    return false;
}

double MainWindow::PHI (int cityi, int cityj, int antk) {
    double ETAij = double (pow (1 / calc_distance (cityi, cityj), Beta) );
    double TAUij = double (pow (PHEROMONES[cityi][cityj],   Alpha) );

    double sum = 0.0;
    for (int city=0; city<NumberOfCities; city++) {
        if (exists(cityi, city)) {
            if (!vizited(antk, city)) {
                double ETA = double (pow (1 / calc_distance (cityi, city), Beta) );
                double TAU = double (pow (PHEROMONES[cityi][city],   Alpha) );
                sum += ETA * TAU;
            }
        }
    }
    return (ETAij * TAUij) / sum;
}

double MainWindow::calc_distance (int cityi, int cityj) {
    return double (
    sqrt (pow (CITIES[cityi][0] - CITIES[cityj][0], 2) +
          pow (CITIES[cityi][1] - CITIES[cityj][1], 2)));
}

double MainWindow::ant_length (int antk) {
    double sum = 0.0;
    for (int j=0; j<NumberOfCities-1; j++) {
        sum += calc_distance (ROUTES[antk][j], ROUTES[antk][j+1]);
    }
    return sum;
}

int MainWindow::valid (int antk) { //, int iteration) {
    for(int i=0; i<NumberOfCities; i++) {
        int cityi;
        int cityj;
        if (i==(NumberOfCities-1)) {
            cityi = ROUTES[antk][i];
            cityj = ROUTES[antk][0];
        }
        else{
            cityi = ROUTES[antk][i];
            cityj = ROUTES[antk][i+1];
        }
        if (cityi < 0 || cityj < 0) {
            return -1;
        }
        if (!exists(cityi, cityj)) {
            return -2;
        }
        for (int j=0; j<i-1; j++) {
            if (ROUTES[antk][i] == ROUTES[antk][j]) {
                return -3;
            }
        }
    }
    return 0;
}

void MainWindow::CalcBestRouteLength() {
    BestRouteLength = 0;
    for (int i=0; i<NumberOfCities; i++) {
        if (i==(NumberOfCities-1)) {
            BestRouteLength += calc_distance (BESTROUTE[i], StartCity);
        }
        else {
            BestRouteLength += calc_distance (BESTROUTE[i], BESTROUTE[i+1]);
        }
    }

}

void MainWindow::updatePHEROMONES () {
    for (int k=0; k<NumberOfAnts; k++) {
        double rlength = ant_length(k);
        int cityi; //
        int cityj; //
        for (int r=0; r<NumberOfCities; r++) {
            if (r==(NumberOfCities-1)) {
                cityi = ROUTES[k][r];
                cityj = ROUTES[k][0];
            }
            else{
                cityi = ROUTES[k][r];
                cityj = ROUTES[k][r+1];
            }
            DELTAPHEROMONES[cityi][cityj] += Q / rlength;
            DELTAPHEROMONES[cityj][cityi] += Q / rlength;
        }
    }
    for (int i=0; i<NumberOfCities; i++) {
        for (int j=0; j<NumberOfCities; j++) {
            PHEROMONES[i][j] = (1 - Rho) * PHEROMONES[i][j] + DELTAPHEROMONES[i][j];
            DELTAPHEROMONES[i][j] = 0.0;
        }
    }
}

int MainWindow::city () {
    double xi = Uniforme();
    int i = 0;
    double sum = PROBS[i][0];
    while (sum < xi) {
        i++;
        sum += PROBS[i][0];
    }
    return int (PROBS[i][1]);
}

void MainWindow::route (int antk) {
    ROUTES[antk][0] = StartCity;
    for (int i=0; i<NumberOfCities-1; i++) {
        int cityi = ROUTES[antk][i];
        int count = 0;
        for (int city=0; city<NumberOfCities; city++) {
            if (cityi == city) {
                continue;
            }
            if (exists (cityi, city)) {
                if (!vizited (antk, city)) {
                    PROBS[count][0] = PHI (cityi, city, antk);
                    PROBS[count][1] = double (city);
                    count++;
                }
            }
        }
        // deadlock
        if (0 == count) {
            return;
        }

        ROUTES[antk][i+1] = city();
    }
}

void MainWindow::optimize (int Iter) {
    QString msg;
    DisplayMsg("Start searching, please wait...");
    DisplayMsg1("");
    clock_t starttime = clock();
    for (int iterations=1; iterations<=Iter; iterations++) {
        if (isDisplay) {
            msg.sprintf("Iteration %d started!", iterations);
            DisplayMsg1(msg);
        }
        for (int k=0; k<NumberOfAnts; k++) {
            if (isDisplay) {
                msg.sprintf("  : Ant %d is on the way!", k);
                DisplayMsg(msg);
            }
            //while (0 != valid(k, iterations)) {
            while (0 != valid(k)) {
                if (isDisplay) {
                    msg.sprintf("  : Ant %d is released again!", k);
                    DisplayMsg(msg);
                 }
                for (int i=0; i<NumberOfCities; i++) {
                    ROUTES[k][i] = -1;
                }
                //find route
                route(k);
            }
            if (isDisplay) {
                msg.clear();
                msg.append("Ant routes at iteration ");
                msg.append(QString::number(iterations));
                msg.append(":\n");
                for (int i=0; i<NumberOfCities; i++) {
                    msg.append(QString::number(ROUTES[k][i]));
                    msg.append(" ");
                }
                msg.append("\n  :: route done\n");
                DisplayMsg(msg);
            }
            
            //find if it's the best route length that ant k just produced
            double rlength = ant_length(k);

            if (rlength < BestRouteLength) {
                BestRouteLength = rlength;
                for (int i=0; i<NumberOfCities; i++) {
                    BESTROUTE[i] = ROUTES[k][i];
                }
            }

            if (isDisplay) {
                msg.sprintf("  : Ant %d has ended!", k);
                DisplayMsg(msg);
            }
        }
        updatePHEROMONES ();
        if (isDisplay) {
            msg.sprintf("updating PHEROMONES . . .");
            DisplayMsg(msg);
            msg.sprintf("update PHEROMONES done!\ndisplay PHEROMNES...");
            DisplayMsg(msg);

            printPHEROMONES (iterations);
        }

        for (int i=0; i<NumberOfAnts; i++) {
            for (int j=0; j<NumberOfCities; j++) {
                ROUTES[i][j] = -1;
            }
        }

        if (isDisplay) {
            msg.sprintf("Iteration %d has ended!\n", iterations);
            DisplayMsg(msg);
        }
    }
    //Time calculation End
    clock_t endtime = clock();
    //show time
    QString msg2;
    msg2.sprintf("Running time %f seconds.",(double(endtime-starttime)/CLOCKS_PER_SEC));
    DisplayMsg2(msg2);
    //show ACO
    if (isACO) {
        // show city locations
        delete scene1;
        delete view1;
        scene1 = new QGraphicsScene;
        view1 = new QGraphicsView(scene1);
        QPainterPath path;
        QFont font;
        QString pos;
        //city as dots
        double paraX = 600.00 / X;
        double paraY = 600.00 / Y;
        for (int i=0; i<NumberOfCities;i++) {
            int x = int (CITIES[i][0]);
            int y = int (CITIES[i][1]);
            if (i==0)
                scene1->addEllipse(x*paraX-3, 600-(y*paraY-3), 6, 6,QPen(QBrush(Qt::red), 1), QBrush(Qt::red));
            else
                scene1->addEllipse(x*paraX-3, 600-(y*paraY-3), 6, 6,QPen(QBrush(Qt::black), 1), QBrush(Qt::black));
            //show city positions
            //pos.sprintf("%d(%d,%d)",i,x,y);
            //font.setPixelSize(13);
            //font.setBold(false);
            //font.setFamily("Calibri");
            //path.addText(x*paraX-20, 600-y*paraY, font,  pos);
            //scene1->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));
        }
        //draw lines according BESTROUTE[i] and CITIES
        for (int i=0; i<NumberOfCities;i++) {
            int x1, y1, x2, y2;
            x1 = int (CITIES[BESTROUTE[i]][0]);
            y1 = int (CITIES[BESTROUTE[i]][1]);
            if (i==(NumberOfCities-1)) {
                x2 = int (CITIES[BESTROUTE[0]][0]);
                y2 = int (CITIES[BESTROUTE[0]][1]);
            }
            else {
                x2 = int (CITIES[BESTROUTE[i+1]][0]);
                y2 = int (CITIES[BESTROUTE[i+1]][1]);
            }
            scene1->addLine(x1*paraX, 600 - y1*paraY, x2*paraX, 600 - y2*paraY, Qt::DashLine);
        }
        //running time
        pos.sprintf("Running time %f seconds.",(double(endtime-starttime)/CLOCKS_PER_SEC));
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+20, font,  pos);
        scene1->addPath(path, QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //calc length
        CalcBestRouteLength();
        //path length
        pos.sprintf("Optimized route length: %.3f", BestRouteLength);
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+40, font,  pos);
        scene1->addPath(path, QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //path coor
        pos.clear();
        pos.append("Route: ");
        QString msg3;
        for (int i=0; i<NumberOfCities; i++) {
            msg3.sprintf("(%d,%d) ",int (CITIES[BESTROUTE[i]][0]), int (CITIES[BESTROUTE[i]][1]));
            pos.append(msg3);
        }
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+60, font,  pos);
        scene1->addPath(path, QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //path number
        pos.clear();
        pos.append("Route: ");
        for (int i=0; i < NumberOfCities; i++) {
            pos.append(QString::number(BESTROUTE[i]));
            if (i!=(NumberOfCities-1)) pos.append("->");
        }
        font.setPixelSize(13);
        font.setBold(false);
        font.setFamily("Calibri");
        path.addText(0, 600+80, font,  pos);
        scene1->addPath(path, QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

        //show
        view1->resize(700,700);
        view1->setWindowTitle("Ant Colony Optimization Algorithm");
        view1->show();
    }
}

void MainWindow::Read (string filename)
{
    FILE *fp;
    char buf[100];
    fp = fopen(filename.c_str(), "r");
    int cityno=0;
    int i=0;
    fgets(buf, sizeof(buf), fp);
    while(fgets(buf, sizeof(buf), fp)!=NULL)
    {   char ss[30];
        char ss1[30];
        char ss2[30];
        int n;
        #define VFMT " %29[^,\n\t]"
        sscanf(buf, VFMT "," VFMT "," VFMT "%n", ss, ss1, ss2, &n);
        CITIES[i][0]=atof(ss1);
        CITIES[i][1]=atof(ss2);
        cout <<i<< " : " <<CITIES[i][0] <<" - " <<CITIES[i][1] <<endl;
        i++;
        cityno++;
    }
    fclose(fp);
    //after read successful, change the system
    ui->horizontalScrollBar_city->setValue(cityno);
    DisplayMsg("City map is loaded from TXT file!");
    ui->pushButton_start->setEnabled(true);
}

void MainWindow::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open city map"), "/", tr("City Files (*.txt)"));
    if (!fileName.isEmpty()) {
        //init ?
        Read(fileName.toStdString());
        //load screen if <11
        if (NumberOfCities<11) {
            LoadMaps();
        }
    }
}

void MainWindow::LoadMaps()
{
    re_init();

    City cities[301];
    City backupcities[301];
 //   vCoordinate vCity;

    //mark city dots on screen according chosenpos and vCity
    delete scene;
    delete view;
    scene = new QGraphicsScene();

    view = new QGraphicsView(scene);

    QPainterPath path;
    QFont font;
    QString pos;
    double paraX = 600.00 / X;
    double paraY = 600.00 / Y;

//    for (int i=0; i<NumberOfCities; i++) {
//        //qDebug() <<CITIES[i][0]<<"-"<<CITIES[i][1];
//        cities[i][0] = CITIES[i][0];
//        cities[i][1] = CITIES[i][1];
//        backupcities[i][0] = CITIES[i][0];
//        backupcities[i][1] = CITIES[i][1];
//    }

    //mark city as dots
    for (int i=0; i<NumberOfCities;i++) {
        int x = int (CITIES[i][0]);
        int y = int (CITIES[i][1]);
        if (i==0)
            scene->addEllipse(x*paraX-3, 600-(y*paraY-3), 6, 6,QPen(QBrush(Qt::red), 1), QBrush(Qt::red));
        else
            scene->addEllipse(x*paraX-3, 600-(y*paraY-3), 6, 6,QPen(QBrush(Qt::black), 1), QBrush(Qt::black));
        // show city location's
        //pos.sprintf("%d(%d,%d)",i,x,y);
        //font.setPixelSize(13);
        //font.setBold(false);
        //font.setFamily("Calibri");
        //path.addText(x*paraX-20, 600-y*paraY, font,  pos);
        //scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));
    }

    total_no_of_input=NumberOfCities;
    //Time calculation Start
    clock_t t;
    t = clock();
    shortestTourLength = tour_length(cities);        //Generate initial value - not final
    copy_tour(shortestTour, cities);
    scramble(cities, cities, total_no_of_input);

    //show city in numbers
    pos.clear();
    pos.append("Route:");
    int startpoint = 0;
    for (int i=0; i<NumberOfCities; i++) {
        if ((backupcities[0][0]==shortestTour[i][0])&&(backupcities[0][1]==shortestTour[i][1])) {
            startpoint = i;
            break;
        }
    }
    for (int i=0; i<NumberOfCities; i++) {
        if ((startpoint+i)>=NumberOfCities) {
            startpoint = startpoint - NumberOfCities;
        }
        for (int j=0; j<NumberOfCities; j++) {
            if ((shortestTour[startpoint+i][0]==backupcities[j][0])&&(shortestTour[startpoint+i][1]==backupcities[j][1])) {
                pos.append(QString::number(j));
                if (i!=(NumberOfCities-1)) pos.append("->");
                break;
            }
        }
    }
    path.addText(0, 600+80, font,  pos);
    scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

    //show city position sequence
    startpoint = 0;
    for (int i=0; i<NumberOfCities; i++) {
        if ((backupcities[0][0]==shortestTour[i][0])&&(backupcities[0][1]==shortestTour[i][1])) {
            startpoint = i;
            break;
        }
    }
    QString tmp2;
    pos.clear();
    pos.append("Route:");
    for (int i = 0; i < total_no_of_input; i++) {
        if ((startpoint+i)>=NumberOfCities) {
            startpoint = startpoint - NumberOfCities;
        }
        tmp2.sprintf("(%d,%d)", shortestTour[startpoint+i][0], shortestTour[startpoint+i][1]);
        pos.append(tmp2);
        if (i < total_no_of_input - 1) {
            pos.append(" , ");
        }
    }
    font.setPixelSize(13);
    font.setBold(false);
    font.setFamily("Calibri");
    path.addText(0, 600+60, font,  pos);
    scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

    //show length
    pos.sprintf("Shortest route %f", double (shortestTourLength));
    font.setPixelSize(13);
    font.setBold(false);
    font.setFamily("Calibri");
    path.addText(0, 600+40, font,  pos);
    scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

    //Time calculation End
    t = clock() - t;

    //show time
    pos.sprintf("Running time %f seconds.",(double(t)/CLOCKS_PER_SEC));
    font.setPixelSize(13);
    font.setBold(false);
    font.setFamily("Calibri");
    path.addText(0, 600+20, font,  pos);
    scene->addPath(path,QPen(QBrush(Qt::black), 2), QBrush(Qt::black));

    //show all lines
    for (int i=0; i<NumberOfCities;i++) {
        int x1,y1,x2,y2;
        x1 = int (shortestTour[i][0]*paraX);
        y1 = 600 - int (shortestTour[i][1]*paraY);
        if (i==(NumberOfCities-1)) {
            x2 = int (shortestTour[0][0]*paraX);
            y2 = 600 - int (shortestTour[0][1]*paraY);
        }
        else {
            x2 = int (shortestTour[i+1][0]*paraX);
            y2 = 600 - int (shortestTour[i+1][1]*paraY);
        }
        scene->addLine(x1,y1,x2,y2,Qt::DashLine);
    }
    view->resize(700,700);
    view->setWindowTitle("Brute Force Algorithm");
    view->show();
}
