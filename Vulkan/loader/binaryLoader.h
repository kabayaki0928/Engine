#pragma once

#include <cstdio>
#include <tuple>
#include <memory>
#include <string>
#include <fstream>

namespace BinaryLoader
{
	using Data = std::pair<std::unique_ptr<unsigned char[]>, size_t>;

	auto load(const std::wstring& path)
	{
		FILE* fp;
		if (_wfopen_s(&fp, path.c_str(), L"rb") != 0) throw std::runtime_error("File not found");

		fseek(fp, 0, SEEK_END);
		auto size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		auto buf = std::make_unique<unsigned char[]>(size);
		fread(buf.get(), sizeof(unsigned char), size, fp);
		fclose(fp);
		return Data(std::move(buf), size);
	}

    static std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }
}