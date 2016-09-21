#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    currentMode = Menu;

    this->setFixedSize(720, 480);

    MainWidget = new QWidget(this);
    MainWidget->setFixedSize(this->size());

    GameWidget = new QWidget(this);
    GameWidget->setFixedSize(this->size());

    SettingWidget = new QWidget(MainWidget);
    SettingWidget->setGeometry(100, 70, 520, 210);
    NumberWidget = new QWidget(SettingWidget);
    NumberWidget->setGeometry(0, 5, 160, 70);
    ComlWidget = new QWidget(SettingWidget);
    ComlWidget->setGeometry(360, 5, 160, 70);
    ModeWidget = new QWidget(SettingWidget);
    ModeWidget->setGeometry(125, 100, 270, 70);

    labelmode = new QLabel("Режим", ModeWidget);
    labelmode->setGeometry(120, 0, 51, 20);
    training = new QRadioButton("Тренировка", ModeWidget);
    training->setGeometry(20, 26, 117, 22);
    arcade = new QRadioButton("Аркада", ModeWidget);
    arcade->setGeometry(170, 26, 91, 22);

    labelcompl = new QLabel("Уровень сложности", ComlWidget);
    labelcompl->setGeometry(10, 10, 141, 17);
    cmb = new QComboBox(ComlWidget);
    cmb->setGeometry(20, 30, 121, 26);

    labelnum = new QLabel("Порядок квадрата", NumberWidget);
    labelnum->setGeometry(20, 10, 131, 17);
    num = new QSpinBox(NumberWidget);
    num->setGeometry(30, 30, 111, 27);

    labelPT = new QLabel(GameWidget);
    labelPT->setGeometry(10, 30, 161, 17);
    labelIT = new QLabel(GameWidget);
    labelIT->setGeometry(460, 30, 251, 20);
    aboutNumlabel = new QLabel("Невставленные числа", GameWidget);
    aboutNumlabel->setGeometry(540, 60, 171, 17);

    numbersList = new QListWidget(GameWidget);
    numbersList->setGeometry(540, 90, 171, 271);

    table   =  new QTableView(GameWidget);
    table->setGeometry(10, 60, 521, 351);

    start  = new QPushButton("&Начать игру", MainWidget);
    start->setGeometry(230, 323, 260, 71);
    check   = new QPushButton("&Проверить квадрат", GameWidget);
    check->setGeometry(538, 363, 171, 47);
    //checkLastNumber = new QPushButton("Проверить последнее введеное число", this);

    delegate  =   new MagicDelegate();

    training->setChecked(true);

    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::darkGray));
    table->setPalette(pal);

    table->setItemDelegate(delegate);

    //connect(table, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(inputInformation(/*index*/)));

    num->setMinimum(3);
    num->setMaximum(1000);


    lst << "Легко"<<"Средне"<<"Сложно";
    cmb->addItems(lst);
    cmb->setEditable(false);

    start->setDefault(true);

    createMenu();

    connect(start, SIGNAL(clicked(bool)), this, SLOT(game()));
    connect(check, SIGNAL(clicked(bool)),this, SLOT(endg()));
    connect(arcade, SIGNAL(clicked(bool)), this, SLOT(arcadeMode()));
    connect(training, SIGNAL(clicked(bool)), this, SLOT(trainingMode()));
//   connect(checkLastNumber, SIGNAL(clicked(bool)), this, SLOT(inputInformation()));

    MainWindow::menu();
}

/*Menu*/
void MainWindow::menu()
{
    qDebug()<<"In Menu";

    GameWidget->hide();
    MainWidget->show();

    if (currentMode == Game)
        return;
    currentMode = Menu;
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

    MainWidget->hide();
    GameWidget->show();

    if(gamemode == Arcade)
        t.start();

    SquareNumber = num->text().toInt();
    SquareComlexity = 0;
    if(cmb->currentText() == "Легко")
        SquareComlexity = 1;
    else if(cmb->currentText() == "Средне")
        SquareComlexity = 2;
    else SquareComlexity = 3;

    delegate->SetMaxValue(SquareNumber * SquareNumber);

    model = new MagicSquareModel(SquareNumber, SquareComlexity);
    model->insertColumns(0, SquareNumber);
    model->insertRows(0, SquareNumber);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));

    labelPT->setText("Порядок квадрата: " + QString::number(SquareNumber));
    labelIT->setText("Осталось незаполненных ячеек: " + QString::number(model->ItemsCountModel()));

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

void MainWindow::createMenu()
{
    mainMenu = new QMenuBar(this);
    file = new QMenu("&Меню",this);

    mainMenu->addMenu(file);

    file->addAction("Выйти в меню", this, SLOT(menuexs()));
    file->addAction("Выйти из игры", qApp, SLOT(quit()));

    this->setMenuBar(mainMenu);
}

void MainWindow::createButtons()
{
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
    if(gamemode == Training){
        if(model->flag == 1){
            QMessageBox::information(this, "Информация", "Число введено верно");
        }
        else
            QMessageBox::information(this, "Информация", "Число введено неверно");
    }
}

void MainWindow::menuexs()
{
    currentMode = Menu;
    MainWindow::menu();
}

MainWindow::~MainWindow()
{
}
