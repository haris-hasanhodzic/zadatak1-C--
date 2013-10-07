zadatak1-C--
============


Zadatak je urađen na 2 načina, a glavna razlika je korištenje niti u drugom primjeru.
Uz zadatak postoji i fajl main_create.cpp koji kreira bazu i puni je podacima.

Prvi način je realizovan bez niti i za korištenje je potrebno u main fajlu uključiti data.h.
Kompajlira se pomoću komande:
g++ main.cpp address.cpp network.cpp data.cpp -l sqlite3


Drugi način je realizovan uz pomoć niti i u main.cpp fajlu je potrebno uključiti data2.h.
Komanda za kompajliranje:
g++ main.cpp address.cpp network.cpp data2.cpp -l sqlite3


Primjer pokretanja programa:

./a.out --database test.db 10.5.0.0

./a.out mreze.txt 10.0.0.0
