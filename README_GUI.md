# Morse Translator - GUI Version

Lightweight native Win32 GUI with visual styles for a cleaner look.

## Changes in latest update
- Added explicit InitCommonControlsEx for better visual styles support
- Increased window height to prevent text cutoff
- Shortened bottom instruction text to fit
- Unicode support for arrows (→)
- Morse mode input filtering (only . - space /)
- Clean title "Morse Translator"
- Better fonts and layout

## Compile
```cmd
g++ -mwindows -Os -s morse_gui.cpp -o MorseTranslatorGUI.exe
```

Run the .exe directly. The GUI now has themed controls (if visual styles are active on your system) and proper Unicode text.