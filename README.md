# Maišos funkcija

Nuosava maišos (hash) funkcija, sukurta naudojant C++ kalbą. Projektas skirtas ištirti maišos funkcijos veikimą, efektyvumą, kolizijas, lavinos efektą ir brute-force paiešką.

## Maišos funkcijos idėja

Mano maišos funkcija sukuria fiksuoto dydžio 256 bitų maišos reikšmę, kuri pateikiama kaip 64 šešioliktainių simbolių eilutė.

Algoritmas veikia šiais etapais:

1. **Pradinė būsena** – sukuriamos 8 atskiros 32 bitų būsenos reikšmės. Visos jos pradžioje nustatomos į `0`.
2. **Įvesties apdorojimas** – įvestis apdorojama baitas po baito. Kiekvienas įvesties baitas paveikia visas 8 būsenos reikšmes.
3. **Būsenos atnaujinimas** – kiekviena būsenos reikšmė atnaujinama pagal formulę:

   `state[i] = state[i] * 7 + byte + i`

4. **Visos įvesties apdorojimas** – šis procesas kartojamas su kiekvienu įvesties baitu. Ankstesnių baitų rezultatas išlieka būsenoje ir yra naudojamas apdorojant kitus baitus.
5. **Maišos sudarymas** – apdorojus visą įvestį, visos 8 būsenos reikšmės sujungiamos į vieną rezultatą.
6. **Rezultato formatavimas** – kiekviena 32 bitų būsenos reikšmė pateikiama kaip 8 šešioliktainiai simboliai. Kadangi naudojamos 8 reikšmės, galutinis rezultatas sudarytas iš 64 šešioliktainių simbolių, t. y. 256 bitų.

Ta pati įvestis visada sugeneruoja tą pačią maišos reikšmę.

## Funkcijos savybės

- Fiksuotas maišos dydis – **256 bitai**.
- Maišos rezultatas pateikiamas kaip **64 šešioliktainiai simboliai**.
- Kiekvienas įvesties baitas paveikia visas 8 būsenos reikšmes.
- Ta pati įvestis visada sugeneruoja tą pačią maišos reikšmę.
- Įvestis apdorojama baitais.
- Palaikomas ASCII ir UTF-8 tekstas.

## Įvestis

Programa palaiko:

- teksto įvedimą ranka;
- failo nuskaitymą;
- ASCII tekstą;
- UTF-8 tekstą;
- tuščią įvestį;
- įvestis su tarpais ir naujos eilutės simboliais.

Failai skaitomi `binary` režimu, todėl į maišą perduodamas tikslus failo baitų turinys. Failo pavadinimas į maišą neįtraukiamas.

UTF-8 tekstas taip pat apdorojamas baitais, todėl simbolių skaičius ir baitų skaičius gali skirtis.

## Kompiliavimas ir paleidimas

Repozitorijos klonavimas:

```bash
git clone https://github.com/dziugasvas/blockchain-tech-1
```

Pereikite į projekto aplanką:

```bash
cd blockchain-tech-1
```

Kompiliavimas:

```bash
make
```

Kompiliavimas ir paleidimas:

```bash
make run
```

Programos paleidimas:

```bash
./main
```

Failą galima nurodyti komandų eilutėje:

```bash
./main input.txt
```

Sukompiliuoto failo pašalinimas:

```bash
make clean
```

## Testavimai

Maišos funkcija buvo testuojama atliekant kelis testus: maišos formato, determinizmo, efektyvumo, kolizijų, lavinos efekto ir brute-force paieškos.

### 1. Maišos formato testavimas

Buvo tikrinama:

- 64 simbolių ilgio rezultatas;
- šešioliktainių simbolių naudojimas;
- skirtingo dydžio įvestys;
- tuščia įvestis;
- ASCII ir UTF-8 tekstas;
- tarpai ir naujos eilutės simboliai.

Visos testuotos įvestys sugeneravo tinkamo formato 64 simbolių šešioliktainę maišos reikšmę.

### 2. Determinizmo testavimas

Ta pati įvestis buvo maišoma kelis kartus ir lyginamos gautos maišos reikšmės.

Taip pat tikrinta seka:

```text
A → B → A
```

Pirmosios ir antrosios `A` maišos reikšmės sutapo, todėl ankstesnis maišos skaičiavimas neturėjo įtakos vėlesniam rezultatui.

### 3. Efektyvumo testavimas

Maišos funkcijos vykdymo laikas buvo matuojamas naudojant skirtingo dydžio įvestis.

| Eilučių skaičius | Baitai | Vidutinis laikas (ns) | Minimalus laikas (ns) | Maksimalus laikas (ns) |
|---:|---:|---:|---:|---:|
| 1 | 70 | 3500,2 | 3417 | 3625 |
| 2 | 123 | 5383,2 | 4875 | 5958 |
| 4 | 205 | 7358,2 | 7209 | 7500 |
| 8 | 362 | 11999,8 | 11917 | 12083 |
| 16 | 996 | 30308,4 | 29708 | 30667 |
| 32 | 1841 | 56342 | 53833 | 59834 |
| 64 | 3712 | 107967 | 107375 | 109250 |
| 128 | 9155 | 312492 | 255667 | 356875 |
| 256 | 20409 | 614692 | 611667 | 621250 |
| 512 | 47434 | 877358 | 809875 | 1022790 |
| 789 | 75595 | 1132180 | 1084330 | 1195330 |

Grafikas:

<img width="563" height="335" alt="Screenshot at Oct 01 11-20-42" src="https://github.com/user-attachments/assets/1b9c85bd-ba5d-46e2-b975-50406ee2763a" />

Didėjant įvesties dydžiui, bendras maišos funkcijos vykdymo laikas taip pat didėjo.

### 4. Kolizijų testavimas

Buvo tikrinama, ar skirtingos įvestys gali sugeneruoti vienodą maišos reikšmę.

Atsitiktinių įvesčių porų testas buvo atliekamas su skirtingo ilgio įvestimis. Kiekvienam ilgiui buvo tikrinama po 100 000 įvesčių porų.

| Įvesties ilgis | Porų kolizijos |
|---:|---:|
| 10 | 0 |
| 100 | 0 |
| 500 | 0 |
| 1000 | 0 |

Atskirai buvo patikrintos žinomos įvestys, kurioms galima gauti vienodą maišos reikšmę:

```text
07 ir 10 -> kolizija
xyz ir xzs -> kolizija
0007 ir 0010 -> kolizija
```

Atsitiktinių įvesčių porų testuose kolizijų nerasta, tačiau papildomas žinomų įvesčių testas parodė, kad maišos funkcijoje kolizijos yra įmanomos.

Šie rezultatai parodo tik testuotas įvestis ir neįrodo, kad maišos funkcija apskritai neturi kitų kolizijų.

### 5. Lavinos efekto testavimas

Lavinos efektas buvo tiriamas generuojant atsitiktines ASCII įvestis ir kiekvienoje įvesčių poroje pakeičiant vieną simbolį.

Kiekvienai porai buvo palyginamos gautos maišos reikšmės. Buvo skaičiuojama, kiek procentų pasikeitė galutinės maišos reikšmės bitų ir šešioliktainių simbolių.

Iš viso ištirta 100 000 įvesčių porų.

| Įvesties ilgis | Minimalus bitų pokytis | Maksimalus bitų pokytis | Vidutinis bitų pokytis | Minimalus hex pokytis | Maksimalus hex pokytis | Vidutinis hex pokytis |
|---:|---:|---:|---:|---:|---:|---:|
| 10 | 3,125 % | 66,7969 % | 31,6304 % | 12,5 % | 100 % | 60,1564 % |
| 100 | 3,125 % | 69,5312 % | 48,2673 % | 12,5 % | 100 % | 90,6882 % |
| 500 | 3,125 % | 69,5312 % | 49,7367 % | 12,5 % | 100 % | 93,187 % |
| 1000 | 3,125 % | 73,8281 % | 49,9252 % | 12,5 % | 100 % | 93,5283 % |
| **Visi įvedimai** | **3,125 %** | **73,8281 %** | **44,8899 %** | **12,5 %** | **100 %** | **84,39 %** |

Bendras bitų skirtumo vidurkis buvo **44,8899 %**, o šešioliktainių simbolių skirtumo vidurkis – **84,39 %**.

#### Bitų skirtumo histograma

Papildomai buvo apskaičiuotas bitų skirtumo pasiskirstymas. Rezultatai suskirstyti į 8 bitų intervalus, nurodant, kiek iš 256 hash bitų pasikeitė kiekvienu atveju.

```text
0–7:      0
8–15:     195
16–23:    588
24–31:    1317
32–39:    1671
40–47:    2001
48–55:    2022
56–63:    1828
64–71:    1952
72–79:    2275
80–87:    2771
88–95:    3512
96–103:   4998
104–111:  7751
112–119:  11191
120–127:  14570
128–135:  15304
136–143:  12903
144–151:  8171
152–159:  3654
160–167:  1085
168–175:  218
176–183:  22
184–191:  1
192–199:  0
200–207:  0
208–215:  0
216–223:  0
224–231:  0
232–239:  0
240–247:  0
248–255:  0
256:      0
```

Šie rezultatai parodo, kad pakeitus vieną įvesties simbolį galutinėje maišos reikšmėje pasikeičia didelė dalis bitų ir šešioliktainių simbolių. Vidutinis bitų pokytis buvo artimas 50 %, tačiau trumpesnėms įvestims jis buvo mažesnis.

### 6. Brute-force testavimas

Buvo atlikta brute-force paieška naudojant keturių skaitmenų įvestį:

```text
4729
```

Iš viso buvo patikrinta 10 000 galimų keturių skaitmenų įvesčių.

#### Paieška be druskos

- Tikslinė įvestis: `4729`
- Bandymų skaičius: 10 000
- Sutapimų skaičius: 5
- Pirmas sutapimas: `4699`
- Bandymų iki pirmo sutapimo: 4700
- Vykdymo laikas: 6916 µs

Rasti sutapimai:

```text
4699
4729
4732
5029
5032
```

#### Paieška su vieša druska

Naudota druska:

```text
ABC
```

- Tikslinė įvestis: `4729`
- Bandymų skaičius: 10 000
- Sutapimų skaičius: 5
- Pirmas sutapimas: `4699`
- Bandymų iki pirmo sutapimo: 4700
- Vykdymo laikas: 8379 µs

Rasti sutapimai:

```text
4699
4729
4732
5029
5032
```

Šis eksperimentas parodė, kad žinoma druska savaime neapsaugo nuo brute-force paieškos, kai galimų įvesčių skaičius yra labai mažas. Taip pat matyti, kad dėl kolizijų pirmas rastas sutapimas nebūtinai yra tikroji pradinė įvestis.

### Slapto atsitiktinumo patikrinimas

Buvo papildomai patikrintas slaptas atsitiktinumas. Naudojant tą pačią įvestį ir tą patį slaptą atsitiktinumą, pakartotinai apskaičiuota `hash(input + secret)` reikšmė.

Šis testas patvirtino, kad naudojant tuos pačius duomenis gaunama ta pati maišos reikšmė.
