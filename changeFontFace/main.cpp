#include <Windows.h>
#include <kthook/kthook.hpp>
#include "samp.hpp"

using CTimer__UpdateSignature = void(__cdecl*)();
kthook::kthook_simple<CTimer__UpdateSignature> CTimerHook{};

void CTimer__Update(const decltype(CTimerHook)& hook) {
    static bool init{};
    if (!init && SAMP::IsSAMPInitialized()) {
        SAMP::CInput__AddCommand("fontface", [](const char* szFontFace) {
            if (strlen(szFontFace)) {
                if (SAMP::refConfig())
                    SAMP::CConfig__WriteStringValue("fontface", szFontFace, 0);
                if (SAMP::refFonts())
                    SAMP::CFonts__Reset();

                if (SAMP::refChat()) {
                    SAMP::CChat__OnResetDevice();
                    SAMP::CChat__UpdateScrollbar();
                }

                if (SAMP::refDeathWindow())
                    SAMP::CDeathWindow__ResetFonts();
                if (SAMP::refScoreboardDialog())
                    SAMP::ResetHueta(SAMP::refScoreboardDialog());
                if (SAMP::refGameUiDialog())
                    SAMP::ResetHueta(SAMP::refGameUiDialog());
                if (SAMP::refClassSelectionDialog())
                    SAMP::ResetHueta(SAMP::refClassSelectionDialog());
                if (SAMP::refDxutDialog())
                    SAMP::ResetHueta(SAMP::refDxutDialog());
                if (SAMP::refHueta())
                    SAMP::ResetHueta(SAMP::refHueta());
                if (SAMP::refHueta1())
                    SAMP::ResetHueta(SAMP::refHueta1());
            }
            else {
                SAMP::CChat__AddDebugFormatted("You have not entered a font name!");
            }
            
        });
        init = { true };
    }

    hook.get_trampoline()();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CTimerHook.set_dest(0x561B10);
        CTimerHook.set_cb(&CTimer__Update);
        CTimerHook.install();
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}