#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsItem>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QtGui>
#include <QGraphicsView>
#include <string.h>

#define X 8000
#define Y 8000

#define MAX_ANTS 200000
#define MAX_CITIES 200000

extern int NumberOfCities;
extern int NumberOfAnts;
extern int IterMax;
extern double Alpha;
extern double Beta;
extern double Rho;
extern double Q;
extern double MaxPheromone;
extern int StartCity;
extern int isDisplay;
extern int isACO;
extern int isBF;
extern double BestRouteLength;

extern int ROUTES[MAX_ANTS+1][MAX_ANTS+1];
extern int GRAPH[MAX_ANTS+1][MAX_ANTS+1];
extern double PHEROMONES[MAX_ANTS+1][MAX_ANTS+1];
extern double DELTAPHEROMONES[MAX_ANTS+1][MAX_ANTS+1];

extern float CITIES[MAX_ANTS+1][2];
extern double PROBS[MAX_ANTS+1][2];
extern int BESTROUTE[MAX_ANTS+1];

extern bool is_init;
extern double xpto;
extern float shortestTourLength;
extern int total_no_of_input;

extern QGraphicsScene *scene;
extern QGraphicsView *view;

extern QGraphicsScene *scene1;
extern QGraphicsView *view1;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initalize ();
    void init_values ();
    void re_init ();
    void init_CITIES (int cityi, int cityj);
    void setCITYPOSITION (int city, int x, int y);
    bool exists (int cityi, int cityc);
    void printPHEROMONES (int iterations);
    double calc_distance (int cityi, int cityj);
    bool vizited (int antk, int c);
    double PHI (int cityi, int cityj, int antk);
    double ant_length (int antk);
    void Read (std::string filename);
    int city ();
    void route (int antk);
    int valid (int antk); //, int iteration);
    void printGRAPH ();
    void printRESULTS ();
    void updatePHEROMONES ();
    void optimize (int Iter);
    void CalcBestRouteLength();
    void LoadMaps();
    void DisplayMsg(QString msg);
    void DisplayMsg1(QString msg);
    void DisplayMsg2(QString msg);
protected:
      void showEvent(QShowEvent *ev);

private slots:

    void on_horizontalScrollBar_ant_valueChanged(int value);

    void on_horizontalScrollBar_city_valueChanged(int value);

    void on_horizontalScrollBar_iter_valueChanged(int value);

    void on_doubleSpinBox_alpha_valueChanged(double arg1);

    void on_doubleSpinBox_beta_valueChanged(double arg1);

    void on_doubleSpinBox_rho_valueChanged(double arg1);

    void on_pushButton_start_clicked();

    void on_pushButton_initial_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void closeEvent(QCloseEvent *event);


    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
