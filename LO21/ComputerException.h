#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H

#include <QString>

/*!
 * \brief La classe ComputerException gere toutes les exceptions de la calculatrice UTComputer.
 */
class ComputerException {
    /*!
     * \brief Explication de l'erreur genere par ComputerException.
     */
    QString info;
    /*!
     * \brief Reste de la ligne de commande dans le cas d'une syntaxe incorrecte.
     */
    QString reste;
  public:
    /*!
     * \brief Constructeur de ComputerException.
     * \param str1 - Initialise l'attribut info.
     * \param str2 - Initialise l'attribut reste.
     */
    ComputerException(const QString& str1, const QString& str2="") : info(str1), reste(str2){}
    /*!
     * \brief Accesseur pour l'attribut info.
     * \return Retourne le string.
     */
    QString getInfo() const {return info;}
    /*!
     * \brief Accesseur pour l'attribut reste.
     * \return Retourne le string.
     */
    QString getReste() const {return reste;}
};

#endif // COMPUTEREXCEPTION_H
