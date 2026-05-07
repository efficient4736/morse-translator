# Morse Translator - GUI Version (Win32)

A simple, lightweight native Windows GUI for the Morse code translator.

## Features
- **Small executable size** (~50-100 KB when compiled with optimizations)
- **No external dependencies** - pure Win32 API + C++ standard library
- Same conversion logic as the console version
- Multiline input and output
- Radio button mode selection (Text → Morse or Morse → Text)
- Clear buttons for convenience
- Error handling with '?' for invalid characters

## How to Compile (Windows)

### Using MinGW / g++ (recommended for small size)
```bash
g++ -mwindows -Os -s morse_gui.cpp -o MorseTranslatorGUI.exe
```

### Using MSVC (Visual Studio Developer Command Prompt)
```cmd
cl /EHsc /O1 /FeMorseTranslatorGUI.exe morse_gui.cpp user32.lib gdi32.lib
```

### Using Dev-C++ or similar
Just add the file and compile as Windows GUI application.

## How to Use
1. Run the executable
2. Select mode with radio buttons
3. Enter text or Morse code in the Input box
4. Click **Convert**
5. View result in Output box
6. Use Clear buttons as needed

## Notes
- For Morse → Text: Separate letters with spaces, words with `/`
- Example Morse input: `... --- ... / .-`
- The app is fixed-size for simplicity and small footprint

## Original Console Version
See `main.cpp` for the original console application.

## License
Same as original project.