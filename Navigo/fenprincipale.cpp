#include <iostream>
#include "fenprincipale.h"
#include "qlineeditperso.h"
#include "qcheckboxcustom.h"
#include "ui_fenprincipale.h"
//#include <vector>
//#include <QRegExp>
//using namespace std;

FenPrincipale::FenPrincipale(QWidget *parent) :QMainWindow(parent),ui(new Ui::FenPrincipale)
{

    ui->setupUi(this);
    i=0;
    //settings=new QSettings(tr("Mon équipe"),tr("Navigo"),this);
    settings =new QSettings("leFichierDesFavoris.ini",QSettings::IniFormat);
    //settings=settings2;

    setFocusPolicy(Qt::ClickFocus);

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *nouvelOnglet = menuFichier->addAction("Nouvel Onglet");
    QAction *fermerOnglet = menuFichier->addAction("Fermer Onglet");

    QMenu *menuNavigation = menuBar()->addMenu("&Navigation");
    QAction *pagePrecedent = menuNavigation->addAction("&Precedent");
    pagePrecedent->setIcon(QIcon("prec.png"));
     //pagePrecedent->setIcon(QIcon("flow.png"));
    //if_Flower_131690
    QAction *pageSuivante = menuNavigation->addAction("&Suivante");
    pageSuivante->setIcon(QIcon("suiv.png"));

    QAction *actualiser = menuNavigation->addAction("&Actualiser");
    actualiser->setIcon(QIcon("actu.png"));

    QAction *stop = menuNavigation->addAction("&Arrêter");
    stop->setIcon(QIcon("stop"));

    QAction *welcome = menuNavigation->addAction("&Accueil");
    welcome->setIcon(QIcon("home.png"));

    //urlDefault ="google.fr";
    urlDefault="http://google.fr";
    adressUrl = new QLineEdit(urlDefault);
    //adressUrl->setMaximumSize(400,10);

    //std::cout<<"urlDefaut vaut"<<urlDefault.toStdString()<<'\n';
    historique=new QComboBox;

    //QAction *optionsParameters = menuNavigation->addAction("Options");

  //  optionsParameters->setIcon(QIcon("if_Flower_131690.png"));
    QAction *go = menuNavigation->addAction(tr("&Aller sur le lien"));
    go->setIcon(QIcon("go.png"));

    QAction *openTab = menuNavigation->addAction(tr("&Ouvrir un nouvel onglet"));

    QAction *actionChercherTexte = menuNavigation->addAction(tr("&Recherche"));
    actionChercherTexte->setShortcut(QKeySequence("Ctrl+F"));
    //actionChercherTexte->addShortCut(QKeySequence("Ctrl+F"));

    QMenu *options = menuBar()->addMenu(tr("&options"));
    QAction *optionsParameters = options->addAction(tr("Paramètres par défaut"));
    optionsParameters->setIcon(QIcon("flow.png"));

    QAction *favoris = options->addAction(tr("Marquer cette page"));
    favoris->setIcon(QIcon("8719.png"));
    QAction *bookMarkDisplay = options->addAction(tr("Afficher les marques-pages"));
    bookMarkDisplay->setIcon(QIcon("if_Documents_657906.png"));

    QMenu *help = menuBar()->addMenu("&?");
    QAction *apropos = help->addAction(tr("à propos"));
    QAction *aproposde = help->addAction(tr("à propos de"));


    QWidget *widgetUrlHistorique = new QWidget;
    widgetUrlHistorique->setMaximumSize(900,90);
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(adressUrl);
    lay->addWidget(historique);
    widgetUrlHistorique->setLayout(lay);
/*
    dialogListeFavoris = new QDialog;
    //frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    //frame->setLineWidth(1);
    dialogListeFavoris->setWindowTitle("Les favoris");
    dialogListeFavoris->setWindowIcon(QIcon("8719.png"));
    QVBoxLayout *layoutDialogListeFavoris = new QVBoxLayout;

    groupeFavorites = new QGroupBox(QString(),dialogListeFavoris);
    layoutDialogListeFavoris->addWidget(groupeFavorites);
    dialogListeFavoris->setLayout(layoutDialogListeFavoris);

    vboxGroupeFavorites = new QVBoxLayout;
*/
    ui->mainToolBar->addAction(pagePrecedent);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(pageSuivante);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actualiser);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(stop);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(welcome);
    ui->mainToolBar->addSeparator();
    //ui->mainToolBar->addWidget(adressUrl);
    ui->mainToolBar->addWidget(widgetUrlHistorique);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(optionsParameters);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(favoris);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(bookMarkDisplay);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(go);

    QWidget *page = new QWidget;
    page->setGeometry(10,10,2500,1000);
    indexPageAccueil=ui->onglets->addTab(page,urlDefault);
    //QWebView *pageWeb = new QWebView(ui->onglets->widget(0));
    QWebView *pageWeb = new QWebView(page);
    std::cout<<"initialisation du qwebview"<<'\n';
    std::cout<< &pageWeb<<'\n';
    //ui->centralWidget->show();
    pageWeb->setGeometry(10,10,2500,1000);
    pageWeb->load(QUrl(urlDefault));
    historique->addItem(urlDefault);

    QObject::connect(nouvelOnglet,SIGNAL(triggered(bool)),this,SLOT(NouvelOnglet()));
    QObject::connect(adressUrl,SIGNAL(editingFinished()),this,SLOT(goToLinkInTab()));
    QObject::connect(pagePrecedent,SIGNAL(triggered(bool)),this,SLOT(allerPagePrecedente()));
    QObject::connect(pageSuivante,SIGNAL(triggered(bool)),this,SLOT(allerPageSuivante()));
    QObject::connect(stop,SIGNAL(triggered(bool)),this,SLOT(stopLoadingPage()));
    QObject::connect(actualiser,SIGNAL(triggered(bool)),this,SLOT(recharger()));
    QObject::connect(welcome,SIGNAL(triggered(bool)),this,SLOT(backToHostPage()));
    QObject::connect(openTab,SIGNAL(triggered(bool)),this,SLOT(NouvelOnglet()));
    QObject::connect(ui->onglets->currentWidget()->findChild<QWebView *>(),SIGNAL(loadProgress(int)),ui->barProgression,SLOT(setValue(int)));
    QObject::connect(ui->onglets->currentWidget()->findChild<QWebView *>(),SIGNAL(loadFinished(bool)),this,SLOT(hideQProgress()));

    QObject::connect(go,SIGNAL(triggered(bool)),this,SLOT(goToLinkInTab()));
    //QObject::connect(adressUrl,SIGNAL(editingFinished()),this,SLOT(changerTitre()));
    QObject::connect(historique,SIGNAL(currentTextChanged(QString)),this,SLOT(goToLinkInTab(QString)));

    QObject::connect(actionChercherTexte,SIGNAL(triggered(bool)),this,SLOT(showWindowSearchText()));
    //QObject::connect(this,SIGNAL(clicked()),this,SLOT(hideWindowSearchText()));

    //ui->windowSearchText->mousePressEvent
    QObject::connect(ui->windowSearchText,SIGNAL(editingFinished()),this,SLOT(rechercheTexte()));

    QObject::connect(actionChercherTexte,SIGNAL(triggered(bool)),this,SLOT(putCursorInQLineEditSearchText()));
    QObject::connect(optionsParameters,SIGNAL(triggered(bool)),this,SLOT(generateWindowOptions()));

    QObject::connect(favoris,SIGNAL(triggered(bool)),this,SLOT(marquerFavori()));
    QObject::connect(bookMarkDisplay,SIGNAL(triggered(bool)),this,SLOT(ouvrirListeFavoris()));


}

FenPrincipale::~FenPrincipale()
{
    delete ui;
}

void FenPrincipale::NouvelOnglet(){
    //ui->onglets->currentWidget()->findChild<QWebView *>()->history()->clear();
    //ui->onglets->currentWidget()->findChild<QWebView *>()->history()->update();
    QWidget *page = new QWidget;
    //adressUrl->setText(QString());

    ui->onglets->setStyleSheet("QTabBar::tab { width: 200 px; }");
    ui->onglets->setElideMode(Qt::ElideRight);

    QWebView *pageWeb = new QWebView(page);
    std::cout<<"nouvel onglet qwebview"<<'\n';
    std::cout<< &pageWeb<<'\n';
    std::cout<<"compte historique"<<pageWeb->history()->count()<<'\n';
    //if(pageWeb->history()->count()==1)
    //    std::cout<<"cela vaut 1"<<'\n';
    pageWeb->setGeometry(10,10,1450,950);


    ui->onglets->setCurrentWidget(ui->onglets->widget(ui->onglets->addTab(page,urlDefault)));
    //pageWeb=ui->onglets->currentWidget()->findChild<QWebView *>();
    transformationLienSansHttpAvecHttpUrlDefault();
    pageWeb->load(QUrl(urlDefault));
    ui->barProgression->show();
    adressUrl->setText(QString());

    QObject::connect(ui->onglets->currentWidget()->findChild<QWebView *>(),SIGNAL(loadFinished(bool)),this,SLOT(hideQProgress()));
    //QObject::connect(pageWeb,SIGNAL(loadFinished(bool)),this,SLOT(hideQProgress()));

    std::cout<<"urlDefaut vaut"<<urlDefault.toStdString()<<'\n';
    std::cout<<"adresseUrl vaut"<<adressUrl->text().toStdString()<<'\n';
}

void FenPrincipale::transformationLienSansHttpAvecHttp(){
     QRegExp r("http://");
    if(r.indexIn(adressUrl->text())==-1)
        {
            adressUrl->setText("http://"+adressUrl->text());
        }
}

void FenPrincipale::transformationLienSansHttpAvecHttpUrlDefault(){
     QRegExp r("http://");
    if(r.indexIn(urlDefault)==-1)
        {
            urlDefault="http://"+urlDefault;
        }

}

void FenPrincipale::goToLinkInTab(){
    QString titre=ui->onglets->currentWidget()->findChild<QWebView *>()->history()->currentItem().originalUrl().authority();
    historique->addItem(titre);//.section('/',2,2));
    ui->onglets->currentWidget()->findChild<QWebView *>()->history()->clear();

    ui->barProgression->show();
   transformationLienSansHttpAvecHttp();
   QWebView *pageWebTemp = new QWebView;
   pageWebTemp= ui->onglets->currentWidget()->findChild<QWebView *>();
   pageWebTemp->load(QUrl(adressUrl->text()));

   setWindowTitle(ui->onglets->currentWidget()->findChild<QWebView *>()->url().toString().section('/',2,2));
   ui->onglets->setTabText(ui->onglets->currentIndex(),ui->onglets->currentWidget()->findChild<QWebView *>()->history()->currentItem().originalUrl().toString());
}

void FenPrincipale::goToLinkInTab(QString str){   //fonction appelée quand on clique

    ui->barProgression->show();

    adressUrl->setText(str);  //sur un des items du QComboBox
   transformationLienSansHttpAvecHttp();
   QWebView *pageWebTemp = new QWebView;
   pageWebTemp= ui->onglets->currentWidget()->findChild<QWebView *>();
   pageWebTemp->load(QUrl(adressUrl->text()));

   setWindowTitle(ui->onglets->currentWidget()->findChild<QWebView *>()->url().toString().section('/',2,2));

   QRegExp r("https?://([a-z]+)\\.([a-z]{2,4})");
   QString titreOnglet =ui->onglets->currentWidget()->findChild<QWebView *>()->history()->currentItem().originalUrl().authority();
   ui->onglets->setTabText( ui->onglets->currentIndex(),titreOnglet);

   historique->addItem(titreOnglet);
   //ui->onglets->currentWidget()->findChild<QWebView *>()->history()->currentItem().originalUrl().toString());//.section('/',2,2));

   ui->onglets->currentWidget()->findChild<QWebView *>()->history()->clear();
}

void FenPrincipale::allerPagePrecedente(){
    ui->barProgression->show();
    ui->onglets->currentWidget()->findChild<QWebView *>()->back();
}

void FenPrincipale::allerPageSuivante(){
     ui->barProgression->show();
    ui->onglets->currentWidget()->findChild<QWebView *>()->forward();
    //update();
}

void FenPrincipale::stopLoadingPage(){
    ui->onglets->currentWidget()->findChild<QWebView *>()->stop();
}

void FenPrincipale::recharger(){
     ui->barProgression->show();
    ui->onglets->currentWidget()->findChild<QWebView *>()->reload();
}

void FenPrincipale::backToHostPage(){
     ui->barProgression->show();
    ui->onglets->setCurrentWidget(ui->onglets->widget(indexPageAccueil));

}

void FenPrincipale::rechercheTexte(){
    ui->onglets->currentWidget()->findChild<QWebView *>()->findText(ui->windowSearchText->text());
   }

void FenPrincipale::putCursorInQLineEditSearchText(){
    ui->windowSearchText->setFocus();
}

void FenPrincipale::generateWindowOptions(){
    windowDialog = new QDialog;
    windowDialog->setWindowTitle("Paramètres optionnels");
    windowDialog->setWindowIcon(QIcon("flow.png"));
    windowDialog->setWindowIconText("salut, ça gaze ?");

    windowDialog->setGeometry(400,200,500,300);
    QVBoxLayout *lay = new QVBoxLayout;

    //QLabel *questionChoixPolice = new QLabel(tr("Quel choix de style veux-tu faire ?"));
    //choixPolice = new QFontComboBox;
    QLabel *questionTaillePolice = new QLabel(tr("Quelle taille de police ?"));
    taillePolice = new QSpinBox;
    QLabel *questionUrlDefault = new QLabel(tr("Quel est l'url par défaut que tu veux ?"));
    choixUrlDefault = new QLineEdit;
    QPushButton *OK = new QPushButton(tr("OK"));
    OK->resize(80,100);
    //lay->addWidget(questionChoixPolice);
    //lay->addWidget(choixPolice);
    lay->addWidget(questionTaillePolice);
    lay->addWidget(taillePolice);
    lay->addWidget(questionUrlDefault);
    lay->addWidget(choixUrlDefault);
    lay->addWidget(OK);

    windowDialog->setLayout(lay);

    windowDialog->show();

    QObject::connect(OK,SIGNAL(clicked(bool)),this,SLOT(applyUrlDefaultFontSize()));
    //QObject::connect(choixUrlDefault,SIGNAL(editingFinished()),this,SLOT(changeUrlDefault()));
}

void FenPrincipale::applyUrlDefaultFontSize(){
    //QWebSettings
    QWebSettings::globalSettings()->setFontSize(QWebSettings::DefaultFontSize,taillePolice->value());
    update();
    //show();
    //QWebSettings::globalSettings()->setFontFamily();
    urlDefault=choixUrlDefault->text();
    //changeUrlDefault();
    saveInQSettings();
    //windowDialog->hide();
}




void FenPrincipale::saveInQSettings(){

    settings->setValue(tr("url par défaut"),urlDefault);
    settings->setValue(tr("Taille de Font"),taillePolice->value());
    //settings->setValue("Style police de caractères",);
}

void FenPrincipale::hideQProgress(){
    ui->barProgression->hide();
    this->update();
}


void FenPrincipale::showWindowSearchText(){
    //ui->windowSearchText->show();
    ui->windowSearchText->setVisible(true);
    //QObject::connect(this,SIGNAL(clicked()),this,SLOT(hideWindowSearchText()));
    //ui->windowSearchText  //mousePressEvent();->mousePressEvent();
}



void FenPrincipale::marquerFavori(){

    settings->setValue(ui->onglets->currentWidget()->findChild<QWebView *>()->title(),ui->onglets->currentWidget()->findChild<QWebView *>()->url().toString());
//faire un test de non-redondance
   QMessageBox::information(this,"Ajout aux favoris", "Vous avez ajouté le site suivant : "+QString("\n") + ui->onglets->currentWidget()->findChild<QWebView *>()->url().toString());

}

void FenPrincipale::ouvrirListeFavoris(){


    dialogListeFavoris = new QDialog;

    dialogListeFavoris->setWindowTitle("Les favoris");
    dialogListeFavoris->setWindowIcon(QIcon("8719.png"));
    QVBoxLayout *layoutDialogListeFavoris = new QVBoxLayout;

    groupeFavorites = new QGroupBox(QString(),dialogListeFavoris);
    layoutDialogListeFavoris->addWidget(groupeFavorites);
    dialogListeFavoris->setLayout(layoutDialogListeFavoris);
    //QObject::connect(dialogListeFavoris,&QDialog::destroyed,[=](){dialogListeFavoris->deleteLater();});

    vboxGroupeFavorites = new QVBoxLayout;

    QStringList keys=settings->allKeys();

    std::vector<QCheckBox*> checkBox1;
    std::vector<QCheckBoxCustom*> checkBox;
    int i=0;
    for(auto it=keys.begin();it !=keys.end();it++){
        checkBox1.push_back(new QCheckBox(settings->value(*it).toString(),groupeFavorites));
     }
    for(auto i(0);i<checkBox1.size();i++){
        checkBox.push_back(new QCheckBoxCustom(checkBox1[i]));
        checkBox1[i]->setChecked(false);
        checkBox[i]->setChecked(false);

        std::cout<<checkBox1[i]->text().toStdString()<<std::endl;

        QWidget *page=new QWidget(ui->centralWidget);
        page->setGeometry(10,10,900,1000);
        std::cout<<"initilaisation du page"<<std::endl;

        QWebView *pageWeb = new QWebView(page);
        pageWeb->setGeometry(10,10,1900,1000);
        std::cout<<"initilaisation du pageWeb"<<std::endl;

        QObject::connect(checkBox1[i],&QCheckBox::stateChanged,[=](){
            std::cout<<"test du premier connect"<<std::endl;
            checkBox[i]->setChecked(true);
             std::cout<<"état du CheckBox"<<checkBox[i]->checkState()<<std::endl;
            checkBox[i]->setCheckedCustom();});

        QObject::connect(checkBox[i],&QCheckBoxCustom::isCheckedSignal,[=](){
                        //std::cout<<settings->value(*it).toString()<<std::endl;
                        pageWeb->load(QUrl(checkBox1[i]->text()));

                        ui->onglets->addTab(page,QUrl(checkBox1[i]->text()).host());
                        std::cout<<"tedt du deuxième connect"<<std::endl;
                                                                });
        vboxGroupeFavorites->addWidget(checkBox1[i]);
                            
    }
    
    std::cout<<"taille de checkBox1"<<checkBox1.size()<<std::endl;
    std::cout<<"taille de checkBox"<<checkBox.size()<<std::endl;

/*
    QObject::connect(dialogListeFavoris,&QDialog::destroyed,[=](){
        for(auto it=checkBox1.begin();it!=checkBox1.end();it++){
            delete checkBox1[i];
            delete checkBox[i];}});
*/

    groupeFavorites->setLayout(vboxGroupeFavorites);

    dialogListeFavoris->show();

}

