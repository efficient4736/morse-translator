# Morse Translator
Text-to-morse and morse-to-text translator (console application for Windows).


# Morsecode-Übersetzer

Ein einfaches C++-Programm, das Text in Morsecode und Morsecode in Text übersetzt. Es ist ideal für Lernende und Enthusiasten, die ein stabiles, benutzerfreundliches Tool ohne externe Abhängigkeiten suchen.

## Funktionen
- **Text zu Morse**: Wandelt Großbuchstaben, Zahlen und Leerzeichen in Morsecode um.
- **Morse zu Text**: Übersetzt Morsecode (Buchstaben durch Leerzeichen, Wörter durch `/` getrennt) zurück in Text.
- **Fehlerbehandlung**: Erkennt ungültige Eingaben und ersetzt sie durch `?` mit entsprechenden Hinweisen.
- **Übersichtliche Ausgabe**: Formatierte Ausgabe mit Freizeilen für bessere Lesbarkeit.
- **Keine Abhängigkeiten**: Nutzt ausschließlich die C++-Standardbibliothek.

## Anforderungen
- C++-Compiler (z. B. Embarcadero Dev-C++, g++, clang++)
- C++11 oder höher
- Keine externen Bibliotheken erforderlich

## Nutzung
1. Kompilieren und starten Sie das Programm.
2. Wählen Sie eine Option:
   - `1`: Text zu Morse
   - `2`: Morse zu Text
3. Geben Sie den Text oder Morsecode ein:
   - Text: Nur Großbuchstaben, Zahlen und Leerzeichen (z. B. `SOS A`)
   - Morsecode: Buchstaben durch Leerzeichen, Wörter durch `/` getrennt (z. B. `... --- ... / .-`)
4. Die Ausgabe wird formatiert angezeigt, ungültige Zeichen werden durch `?` ersetzt.

### Beispiel
**Eingabe (Text zu Morse):**
```
Wahl: 1
Text eingeben: SOS A
Morsecode-Ausgabe:
... --- ... 
.-
```

**Eingabe (Morse zu Text):**
```
Wahl: 2
Morsecode eingeben: ... --- ... / .-
Text-Ausgabe:
SOS A
```

## Installation
1. Klone das Repository:
   ```bash
   git clone https://github.com/efficient4736/morse-translator.git
   ```
2. Kompiliere die Datei `morse_translator.cpp`:
   ```bash
   g++ morse_translator.cpp -o morse_translator
   ```
3. Starte das Programm:
   ```bash
   ./morse_translator
   ```
