#pragma once

#include "aes.h"
#include "cJSON.h"

#include <iostream>
#include <fstream>

#include <filesystem>

class NeteaseMusicMetadata {

private:
	std::string mAlbum;
	std::string mArtist;
	std::string mFormat;
	std::string mName;
	int mDuration;
	int mBitrate;

private:
	cJSON* mRaw;

public:
	NeteaseMusicMetadata(cJSON*);
	~NeteaseMusicMetadata();
    const std::string& name() const { return mName; }
    const std::string& album() const { return mAlbum; }
    const std::string& artist() const { return mArtist; }
    const std::string& format() const { return mFormat; }
    const int duration() const { return mDuration; }
    const int bitrate() const { return mBitrate; }

};

class NeteaseCrypt {

private:
	static const unsigned char sCoreKey[17];
	static const unsigned char sModifyKey[17];
	static const unsigned char mPng[8];
	enum NcmFormat { MP3, FLAC };

private:
	std::string mFilepath;
	std::filesystem::path mDumpFilepath;
	NcmFormat mFormat;
	std::string mImageData;
	std::ifstream mFile;
	unsigned char mKeyBox[256]{};
	NeteaseMusicMetadata* mMetaData;
	std::string mErrorMessage;

private:
	bool isNcmFile();
	bool openFile(std::string const&);
	int read(char *s, std::streamsize n);
	void buildKeyBox(unsigned char *key, int keyLen);
	std::string mimeType(std::string& data);

public:
	const std::string& filepath() const { return mFilepath; }
	const std::filesystem::path dumpFilepath() const { return mDumpFilepath; }
	const void errorMessage(const char *message) { mErrorMessage = message; }
	const std::string& errorMessage() const { return mErrorMessage; }

public:
	NeteaseCrypt();
	~NeteaseCrypt();

public:
	void Open(std::string const&);
	void Dump(std::string const&);
	void FixMetadata();
};