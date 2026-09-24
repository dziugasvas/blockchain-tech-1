# Maišos funkcija

Maišos funkcija, sukurta naudojant C++ kalbą.

## Idėja

- Naudojamos 8 atskiros 32 bitų būsenos reikšmės.
- Kiekvienas įvesties baitas paveikia visas 8 būsenos dalis.
- Būsena keičiama pagal formulę `state[i] = state[i] * 7 + byte + i`.
- Galutinis rezultatas yra 256 bitų ilgio ir pateikiamas kaip 64 hex simboliai.

## Įvestis

Programa palaiko teksto įvedimą ranka ir failo nuskaitymą.

Failai skaitomi `binary` režimu pagal tikslius jų baitus. Rankinio įvedimo metu Enter sukurtas naujos eilutės simbolis į maišą neįtraukiamas. UTF-8 tekstas apdorojamas baitais.

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