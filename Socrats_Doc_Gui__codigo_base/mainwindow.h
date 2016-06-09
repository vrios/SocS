#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "world.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void paintEvent(QPaintEvent*);
    
private slots:
    void on_pushButtonGeraMundo_clicked();
    void on_pushButtonRodaUm_clicked();
    void on_pushButtonRodaIniciar_clicked();
    void on_actionCarregar_estado_triggered();

  //  void on_pushButtonMov_Clust_clicked();

    void on_radioButtonGrupal_toggled(bool checked);

    void on_radioButtonIndividual_toggled(bool checked);

    void on_spinBoxNturns_editingFinished();

    void on_doubleSpinBoxMemMod_editingFinished();

private:
    Ui::MainWindow *ui;
    bool mundoExiste;
    bool play;
    int mem_type;
    class World * ptrMundo;
    class space * ptrMySpace;

    QTimer passatempo;

    double corFat;//para as cores do dbscan
    unsigned int corIni;

};

#endif // MAINWINDOW_H
