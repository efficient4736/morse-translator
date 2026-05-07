#include <windows.h>
#include <commctrl.h>
#include <string>
#include <map>
#include <cctype>
#include <vector>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_INPUT_EDIT       101
#define ID_OUTPUT_EDIT      102
#define ID_BTN_CONVERT      103
#define ID_BTN_CLEAR_INPUT  104
#define ID_BTN_CLEAR_OUTPUT 105
#define ID_RADIO_T2M        106
#define ID_RADIO_M2T        107

HWND hInput, hOutput, hBtnConvert, hBtnClearInput, hBtnClearOutput, hRadioT2M, hRadioM2T;
HFONT hFontLabel, hFontEdit;

std::map<char, std::string> morse = { /* ... same as before ... */ };
std::map<std::string, char> morse_to_char;

void InitMorseMaps() { /* ... same ... */ }

std::string TextToMorse(const std::string& text) { /* ... same ... */ }
std::string MorseToText(const std::string& morse_input) { /* ... same ... */ }
std::string FilterMorseInput(const std::string& input) { /* ... same ... */ }

void LayoutControls(HWND hwnd, int width, int height) {
    // Simple proportional layout for resizable window
    int margin = 20;
    int radioY = 15;
    int inputY = 55;
    int inputH = (height - 200) / 2;
    int outputY = inputY + inputH + 20;
    int outputH = inputH;
    int btnY = height - 70;

    MoveWindow(hRadioT2M, margin + 60, radioY, 145, 26, TRUE);
    MoveWindow(hRadioM2T, margin + 215, radioY, 145, 26, TRUE);
    MoveWindow(hInput, margin, inputY, width - 2*margin, inputH, TRUE);
    MoveWindow(hOutput, margin, outputY, width - 2*margin, outputH, TRUE);
    MoveWindow(hBtnConvert, margin, btnY, 130, 38, TRUE);
    MoveWindow(hBtnClearInput, margin + 145, btnY, 130, 38, TRUE);
    MoveWindow(hBtnClearOutput, margin + 290, btnY, 130, 38, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            INITCOMMONCONTROLSEX icex = {sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES};
            InitCommonControlsEx(&icex);

            hFontLabel = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Segoe UI");
            hFontEdit = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas");

            CreateWindow("STATIC", "Mode:", WS_VISIBLE | WS_CHILD, 20, 15, 50, 22, hwnd, NULL, NULL, NULL);

            hRadioT2M = CreateWindowW(L"BUTTON", L"Text → Morse", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 80, 13, 145, 26, hwnd, (HMENU)ID_RADIO_T2M, NULL, NULL);
            hRadioM2T = CreateWindowW(L"BUTTON", L"Morse → Text", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 235, 13, 145, 26, hwnd, (HMENU)ID_RADIO_M2T, NULL, NULL);
            SendMessage(hRadioT2M, BM_SETCHECK, BST_CHECKED, 0);

            CreateWindow("STATIC", "Input:", WS_VISIBLE | WS_CHILD, 20, 50, 60, 20, hwnd, NULL, NULL, NULL);
            hInput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN, 20, 70, 560, 160, hwnd, (HMENU)ID_INPUT_EDIT, NULL, NULL);
            SendMessage(hInput, WM_SETFONT, (WPARAM)hFontEdit, TRUE);

            CreateWindow("STATIC", "Output:", WS_VISIBLE | WS_CHILD, 20, 240, 60, 20, hwnd, NULL, NULL, NULL);
            hOutput = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY, 20, 260, 560, 160, hwnd, (HMENU)ID_OUTPUT_EDIT, NULL, NULL);
            SendMessage(hOutput, WM_SETFONT, (WPARAM)hFontEdit, TRUE);

            hBtnConvert = CreateWindow("BUTTON", "Convert", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 435, 130, 38, hwnd, (HMENU)ID_BTN_CONVERT, NULL, NULL);
            hBtnClearInput = CreateWindow("BUTTON", "Clear Input", WS_VISIBLE | WS_CHILD, 165, 435, 130, 38, hwnd, (HMENU)ID_BTN_CLEAR_INPUT, NULL, NULL);
            hBtnClearOutput = CreateWindow("BUTTON", "Clear Output", WS_VISIBLE | WS_CHILD, 310, 435, 130, 38, hwnd, (HMENU)ID_BTN_CLEAR_OUTPUT, NULL, NULL);

            CreateWindow("STATIC", "In Morse mode: only . - space / allowed.", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 485, 560, 25, hwnd, NULL, NULL, NULL);

            // Initial layout
            RECT rc;
            GetClientRect(hwnd, &rc);
            LayoutControls(hwnd, rc.right, rc.bottom);
            return 0;
        }

        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            LayoutControls(hwnd, width, height);
            return 0;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            if (wmId == ID_BTN_CONVERT) {
                // ... same convert logic with FilterMorseInput ...
            } else if (wmId == ID_BTN_CLEAR_INPUT) {
                SetWindowText(hInput, "");
            } else if (wmId == ID_BTN_CLEAR_OUTPUT) {
                SetWindowText(hOutput, "");
            }
            return 0;
        }

        case WM_DESTROY: {
            DeleteObject(hFontLabel);
            DeleteObject(hFontEdit);
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    InitMorseMaps();

    const wchar_t* CLASS_NAME = L"MorseTranslatorGUI";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"Morse Translator",
        WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 620, 560, NULL, NULL, hInstance, NULL);

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
