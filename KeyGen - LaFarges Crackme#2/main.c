#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/*0040117A*/int *phase01 (char*);       //Passwortlogik 1 (XOR)
/*004011A3*/void phase02 (int*, int);   //Passwortlogik 2 (XOR)
/*004011D1*/void phase03 (int*, int);   //Passwortlogik 3 (XOR)
/*004011FA*/void phase04 (int*, int);   //Passwortlogik 4 (XOR)
/*00401220*/int *phase05 (int*, int);   //Passwortlogik 5 (CPY)

int main()
{
    char user[20];                  //Benutzername Platzhalter
    unsigned char p5Codes8bit[4];   //Konvertierungshilfe
    uint32_t *pnt;                  //Char zu Int Zeiger
    char passwordReverse[20];       //Passwort invertieren
    int pwl = 0;                    //Zähler Passwort Inv.
    int reverseHelper = 0;          //Zähler Passwort Inv.
    char password[20];              //Passwort Platzhalter

    //Eingabe Username:
    system("cls");
    printf("Username: ");
    scanf("%s", user);

    //Mindestlaenge Benutzername:
    if(strlen(user) < 4)
    {
        printf("Fehler: Name kleiner 4 Zeichen\n");
        return 0;
    }

    //Maximallaenge Benutzername:
    if(strlen(user) > 20)
    {
        printf("Fehler: Name groesser 20 Zeichen\n");
        return 0;
    }

    //Hauptlogik Passwort:
    /*XOR:*/int *phase01Code = phase01(&user);
    /*XOR:*/phase02(phase01Code, strlen(user));
    /*XOR:*/phase03(phase01Code, strlen(user));
    /*XOR:*/phase04(phase01Code, strlen(user));
    /*CPY:*/int *phase05Code = phase05(phase01Code, strlen(user));

    //Konvertierung Char to Int:
    for(int i = 0; i<4; i++)
    {
        //8 Bit fuer fortlaufende Speicheradressen
        p5Codes8bit[i] = *(phase05Code+(i));
    }

    //Schiebe Zeiger auf Anfang Char-Array
    pnt = &p5Codes8bit;

    //Lass Int auf Anfang Char-Array zeigen
    uint32_t temp = *pnt;

    //Berechne Passwort
    do
    {
        passwordReverse[pwl] =  (temp % 10) + 48;
        pwl++;
    }while(temp = temp / 10);

    //Invertiere Passwort
    for(int i = pwl -1; i>=0; i--)
    {
        password[reverseHelper] = passwordReverse[i];
        reverseHelper++;
    }

    //Ausgabe Passwort
    system("cls");
    printf("Username: %s\nReg.code: ", user);
    for(int k = 0; k < pwl; k++)
    {
        printf("%c", password[k]);
    }
    printf("\n\n");
    system("pause");
    return 0;
}

//Umsortierung und Addition
int *phase05 (int *phase01Code, int laenge)
{
    static int p05[4] = {0,0,0,0};
    int c = 0;
    for(int i = 0; i < laenge; i++)
    {
        int temp = *(phase01Code+(i));
        unsigned char temp2 = temp + p05[c];
        p05[c] = temp2;
        if(c == 3)
        {
            c = 0;
        }
        else
        {
            c++;
        }
    }
    return p05;
}

//Bitweise Verschiebung mit Geheimcode
void phase04 (int *phase01Code, int laenge)
{
    int geheimCode[] = {181/*B5*/, 27/*1B*/, 201/*C9*/, 80/*50*/, 115/*73*/};
    int c = 0;
    for(int i = laenge; i > 0; i--)
    {
        int temp = *(phase01Code+(i-1));
        int temp2 = geheimCode[c] ^ temp;
        geheimCode[c] = temp;
        *(phase01Code+(i-1)) = temp2;
        if(c == 4)
        {
            c = 0;
        }
        else
        {
            c++;
        }
    }
}

//Bitweise Verschiebung mit Geheimcode
void phase03 (int *phase01Code, int laenge)
{
    int geheimCode[] = {247/*F7*/, 253/*FD*/, 244/*F4*/, 231/*E7*/, 185/*B9*/};
    int c = 0;
    for(int i = 0; i <= laenge; i++)
    {
        int temp = *(phase01Code+(i));
        int temp2 = geheimCode[c] ^ temp;
        geheimCode[c] = temp;
        *(phase01Code+(i)) = temp2;
        if(c == 4)
        {
            c = 0;
        }
        else
        {
            c++;
        }
    }
}

//Bitweise Verschiebung mit Geheimcode
void phase02 (int *phase01Code, int laenge)
{
    int geheimCode[] = {120/*78*/, 240/*F0*/, 208/*D0*/, 3/*03*/, 231/*E7*/};
    int c = 0;
    for(int i = laenge; i > 0; i--)
    {
        int temp = *(phase01Code+(i-1));
        int temp2 = geheimCode[c] ^ temp;
        geheimCode[c] = temp;
        *(phase01Code+(i-1)) = temp2;
        if(c == 4)
        {
            c = 0;
        }
        else
        {
            c++;
        }
    }
}

//Bitweise Verschiebung mit Geheimcode
int *phase01 (char *user)
{
    static int userHelper[20];
    int geheimCode[] = {170/*AA*/, 137/*89*/, 196/*C4*/, 254/*FE*/, 70/*46*/};
    int *geheimZeiger;
    geheimZeiger = geheimCode;

    int temp = 0;
    int temp2 = 0;
    for( int n=0; n < strlen(user); n++ )
    {
        if(n>=5)
        {
            geheimCode[temp] = user[temp2+1];
        }

        userHelper[n] = user[n+1] ^ *geheimZeiger;

        if(n>=5)
        {
            temp2++;
        }

        temp++;

        if(5 == temp)
        {
            geheimZeiger = geheimCode;
            temp = 0;
        }
        else
        {
            geheimZeiger++;
        }
    }
    return userHelper;
}
