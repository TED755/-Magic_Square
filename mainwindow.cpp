#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    currentMode = Menu;

    table   =  new QTableView(this);

    start  = new QPushButton(this);
    check   = new QPushButton(this);

    num = new QSpinBox(this);
    cmb = new QComboBox(this);

    labelPT   =     new QLabel(this);
    labelIT = new QLabel(this);

    delegate  =   new MagicDelegate();

    labelnum = new QLabel(this);
    labelcompl = new QLabel(this);

    labelmode = new QLabel("Режим",this);
    arcade = new QRadioButton("Аркада",this);
    training = new QRadioButton("Тренировка", this);
    training->setChecked(true);

    QPalette pal = palette();
        pal.setColor(backgroundRole(), QColor(Qt::darkGray));
        table->setPalette(pal);

    table->setItemDelegate(delegate);

    labelcompl->setText("Уровень сложности");
    labelnum->setText("Порядок квадрата");

    num->setMinimum(3);
    num->setMaximum(1000);


    lst << "Легко"<<"Средне"<<"Сложно";
    cmb->addItems(lst);
    cmb->setEditable(false);

    start->setText("Начать");
    start->setDefault(true);
    check->setText("Проверить квадрат");

    createLayouts();
    createMenu();

    connect(start, SIGNAL(clicked(bool)), this, SLOT(game()));
    connect(check, SIGNAL(clicked(bool)),this, SLOT(endg()));

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
    labelmode->hide();
    arcade->hide();
    training->hide();
    check->show();
    table->show();

    int a = num->text().toInt();
    int c = 0;
    if(cmb->currentText() == "Легко")
        c = 1;
    else if(cmb->currentText() == "Средне")
        c = 2;
    else c = 3;


    num->hide();
    labelcompl->hide();
    labelnum->hide();

    delegate->SetMaxValue(a*a);

    model = new MagicSquareModel(a, c);
    model->insertColumns(0,a);
    model->insertRows(0, a);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));

    labelPT->setText("Порядок квадрата: " + QString::number(a));
    labelIT->setText("Осталось незаполненных ячеек: "  + QString::number(model->ItemsCountModel()));


    labelPT->show();
    labelIT->show();

    table->setModel(model);

    qDebug()<<"Build";    

}

void MainWindow::endg()
{
    int a = num->text().toInt();
    if (model->Full(a)){
        QMessageBox::information(this, "Вы победили!", "КВАДРАТ МАГИЧЕСКИЙ!");
        qDebug() << "It's working!";
        MainWindow::menuexs();
    }
    else {
        QMessageBox::information(this, "Попробуйте еще раз", "Квадрат не магический");
        qDebug()<< "Not magic";
    }
}

void MainWindow::createLayouts()
{
    mainLayout = new QVBoxLayout(this);
    layout = new QHBoxLayout(this);
    center = new QGridLayout(this);

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

void MainWindow::ItemChanged()
{
    labelIT->setText("Осталось незаполненных ячеек: "  + QString::number(model->ItemsCountModel()));
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
