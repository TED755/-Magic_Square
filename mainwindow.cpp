#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    currentMode = Menu;


    mmenubar = new QMenuBar(this);
    mmenu = new QMenu("Меню", this);
    mmenu->addAction("&Exit", qApp, SLOT(quit()));
    mmenubar->addMenu(mmenu);



    layout    = new QVBoxLayout(this);
    laylabel = new QHBoxLayout(this);

    table   =  new QTableView(this);

    start  = new QPushButton(this);
    end   = new QPushButton(this);
    exit = new QPushButton(this);
    menuex = new QPushButton(this);

    num = new QSpinBox(this);
    cmb = new QComboBox(this);

    labelPN   =    new QLabel(this);
    labelPT   =     new QLabel(this);
    labelIN = new QLabel(this);
    labelIT = new QLabel(this);
    delegate  =   new MagicDelegate();

    laycompl = new QVBoxLayout(this);
    laynum = new QVBoxLayout(this);
    sun = new QHBoxLayout(this);
    main = new QVBoxLayout(this);

    labelnum = new QLabel(this);
    labelcompl = new QLabel(this);


    QPalette pal = palette();
        pal.setColor(backgroundRole(), QColor(Qt::darkGray));
        table->setPalette(pal);

    table->setItemDelegate(delegate);

    labelcompl->setText("Уровень сложности");
    labelnum->setText("Порядок");

    num->setMinimum(3);
    num->setMaximum(1000);


    lst << "Легко"<<"Средне"<<"Сложно";
    cmb->addItems(lst);
    cmb->setEditable(false);

    start->setText("Начать");
    start->setDefault(true);
    end->setText("Проверить квадрат");
    exit->setText("Выход");
    menuex->setText("Выход в меню");

    laycompl->addWidget(labelcompl);
    laycompl->addWidget(cmb);
    laynum->addWidget(labelnum);
    laynum->addWidget(num);
    sun->addLayout(laycompl);
    sun->addLayout(laynum);
    main->addLayout(sun);
    main->addWidget(start);

    laylabel->addWidget(labelPT);
    laylabel->addWidget(labelPN);
    laylabel->addWidget(labelIT);
    laylabel->addWidget(labelIN);

    layout->addWidget(mmenubar);
    layout->addWidget(&mods);
    layout->addLayout(laylabel);
    layout->addLayout(main);
    layout->addWidget(table);
    layout->addWidget(end);
    layout->addWidget(menuex);
    layout->addWidget(exit);


    connect(start, SIGNAL(clicked(bool)), this, SLOT(game()));
    connect(end, SIGNAL(clicked(bool)),this, SLOT(endg()));
    connect(exit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
    connect(menuex, SIGNAL(clicked(bool)), this, SLOT(menuexs()));

    labelcompl->hide();
    labelnum->hide();
    num->hide();
    cmb->hide();
    start->hide();
    menuex->hide();
    exit->hide();
    mods.hide();
    table->hide();
    end->hide();
    labelPN->hide();
    labelPT->hide();
    labelIN->hide();
    labelIT->hide();

    MainWindow::menu();
}

/*Menu*/
void MainWindow::menu()
{
    qDebug()<<"In Menu";
    table->hide();
    end->hide();
    labelPN->hide();
    labelPT->hide();
    labelIN->hide();
    labelIT->hide();
    menuex->hide();
    if (currentMode == Game)
        return;
    currentMode = Menu;

    start->show();
    cmb->show();
    num->show();
    labelcompl->show();
    labelnum->show();
    exit->show();
    mods.show();

}

/*game*/
void MainWindow::game()
{
    qDebug()<<"In game";
    if(currentMode == Game)
        return;

    currentMode = Game;

    start->hide();
    num->hide();
    cmb->hide();
    end->show();
    exit->show();
    menuex->show();
    table->show();
    mods.hide();

    int a = num->text().toInt();

    num->hide();
    labelcompl->hide();
    labelnum->hide();

    delegate->SetMaxValue(a*a);

    model = new MagicSquareModel(a);
    model->insertColumns(0,a);
    model->insertRows(0, a);

    labelPT->setText("Порядок квадрата: ");
    labelPN->setNum(a);
    labelIT->setText("Осталось незаполненных ячеек: ");
    labelIN->setNum(model->ItemsCountModel());

    labelPT->show();
    labelPN->show();
    labelIT->show();

//    QPalette pal = palette();
//    pal.setColor(backgroundRole(), QColor(Qt::yellow));

    table->setModel(model);
    //table->setPalette(pal);
    //table->setFrameStyle(100);
    //table->setGeometry(1000,10000,255,128);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));
    labelIN->show();

    qDebug()<<"Build";    

}

void MainWindow::endg()
{
    int b = num->text().toInt();
    if (model->Full(b)){
        QMessageBox::information(this, "Вы победили!", "КВАДРАТ МАГИЧЕСКИЙ!");
        qDebug() << "It's working!";
        MainWindow::menuexs();
    }
    else {
        QMessageBox::information(this, "Попробуйте еще раз", "Квадрат не магический");
        qDebug()<< "Not magic";
    }
}

void MainWindow::ItemChanged()
{
    labelIN->setNum(model->ItemsCountModel());
}

void MainWindow::menuexs()
{
    qDebug()<<"clicked";
    currentMode = Menu;
    MainWindow::menu();
}

MainWindow::~MainWindow()
{
}
