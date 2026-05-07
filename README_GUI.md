# Morse Translator GUI - Modernized

Resizable window, dynamic layout, Unicode, Morse input filter, visual styles.

## New in this version
- Resizable window with automatic control repositioning
- Proper wide-string Unicode (correct arrows and title)
- InitCommonControlsEx + manifest for visual styles
- Darker / cleaner look possible with system themes
- Fullscreen support can be added easily (F11 toggle)

## Compile (add -municode for best Unicode support)
g++ -mwindows -municode -Os -s morse_gui.cpp -o MorseTranslatorGUI.exe

Run and enjoy the improved modern-feeling native GUI.