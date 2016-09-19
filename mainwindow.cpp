#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    currentMode = Menu;

    table   =  new QTableView(this);

    start  = new QPushButton("&Начать игру", this);
    check   = new QPushButton("&Проверить квадрат", this);

    num = new QSpinBox(this);
    cmb = new QComboBox(this);

    labelPT   =     new QLabel(this);
    labelIT = new QLabel(this);

    delegate  =   new MagicDelegate();

    labelnum = new QLabel("Порядок квадрата",this);
    labelcompl = new QLabel("Уровень сложности", this);

    labelmode = new QLabel("Режим",this);
    arcade = new QRadioButton("Аркада",this);
    training = new QRadioButton("Тренировка", this);
    training->setChecked(true);

    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::darkGray));
    table->setPalette(pal);

    table->setItemDelegate(delegate);

    connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(inputInformation(/*index*/)));

    num->setMinimum(3);
    num->setMaximum(1000);


    lst << "Легко"<<"Средне"<<"Сложно";
    cmb->addItems(lst);
    cmb->setEditable(false);

    start->setDefault(true);

    createLayouts();
    createMenu();
    createButtons();

    connect(start, SIGNAL(clicked(bool)), this, SLOT(game()));
    connect(check, SIGNAL(clicked(bool)),this, SLOT(endg()));
    connect(arcade, SIGNAL(clicked(bool)), this, SLOT(arcadeMode()));
    connect(training, SIGNAL(clicked(bool)), this, SLOT(trainingMode()));

    labelcompl->hide();
    labelnum->hide();
    num->hide();
    cmb->hide();
    start->hide();
    table->hide();
    check->hide();
    labelPT->hide();
    labelIT->hide();
    labelmode->hide();
    arcade->hide();
    training->hide();

    MainWindow::menu();
}

/*Menu*/
void MainWindow::menu()
{
    qDebug()<<"In Menu";

    table->hide();
    check->hide();
    labelPT->hide();
    labelIT->hide();
    if (currentMode == Game)
        return;
    currentMode = Menu;

    start->show();
    cmb->show();
    num->show();
    labelcompl->show();
    labelnum->show();
    labelmode->show();
    arcade->show();
    training->show();

}

void MainWindow::trainingMode()
{
    gamemode = Training;
}

void MainWindow::arcadeMode()
{
    gamemode = Arcade;
}
/*Game*/
void MainWindow::game()
{
    qDebug()<<"In game";
    if(currentMode == Game)
        return;
    currentMode = Game;

    start->hide();
    num->hide();
    cmb->hide();
    labelmode->hide();
    arcade->hide();
    training->hide();
    check->show();
    table->show();

    if(gamemode == Arcade)
        t.start();

    SquareNumber = num->text().toInt();
    SquareComlexity = 0;
    if(cmb->currentText() == "Легко")
        SquareComlexity = 1;
    else if(cmb->currentText() == "Средне")
        SquareComlexity = 2;
    else SquareComlexity = 3;

    num->hide();
    labelcompl->hide();
    labelnum->hide();

    delegate->SetMaxValue(SquareNumber * SquareNumber);

    model = new MagicSquareModel(SquareNumber, SquareComlexity);
    model->insertColumns(0, SquareNumber);
    model->insertRows(0, SquareNumber);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));

    labelPT->setText("Порядок квадрата: " + QString::number(SquareNumber));
    labelIT->setText("Осталось незаполненных ячеек: "  + QString::number(model->ItemsCountModel()));


    labelPT->show();
    labelIT->show();

    table->setModel(model);

    qDebug()<<"Build";
}

void MainWindow::endg()
{
    time = t.elapsed();
    qDebug()<<"Время: "<<time;
    if (model->Full(SquareNumber)){
        if (gamemode == Arcade){
            countPoints();
            QMessageBox::information(this, "Вы победили!",
                                 "КВАДРАТ МАГИЧЕСКИЙ!\nНабрано очков: " + QString::number(points));
        }
        else
            QMessageBox::information(this,"Вы победили!", "КВАДРАТ МАГИЧЕСКИЙ!");
        qDebug() << "Magic";
        MainWindow::menuexs();
    }
    else {
        QMessageBox::information(this, "Попробуйте еще раз", "Квадрат не магический");
        qDebug()<< "Not magic";
    }
}

void MainWindow::countPoints()
{
    //points = SquareComlexity * SquareNumber * 8900 - time;
    points = SquareNumber * SquareComlexity * 100 - time/1000;
}

void MainWindow::createLayouts()
{
    mainLayout = new QVBoxLayout(this);
    layout = new QHBoxLayout(this);
    center = new QGridLayout(this);
    HorizontalLayout = new QHBoxLayout(this);
    ButtonsLay = new QGridLayout(this);

    center->addWidget(labelcompl, 1, 1, Qt::AlignCenter);
    center->addWidget(cmb, 2, 1, Qt::AlignCenter);
    center->addWidget(labelnum, 1, 2, Qt::AlignCenter);
    center->addWidget(num, 2, 2, Qt::AlignCenter);
    center->addWidget(labelmode, 3, 1, 1, 2, Qt::AlignCenter);
    center->addWidget(training, 4, 1, Qt::AlignCenter);
    center->addWidget(arcade, 4, 2, Qt::AlignCenter);

    layout->addWidget(labelPT);
    layout->addWidget(labelIT);

    mainLayout->addLayout(layout);
    mainLayout->addLayout(center);
    HorizontalLayout->addLayout(mainLayout);
    HorizontalLayout->addLayout(ButtonsLay);
    mainLayout->addWidget(start);
    mainLayout->addWidget(table);
    mainLayout->addWidget(check);
}

void MainWindow::createMenu()
{
    mainMenu = new QMenuBar(this);
    file = new QMenu("&Меню",this);

    mainMenu->addMenu(file);

    file->addAction("Выйти в меню", this, SLOT(menuexs()));
    file->addAction("Выйти из игры", qApp, SLOT(quit()));

    mainLayout->setMenuBar(mainMenu);
}

void MainWindow::createButtons()
{
//    for(int i = 0; i < 4; i++)
//    {
//        QPushButton* r = new QPushButton(this);
//        //r->setGeometry(30, 15 + i*h, w, h);
// //        ButtonsLay->addWidget(r, i, 0);
//        layout->addWidget(r, i, j);
//        buttons.push_back(r);
//    }
    qDebug()<<"$: "<<model->numbersSize();
    for(int n = 0; n < model->numbersSize(); n++)
        //for(int i = 0; i < model->size(); i++)
            //for(int j = 0; j < model->size(); j++){
                {
                    QPushButton* r = new QPushButton(this);
                    //r->setGeometry(30, 15 + i*h, w, h);
            //        ButtonsLay->addWidget(r, i, 0);
                    layout->addWidget(r);
                    buttons.push_back(r);
                }
                //QPushButton* b = new QPushButton(QString::number((double)n), this);
                //ButtonsLay->addWidget(b);
            //}
}

void MainWindow::ItemChanged()
{
    labelIT->setText("Осталось незаполненных ячеек: "  + QString::number(model->ItemsCountModel()));
}

void MainWindow::inputInformation(/*QModelIndex &index*/)
{
    qDebug()<<"clicked";
    if(model->flag == 1){
        qDebug()<<"true";
        //model->flag = 0;
    }
    else {
        qDebug()<<"false";
        //model->flag = 0;
    }
//    int row = index.row();
//    int col = index.column();
//    if(gamemode == Training){
//        //if(model->CheckValueModel(/*row, col)*/){
//            QMessageBox::information(this, "Информация", "Число введено верно");
//        }
//        else
//            QMessageBox::information(this, "Информация", "Число введено неверно");
//    }
}

void MainWindow::menuexs()
{
    currentMode = Menu;
    MainWindow::menu();
}

MainWindow::~MainWindow()
{
}
