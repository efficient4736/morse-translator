# Morse Translator - GUI Version (Win32)

A simple, lightweight native Windows GUI for the Morse code translator.

## Improvements in this version
- Modern visual styles enabled (themed controls)
- Proper Unicode support for arrows and special characters
- Morse mode input is automatically filtered to valid characters only (`.` `-` space `/`)
- Cleaner window title without "(Win32)"
- Better fonts (Segoe UI + Consolas)
- Updated instructions

## Features
- **Small executable size** (~50-100 KB when compiled with optimizations)
- **No external dependencies** - pure Win32 API + C++ standard library
- Same conversion logic as the console version
- Multiline input and output
- Radio button mode selection
- Clear buttons
- Error handling with '?' for invalid characters

## How to Compile (Windows)

### Using MinGW / g++ (recommended for small size)
```bash
g++ -mwindows -Os -s morse_gui.cpp -o MorseTranslatorGUI.exe
```

### Using MSVC
```cmd
cl /EHsc /O1 /FeMorseTranslatorGUI.exe morse_gui.cpp user32.lib gdi32.lib comctl32.lib
```

## How to Use
1. Run the executable
2. Select mode with radio buttons
3. Enter text or Morse code in the Input box
   - In **Morse → Text** mode only `.` `-` space and `/` are accepted (others are ignored)
4. Click **Convert**
5. View result in Output box
6. Use Clear buttons as needed

## Notes
- For Morse → Text: Separate letters with spaces, words with `/`
- Example Morse input: `... --- ... / .-`
- The app uses a fixed-size window for simplicity

## Original Console Version
See `main.cpp` for the original console application.

## Adding a Custom Icon (optional)
To replace the default icon in the title bar and taskbar:
1. Create or download a `.ico` file (e.g. 32x32 or 16x16)
2. Add it as a resource in your project or use tools like Resource Hacker on the .exe

## License
Same as original project.