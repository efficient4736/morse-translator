#include <windows.h>
#include <string>
#include <map>
#include <cctype>
#include <vector>

// Enable visual styles for a more modern look (themed buttons, etc.)
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Control IDs
#define ID_INPUT_EDIT       101
#define ID_OUTPUT_EDIT      102
#define ID_BTN_CONVERT      103
#define ID_BTN_CLEAR_INPUT  104
#define ID_BTN_CLEAR_OUTPUT 105
#define ID_RADIO_T2M        106
#define ID_RADIO_M2T        107
#define ID_STATIC_MODE      108

// Global handles
HWND hInput, hOutput;
HWND hBtnConvert, hBtnClearInput, hBtnClearOutput;
HWND hRadioT2M, hRadioM2T;
HFONT hFontLabel, hFontEdit;

// Morse code map (same as console version)
std::map<char, std::string> morse = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, 
    {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, 
    {'7', "--..."}, {'8', "---.."}, {'9', "----."}
};

// Inverse map
std::map<std::string, char> morse_to_char;

void InitMorseMaps() {
    for (const auto& pair : morse) {
        morse_to_char[pair.second] = pair.first;
    }
}

// Text to Morse conversion (same logic as console)
std::string TextToMorse(const std::string& text) {
    std::string result;
    std::string word = "";
    bool has_invalid = false;
    
    for (char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                result += word + "\n";
                word = "";
            }
        } else {
            char uc = toupper(c);
            if (morse.find(uc) != morse.end()) {
                word += morse[uc] + " ";
            } else {
                word += "? ";
                has_invalid = true;
            }
        }
    }
    if (!word.empty()) {
        result += word + "\n";
    }
    if (has_invalid) {
        result += "\n[Hinweis: Ungültige Zeichen wurden durch '?' ersetzt.]\n";
    }
    return result;
}

// Morse to Text conversion (same logic as console)
std::string MorseToText(const std::string& morse_input) {
    std::string result;
    std::string letter = "";
    bool has_invalid = false;
    
    for (size_t i = 0; i <= morse_input.size(); ++i) {
        char c = (i < morse_input.size()) ? morse_input[i] : ' ';
        if (c == ' ' || c == '/') {
            if (!letter.empty()) {
                if (morse_to_char.find(letter) != morse_to_char.end()) {
                    result += morse_to_char[letter];
                } else {
                    result += "?";
                    has_invalid = true;
                }
                letter = "";
            }
            if (c == '/') {
                result += " ";
            }
        } else {
            letter += c;
        }
    }
    if (has_invalid) {
        result += "\n\n[Hinweis: Ungültige Morsezeichen wurden durch '?' ersetzt.]";
    }
    return result;
}

// Helper: Filter input for Morse mode (only . - space / allowed)
std::string FilterMorseInput(const std::string& input) {
    std::string filtered;
    for (char c : input) {
        if (c == '.' || c == '-' || c == ' ' || c == '/') {
            filtered += c;
        }
    }
    return filtered;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create fonts - Segoe UI for modern look on labels/buttons, Consolas for code
            hFontLabel = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                   DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                   CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
            
            hFontEdit = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                    CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas");
            
            // Mode label
            CreateWindow("STATIC", "Mode:", WS_VISIBLE | WS_CHILD,
                         20, 15, 50, 22, hwnd, (HMENU)ID_STATIC_MODE, NULL, NULL);
            
            // Radio buttons for mode (wide strings for proper Unicode arrow)
            hRadioT2M = CreateWindowW(L"BUTTON", L"Text → Morse", 
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
                80, 13, 145, 26, hwnd, (HMENU)ID_RADIO_T2M, NULL, NULL);
            
            hRadioM2T = CreateWindowW(L"BUTTON", L"Morse → Text", 
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                235, 13, 145, 26, hwnd, (HMENU)ID_RADIO_M2T, NULL, NULL);
            
            // Default to Text to Morse
            SendMessage(hRadioT2M, BM_SETCHECK, BST_CHECKED, 0);
            
            // Input label
            CreateWindow("STATIC", "Input:", WS_VISIBLE | WS_CHILD,
                         20, 50, 60, 20, hwnd, NULL, NULL, NULL);
            
            // Input edit (multiline)
            hInput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
                WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN,
                20, 70, 560, 160, hwnd, (HMENU)ID_INPUT_EDIT, NULL, NULL);
            SendMessage(hInput, WM_SETFONT, (WPARAM)hFontEdit, TRUE);
            
            // Output label
            CreateWindow("STATIC", "Output:", WS_VISIBLE | WS_CHILD,
                         20, 240, 60, 20, hwnd, NULL, NULL, NULL);
            
            // Output edit (multiline, read-only)
            hOutput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", 
                WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
                20, 260, 560, 160, hwnd, (HMENU)ID_OUTPUT_EDIT, NULL, NULL);
            SendMessage(hOutput, WM_SETFONT, (WPARAM)hFontEdit, TRUE);
            
            // Buttons - slightly larger and better spaced
            hBtnConvert = CreateWindow("BUTTON", "Convert", 
                WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 435, 130, 38, hwnd, (HMENU)ID_BTN_CONVERT, NULL, NULL);
            
            hBtnClearInput = CreateWindow("BUTTON", "Clear Input", 
                WS_VISIBLE | WS_CHILD,
                165, 435, 130, 38, hwnd, (HMENU)ID_BTN_CLEAR_INPUT, NULL, NULL);
            
            hBtnClearOutput = CreateWindow("BUTTON", "Clear Output", 
                WS_VISIBLE | WS_CHILD,
                310, 435, 130, 38, hwnd, (HMENU)ID_BTN_CLEAR_OUTPUT, NULL, NULL);
            
            // Instructions / hint at bottom (updated for Morse restrictions)
            CreateWindow("STATIC", 
                "Instructions: In Morse mode only . - space and / are allowed. Use spaces between letters, / between words.",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                20, 485, 560, 35, hwnd, NULL, NULL, NULL);
            
            return 0;
        }
        
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            
            if (wmId == ID_BTN_CONVERT) {
                // Get input text
                int len = GetWindowTextLength(hInput) + 1;
                std::vector<char> buffer(len);
                GetWindowText(hInput, buffer.data(), len);
                std::string input(buffer.data());
                
                // Determine mode
                bool isTextToMorse = (SendMessage(hRadioT2M, BM_GETCHECK, 0, 0) == BST_CHECKED);
                
                std::string processedInput = input;
                if (!isTextToMorse) {
                    // Morse mode: filter to only valid characters . - space /
                    processedInput = FilterMorseInput(input);
                    if (processedInput != input && !input.empty()) {
                        // Optionally show that invalid chars were removed (simple approach: just use filtered)
                    }
                }
                
                std::string output;
                if (isTextToMorse) {
                    output = TextToMorse(processedInput);
                } else {
                    output = MorseToText(processedInput);
                }
                
                // Set output
                SetWindowText(hOutput, output.c_str());
            } 
            else if (wmId == ID_BTN_CLEAR_INPUT) {
                SetWindowText(hInput, "");
            } 
            else if (wmId == ID_BTN_CLEAR_OUTPUT) {
                SetWindowText(hOutput, "");
            }
            
            return 0;
        }
        
        case WM_DESTROY: {
            if (hFontLabel) DeleteObject(hFontLabel);
            if (hFontEdit) DeleteObject(hFontEdit);
            PostQuitMessage(0);
            return 0;
        }
        
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    InitMorseMaps();
    
    const wchar_t* CLASS_NAME = L"MorseTranslatorGUI";
    
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // Default icon (can be replaced with custom .ico)
    
    RegisterClassW(&wc);
    
    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, L"Morse Translator",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 620, 540,
        NULL, NULL, hInstance, NULL
    );
    
    if (!hwnd) return 0;
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}
