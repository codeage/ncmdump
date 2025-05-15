#include "libncmdump.h"
#include <filesystem>
#include <Windows.h>

namespace fs = std::filesystem;

extern "C" {
	API NeteaseCrypt* CreateNeteaseCrypt() {
		return new NeteaseCrypt();
	}

	API int Open(NeteaseCrypt* neteaseCrypt, const char* path) {
		try
		{
			fs::path fPath = fs::u8path(path);
			neteaseCrypt->Open(fPath.u8string());
		}
		catch (const std::exception& e)
		{
			neteaseCrypt->errorMessage(e.what());
			return 1;
		}
		return 0;
	}

	API int Dump(NeteaseCrypt* neteaseCrypt, const char* outputPath) {
		try
		{
			neteaseCrypt->Dump(outputPath);
		}
		catch (const std::exception& e)
		{
			neteaseCrypt->errorMessage(e.what());
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
			neteaseCrypt->errorMessage(e.what());
		}
	}

	API void DestroyNeteaseCrypt(NeteaseCrypt* neteaseCrypt) {
		delete neteaseCrypt;
	}

	API void GetDumpFilePath(NeteaseCrypt* neteaseCrypt, char* buffer, int bufferSize) {
		if (!buffer || bufferSize <= 0)
			return;

		try
		{
			std::strncpy(buffer, neteaseCrypt->dumpFilepath().u8string().c_str(), bufferSize - 1);
			buffer[bufferSize - 1] = '\0';
		}
		catch (const std::exception& e)
		{
			neteaseCrypt->errorMessage(e.what());
		}
	}

	API void GetErrorMessage(NeteaseCrypt* neteaseCrypt, char* buffer, int bufferSize) {
		if (!buffer || bufferSize <= 0)
			return;

		try
		{
			std::strncpy(buffer, neteaseCrypt->errorMessage().c_str(), bufferSize - 1);
			buffer[bufferSize - 1] = '\0';
		}
		catch (const std::exception&)
		{
		}
	}
}