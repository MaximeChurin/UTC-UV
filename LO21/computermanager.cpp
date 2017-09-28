#include "ComputerManager.h"
#include "ComputerException.h"
#include "Pile.hpp"
#include <QFile>
#include <QIODevice>
#include <qxmlstream.h>
#include <QXmlStreamWriter>
#include <QDataStream>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include<iostream>

ComputerManager* ComputerManager::manager = 0;
void ComputerManagerDataXML::charger(const QString& f){

    fichier = f;

    Pile& Pile = Pile::getInstance();

    LitteraleManager& litMng = LitteraleManager::getInstance();

    QFile fin(f);
    // Si on ne peut pas ouvrir le fichier, on envoie une erreur
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw ComputerException("Erreur ouverture fichier Contexte");
    }

    QXmlStreamReader xml(&fin);
    // lecture du fichier xml en entier
    while(!xml.atEnd() && !xml.hasError()) {

        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument) continue;

        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "Computermanager") {

                  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Computermanager")) {
                        double renum = 0.0, reden = 0.0, imnum = 0.0, imden = 0.0;
                        std::string exp;
                        std::string prog;

                        if(xml.name() == "pile"){

                        /***** Lecture du contenu de la balise pile contenant les anciens éléments de la pile *****/

                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "pile")) {

                            if(xml.name() == "litterale") {
                                 /***** Lecture du contenu de la balise litterale *****/

                                renum = 0.0; reden = 0.0; imnum = 0.0; imden = 0.0;
                                QString exp = "";
                                QString prog = "";

                                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "litterale")) {

                                     /***** Lecture des sous-balises de litterale *****/

                                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                                        if(xml.name() == "renum") {
                                            xml.readNext(); renum=xml.text().toString().toDouble();
                                        }
                                        if(xml.name() == "reden") {
                                            xml.readNext(); reden=xml.text().toString().toDouble();
                                        }
                                        if(xml.name() == "imnum") {
                                            xml.readNext(); imnum=xml.text().toString().toDouble();
                                        }
                                        if(xml.name() == "imden") {
                                            xml.readNext(); imden=xml.text().toString().toDouble();
                                        }
                                        if(xml.name() == "exp") {
                                            xml.readNext(); exp=xml.text().toString();
                                        }
                                        if(xml.name() == "prog") {
                                            xml.readNext(); prog=xml.text().toString();
                                        }
                                    xml.readNext();
                                    }

                                    xml.readNextStartElement();
                                }
                                /***** On push sur la pile les anciens constituants de la pile recréés *****/
                                if(exp != "" && prog =="") {
                                    Expression* nouveauLitterale = new Expression(exp.toUtf8().constData());
                                    Pile.push(litMng.ajoutLitterale(nouveauLitterale));
                                }
                                else if(prog != "" && exp == "") {
                                    Programme* nouveauLitterale = new Programme(prog.toUtf8().constData());
                                    Pile.push(litMng.ajoutLitterale(nouveauLitterale));
                                }
                                else {
                                    Litterale* nouveauLitterale = &bonType(renum,reden,imnum,imden);
                                    Pile.push(litMng.ajoutLitterale(nouveauLitterale));
                                }




                            }//literale

                             xml.readNext();
                        }

                        }//pile
                        /***** Fin de lecture du contenu de la balise pile *****/

                        if(xml.name() == "map"){
                           /***** Lecture du contenu de la balise map *****/


                          while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "map")) {

                              double renum = 0.0, reden = 0.0, imnum = 0.0, imden = 0.0;

                              if(xml.name() == "el") {

                                    /***** Lecture du contenu de la sous-balise el *****/
                                  renum = 0.0; reden = 0.0; imnum = 0.0; imden = 0.0;
                                  QString exp = "";
                                  QString prog = "";
                                  QString id = "";

                                  while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "el")) {

                                      if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                          if(xml.name() == "id") {
                                              xml.readNext(); id=xml.text().toString().toUtf8().constData();
                                          }
                                          if(xml.name() == "renum") {
                                              xml.readNext(); renum=xml.text().toString().toDouble();
                                          }
                                          if(xml.name() == "reden") {
                                              xml.readNext(); reden=xml.text().toString().toDouble();
                                          }
                                          if(xml.name() == "imnum") {
                                              xml.readNext(); imnum=xml.text().toString().toDouble();
                                          }
                                          if(xml.name() == "imden") {
                                              xml.readNext(); imden=xml.text().toString().toDouble();
                                          }
                                          if(xml.name() == "exp") {
                                              xml.readNext(); exp=xml.text().toString();
                                          }
                                          if(xml.name() == "prog") {
                                              xml.readNext(); prog=xml.text().toString();
                                          }

                                      xml.readNext();

                                      }
                                      xml.readNextStartElement();
                                  }

                                   /***** On recréé le mappage id - Expression/Programme/Variable *****/

                                  if(exp != "" && prog =="") {
                                      Expression* nouveauLitterale = new Expression(exp.toUtf8().constData());
                                      Expression* nouveauId = new Expression(id.toUtf8().constData());
                                      STO(*nouveauLitterale,*nouveauId);
                                  }
                                  else if(prog != "" && exp == "") {
                                      Programme* nouveauLitterale = new Programme(prog.toUtf8().constData());
                                      Expression* nouveauId = new Expression(id.toUtf8().constData());
                                      STO(*nouveauLitterale,*nouveauId);
                                  }
                                  else {
                                      Litterale* nouveauLitterale = &bonType(renum,reden,imnum,imden);
                                      Expression* nouveauId = new Expression(id.toUtf8().constData());
                                      STO(*nouveauLitterale,*nouveauId);
                                  }

                              }//el

                               xml.readNext();
                          }
                        }// End map
                        /***** Fin de lecture de la balise map *****/
                          xml.readNextStartElement();
                        }
                        xml.readNextStartElement();
                    }//computermanager

                  xml.readNext();
        }//fin du fichier
    // handler erreur
    if(xml.hasError()) {
        throw ComputerException("Erreur lecteur fichier Contexte, parser xml");
    }

    xml.clear();

    }//while
}


void ComputerManagerDataXML::sauvegarder(const QString& f) {

    if (f!=""){
        fichier = f;
    }
    if(fichier==""){
        throw ComputerException("Fichier non renseigné");
    }

    LitteraleManager& litMng = LitteraleManager::getInstance();
    Pile& Pile = Pile::getInstance();

    QFile nouveauFichier(fichier);
    if (!(nouveauFichier.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))) throw ComputerException(QString("erreur ouverture fichier xml"));
    qDebug() << nouveauFichier.readAll();

     QXmlStreamWriter stream(&nouveauFichier);

     stream.setAutoFormatting(true);
     stream.writeStartDocument();

     stream.writeStartElement("Computermanager");

     //Pile -> sauvegarde de l'état de la pile

     stream.writeStartElement("pile");
     for(std::deque<Litterale*>::const_iterator iterator = Pile.getIteratorBegin(); iterator != Pile.getIteratorEnd(); ++iterator){
         stream.writeStartElement("litterale");
         const Litterale* lit = *iterator;
          /***** choix des sous-balises pour la pile *****/
        Numerique* p = dynamic_cast<Numerique*>(*iterator);
        Complexe* cpx = dynamic_cast<Complexe*>(*iterator);
        if(p!=0 || cpx != 0) {
            stream.writeTextElement("renum", QString::number(lit->getPartieReelleNum()));
            stream.writeTextElement("reden", QString::number(lit->getPartieReelleDen()));
            stream.writeTextElement("imnum",QString::number(lit->getPartieImNum()));
            stream.writeTextElement("imden", QString::number(lit->getPartieImDen()));
            stream.writeEndElement();
        }
        Expression* exp = dynamic_cast<Expression*>(*iterator);
        if(exp!=0) {
            stream.writeTextElement("exp", QString::fromStdString(exp->getExpression()));
            stream.writeEndElement();
        }
        Programme* prog = dynamic_cast<Programme*>(*iterator);
        if(prog!=0) {
            stream.writeTextElement("prog", QString::fromStdString(prog->getContenu()));
            stream.writeEndElement();
        }


     }

     stream.writeEndElement();// Fin pile

      //Map -> sauvegarde des programmes et variables définies lors de l'éxécution
      stream.writeStartElement("map");

      typedef std::map<std::string, Litterale*>::iterator it_type;
      extern std::map<string,Litterale*> Map;
      for(it_type iterator = Map.begin(); iterator != Map.end(); iterator++) {
          stream.writeStartElement("el");
           /***** Choix des sous-balises pour la Map *****/
          Numerique* p = dynamic_cast<Numerique*>(iterator->second);
          Expression* exp = dynamic_cast<Expression*>(iterator->second);
          Programme* prog = dynamic_cast<Programme*>(iterator->second);
          if(p!=0) {
              stream.writeTextElement("id", QString::fromStdString(iterator->first));
              stream.writeTextElement("renum", QString::number(p->getPartieReelleNum()));
              stream.writeTextElement("reden", QString::number(p->getPartieReelleDen()));
              stream.writeTextElement("imnum",QString::number(p->getPartieImNum()));
              stream.writeTextElement("imden", QString::number(p->getPartieImDen()));

              stream.writeEndElement();//el
          }
          if(exp!=0) {
              stream.writeTextElement("id", QString::fromStdString(iterator->first));
              stream.writeTextElement("exp", QString::fromStdString(exp->getExpression()));
              stream.writeEndElement();//el
          }
          if(prog!=0) {
              stream.writeTextElement("id", QString::fromStdString(iterator->first));
              stream.writeTextElement("prog", QString::fromStdString(prog->getContenu()));
              stream.writeEndElement();//el
          }


      }
      stream.writeEndElement();// map


      stream.writeStartElement("param");

///////*****Ecrire ici*******/////





      stream.writeEndElement();// Fin param

     stream.writeEndElement();// Computer manager
     stream.writeEndDocument();

     nouveauFichier.close();

}
