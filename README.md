# Controlul pinii GPIO folosind MSP430

Acest proiect implementează controlul a trei pini GPIO (`P4.6`, `P4.4` și `P4.7`) conectați la microcontrolerul **MSP430**. Fiecare pin este controlat printr-un temporizator dedicat, configurat să genereze întreruperi periodice pentru a schimba starea pinului (HIGH/LOW).  

## Caracteristici
- **Pin `P4.6`**: Configurează ieșirea GPIO și o comută periodic cu o frecvență de **1 Hz** (1 secundă HIGH, 1 secundă LOW).  
- **Pin `P4.4`**: Configurează ieșirea GPIO și o comută periodic cu o frecvență diferită, setată prin temporizator.  
- **Pin `P4.7`**: Configurează ieșirea GPIO și o comută periodic cu o altă frecvență configurată.  

## Configurare
- **Microcontroler utilizat**: MSP430FR2xxx  
- **Surse de ceas**: ACLK setat la 32 kHz  
- **Temporizatoare**: 
  - Timer_B0 controlează starea pinului `P4.6`
  - Timer_B1 controlează starea pinului `P4.4`
  - Timer_B2 controlează starea pinului `P4.7`  

## Cum funcționează
1. Fiecare pin este controlat de o **rutină de întrerupere** asociată temporizatorului său.  
2. Temporizatoarele sunt configurate în mod "UP" pentru a genera întreruperi periodice.  
3. La fiecare întrerupere, starea pinului corespunzător este schimbată (HIGH/LOW).  
4. Valorile configurate în registrele `CCR0` și `CCR2` determină frecvența și durata perioadelor pentru fiecare pin.

## Utilizare
Acest cod poate fi folosit ca bază pentru aplicații precum:  
- Comutarea periodică a stării pinii GPIO.  
- Generarea de semnale digitale pentru periferice.  
- Aplicații care necesită evenimente periodice folosind temporizatoare.  

---
