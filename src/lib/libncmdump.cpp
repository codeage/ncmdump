#include "libncmdump.h"
#include <filesystem>
#include <Windows.h>

namespace fs = std::filesystem;

// Thread local storage for the last error message
thread_local std::string lastErrorMessage;

extern "C" {
	API NeteaseCrypt* CreateNeteaseCrypt(const char* path) {
		try
		{
			fs::path fPath = fs::u8path(path);
			return new NeteaseCrypt(fPath.u8string());
		}
		catch (const std::exception& e)
		{
			lastErrorMessage = e.what();
			return nullptr;
		}
	}

	API int Dump(NeteaseCrypt* neteaseCrypt, const char* outputPath) {
		try
		{
			neteaseCrypt->Dump(outputPath);
		}
		catch (const std::exception& e)
		{
			lastErrorMessage = e.what();
			return 1;
		}
		return 0;
	}

	API void FixMetadata(NeteaseCrypt* neteaseCrypt) {
		try
		{
			neteaseCrypt->FixMetadata();
		}
		catch (const std::exception& e)
		{
			lastErrorMessage = e.what();
		}
	}

	API void DestroyNeteaseCrypt(NeteaseCrypt* neteaseCrypt) {
		delete neteaseCrypt;
	}

	API void GetErrorMessage(char* buffer, int bufferSize)
	{
		if (!buffer || bufferSize <= 0)
			return;

		std::strncpy(buffer, lastErrorMessage.c_str(), bufferSize - 1);
		buffer[bufferSize - 1] = '\0';
	}
}