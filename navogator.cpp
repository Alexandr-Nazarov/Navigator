#include "navogator.h"
#include "ui_navogator.h"

Navogator::Navogator(QWidget *parent)
    : /*QWidget*/QMainWindow(parent)
    , ui(new Ui::Navogator)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint |
                         Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint );
   // ui->horizontalLayout->SetMaximumSize ;
   // ui->tableView->setMaximumSize(1000,1000);
//    ui->graphicsView->setGeometry(10,10,this->width()-300, this->height()-20);
//    ui->widget->setGeometry(ui->graphicsView->x()+ui->graphicsView->width(),ui->graphicsView->y(), 130, 450 );
 //   ui->tableView->setGeometry(ui->widget->x()+ui->widget->width(), );
 // repaint();



    QObject::connect(ui->X_size, SIGNAL(textChanged(QString)),ui->widget,SLOT(selected_Dimension_X(QString)) );
    QObject::connect(ui->Y_size, SIGNAL(textChanged(QString)),ui->widget,SLOT(selected_Dimension_Y(QString)) );

    QObject::connect(ui->Impass_Box, SIGNAL(clicked(bool)), ui->widget,SLOT(selected_Impassable(bool)) );
    QObject::connect(ui->UniformBox, SIGNAL(clicked(bool)), ui->widget,SLOT(selected_Uniform(bool)) );


    QValidator* my_line_value=new QIntValidator(1,999);
    ui->X_size->setValidator(my_line_value);
    ui->X_size->setMaxLength(4);
    ui->X_size->setText("27");

    ui->Y_size->setValidator(my_line_value);
    ui->Y_size->setMaxLength(4);
    ui->Y_size->setText("22");

    ui->GoButton->setEnabled(false);
    ui->DijButton->setEnabled(false);
    ui->traceButton->setEnabled(false);

    ui->accurEdit->setValidator(my_line_value);



    //ui->tableView->setModel();
 //   ui->tableView->show();
//    ui->tableView->set
//    ui->tableView->height(100);
  //   ui->tableView->repaint();


    QObject::connect(ui->Dimension_but, SIGNAL(clicked()),ui->widget,SLOT(create_Matrix()) );
    QObject::connect(ui->widget, SIGNAL(ModelCreate(TableModel&)),ui->tableView, SLOT(fill_table(TableModel&)));
    QObject::connect(ui->Dimension_but, SIGNAL(clicked()),ui->label_Alg, SLOT(clear()) );
    QObject::connect(ui->GoButton, SIGNAL(clicked()),ui->label_Alg, SLOT(clear()) );
 //   QObject::connect(ui->mapButton, SIGNAL(clicked()),ui->widget,SLOT(create_Map_Matrix()));
    QObject::connect(ui->widget, SIGNAL(XChanged(QString)),ui->X_size,SLOT(setText(QString)));
    QObject::connect(ui->widget, SIGNAL(YChanged(QString)),ui->Y_size,SLOT(setText(QString)));

    My_scene *scene=new My_scene();
    ui->graphicsView->setScene(scene);

    QObject::connect(ui->widget, SIGNAL(ModelCreate(TableModel&)),scene , SLOT(fill_scene(TableModel&)));
    QObject::connect(ui->tableView,SIGNAL(dataChanged(QModelIndex)),scene , SLOT(fillChanges(QModelIndex)));
  //  QObject::connect(ui->tableView,SIGNAL(dataChanged(TableModel&),scene ,SLOT(fill_scene(TableModel&)));
     QObject::connect(scene, SIGNAL(BlackAreas(bool)),ui->Impass_Box, SLOT(setChecked(bool))   );
     QObject::connect(scene, SIGNAL(BlackAreas(bool)),ui->tableView, SLOT(reset()));
     QObject::connect(scene, SIGNAL(BlackAreas(bool)),ui->widget,SLOT(selected_Impassable(bool)) );

   //  QObject::connect(ui->widget, SIGNAL(ModelCreate(TableModel&)),scene,SLOT(take_model(TableModel&)));
    QObject::connect(scene,SIGNAL(GetIndex(QModelIndex&,int,int)),ui->widget, SLOT(send_index(QModelIndex&,int,int)));



    My_Way *my_way=new My_Way();
    QObject::connect(scene,SIGNAL(Start_Finish_Points(QModelIndex&,QModelIndex&)), my_way, SLOT(Get_Start_Finish_Points(QModelIndex&,QModelIndex&)));
    QObject::connect(my_way,SIGNAL(GetIndex(QModelIndex&,int,int)),ui->widget, SLOT(send_index(QModelIndex&,int,int)));
    QObject::connect(my_way,SIGNAL(GetXY(QModelIndex&)),ui->widget, SLOT(send_XY(QModelIndex&)));
    QObject::connect(my_way,SIGNAL(Progress(int)),ui->progressBar,SLOT(setValue(int)));
    QObject::connect(ui->accurEdit,SIGNAL(textEdited(QString)), my_way, SLOT(Set_Accuracy_val(QString)));
    QObject::connect(my_way,SIGNAL(AlgBrush(QColor)),scene, SLOT(SetAlgBrush(QColor)));

    int accur=0;
    int accur_max=(ui->X_size->text().toInt()>ui->Y_size->text().toInt()) ? ui->X_size->text().toInt(): ui->Y_size->text().toInt();
    for (int i=0; i<= accur_max;i++) accur+=i; accur/=10;
    if (accur>999) accur=999;
    ui->accurEdit->setText(QString::number(accur));
    emit ui->accurEdit->textEdited(QString::number(accur));
    QObject::connect(ui->X_size,&QLineEdit::textChanged, [this](QString val)mutable{int accur=0;
                                                                                    int accur_max=(val.toInt()>ui->Y_size->text().toInt()) ? val.toInt(): ui->Y_size->text().toInt();
                                                                                    for (int i=0; i<= accur_max;i++) accur+=i; accur/=10;
                                                                                    if (accur>999) accur=999;
                                                                                    ui->accurEdit->setText(QString::number(accur));
                                                                                    emit ui->accurEdit->textEdited(QString::number(accur)); });
    QObject::connect(ui->Y_size,&QLineEdit::textChanged, [this](QString val)mutable{int accur=0;
                                                                                    int accur_max=(val.toInt()>ui->X_size->text().toInt()) ? val.toInt(): ui->X_size->text().toInt();
                                                                                    for (int i=0; i<= accur_max;i++) accur+=i; accur/=10;
                                                                                    if (accur>999) accur=999;
                                                                                    ui->accurEdit->setText(QString::number(accur));
                                                                                    emit ui->accurEdit->textEdited(QString::number(accur)); });

    QObject::connect(my_way,SIGNAL(AlgName(QString)),ui->label_Alg,SLOT(setText(QString)));

    //Go
    QObject::connect(ui->Dimension_but, SIGNAL(clicked(bool)) ,ui->GoButton, SLOT(setEnabled(bool)));
    QObject::connect(scene,SIGNAL(enableGo(bool)),ui->GoButton, SLOT(setEnabled(bool)));
    QObject::connect(ui->GoButton, SIGNAL(clicked(bool)),my_way, SLOT(Finding_Way()));
    QObject::connect(ui->DijButton, SIGNAL(clicked(bool)),my_way, SLOT(Finding_Dij_Way()));
    QObject::connect(ui->Dimension_but, SIGNAL(clicked(bool)) ,ui->DijButton, SLOT(setEnabled(bool)));
    QObject::connect(scene,SIGNAL(enableGo(bool)),ui->DijButton, SLOT(setEnabled(bool)));
    QObject::connect(scene,SIGNAL(enableTrace(bool)),ui->traceButton, SLOT(setEnabled(bool)));

    QObject::connect(my_way,SIGNAL(PaintingWay(QModelIndex)),scene , SLOT(fillChanges(QModelIndex)));
    QObject::connect(my_way,SIGNAL(Way_long(int)),ui->lcdNumber, SLOT(display(int)) );
    QObject::connect(ui->Impass_Box, SIGNAL(clicked(bool)),my_way,SLOT(selected_Impassable(bool)) );
    QObject::connect(ui->Dimension_but, SIGNAL(clicked()),my_way, SLOT(clear_Way()));
    QObject::connect(my_way,SIGNAL(DrawingWay(bool)),ui->GoButton, SLOT(setDisabled(bool)));
    QObject::connect(my_way,SIGNAL(DrawingWay(bool)),ui->DijButton, SLOT(setDisabled(bool)));
    QObject::connect(scene,SIGNAL(enableGo(bool))  , ui->tableView, SLOT(setDisabled(bool)));
    QObject::connect(ui->Dimension_but, SIGNAL(clicked(bool)),ui->tableView, SLOT(setDisabled(bool)));
    QObject::connect(scene, SIGNAL(BlackAreas(bool)),my_way,SLOT(selected_Impassable(bool)) );
    QObject::connect(my_way,SIGNAL(DrawingWay(bool))   , ui->tableView, SLOT(setDisabled(bool)));
    QObject::connect(ui->mapButton,SIGNAL(clicked(bool)),my_way, SLOT(map_is_selected(bool)));
    QObject::connect(my_way, SIGNAL(DomIsTrue(bool)), ui->Impass_Box, SLOT(setChecked(bool)));
    QObject::connect(ui->Dimension_but, SIGNAL(clicked(bool)), my_way, SLOT(map_is_not_selected(bool)));

    //Size
    int prev_value_2=1;

    QObject::connect(ui->dial,&QDial::valueChanged,[this,prev_value_2](qreal angle)mutable{
                                                                             if (angle<prev_value_2)
              {ui->graphicsView->scale(1+1/(-static_cast <int>(angle)+prev_value_2),1+1/(-static_cast <int>(angle)+prev_value_2)); }
                                                                    else ui->graphicsView->scale (0.5,0.5);prev_value_2=angle;});

    //Tracing
     ui->graphicsView->setMouseTracking(true);
     QObject::connect(ui->traceButton, SIGNAL(clicked(bool)),scene, SLOT(SetTracing(/*bool*/)));
     QObject::connect(ui->Dimension_but, SIGNAL(clicked(bool)) ,ui->traceButton, SLOT(setEnabled(bool)));
     QObject::connect(scene, SIGNAL(findTheWay()),my_way,SLOT(Finding_Tracing_Way()));
     QObject::connect(my_way, SIGNAL(Set_Start_Finish_Points(QModelIndex&,QModelIndex&)),scene, SLOT(Get_Start_Finish_Index(QModelIndex&,QModelIndex&)));
     QObject::connect(my_way, SIGNAL(Checked(bool)),scene, SLOT(Check_Points(bool)));
     QObject::connect(my_way, SIGNAL(Reached(bool)),scene, SLOT(Reached(bool)));
     QObject::connect(scene, SIGNAL(ReachNotToTrace()),my_way, SLOT(ReachNotToTrace()));
   //  QObject::connect(scene, SIGNAL(kill_Timer()),my_way, SLOT(kill_Timer()));
     QObject::connect(ui->traceButton, SIGNAL(clicked(bool)),my_way,SLOT(Create_matrix_for_Dijkstra_faster()));
   //  QObject::connect(my_way, SIGNAL(Timer_lapse(int)),scene, SLOT(Timer_lapse(int)));

    //menubar
    m_bar= new QMenuBar(this);
    info=new QMenu(tr("Information"));

    help_action=new QAction(tr("Help"));
    QIcon icon_help(":/Icons/iconInstructions.ico");
    help_action->setIcon(icon_help);
    info->addAction(help_action);

    about_action=new QAction(tr("About"));
    QIcon icon_info(":/Icons/iconInfo.ico");
    about_action->setIcon(icon_info);
    info->addAction(about_action);

    open=new QMenu(tr("File"));
    open_table_action=new QAction(tr("Open table"));
    save_table_action=new QAction(tr("Save table"));
    open_map_action=new QAction(tr("Open map"));
    open->addAction(open_table_action);
    open->addAction(save_table_action);
    open->addAction(open_map_action);

    m_bar->addMenu(open);
    m_bar->addMenu(info);

    QObject::connect(about_action, SIGNAL(triggered(bool)),this,SLOT(on_about_action_triggered()) );
    QObject::connect(help_action, SIGNAL(triggered(bool)),this,SLOT(on_help_action_triggered()) );

    QObject::connect(save_table_action, SIGNAL(triggered(bool)),this,SLOT(on_save_table_action_triggered()) );
    QObject::connect(this, SIGNAL(toSaveInFile(QTextStream&)),ui->widget,SLOT(sendToSaveInFile(QTextStream&)));

    QObject::connect(open_table_action, SIGNAL(triggered(bool)),this,SLOT(on_open_table_action_triggered()) );
    QObject::connect(this, SIGNAL(toOpenFromFile(QTextStream&)),ui->widget,SLOT(takeToOpenFromFile(QTextStream&)));

    QObject::connect(open_map_action, SIGNAL(triggered(bool)),this,SLOT(on_open_map_action_triggered()) );
    QObject::connect(this, SIGNAL(sendMap(QString&)) ,ui->widget,SLOT(create_Map_Matrix(QString&)));
    QObject::connect(open_map_action, SIGNAL(triggered(bool)),my_way, SLOT(map_is_selected(bool)));
    QObject::connect(ui->mapButton, SIGNAL(clicked()),open_map_action,SLOT(trigger()));
    ui->mapButton->hide();  //!!!!  убрал кнопку опционально



}

void Navogator::on_about_action_triggered(){
    QMessageBox::information(this,"Navigator",tr("Minimum path finder on 4-linked fields\n"),
                                              "Nazarov Aleksandr\n"
                                              "2024\n"
                                              "nazarov-alexandr@mail.ru\n"
                                              "Version: v3.2");
}

void Navogator::on_help_action_triggered(){
    QMessageBox::information(this,tr("Help"),tr("1. Choose the size of the field\n"
                                         "2. You can create impassable areas (also right button)\n"
                                         "3. You can create uniform field\n"
                                         "4. Select first and last point\n"
                                         "5. If you're using Customs algorithms, set number of iterations\n"
                                         "6. You can also use the Dijkstra algorithm\n"
                                         "7. You can dynamically follow the finish point:\n"
                                         "    select a starting point and click \"Tracing\""));
}

void Navogator::on_save_table_action_triggered(){
    QString filePath=QFileDialog::getSaveFileName(nullptr, "Save table",QDir::currentPath()/*homePath()*/,"Text files (*.txt)");
    if (!filePath.isEmpty()){

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {

            QTextStream out(&file);

            emit toSaveInFile(out);

            file.close();
        }

    }
}


void Navogator::on_open_table_action_triggered(){
    QString filePath=QFileDialog::getOpenFileName(nullptr, "Open table",QDir::currentPath(),"Text files (*.txt)");
        if (!filePath.isEmpty()){
            QFile file(filePath);
                if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
                    QTextStream in(&file);
              //      QString text=in.readAll();
               //     qDebug()<<text ;
                    emit toOpenFromFile(in);
                    file.close();
                }
        }
}


void Navogator::on_open_map_action_triggered(){

    QString filePath=QFileDialog::getOpenFileName(nullptr, "Open map",QDir::currentPath(),"Map files (*.png)");
    emit sendMap(filePath);
}


Navogator::~Navogator()
{
    delete m_bar;
    delete info;
    delete help_action;
    delete about_action;
    delete ui;
}



void Navogator::paintEvent(QPaintEvent *event)
{
    m_bar->setGeometry(0,0,this->width(),21);

    ui->graphicsView->setGeometry(10,30,this->width()/2, this->height()-15-m_bar->height());
    ui->widget->setGeometry(ui->graphicsView->x()+ui->graphicsView->width(),ui->graphicsView->y(), 130, 425 );
    ui->tableView->setGeometry(ui->widget->x()+ui->widget->width(),ui->widget->y(),this->width()/2-150, ui->graphicsView->height());
}

//QMenuBar* Navogator::createmenubar(QFrame *frame){
//    QMenuBar* bar= new QMenuBar(frame/*,Qt::WindowStaysOnTopHint*/);//    ("No",frame,Qt::WindowStaysOnTopHint);
//  //  label->setFrameStyle(QFrame::Box );
//   // label->setMinimumWidth(20);
//   // label->setMaximumWidth(30);
//   // label->setMaximumHeight(20);
// //   label->setAlignment(Qt::AlignCenter );
//   // label->setPixmap("");

//  return bar;
//}

