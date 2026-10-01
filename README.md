# Maišos funkcija

> **Versija: v0.2.** Šioje versijoje maišos funkcija (`hashFunction`) buvo atnaujinta naudojant **Claude AI (Anthropic)**. Ankstesnė, savarankiškai sukurta versija (v0.1 / v0.1.2) palyginama žemiau, skyriuje „v0.1.2 ir v0.2 palyginimas“.

Nuosava maišos (hash) funkcija, sukurta naudojant C++ kalbą. Projektas skirtas ištirti maišos funkcijos veikimą, efektyvumą, kolizijas, lavinos efektą ir brute-force paiešką.

## Maišos funkcijos idėja

Mano maišos funkcija sukuria fiksuoto dydžio 256 bitų maišos reikšmę, kuri pateikiama kaip 64 šešioliktainių simbolių eilutė.

Algoritmas (v0.2) veikia šiais etapais:

1. **Pradinė būsena** – sukuriamos 8 atskiros 32 bitų būsenos reikšmės `h[0..7]`. Jos nebėra nuliai: naudojamos fiksuotos konstantos, gautos iš kvadratinių šaknų trupmeninių dalių pirmųjų 32 bitų (pirminiai skaičiai 41, 43, 47, 53, 59, 61, 67, 71).
2. **Įvesties padalijimas ir užpildymas** – įvestis dalijama 32 baitų (256 bitų) blokais. Likę baitai papildomi baitu `0x80`, nuliais, o paskutiniai 8 bloko baitai užpildomi įvesties ilgiu baitais (64 bitų skaičius, little-endian). Priklausomai nuo likusių baitų skaičiaus, pridedamas vienas arba du paskutiniai blokai.
3. **Bloko apdorojimas** – 32 baitų blokas paverčiamas 8 žodžiais `w[i]` (32 bitų, little-endian), o darbinė būsena `x[i] = h[i] XOR w[i]`.
4. **Maišymo permutacija (10 raundų)** – kiekviename raunde:
   - prie `x[0]` pridedama raundo konstanta;
   - kiekvienai `x[i]`: sudedama su kaimynine reikšme, pasukama bitais (`rotl`) ir sujungiama XOR su kita reikšme;
   - kiekviena `x[i]` padauginama iš nelyginės konstantos ir sumaišoma su `x[i] >> 15`.
5. **Būsenos atnaujinimas** – po permutacijos `h[i] = h[i] + x[i]` (mod 2³²), t. y. rezultatas pridedamas prie ankstesnės būsenos.
6. **Rezultato formatavimas** – apdorojus visus blokus, 8 būsenos reikšmės užrašomos kaip 8 šešioliktainiai simboliai kiekviena (mažosiomis raidėmis). Galutinis rezultatas sudarytas iš 64 šešioliktainių simbolių, t. y. 256 bitų.

Pseudokodas:

```text
h[0..7] = IV[0..7]
padalinti įvestį į 32 baitų blokus, gale pridėti 0x80, nulius ir ilgį (8 baitai)

kiekvienam blokui:
    w[0..7] = blokas (32 bitų žodžiai, little-endian)
    x[i]    = h[i] XOR w[i]

    kartoti 10 raundų (r = 0..9):
        x[0] = x[0] + RK[r]
        kiekvienam i = 0..7:
            x[i] = x[i] + x[(i+1) mod 8]
            x[i] = rotl(x[i], ROT[i])            # ROT = {5, 9, 13, 17, 21, 25, 29, 11}
            x[i] = x[i] XOR x[(i+3) mod 8]
        kiekvienam i = 0..7:
            x[i] = x[i] * (i nelyginis ? 0x243F6A89 : 0xB7E15163)
            x[i] = x[i] XOR (x[i] >> 15)

    h[i] = h[i] + x[i]                           # visa aritmetika mod 2^32

rezultatas = hex(h[0]) || ... || hex(h[7])       # po 8 mažųjų hex simbolių
```

Ta pati įvestis visada sugeneruoja tą pačią maišos reikšmę.

## Funkcijos savybės

- Fiksuotas maišos dydis – **256 bitai**.
- Maišos rezultatas pateikiamas kaip **64 šešioliktainiai simboliai**.
- Įvestis apdorojama **32 baitų blokais**, gale pridedamas užpildymas su įvesties ilgiu.
- Pradinė būsena yra fiksuotos konstantos, o ne nuliai.
- Kiekvieno bloko apdorojimas paveikia visas 8 būsenos reikšmes.
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

Maišos funkcija buvo testuojama atliekant kelis testus: maišos formato, determinizmo, efektyvumo, kolizijų, lavinos efekto ir brute-force paieškos. Žemiau pateikti **v0.2** versijos rezultatai; v0.1.2 rezultatai pateikti skyriuje „v0.1.2 ir v0.2 palyginimas“.

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
| 1 | 70 | 4291,6 | 4250 | 4333 |
| 2 | 123 | 6550 | 6459 | 6625 |
| 4 | 205 | 8725 | 8667 | 8791 |
| 8 | 362 | 14424,8 | 14291 | 14625 |
| 16 | 996 | 36883 | 36750 | 37041 |
| 32 | 1841 | 67200,2 | 66125 | 68667 |
| 64 | 3712 | 137433 | 132125 | 149250 |
| 128 | 9155 | 325125 | 324083 | 327250 |
| 256 | 20409 | 478816 | 456333 | 532125 |
| 512 | 47434 | 829300 | 806708 | 890667 |
| 789 | 75595 | 1028880 | 985917 | 1063710 |

Grafikas:

<img width="566" height="339" alt="Screenshot at Oct 01 12-25-33" src="https://github.com/user-attachments/assets/4ccc4d2e-b441-4183-baf9-980778b2b011" />

Didėjant įvesties dydžiui, bendras maišos funkcijos vykdymo laikas taip pat didėjo. Matavimai atlikti po 5 kartus kiekvienam dydžiui, todėl pavieniai taškai gali labiau išsiskirti: pavyzdžiui, 256 eilučių įvestyje (20 409 baitų) laikas yra 478 816 ns, o 128 eilučių įvestyje (9 155 baitai) – 325 125 ns.

### 4. Kolizijų testavimas

Buvo tikrinama, ar skirtingos įvestys gali sugeneruoti vienodą maišos reikšmę.

Atsitiktinių įvesčių porų testas buvo atliekamas su skirtingo ilgio įvestimis. Kiekvienam ilgiui buvo tikrinama po 100 000 įvesčių porų.

| Įvesties ilgis | Porų kolizijos |
|---:|---:|
| 10 | 0 |
| 100 | 0 |
| 500 | 0 |
| 1000 | 0 |

Atskirai buvo patikrintos žinomos įvestys, kurioms v0.1.2 versijoje buvo galima gauti vienodą maišos reikšmę:

```text
07 ir 10
xyz ir xzs
0007 ir 0010
```

Šių porų testas v0.2 versijoje kolizijų neišvedė, t. y. nė vienos iš šių porų maišos reikšmės nesutapo.

Šie rezultatai parodo tik testuotas įvestis ir neįrodo, kad maišos funkcija apskritai neturi kolizijų.

### 5. Lavinos efekto testavimas

Lavinos efektas buvo tiriamas generuojant atsitiktines ASCII įvestis ir kiekvienoje įvesčių poroje pakeičiant vieną simbolį.

Kiekvienai porai buvo palyginamos gautos maišos reikšmės. Buvo skaičiuojama, kiek procentų pasikeitė galutinės maišos reikšmės bitų ir šešioliktainių simbolių.

Iš viso ištirta 100 000 įvesčių porų.

| Įvesties ilgis | Minimalus bitų pokytis | Maksimalus bitų pokytis | Vidutinis bitų pokytis | Minimalus hex pokytis | Maksimalus hex pokytis | Vidutinis hex pokytis |
|---:|---:|---:|---:|---:|---:|---:|
| 10 | 36,7188 % | 62,1094 % | 49,9782 % | 78,125 % | 100 % | 93,6988 % |
| 100 | 37,8906 % | 62,5 % | 50,0149 % | 79,6875 % | 100 % | 93,7602 % |
| 500 | 35,5469 % | 61,7188 % | 49,9728 % | 79,6875 % | 100 % | 93,7358 % |
| 1000 | 37,1094 % | 61,7188 % | 49,9878 % | 76,5625 % | 100 % | 93,7603 % |
| **Visi įvedimai** | **35,5469 %** | **62,5 %** | **49,9884 %** | **76,5625 %** | **100 %** | **93,7388 %** |

Bendras bitų skirtumo vidurkis buvo **49,9884 %**, o šešioliktainių simbolių skirtumo vidurkis – **93,7388 %**. Bendros minimalios ir maksimalios reikšmės lentelėje paimtos iš atskirų ilgių eilučių (rezultatų faile pateikti tik vidurkiai).

#### Bitų skirtumo histograma

Papildomai buvo apskaičiuotas bitų skirtumo pasiskirstymas. Rezultatai suskirstyti į 8 bitų intervalus, nurodant, kiek iš 256 hash bitų pasikeitė kiekvienu atveju.

```text
0–7:      0
8–15:     0
16–23:    0
24–31:    0
32–39:    0
40–47:    0
48–55:    0
56–63:    0
64–71:    0
72–79:    0
80–87:    0
88–95:    5
96–103:   85
104–111:  1856
112–119:  12517
120–127:  33202
128–135:  35146
136–143:  14514
144–151:  2514
152–159:  160
160–167:  1
168–175:  0
176–183:  0
184–191:  0
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

Dauguma porų (68 348 iš 100 000) pateko į 120–135 bitų intervalus, t. y. aplink 128 bitus (50 % maišos reikšmės bitų). Visų ilgių, įskaitant trumpiausią (10), vidutinis bitų pokytis buvo artimas 50 %.

### 6. Brute-force testavimas

Buvo atlikta brute-force paieška naudojant keturių skaitmenų įvestį:

```text
4729
```

Iš viso buvo patikrinta 10 000 galimų keturių skaitmenų įvesčių.

#### Paieška be druskos

- Tikslinė įvestis: `4729`
- Bandymų skaičius: 10 000
- Sutapimų skaičius: 1
- Pirmas sutapimas: `4729`
- Bandymų iki pirmo sutapimo: 4730
- Vykdymo laikas: 5967 µs

Rasti sutapimai:

```text
4729
```

#### Paieška su vieša druska

Naudota druska:

```text
ABC
```

- Tikslinė įvestis: `4729`
- Bandymų skaičius: 10 000
- Sutapimų skaičius: 1
- Pirmas sutapimas: `4729`
- Bandymų iki pirmo sutapimo: 4730
- Vykdymo laikas: 6824 µs

Rasti sutapimai:

```text
4729
```

Šiame kandidatų rinkinyje (0000–9999) tiek be druskos, tiek su druska rastas tik vienas sutapimas – pati tikslinė įvestis. Eksperimentas taip pat parodė, kad žinoma druska savaime neapsaugo nuo brute-force paieškos, kai galimų įvesčių skaičius yra labai mažas: perrinkti visus 10 000 kandidatų užtruko kelias milisekundes.

### Slapto atsitiktinumo patikrinimas

Buvo papildomai patikrintas slaptas atsitiktinumas. Naudojant tą pačią įvestį ir tą patį slaptą atsitiktinumą, pakartotinai apskaičiuota `hash(input + secret)` reikšmė.

Šis testas patvirtino, kad naudojant tuos pačius duomenis gaunama ta pati maišos reikšmė.

## v0.1 ir v0.2 palyginimas

Abi versijos buvo testuotos tais pačiais testais. v0.1.2 reikšmės paimtos iš ankstesnės README versijos, v0.2 – iš šioje versijoje pateiktų rezultatų.

| Sritis | v0.1.2 | v0.2 |
|---|---|---|
| Algoritmas | 8 × 32 bitų būsena, pradinės reikšmės `0`; kiekvienam baitui: `state[i] = state[i] * 7 + byte + i` | 8 × 32 bitų būsena, pradinės reikšmės – fiksuotos konstantos; 32 baitų blokai, užpildymas su ilgiu; 10 raundų permutacija (sudėtis, pasukimas, XOR, daugyba, `x >> 15`); rezultatas pridedamas prie ankstesnės būsenos |
| Išvesties dydis | 256 bitai, 64 hex simboliai | 256 bitai, 64 hex simboliai |
| Efektyvumas (visas failas, 75 595 baitai, vid.) | 1 132 180 ns | 1 028 880 ns |
| Atsitiktinių porų kolizijos (100 000 porų, ilgiai 10 / 100 / 500 / 1000) | 0 / 0 / 0 / 0 | 0 / 0 / 0 / 0 |
| Žinomų įvesčių kolizijos (`07`/`10`, `xyz`/`xzs`, `0007`/`0010`) | 3 iš 3 porų sutapo | 0 iš 3 porų sutapo |
| Lavina: bitų pokytis, vidurkis (visi įvedimai) | 44,8899 % | 49,9884 % |
| Lavina: bitų pokytis, vidurkis (ilgis 10) | 31,6304 % | 49,9782 % |
| Lavina: bitų pokytis, min. – maks. (visi įvedimai) | 3,125 % – 73,8281 % | 35,5469 % – 62,5 % |
| Lavina: hex pokytis, vidurkis (visi įvedimai) | 84,39 % | 93,7388 % |
| Lavina: hex pokytis, min. – maks. (visi įvedimai) | 12,5 % – 100 % | 76,5625 % – 100 % |
| Brute-force `4729`, be druskos: sutapimai | 5 (`4699`, `4729`, `4732`, `5029`, `5032`) | 1 (`4729`) |
| Brute-force: bandymų iki pirmo sutapimo | 4700 (`4699`) | 4730 (`4729`) |
| Brute-force: laikas be druskos / su druska `ABC` | 6916 µs / 8379 µs | 5967 µs / 6824 µs |
| Brute-force su druska `ABC`: sutapimai | 5 | 1 |

### Efektyvumo palyginimas

Vidutinis vienos maišos skaičiavimo laikas (ns), naudojant tą patį efektyvumo testą:

| Eilučių skaičius | Baitai | v0.1.2 | v0.2 |
|---:|---:|---:|---:|
| 1 | 70 | 3500,2 | 4291,6 |
| 2 | 123 | 5383,2 | 6550 |
| 4 | 205 | 7358,2 | 8725 |
| 8 | 362 | 11999,8 | 14424,8 |
| 16 | 996 | 30308,4 | 36883 |
| 32 | 1841 | 56342 | 67200,2 |
| 64 | 3712 | 107967 | 137433 |
| 128 | 9155 | 312492 | 325125 |
| 256 | 20409 | 614692 | 478816 |
| 512 | 47434 | 877358 | 829300 |
| 789 | 75595 | 1132180 | 1028880 |

## DI naudojimas

- **Įrankis:** Claude (Anthropic).
- **Kam naudota:** v0.2 versijos maišos funkcijai (`hashFunction`) atnaujinti. Pasiūlyti ir įgyvendinti: apdorojimas 32 baitų blokais su užpildymu ir įvesties ilgiu, nenulinės pradinės konstantos, raundų permutacija (sudėtis, pasukimas, XOR, daugyba nelyginėmis konstantomis, `x >> 15`) ir ankstesnės būsenos pridėjimas po kiekvieno bloko.
- **Likusi dalis:** testai (`tests.cpp`), jų paleidimas ir rezultatų pateikimas atlikti savarankiškai; v0.1.2 funkcija ir testai sukurti be DI.

**Testavimo aplinka:** Apple MacBook Air (M4), macOS, Apple clang (komanda `g++` macOS sistemoje), kompiliavimas per `Makefile` (`g++ -std=c++17`, be optimizavimo parametrų). Tai mokomoji maišos funkcija, o ne saugi maiša: ji nėra skirta slaptažodžiams ar realiems duomenims saugoti, o atlikti testai nepatvirtina jos kriptografinio saugumo.
