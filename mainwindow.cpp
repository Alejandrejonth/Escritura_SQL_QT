#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QtNetwork>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QDebug>


QSqlDatabase baseDeDatos = QSqlDatabase::addDatabase("QMYSQL");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //configurar base de datos.
    //Paso#1. cofigurar el servidor de la base de datos.
    baseDeDatos.setHostName("localhost");
    //baseDeDatos.setHostName("https://paginaweb.com");

    //Paso#2 configurar el puerto.
    baseDeDatos.setPort(3306);

    //Paso#3 configurar a que Bd nos conectaremos.
    baseDeDatos.setDatabaseName("2021B2");

    //Paso#4. Configurar el usuario al que se conectará.
    baseDeDatos.setUserName("admin51");

    //Paso #5 Configurar la contraseña del usuario anterior.
    baseDeDatos.setPassword("hola1234");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //Paso #1. Guardar la información ingresada en variables
    QString nombre = ui->lineEdit->text();
    QString apellido1 = ui->lineEdit_2->text();
    QString apellido2 = ui->lineEdit_3->text();
    QString codigo = ui->lineEdit_4->text();

    //obtener la fecha.
    //formato UNIX
    long int fechaUnix = QDateTime::currentSecsSinceEpoch();

    //Formato String
    QDateTime tiempo= QDateTime::currentDateTime();
    QString fechaString = tiempo.toString();

    ui->lineEdit_5->setText(fechaString);

    //Paso # 2. Hacer la conexión con la base de datos.
       if(baseDeDatos.open()){
           //Paso # 2.1 Preparar un comando de mysql para insertar los datos.
           QString comandoTexto = "INSERT INTO ejemplo3(nombre, apellidoPaterno, apellidoMaterno, codigo, fecha) VALUES (?, ?, ?, ?, ?)";

           //Paso # 2.2 Crear el comando mysql
           QSqlQuery comando;

           //Paso # 2.3 Preparar e inicializar el comando anterior.
           comando.prepare(comandoTexto);
           comando.addBindValue(nombre);
           comando.addBindValue(apellido1);
           comando.addBindValue(apellido2);
           comando.addBindValue(codigo);
           comando.addBindValue(QString::number(fechaUnix));

           //Paso # 2.4 Ejecutar el comando de mysql.
           if(comando.exec()){
               qDebug()<<"La fila se inserto";
           }
           else{
               qDebug()<<"Error_unu";
           }
       }
       else{
           qDebug() << "Error al abrir la base de datos";
           qDebug() << "Verifica la contraseña,";
           qDebug() << "Nombre de la base de datos,";
           qDebug() << "Nombre de la tabla de base de datos";
           //qDebug() << "La estructura y los datos enviados no coinciden";
       }


}

