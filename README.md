Uruchamianie
===========================


* gra z komputerem białymi
 `./chess H C `

* gra z komputerem czarnymi 
  `./chess C H `

* wczytanie dowolnego początkowego ustawienia, format musi byc taki jak w pliku sample.chess
 `./chess H C <sciezka_do_pliku_*.chess> `


Ficzery
===========================

Zaimplementowane są:

* roszada (np e1g1)

* promocja

* en passant

* remis w przypadku trzykrotnego powtórzenia (nie do końca zgodne z regułami ale w większości przypadków działa)

Nie ma reguły 50 ruchów bez bicia


Oznaczenia
===========================

* H - królowa (hetman)

* S - skoczek

* W - wieża

* K - król

* G - laufer (goniec)

Sterowanie
===========================

* ruchy podajemy w postaci np. a2a3 lub A2A3 (wielkośc liter nie ma znaczenia)

* w przypadku promocji podajemy czwartą literę [whgs], oznczającaą na co chcemy promować, gdy jej nie podamy to promocja jest do królowej 