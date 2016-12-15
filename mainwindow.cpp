#include "mainwindow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    currentMode = Menu;

    createLayouts();
    createMenu();
    setSettings();

    menu();

    connect(start, SIGNAL(clicked(bool)), this, SLOT(game()));
    connect(check, SIGNAL(clicked(bool)),this, SLOT(endg()));
    connect(arcade, SIGNAL(clicked(bool)), this, SLOT(arcadeMode()));
    connect(training, SIGNAL(clicked(bool)), this, SLOT(trainingMode()));
    connect(checkLastNumber, SIGNAL(clicked(bool)), this, SLOT(inputInformation()));
}

void Widget::createLayouts()
{
    mainLayout = new QVBoxLayout();
    SettingWidget = new QWidget(this);

    NumberWidget = new QWidget(SettingWidget);
    NumberWidget->setToolTip("Выберите порядка квадрата");
    labelnum = new QLabel("Порядок", NumberWidget);
    num = new QSpinBox(NumberWidget);
    QVBoxLayout *wlay1 = new QVBoxLayout();
    wlay1->addWidget(labelnum);
    wlay1->addWidget(num);
    wlay1->setAlignment(Qt::AlignCenter);
    NumberWidget->setLayout(wlay1);

    ComplWidget = new QWidget(SettingWidget);
    ComplWidget->setToolTip("Выберите уровень сложности");
    labelcompl = new QLabel("Сложность", ComplWidget);
    cmb = new QComboBox(ComplWidget);
    QVBoxLayout *wlay2 = new QVBoxLayout();
    wlay2->addWidget(labelcompl);
    wlay2->addWidget(cmb);
    wlay2->setAlignment(Qt::AlignCenter);
    ComplWidget->setLayout(wlay2);

    ModeWidget = new QWidget(SettingWidget);
    ModeWidget->setToolTip("Выберите режим игры");
    labelmode = new QLabel("Режим", ModeWidget);
    training = new QRadioButton("Тренировка", ModeWidget);
    arcade = new QRadioButton("Аркада", ModeWidget);
    QVBoxLayout *wlay3 = new QVBoxLayout();
    wlay3->addWidget(labelmode);
    wlay3->addWidget(training);
    wlay3->addWidget(arcade);
    wlay3->setAlignment(Qt::AlignCenter);
    ModeWidget->setLayout(wlay3);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(NumberWidget);
    hbox->addWidget(ComplWidget);
    hbox->addWidget(ModeWidget);
    SettingWidget->setLayout(hbox);

    welcome = new QLabel("Магический квадрат", SettingWidget);
    QFont wFont;
    wFont.setPointSize(35);
    welcome->setFont(wFont);
    welcome->setAlignment(Qt::AlignCenter);

    start = new QPushButton("&Начать игру", SettingWidget);

    mainLayout->addWidget(welcome);
    mainLayout->addWidget(SettingWidget);
    mainLayout->addWidget(start);

    SettingWidget->hide();
    welcome->hide();
    start->hide();

    /*Setting GameLayouts*/

    QHBoxLayout *forTable = new QHBoxLayout();

    table = new QTableView(this);
    forTable->addWidget(table);
    forTable->setAlignment(Qt::AlignCenter);
    table->hide();

    infoW = new QVBoxLayout();
    labelPT = new QLabel(this);
    labelPT->setAlignment(Qt::AlignCenter);
    labelIT = new QLabel(this);
    labelIT->setAlignment(Qt::AlignCenter);
    check = new QPushButton("&Проверить квадрат", this);
    check->setToolTip("Проверить квадрат на магичность");
    checkLastNumber = new QPushButton("П&роверить число", this);
    checkLastNumber->setToolTip("Проверить последнее введеное число");
    aboutNumlabel = new QLabel("Неиспользованные числа", this);
    aboutNumlabel->setAlignment(Qt::AlignCenter);
    numbersList = new QListWidget(this);
    numbersList->setToolTip("Числа, которые необходимо вставить");
    infoW->addWidget(labelPT);
    infoW->addWidget(labelIT);
    infoW->addWidget(aboutNumlabel);
    infoW->addWidget(numbersList);
    infoW->addWidget(check);
    infoW->addWidget(checkLastNumber);


    QHBoxLayout *layout = new QHBoxLayout();
    layout->addLayout(forTable);
    layout->addLayout(infoW);
    layout->setAlignment(Qt::AlignCenter);

    mainLayout->addLayout(layout);

    setLayout(mainLayout);
}

void Widget::createMenu()
{
    MenuBar = new QMenuBar(this);
    file = new QMenu("&Меню",this);
    about = new QMenu("&О программе", this);

    MenuBar->addMenu(file);
    MenuBar->addMenu(about);

    file->addAction("Выйти в меню", this, SLOT(menuexs()));
    file->addSeparator();
    file->addAction("Выйти из игры", qApp, SLOT(quit()));

    about->addAction("О программе", this, SLOT(aboutDevelopers()));

    mainLayout->setMenuBar(MenuBar);
}

void Widget::setSettings()
{
    labelnum->setAlignment(Qt::AlignCenter);
    labelcompl->setAlignment(Qt::AlignCenter);
    labelmode->setAlignment(Qt::AlignCenter);

    delegate = new MagicDelegate();

    training->setChecked(true);

    num->setMinimum(3);
    num->setMaximum(100);

    lst << "Легко"<<"Средне"<<"Сложно";
    cmb->addItems(lst);
    cmb->setEditable(false);

    start->setDefault(true);
}

/*Menu*/
void Widget::menu()
{
    qDebug()<<"In Menu";

    hideGame();

    if (currentMode == Game)
        return;
    currentMode = Menu;
}

/*Game*/
void Widget::game()
{
    qDebug()<<"In game";
    if(currentMode == Game)
        return;
    currentMode = Game;
    hideMenu();

    if(gamemode == Arcade){
        qDebug()<<"Arcade";
        t.start();
        checkLastNumber->hide();
        aboutNumlabel->hide();
        numbersList->hide();
    }
    int w = checkLastNumber->width();
    numbersList->setMaximumWidth(w);

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

    QPalette pal = palette();
    pal.setColor(backgroundRole(), QColor(Qt::darkGray));
    table->setPalette(pal);

    table->setItemDelegate(delegate);

    int h = 345;
    table->setMinimumSize(h, h);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(ItemChanged()));

    numbersListsSlot();
    labelPT->setText("Порядок : " + QString::number(SquareNumber));
    labelIT->setText("Осталось ячеек: " + QString::number(model->ItemsCountModel()));
    labelIT->setToolTip("Количество пустых ячеек");

    table->setModel(model);

    QFont tFont;

    tFont.setPointSize(20);

    for(int i = 0; i < SquareNumber; i++){
        table->setColumnWidth(i, 105);
    }
    for(int i = 0; i < SquareNumber; i++)
        table->setRowHeight(i, 105);

    qDebug()<<"Build";
}

void Widget::trainingMode()
{
    gamemode = Training;
}

void Widget::arcadeMode()
{
    gamemode = Arcade;
}

void Widget::endg()
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
        FreeMemory();
        Widget::menuexs();
    }
    else {
        QMessageBox::information(this, "Попробуйте еще раз", "Квадрат не магический");
        qDebug()<< "Not magic";
    }
}

void Widget::countPoints()
{
    points = SquareNumber * SquareComlexity * 100 - time/1000;
}



void Widget::numbersListsSlot()
{
    numbersList->clear();
    for (int i = 0; i < model->x; i++){
        QListWidgetItem* item = new QListWidgetItem();
        if(model->getNumber(i) != 0){
            item->setText(QString::number((double)model->getNumber(i)));
            item->setTextAlignment(Qt::AlignCenter);
            QFont font;
            font.setPointSize(30);
            item->setFont(font);
            numbersList->addItem(item);
        }
    }
}

void Widget::ItemChanged()
{
    labelIT->setText("Осталось незаполненных ячеек: "  + QString::number(model->ItemsCountModel()));
    numbersListsSlot();
    flag = true;
}

void Widget::inputInformation()
{
    if(!flag){
        QMessageBox::information(this, "Информация", "Вы еще не вводили чисел");
        return;
    }
    qDebug()<<"clicked";
    if(model->flag){
        qDebug()<<"true";
        QMessageBox::information(this, "Информация", "Число введено верно");
    }
    else {
        qDebug()<<"false";
        QMessageBox::information(this, "Информация", "Число введено неверно");
    }

}

void Widget::aboutDevelopers()
{
    QMessageBox::information(this, "О программе",
                             "Magic Square version 1.0\nDevelopted by Evgeny Tikhomirov\n"
                             "Yaroslavl, 2015-2016");
}

void Widget::menuexs()
{
    currentMode = Menu;
    Widget::menu();
}

void Widget::hideMenu()
{
    SettingWidget->hide();
    start->hide();
    welcome->hide();

    table->show();
    labelIT->show();
    labelPT->show();
    check->show();
    checkLastNumber->show();
    aboutNumlabel->show();
    numbersList->show();
}

void Widget::hideGame()
{
    table->hide();
    labelIT->hide();
    labelPT->hide();
    check->hide();
    checkLastNumber->hide();
    aboutNumlabel->hide();
    numbersList->hide();

    SettingWidget->show();
    start->show();
    welcome->show();
}

void Widget::FreeMemory()
{
    numbersList->clear();
    time = 0;
    points = 0;
    model->FreeMemory();
}

Widget::~Widget()
{}
