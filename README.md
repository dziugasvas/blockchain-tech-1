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
| 1 | 70 | 4533,4 | 4417 | 4709 |
| 2 | 123 | 6991,8 | 6542 | 7709 |
| 4 | 205 | 9533,4 | 9333 | 9792 |
| 8 | 362 | 15258,2 | 14958 | 15750 |
| 16 | 996 | 40691,6 | 38542 | 43291 |
| 32 | 1841 | 70758,4 | 68959 | 71333 |
| 64 | 3712 | 137025 | 134875 | 141459 |
| 128 | 9155 | 302883 | 299208 | 308500 |
| 256 | 20409 | 397642 | 321750 | 584417 |
| 512 | 47434 | 895508 | 797083 | 959375 |
| 789 | 75595 | 1097930 | 1048290 | 1119380 |

Didėjant įvesties dydžiui, bendras maišos funkcijos vykdymo laikas taip pat didėjo.

### 4. Kolizijų testavimas

Buvo tikrinama, ar skirtingos įvestys gali sugeneruoti vienodą maišos reikšmę.

Kiekvienam įvesties ilgiui buvo patikrinta po 100 000 įvesčių porų.

| Įvesties ilgis | Porų kolizijos |
|---:|---:|
| 10 | 0 |
| 100 | 0 |
| 500 | 0 |
| 1000 | 0 |

Papildomai buvo atliktas struktūrinių įvesčių testas:

- Įvesčių skaičius: 8
- Rastos kolizijos: 0

Testuotose įvestyse kolizijų rasta nebuvo. Šie rezultatai apibūdina tik testuotas įvestis ir neįrodo, kad maišos funkcija apskritai neturi kolizijų.

### 5. Lavinos efekto testavimas

Lavinos efektas buvo tiriamas pakeičiant vieną įvesties simbolį ir skaičiuojant, kiek pasikeitė galutinės maišos reikšmės bitų bei šešioliktainių simbolių.

Iš viso ištirta 100 000 įvesčių porų.

#### Bitų pokytis

| Įvesties ilgis | Minimalus | Maksimalus | Vidurkis |
|---:|---:|---:|---:|
| 10 | 3,125 % | 66,7969 % | 31,6304 % |
| 100 | 3,125 % | 69,5312 % | 48,2673 % |
| 500 | 3,125 % | 69,5312 % | 49,7367 % |
| 1000 | 3,125 % | 73,8281 % | 49,9252 % |
| **Visos įvestys** | — | — | **44,8899 %** |

#### Šešioliktainių simbolių pokytis

| Įvesties ilgis | Minimalus | Maksimalus | Vidurkis |
|---:|---:|---:|---:|
| 10 | 12,5 % | 100 % | 60,1564 % |
| 100 | 12,5 % | 100 % | 90,6882 % |
| 500 | 12,5 % | 100 % | 93,187 % |
| 1000 | 12,5 % | 100 % | 93,5283 % |
| **Visos įvestys** | — | — | **84,39 %** |

Vidutinis bitų skirtumas buvo 44,8899 %, o šešioliktainių simbolių skirtumas – 84,39 %.

### 6. Brute-force testavimas

Buvo atlikta brute-force paieška naudojant keturių skaitmenų įvestį.

Tikslinė įvestis:

```text
4729
```

Iš viso buvo patikrinta 10 000 galimų keturių skaitmenų įvesčių.

#### Paieška be druskos

- Bandymų skaičius: 10 000
- Sutapimų skaičius: 5
- Pirmas sutapimas: po 4700 bandymų
- Vykdymo laikas: 7096 µs

#### Paieška su vieša druska

Naudota druska:

```text
ABC
```

- Bandymų skaičius: 10 000
- Sutapimų skaičius: 5
- Pirmas sutapimas: po 4700 bandymų
- Vykdymo laikas: 7906 µs

Šis testas parodė, kad žinoma druska pati savaime nepašalina brute-force paieškos galimybės, kai galimų įvesčių aibė yra labai maža.

### Slapto atsitiktinumo patikrinimas

Papildomai patikrintas slapto atsitiktinumo panaudojimas.

Naudotas slaptas atsitiktinumas:

`X7pQ2`

Buvo apskaičiuota `hash(target + secret)` reikšmė ir patikrinta,
ar pakartotinai naudojant tą pačią įvestį gaunama ta pati maišos reikšmė.