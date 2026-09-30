# Modularizare

- **Materia:** POO AC
- **Laborator:** Laborator 1 · Debugging
- **Punctaj:** 2 puncte
- **Interval:** 28 sept. 2026, 18:00–20:00

Modularizarea codului este necesară în aplicații și se realizează cu ajutorul bibliotecilor.

Începând de acum, toate programele pe care le veți scrie vor fi structurate în mai multe biblioteci (fișiere sursă + fișiere header).

De exemplu, într-o aplicație generică, o bibliotecă se poate ocupa de accesul la date, alta de autentificarea utilizatorilor, alta de configurări, alta de interfața cu utilizatorul ș.a.m.d.

### CERINȚĂ
Identificați care sunt funcționalitățile distincte în program și creați biblioteci pentru fiecare.

- Soluția trebuie să conțină minim 2 biblioteci.
- Fișierul `main` trebuie să conțină o singură funcție, `main()`.
Restul funcțiilor trebuie împărțite conform componentelor/funcționalităților diferite pe care le identificați în aplicație.

 ### IMPORTANT
Rezolvați întâi toate erorile (Ex 1.) și abia apoi treceți la modularizare.
Altfel, este mai dificil să distingeți între erorile din codul original și eventualele greșeli care pot apărea la separarea codului în module.

### Rulare locală

Compilați și rulați exact cum face și checkerul (Linux, WSL sau macOS, `g++` 11 sau mai nou), din folderul exercițiului, cu toate fișierele `.cpp` de acolo:

```bash
g++ -Wall -Wextra -g -fsanitize=address,undefined *.cpp -o app
./app
```

Programul citește `01.in` și scrie raportul în `01.out`, în folderul curent. Fișierul `01.out` primit odată cu scheletul este ieșirea corectă, deci păstrați-vă o copie înainte de prima rulare și comparați după fiecare rulare:

```bash
cp 01.out asteptat.out          # o singură dată, înainte de prima rulare
./app && diff 01.out asteptat.out && echo OK
```

Dacă `diff` nu afișează nimic, ieșirea este identică. Erorile de memorie găsite de AddressSanitizer sau UndefinedBehaviorSanitizer apar pe ecran la rulare, iar programul se termină cu cod diferit de 0; checkerul le consideră test picat, chiar dacă ieșirea arată bine.

Pe Windows folosiți WSL cu Ubuntu; sanitizer-ele nu funcționează în MinGW. Compilarea fără sanitizer-e (`g++ -Wall -Wextra *.cpp -o app`) merge oriunde, dar nu prinde erorile de memorie.

Pe lângă exemplul din `01.in`, checkerul rulează și teste ascunse care verifică fiecare eroare separat, așa că un program care trece doar pe exemplu nu ia punctajul maxim.

---
_Generat de Rezultate – nu edita; modificările sunt suprascrise._
