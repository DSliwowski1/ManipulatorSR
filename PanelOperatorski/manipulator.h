#ifndef MANIPULATOR_H
#define MANIPULATOR_H

/*! \class Manipulator
    \brief Klasa przechowująca informacja na temat manipulatora.
*/

class Manipulator
{
    double  _Q2_deg;
    double  _Q1_deg;
    double  _Q0_deg;

   public:

    /*!
     * \brief Manipulator() - Konstruktor klasy; ustawia wartości na 0
     */
    Manipulator()
       { _Q0_deg = _Q1_deg = _Q2_deg = 0; }

    /*!
     * \brief SetQ0_deg - usatw wartość Q0 w stopniach
     * \param Q0_deg - wartość w stopniach
     */
    void SetQ0_deg(double Q0_deg) { _Q0_deg = Q0_deg; }
    /*!
     * \brief GetQ0_deg - zwraca wartość Q0 w stopniach
     * \return zwraca wartość Q0 w stopniach
     */
    double GetQ0_deg() const { return _Q0_deg; }

    /*!
     * \brief SetQ1_deg - usatw wartość Q1 w stopniach
     * \param Q1_deg - wartość w stopniach
     */
    void SetQ1_deg(double Q1_deg) { _Q1_deg = Q1_deg; }
    /*!
     * \brief GetQ0_deg - zwraca wartość Q1 w stopniach
     * \return zwraca wartość Q1 w stopniach
     */
    double GetQ1_deg() const { return _Q1_deg; }

    /*!
     * \brief SetQ2_deg - usatw wartość Q2 w stopniach
     * \param Q2_deg - wartość w stopniach
     */
    void SetQ2_deg(double Q2_deg) { _Q2_deg = Q2_deg; }
    /*!
     * \brief GetQ2_deg - zwraca wartość Q2 w stopniach
     * \return zwraca wartość Q2 w stopniach
     */
    double GetQ2_deg() const { return _Q2_deg; }

  };


  extern Manipulator  Manip;

#endif // MANIPULATOR_H
