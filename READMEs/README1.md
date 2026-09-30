# Laborator 1 · Debugging

În acest laborator veți lucra cu un program deja scris, care:
-   primește un fișier de intrare, `01.in`, ce conține date de temperatură și precipitații provenite de la diferite stații meteo, din mai multe zile;
-   scrie un raport, `01.out`, cu diverse statistici calculate pentru fiecare stație meteo.

În cod există **9 erori**.

O parte dintre ele produc erori la compilare, altele produc rezultate eronate, iar altele sunt vizibile doar dacă se efectuează o analiză a utilizării memoriei cu instrumente separate.


> OBS 
> Exemple de instrumente care ajută la depanarea erorilor de memorie sunt [Valgrind](https://valgrind.org/) și [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer).
>
> Utilizarea lor este recomandată în general și vor fi utilizate și în verificarea automată a laboratoarelor voastre de acum înainte.

**Scopul laboratorului este să înțelegeți funcționarea programului, să corectați greșelile și să modularizați codul.**

Predă prin push pe branch-ul implicit înainte de termen

Enunțurile complete sunt în fișierul `ASSIGNMENT.md` din fiecare folder de exercițiu/temă (scris automat de Rezultate – nu îl edita).
