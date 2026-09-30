# Depanare

- **Materia:** POO AC
- **Laborator:** Laborator 1 · Debugging
- **Punctaj:** 8 puncte
- **Interval:** 28 sept. 2026, 18:00–20:00

### CERINȚĂ
Începeți cu înțelegerea codului: studiați atât
codul sursă, cât și fișierul de intrare și cel de ieșire corect.
Continuați cu identificarea și eliminarea celor 9 erori.

### TIPS
Câteva întrebări care să vă ajute:
 -   Câmpurile unei structuri stau unul după altul în memorie. Care
     sunt consecințele dacă într-un câmp se scrie mai mult decât
     spațiul alocat pentru el?
 -   Ce face `copyStation()` și de ce este nevoie de o funcție separată
     pentru copiere?
 -   Ce se întâmplă exact într-o operație de atribuire de tip `a = b`,
     unde `a` și `b` sunt structuri care conțin un pointer? Dacă acel
     pointer reprezintă adresa de început a unui tablou, după operația
     de atribuire, câte tablouri vor exista în memorie?
 -   Pentru fiecare alocare dinamică de memorie din program există și
     eliberarea corespunzătoare?
 -   Ce returnează `fgets` la sfârșitul fișierului? Dar `readHeader()`?
 -   Dacă nu sunteți familiarizați cu sintaxa, căutați pe net ce
     citește `%63[^,]`.
 -   Funcția `hottestDay()` ia în considerare toate cazurile reale
     posibile? Ce returnează?

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
