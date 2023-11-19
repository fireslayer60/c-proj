// mainwindow.cpp
#include "mainwindow.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <iostream>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/* 7d2ac63df9c82da33d4e81eb2c46361f*/
struct Node {
    QString name;
    QString artist;
    QString url;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    void append(const QString& name, const QString& artist,const QString& url) {
        Node* newNode = new Node;
        newNode->name = name;
        newNode->url = url;
        newNode->artist = artist;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display() const {
        Node* current = head;
        while (current) {
            qDebug() << current->name << "by" << current->artist;
            current = current->next;
        }
    }

    QString getrand() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 49);
        int randNum = dist(gen);
        Node* current = head;
        for(int i=0;i<randNum;i++){
            current = current->next;
        }
        return current->name + " by " + current->artist+"   URL--->  "+current->url ;
    }

private:
    Node* head;
};

QString MainWindow::fetchSongs(const QString &genre) {

    QEventLoop eventLoop;


    QString lastFmApiKey = "7d2ac63df9c82da33d4e81eb2c46361f";
    QString lastFmEndpoint = "http://ws.audioscrobbler.com/2.0/?method=tag.gettoptracks&tag=" + genre + "&api_key=" + lastFmApiKey + "&format=json";
/* "http://ws.audioscrobbler.com/2.0/?method=tag.gettoptracks&tag=rock&api_key=7d2ac63df9c82da33d4e81eb2c46361f&format=json"*/
    QNetworkAccessManager manager;


    QNetworkRequest request;
    request.setUrl(QUrl(lastFmEndpoint));

    QNetworkReply *reply = manager.get(request);


    LinkedList songList;

    QString result,urll;


    QObject::connect(reply, &QNetworkReply::finished, this, [=, &eventLoop, &result, &songList]() {
        int yo=0;
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);


            QJsonObject jsonResponse = doc.object();
            QJsonObject tracks = jsonResponse["tracks"].toObject();
            QJsonArray trackArray = tracks["track"].toArray();

            qDebug() << "Top songs in the genre:" << genre;
            for (const QJsonValue &trackValue : trackArray) {
                QJsonObject track = trackValue.toObject();
                QString name = track["name"].toString();
                QString url = track["url"].toString();
                QString artist = track["artist"].toObject()["name"].toString();

                qDebug() << name << "by" << artist;
                yo= yo+1;

                songList.append(name, artist,url);
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();

        qDebug() << yo;
        qDebug() << "List of songs in the genre:" << genre;


        result = songList.getrand();

        eventLoop.quit();
    });

    eventLoop.exec();


    return result;
}




QString hi;
QString hi2,h2;
QString hi3,h3;
QString hi4,h4;
QString hi5,h5;
QString hi6,h6;
void MainWindow::on_pushButton_clicked() {
    // Call fetchSongs with the desired genre, e.g., "rock"
    hi = ui->lineEdit->text();
    hi2 = fetchSongs(hi);
    hi3 = fetchSongs(hi);
    hi4 = fetchSongs(hi);
    hi5 = fetchSongs(hi);
    hi6 = fetchSongs(hi);
    ui->label_4->setText(hi2);
    ui->label_5->setText(hi3);
    ui->label_6->setText(hi4);
    ui->label_7->setText(hi5);
    ui->label_8->setText(hi6);
    ui->label_4->setTextFormat(Qt::RichText);
    ui->label_4->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_4->setOpenExternalLinks(true);
    ui->label_5->setTextFormat(Qt::RichText);
    ui->label_5->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_5->setOpenExternalLinks(true);
    ui->label_6->setTextFormat(Qt::RichText);
    ui->label_6->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_6->setOpenExternalLinks(true);
    ui->label_7->setTextFormat(Qt::RichText);
    ui->label_7->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_7->setOpenExternalLinks(true);
    ui->label_8->setTextFormat(Qt::RichText);
    ui->label_8->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label_8->setOpenExternalLinks(true);
}

