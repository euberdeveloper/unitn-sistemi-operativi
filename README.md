[![State-of-the-art Shitcode](https://img.shields.io/static/v1?label=State-of-the-art&message=Shitcode&color=7B5804)](https://github.com/trekhleb/state-of-the-art-shitcode)

Nome macrocartella 'Val_rect_fact'

mail gruppo:
euberdeveloper@gmail.com

componenti gruppo:

Eugenio Berretta 201514 eugenio.berretta@studenti.unitn.it
Sebastiano Dissegna 202226 sebastiano.dissegna@studenti.unitn.it
Federico Stefini 202112 federico.stefini@studenti.unitn.it
Davide Bressan 205288 davie.bressan@studenti.unitn.it

Scelte implementative

Abbiamo deciso di creare una shell per ciascuno dei tre principali eseguibili indipendenti.
Scrivere help in ciascuna delle shell per vederne i rispettivi comandi.


Processo A

Abbiamo seguito la  consegna, inoltre comunica con R attraverso una named pipe.
 


Processo Main

Il processo Main funge da wrapper e ridireziona i comandi ad Analyzer e/o Reporter.
scrivere help nel terminale per vedere i comandi

Processo R

Il processo Report comunica attraverso una named pipe con il processo A dal quale legge i dati ottenuti dall'analisi e li stampa in una tabella ordinata attraverso il comando show





Indicazioni testing:
0 - compilare con make
1 - avviare main
2 - srivere help su terminale per vederne i comandi
3 - consigliabile mettere il terminale a schermo intero per vedere bene la tabella con i dati ottenuti dai file su reporter
