#ifndef CRC_H
#define CRC_H

typedef unsigned char byte;
#define WIDTH  (8 * sizeof(byte))
#define POLYNOMIAL 0x07

/*!
  \file
   \fn char CRC8(char const message[], int nBytes)

   \brief Oblicza CRC8 dla zadanej wiadomości. Korzysta w tym celu z wielomianu POLYNOMIAL

   \param message - wiadomość do przesłania
   \param nBytes - ilość bitów w wiadomości

   \return Obliczona dla wiadmości suma kontrolna
*/

char CRC8(char const message[], int nBytes)
{
    char  remainder = 0;
    for (int byte = 0; byte < nBytes; ++byte)
    {
        remainder ^= message[byte];
        for (int bit = 8; bit > 0; --bit)
        {
            if ((remainder & 0x80) != 0)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    return (remainder);
}

#endif // CRC_H
