#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ComputerManager.h"
#include <QFileDialog>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("UTComputer");
    this->setFixedSize(700, 650);

    Pile& pile = Pile::getInstance();
    ComputerManager& CM = ComputerManager::getManager();


    saveButton = ui->Sauvegarde;

    message = ui->lineEdit_2;
    message->setReadOnly(true);

    ligne_de_commande = ui->lineEdit;
    ligne_de_commande->setFocus(Qt::OtherFocusReason);
    ligne_de_commande->installEventFilter(this);

    vuePile = ui->tableWidget;

    initPile();
    initVariableProgramme();

    shortcut1 = new QShortcut(QKeySequence("Ctrl+Z"),this);
    shortcut2 = new QShortcut(QKeySequence("Ctrl+Y"),this);

    connect(shortcut1,SIGNAL(activated()),this,SLOT(on_Undo_clicked()));
    connect(shortcut2,SIGNAL(activated()),this,SLOT(on_Redo_clicked()));

    connect(&pile, SIGNAL(modificationEtat()), this, SLOT(refresh()));
    connect(this, SIGNAL(operation()), this, SLOT(on_buttonEnter_clicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(changeNbViews()));
    this->chargeExec();
    connect(ui->vueProgramme, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateMapProgramme(QTableWidgetItem*)));
    connect(ui->vueVariable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateMapVariable(QTableWidgetItem*)));
    connect(ui->clavier, SIGNAL(stateChanged(int)), this, SLOT(toggleGraphicPad()));
    this->chargeExec();
}

void MainWindow::initPile(){
    Pile& pile = Pile::getInstance();
    pile.setMaxAffiche(7);
    vuePile->setRowCount(pile.getMaxAffiche());
    vuePile->setColumnCount(1);

    QStringList nombres;
    for(unsigned int i=pile.getMaxAffiche(); i>0; i--){
        QString str = QString::number(i);
        str+=" : ";
        nombres << str;
        vuePile->setItem(i - 1, 0, new QTableWidgetItem(""));
    }
    vuePile->setVerticalHeaderLabels(nombres);
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::chargeExec(){
    ComputerManager& CM = ComputerManager::getManager();
    try{
        CM.charger("etat.xml");
    }catch(ComputerException& CE){
        CE.getInfo();
    }


}

void MainWindow::initVariableProgramme(){
    ui->vueVariable->setRowCount(5);
    ui->vueVariable->setColumnCount(2);

    QStringList nombres;
    for(unsigned int i=7; i>0; i--){
        QString str = QString::number(5-i+1);
        str+=" : ";
        nombres << str;
        ui->vueVariable->setItem(i - 1, 0, new QTableWidgetItem(""));
        ui->vueVariable->setItem(i - 1, 1, new QTableWidgetItem(""));
    }
    ui->vueVariable->setVerticalHeaderLabels(nombres);
    ui->vueVariable->setEditTriggers(QAbstractItemView::AllEditTriggers);;

    ui->vueProgramme->setRowCount(5);
    ui->vueProgramme->setColumnCount(2);

    for(unsigned int i=7; i>0; i--){
        QString str = QString::number(i);
        str+=" : ";
        nombres << str;
        ui->vueProgramme->setItem(i - 1, 0, new QTableWidgetItem(""));
        ui->vueProgramme->setItem(i - 1, 1, new QTableWidgetItem(""));
    }
    ui->vueProgramme->setVerticalHeaderLabels(nombres);
    ui->vueProgramme->setEditTriggers(QAbstractItemView::AllEditTriggers);
}

void MainWindow::changeVariableProgrammeTable(){
    extern std::map<string,Litterale*> Map;
    for(unsigned int i=0; i<Map.size(); i++) {
        ui->vueVariable->setItem(i, 0, new QTableWidgetItem(""));
        ui->vueVariable->setItem(i, 1, new QTableWidgetItem(""));
        ui->vueProgramme->setItem(i, 0, new QTableWidgetItem(""));
        ui->vueProgramme->setItem(i, 1, new QTableWidgetItem(""));
    }
    unsigned int nbVariable =0;
    unsigned int nbProgramme =0;
    for(auto ite = Map.begin() ;ite != Map.end() ; ite++){
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(ite->first));
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        if(QString::fromStdString(ite->second->toString())[1]=='['){
            ui->vueProgramme->setItem(nbProgramme, 0, item);
            ui->vueProgramme->setItem(nbProgramme, 1, new QTableWidgetItem(QString::fromStdString(ite->second->getExpression())));
            nbProgramme++;
        }
        else{
            ui->vueVariable->setItem(nbVariable, 0, item);
            ui->vueVariable->setItem(nbVariable, 1, new QTableWidgetItem(QString::fromStdString(ite->second->getExpression())));
            nbVariable++;
        }
    }
}

void MainWindow::onSaveClicked(){
    ComputerManager& CM = ComputerManager::getManager();
    QString filename = "etat.xml";
    CM.sauvegarder(filename);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event){
    if (target == ligne_de_commande){
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Apostrophe)
                expression = analyse(ligne_de_commande->text(),1);
            else if (keyEvent->key() == Qt::Key_BracketLeft || keyEvent->key() == Qt::Key_BracketRight)
                programme = analyse(ligne_de_commande->text(),0);
            else if (keyEvent->key() == Qt::Key_Plus || keyEvent->key() == Qt::Key_Minus ||
                    keyEvent->key() == Qt::Key_Dollar || keyEvent->key() == Qt::Key_Slash ||
                    keyEvent->key() == Qt::Key_Asterisk || keyEvent->key() == Qt::Key_division ||
                    keyEvent->key() == Qt::Key_Less || keyEvent->key() == Qt::Key_multiply) {
                if(!expression && !programme)
                    emit operation();
            }
            else if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
                emit operation();
            else
                keyEvent->ignore();
            return false;
        }

        else if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Left)
                return true;
            else
                keyEvent->ignore();
            return false;
        }
        else{
            event->ignore();
            return false;
        }
    }
    return QMainWindow::eventFilter(target, event);
}


void MainWindow::refresh(){
    Pile& pile = Pile::getInstance();
    message->setText(pile.getMessage());    
    changeVariableProgrammeTable();
    if (ui->beep->isChecked() && message->text()!="")
        QApplication::beep();

    for(unsigned int i=0; i<pile.getMaxAffiche(); i++) {
        vuePile->setItem(i, 0, new QTableWidgetItem(""));
    }
    unsigned int nb =0;
    for(deque<Litterale*>::const_iterator it = pile.getIteratorBegin(); it!=pile.getIteratorEnd(); nb++, ++it){
        if(pile.getTaille()<=pile.getMaxAffiche())
            vuePile->setItem(pile.getMaxAffiche()-nb-1, 0, new QTableWidgetItem(QString::fromStdString((*it)->toString())));
        else
            vuePile->setItem(pile.getTaille()-nb-1, 0, new QTableWidgetItem(QString::fromStdString((*it)->toString())));
    }
}

void MainWindow::updateMapProgramme(QTableWidgetItem* item){
    extern std::map<string,Litterale*> Map;
    QTableWidgetItem* i1 = ui->vueProgramme->item(item->row(), 0);
    QTableWidgetItem* i2 = ui->vueProgramme->item(item->row(), 1);
    string id = i1->text().toStdString();
    string val = i2->text().toStdString();
    if(id != "" && val!=""){
        auto it = Map.find(id);
        if (it == Map.end())
            STO(*new Expression(val), *new Expression(id));
        else
            it->second = new Expression(val);
    }
}

void MainWindow::updateMapVariable(QTableWidgetItem* item){
    extern std::map<string,Litterale*> Map;
    QTableWidgetItem* i1 = ui->vueVariable->item(item->row(), 0);
    QTableWidgetItem* i2 = ui->vueVariable->item(item->row(), 1);
    string id = i1->text().toStdString();
    string val = i2->text().toStdString();
    if(id != "" && val!=""){
        auto it = Map.find(id);
        if (it == Map.end())
            STO(*new Expression(val), *new Expression(id));
        else
            it->second = new Expression(val);
    }
}


void MainWindow::on_buttonEnter_clicked() {
    Controleur& controleur = Controleur::getInstance();
    Pile& pile = Pile::getInstance();
    pile.setMessage("");
    QString c = ligne_de_commande->text();
    try {
        controleur.traitementRPN(c.toStdString());        
        ligne_de_commande->clear();
    } catch(ComputerException c) {
        pile.setMessage(c.getInfo());
        ligne_de_commande->setText(c.getReste());
    }
    emit pile.modificationEtat();
}

MainWindow::~MainWindow(){
    onSaveClicked();
    delete ui;
}

void MainWindow::on_button0_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"0");}
void MainWindow::on_button1_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"1");}
void MainWindow::on_button2_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"2");}
void MainWindow::on_button3_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"3");}
void MainWindow::on_button4_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"4");}
void MainWindow::on_button5_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"5");}
void MainWindow::on_button6_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"6");}
void MainWindow::on_button7_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"7");}
void MainWindow::on_button8_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"8");}
void MainWindow::on_button9_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+"9");}
void MainWindow::on_buttonPoint_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+".");}
void MainWindow::on_buttonSpace_clicked(){ligne_de_commande->setText(ligne_de_commande->text()+" ");}
void MainWindow::on_createExpression_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"'");
    expression = analyse(ligne_de_commande->text(),1);
}
void MainWindow::on_beginProgramme_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"[");
    programme = analyse(ligne_de_commande->text(),0);
}
void MainWindow::on_endProgramme_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"]");
    programme = analyse(ligne_de_commande->text(),0);
}

bool MainWindow::analyse(const QString& str, int option){
    if (option){
        return (str.count(QRegExp("'"))%2)==1;
    }
    else{
        return (str.count('[')-str.count(']'))!=0;
    }
}

void MainWindow::on_buttonSuppr_clicked(){ligne_de_commande->backspace();}

void MainWindow::on_buttonDivision_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"/");
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_buttonMultiplication_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"*");
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_buttonNEG_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"NEG");
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_buttonSoustraction_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"-");
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_buttonAddition_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"+");
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Pile_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Boucle_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Trigo_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Autre_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Complexe_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Logique_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}
void MainWindow::on_Expression_Programme_Variable_activated(const QString &arg){
    ligne_de_commande->setText(ligne_de_commande->text()+arg);
    if(!expression && !programme)
        emit operation();
}

void MainWindow::on_Undo_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"UNDO");
    if(!expression && !programme)
        emit operation();
}

void MainWindow::on_Redo_clicked(){
    ligne_de_commande->setText(ligne_de_commande->text()+"REDO");
    if(!expression && !programme)
        emit operation();
}

void MainWindow::changeNbViews()
{   Pile& pile = Pile::getInstance();
    //pile.setMaxAffiche(getNbVuesPile->text().toInt());
    pile.setMaxAffiche(ui->spinBox->value());
    vuePile->clear();
    unsigned int i = vuePile->rowCount()-1;
    while(pile.getMaxAffiche() < (unsigned int)vuePile->rowCount())
    {
        vuePile->removeRow(i);
        i--;
    }
    while(pile.getMaxAffiche()  > (unsigned int)vuePile->rowCount())
    {
        vuePile->insertRow(i+1);
        i++;
    }
    QStringList nombres;
    for (i= pile.getMaxAffiche(); i>0; i--)
    {
        QString str=QString::number(i);
        str+=":";
        nombres<<str;
    }
    vuePile->setVerticalHeaderLabels(nombres);
    for(i=0;i<pile.getMaxAffiche() ;i++)
        vuePile->setItem(i,0, new QTableWidgetItem(""));
    refresh();
}


void MainWindow::toggleGraphicPad(){
    if(ui->clavier->isChecked()){
        ui->Clavier_2->hide();
    }
    else{
        ui->Clavier_2->show();
    }
}
