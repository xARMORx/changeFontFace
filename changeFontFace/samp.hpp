#ifndef _SAMP_LIBRARY_HPP_
#define _SAMP_LIBRARY_HPP_

#include <Windows.h>

using CMDPROC = void(__cdecl*)(const char*);

namespace SAMP
{
	enum class sampVersion : int
	{
		unknown = 0,
		notLoaded = -1,
		R1 = 1,
		R3 = 2,
		R5 = 3,
	}; // enum class sampVersion
	unsigned long GetSAMPHandle() {
		static unsigned long samp{ 0 };
		if (!samp) {
			samp = reinterpret_cast<unsigned long>(GetModuleHandleA("samp"));
			if (!samp || samp == -1 || reinterpret_cast<HANDLE>(samp) == INVALID_HANDLE_VALUE) {
				samp = 0;
			}
		}
		return samp;
	}
	enum sampVersion GetSAMPVersion() {
		static sampVersion sampVersion = sampVersion::unknown;
		if (sampVersion != sampVersion::unknown) {
			return sampVersion;
		}
		unsigned long samp = GetSAMPHandle();
		if (!samp) {
			sampVersion = sampVersion::notLoaded;
		}
		else {
			unsigned long EntryPoint = reinterpret_cast<IMAGE_NT_HEADERS*>(samp + reinterpret_cast<IMAGE_DOS_HEADER*>(samp)->e_lfanew)->OptionalHeader.AddressOfEntryPoint;
			switch (EntryPoint) {
			case (0x31DF13): {
				sampVersion = sampVersion::R1;
				break;
			}
			case (0xCC4D0): {
				sampVersion = sampVersion::R3;
				break;
			}
			case (0xCBC90): {
				sampVersion = sampVersion::R5;
				break;
			}
			default: {
				sampVersion = sampVersion::unknown;
				break;
			}
			}
		}
		return sampVersion;
	}

	bool IsSAMPInitialized() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0F8) != nullptr;
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8DC) != nullptr;
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB94) != nullptr;
		return false;
	}

	void* refConfig() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0E0);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8C4);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB7C);
		return nullptr;
	}

	int CConfig__WriteStringValue(const char* szString, const char* szValue, int bReadOnly) {
		if (GetSAMPVersion() == sampVersion::R1)
			return reinterpret_cast<int(__thiscall*)(void*, const char*, const char*, int)>(GetSAMPHandle() + 0x62520)(refConfig(), szString, szValue, bReadOnly);
		else if (GetSAMPVersion() == sampVersion::R3)
			return reinterpret_cast<int(__thiscall*)(void*, const char*, const char*, int)>(GetSAMPHandle() + 0x65970)(refConfig(), szString, szValue, bReadOnly);
		else if (GetSAMPVersion() == sampVersion::R5)
			return reinterpret_cast<int(__thiscall*)(void*, const char*, const char*, int)>(GetSAMPHandle() + 0x660E0)(refConfig(), szString, szValue, bReadOnly);
		return 0;
	}

	void* refFonts() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0FC);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8E4);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB9C);
		return nullptr;
	}

	void CFonts__Reset() {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x67200)(refFonts());
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x6B170)(refFonts());
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x6B8E0)(refFonts());
	}

	void* refChat() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0E4);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8C8);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB80);
		return nullptr;
	}

	void CChat__OnResetDevice() {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x64600)(refChat());
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x67A50)(refChat());
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x681D0)(refChat());
	}

	void CChat__UpdateScrollbar() {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x63630)(refChat());
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x66A80)(refChat());
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x67200)(refChat());
	}

	template <typename... T>
	void CChat__AddDebugFormatted(const char* szText, T... arguments) {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__cdecl*)(void*, const char*, T...)>(GetSAMPHandle() + 0x64520)(refChat(), szText, arguments...);
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__cdecl*)(void*, const char*, T...)>(GetSAMPHandle() + 0x67970)(refChat(), szText, arguments...);
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__cdecl*)(void*, const char*, T...)>(GetSAMPHandle() + 0x680F0)(refChat(), szText, arguments...);
	}

	void* refDeathWindow() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0EC);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8D0);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB88);
		return nullptr;
	}

	void CDeathWindow__ResetFonts() {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x664B0)(refDeathWindow());
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x699E0)(refDeathWindow());
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x6A150)(refDeathWindow());
	}

	void* refInputBox() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A0E8);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E8CC);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EB84);
		return nullptr;
	}

	void CInput__AddCommand(const char* szCommand, CMDPROC handler) {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*, const char*, CMDPROC)>(GetSAMPHandle() + 0x65AD0)(refInputBox(), szCommand, handler);
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*, const char*, CMDPROC)>(GetSAMPHandle() + 0x69000)(refInputBox(), szCommand, handler);
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*, const char*, CMDPROC)>(GetSAMPHandle() + 0x69770)(refInputBox(), szCommand, handler);
	}

	void* refScoreboardDialog() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A188);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E970);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC28);
		return nullptr;
	}

	void* refGameUiDialog() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A184);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E96C);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC24);
		return nullptr;
	}

	void* refClassSelectionDialog() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A18C);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E974);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC2C);
		return nullptr;
	}

	void* refDxutDialog() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A190);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E978);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC30);
		return nullptr;
	}

	void* refHueta() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A190);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E97C);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC34);
		return nullptr;
	}

	void* refHueta1() {
		if (GetSAMPVersion() == sampVersion::R1)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x21A194);
		else if (GetSAMPVersion() == sampVersion::R3)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26E980);
		else if (GetSAMPVersion() == sampVersion::R5)
			return *reinterpret_cast<void**>(GetSAMPHandle() + 0x26EC38);
		return nullptr;
	}

	void ResetHueta(void* pointer) {
		if (GetSAMPVersion() == sampVersion::R1)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x89110)(pointer);
		else if (GetSAMPVersion() == sampVersion::R3)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x8D030)(pointer);
		else if (GetSAMPVersion() == sampVersion::R5)
			reinterpret_cast<void(__thiscall*)(void*)>(GetSAMPHandle() + 0x8D740)(pointer);
	}

}; // namespace SAMP

#endif // !_SAMP_LIBRARY_HPP_