#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QString>
#include <cmath>
#include <cstdlib>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mundoExiste=false;//inicia sem mundo
    this->play=false;//inicia pausado
    if (this->ui->radioButtonGrupal->isChecked())this->mem_type=1;
    if (this->ui->radioButtonIndividual->isChecked())this->mem_type=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    //if( this->ptrMundo.num_turnos % 100 ==0)
    //{
    QPainter estojo;//cria o estojo de pintura

    estojo.begin(this);//faz o estojo desenhar nesta janela
    estojo.setRenderHint(QPainter::Antialiasing);//desenho mais suave
    //define coordenadas

    //acochambration das coordenadas para ficar bunitinho dentro do groupbox
    int x0=this->ui->groupBox->geometry().x()+2;
    int y0=this->ui->groupBox->geometry().y()+35;
    int w=this->ui->groupBox->geometry().width()-5;
    int h=this->ui->groupBox->geometry().height()-2;

    //fator de correção da escala do mundo para a escala da janela
    //todas as coordenadas finais tem de ser multiplicadas por este fator para evitar erros
    double fx=(double)w/this->ptrMundo.get_X();
    double fy=(double)h/this->ptrMundo.get_Y();

    if (this->mundoExiste)
    {
        //desenha grid
        estojo.setBrush(QBrush(QColor(125, 125, 125,0.3)));
        double a=x0;
        double b=y0;
                    for (int i=0; i<(this->ptrMundo.get_X()/this->ptrMundo.raio_medio);i++)
                    {
                        //linhas verticais
                        estojo.drawLine(a,b,a,b+this->ptrMundo.get_Y()*fy);
                        a+=(this->ptrMundo.raio_medio*fx);
                    }
        a=0+x0;

                    for (int j =0; j<(this->ptrMundo.get_X()/this->ptrMundo.raio_medio); j++)
                    {
                        //linhas horizontais
                        estojo.drawLine(a,b,a+this->ptrMundo.get_X()*fx,b);
                        b+=(this->ptrMundo.raio_medio*fy);
                    }


        //desenha agentes
        for (int i =0; i<this->ptrMundo.get_size_agentes();i++)
        {
            Agents* ator = this->ptrMundo.get_agent(i);
            int x= x0 + fx * ator->get_x();//coordenadas x e y corrigidas pelo formato da janela
            int y= y0 + fy * ator->get_y();
            //double raio =ator->get_raio();
            double diametro=2*ator->get_raio();//diametro do raio de ação
            double angulo = ator->get_angulo();
            estojo.setPen(QColor(255,0,0));
            if (ator->ator)
                estojo.setPen(QColor(0,255,0));
            if (ator->outro)
                estojo.setPen(QColor(0,255,255));

            //desenha uma elipse de raio 1 com a cor vermelha centrada na coordenada x e y do agente
            estojo.drawEllipse(x-((1*fx)/2),
                               y-((1*fy)/2),
                               1*fx,
                               1*fy
                               );
            //         //   retangulo de lado 1com a cor do agente centrada na coordenada x e y do agente
            //                 estojo.setPen(QColor(0,255,0));
            //                        estojo.drawRect(x-((1*fx)/2),
            //                                        y-((1*fy)/2),
            //                                        1*fx,
            //                                        1*fx);
            estojo.setBrush(QColor(100,100,200, 30));//cria uma paleta de cores variando entre preto e branco,
            //com numero de cores igual a numero de agentes
            estojo.setPen(QColor(255,255,255));

            //desenha uma elipse com o diametro do raio de ação do agente, centrado na coordena x e y do agente
            estojo.setPen(QColor ((QRgb) (ator->cluster*corFat+corIni) ));
            //estojo.setPen(QColor(0,0,255));
            estojo.drawEllipse(x-((diametro*fx)/2),
                               y-((diametro*fy)/2),
                               diametro*fx,
                               diametro*fy
                               );
            // numero do agente
            QString labelx= QString::number((int)ator->get_x());
            QString labely= QString::number((int)ator->get_y());
           // QString nome = QString::number(ator->get_id());
            QString nome = QString::number(ator->cluster);
            //QString coord1=labelx + "  " +labely;
            //estojo.drawText (x, y,coord1);
            estojo.drawText(x,y-10,nome);

            //angulo do agente
            estojo.drawLine(x,
                            y,
                            x + (cos(angulo)*ator->get_passo()*fx),
                            y + (sin(angulo)*ator->get_passo()*fy)
                            );

            //estojo.drawPolyline(points, 3);
            //desenha um triangulo centrado no ponto
            //            estojo.setPen(QColor(255,0,0));

            //            //pontos do triangulo
            //            estojo.save();
            //             estojo.translate(x,y);
            //            estojo.rotate(((ator->get_angulo()*180)/M_PI));
            //            estojo.setPen(QColor(255,0,0));
            //            int lado_T=3 ;
            //            double c=(lado_T/2)*fx;
            //            double r=(lado_T*((sqrt(3))/3))*fy;
            //            double h=(lado_T*((sqrt(3))/6))*fy;
            //            QPointF forma_agente[4] = {
            //                 QPointF( -c, -h)
            //                ,QPointF(0,  +r),
            //                QPointF(+c, -h)
            //                ,QPointF(0, 0)


            //            };

            //            estojo.drawPolygon(forma_agente, 4);
            //            // estojo.drawRect(0,0,c*fx,-r*fx);
            //            estojo.restore();


        }
    }


    estojo.end();//encerra o desenho
    //}
}

void MainWindow::on_pushButtonGeraMundo_clicked()
{
    if(this->mundoExiste) delete this->ptrMundo;//destroi o mundo pre-existente ao apertar o botao para não haver sobreposição
    this->ptrMundo=new World (this->ui->doubleSpinBoxX->value(),
                              this->ui->spinBox_N_agentes->value(),
                              this->ui->spinBoxRaio->value(),
                              this->ui->doubleSpinBoxEps->value(),
                              this->ui->spinBoxMinPts->value(),
                              this->ui->spinBox_MemLength->value(),
                              this->mem_type) ;
    this->mundoExiste=true;

    this->ptrMundo.num_turnos=0;

    QColor cor = QColor(255,255,255);//define objeto QColor da cor branca
    unsigned int fcor = cor.rgb();//define fcor com o valor int retornado pela funçao rgb de cor
    cor = QColor(0,0,0);//define cor preta
    this->corIni = cor.rgb();
    this->corFat = (fcor-corIni)/this->ui->spinBox_N_agentes->value();//gera um fator de conversao de cores para que o numero de times seja igual ao numero de cores


    this->update();
}

void MainWindow::on_pushButtonRodaUm_clicked()
{   if (this->mem_type==0)
    {
        this->ptrMundo.update2_i(
                    //this
                    );
    }
    if (this->mem_type==1)
    {
        this->ptrMundo.update2_g(
                    //this
                    );
    }
    this->ui->spinBoxContaTurnos->setValue(this->ptrMundo.num_turnos);
    this->ui->spinBoxClusters->setValue(this->ptrMundo.n_clusters()-1);
    this->update();

}

void MainWindow::on_pushButtonRodaIniciar_clicked()
{
    int x=0;
    if (this->mem_type==0)
    {
        while (x<100)
        {

            this->ptrMundo.update2_i(
                        //this
                        );
            x++;
            this->ui->spinBoxContaTurnos->setValue(this->ptrMundo.num_turnos);
            this->ui->spinBoxClusters->setValue(this->ptrMundo.n_clusters()-1);
            this->repaint();
        }
    }
    if (this->mem_type==1)
    {
        while (x<100)
        {
            this->ptrMundo.update2_g(
                        //this
                        );
            x++;
            this->ui->spinBoxContaTurnos->setValue(this->ptrMundo.num_turnos);
            this->ui->spinBoxClusters->setValue(this->ptrMundo.n_clusters()-1);
            this->repaint();
        }
    }

    this->repaint();
}

void MainWindow::on_actionCarregar_estado_triggered()
{

}


void MainWindow::on_radioButtonGrupal_toggled(bool checked)
{
    if (checked)this->mem_type = 1;
}

void MainWindow::on_radioButtonIndividual_toggled(bool checked)
{
    if (checked)this->mem_type = 0;
}

void MainWindow::on_pushButtonMov_Clust_clicked()
{

}
