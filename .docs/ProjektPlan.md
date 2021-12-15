# SemesterProjekt

## Was soll erreicht werden?

* Knacken von Chiffren
    * Caesar
    * potentiell Vigenere und/oder Enigma

## Welche Eigenschaften soll die Lösung haben?

* Brute-Force-Attack
    * Alle Möglichkeiten werden probiert
* Bewertungssystem im Bezug auf BFA
    * Wörterbuch Überprüfung
        * Einzelne Wörter in einem Wörterbuch nachschlagen
    * Vokale Überprüfung
        * Jedes Wort muss minimum ein Vokal enthalten
    * typische Zeichenfolgen
        * Ein `Q` muss immer mit einem `u` gefolgt werden.
            * Abzug wenn dies nicht der Fall ist

## Was ist der Plan?

* Caesar-chiffre implementieren
    * encode und decode Funktion
* "Map", bzw. Array mit 2 Werten
    * Lösungstext und Bewertungswert
* Bewertungssystem
    * Vokal Überprüfung implementieren
    * Wörterbuch Überprüfung implementieren
        * Dateien einlesen
        * Wörterbuch finden
    * Zeichenfolge bewerten
* User-Interaktion
    * Console oder GUI
    * GUI
        * Qt
        * Ultra Appkit
        * Nuklear