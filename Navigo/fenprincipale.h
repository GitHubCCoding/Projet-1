#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QLineEdit>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QtWidgets/QTableWidget>
#include <QWidget>
//#include <QWebView>

namespace Ui {
class FenPrincipale;
}

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenPrincipale(QWidget *parent = 0);
    void transformationLienSansHttpAvecHttp();
    void transformationLienSansHttpAvecHttpUrlDefault();
    void saveInQSettings();
    //virtual void mousePressEvent(QMouseEvent *event);
    //virtual void focusOutEvent(QFocusEvent *event);
    ~FenPrincipale();
    //void completeHistoric();

private:
    Ui::FenPrincipale *ui;
    QLineEdit *adressUrl;
    int indexPageAccueil;
    QComboBox *historique;
    QString urlDefault;
    QLineEdit *choixUrlDefault;
    QDialog *windowDialog;
    QFontComboBox *choixPolice;
    QSpinBox *taillePolice;
    int i;
    QSettings *settings;
    QDialog *dialogListeFavoris;
    QGroupBox *groupeFavorites;
    QVBoxLayout *vboxGroupeFavorites;
    //QCheckBox *checkBox;
    //QWebHistory *historiqueQWebHistory;
    //QTabWidget *onglets;

public slots:
    void NouvelOnglet();
    void goToLinkInTab(QString str);
    void goToLinkInTab();
    //void goToLinkInTab();
    void allerPagePrecedente();

    void allerPageSuivante();
    void stopLoadingPage();
    void recharger();
    void backToHostPage();
    void rechercheTexte();
    void putCursorInQLineEditSearchText();
    void generateWindowOptions();
    //void changeUrlDefault();
    void hideQProgress();
    void showWindowSearchText();
    void applyUrlDefaultFontSize();
    void marquerFavori();
    void ouvrirListeFavoris();
    //void deleteCheckBoxFavorite();
    //void hideWindowSearchText();
    //void changerTitre();
    //QString raccourciUrl();

signals:
    void clicked();
//protected:
    //virtual void mousePressEvent(QMouseEvent *event);
};


#endif // FENPRINCIPALE_H
