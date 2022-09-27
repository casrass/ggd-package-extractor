
#include <windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>

auto main(unsigned __int32 argc, char* argv[]) -> __int32 // x64, c++20
{
    if (argc == 2)
    {
        std::ifstream data_file(argv[1], std::ios::binary);

        std::string data_vec((std::istreambuf_iterator<char>(data_file))
            , std::istreambuf_iterator<char>());

        std::filesystem::create_directory("output");

        for (unsigned __int64 x = 0; x < data_vec.size() - 4; ++x)
        {
            if (data_vec.substr(x, 4) != "RIFF")
                continue;

            static std::string file_name, dir_name;

            if (std::isprint(data_vec[x - 0x10b]) != 0)
            {
                file_name.erase();

                for (unsigned __int64 base = x - 0x10b; data_vec[base] != 0; ++base)
                {
                    file_name.push_back(data_vec[base]);
                }

                file_name.pop_back();

                dir_name = "output\\" + file_name.substr(0, file_name.find("  "));

                std::filesystem::create_directory(dir_name);
            }
            else file_name += "Second";

            std::cout << "unpacking file @ 0x" << std::hex << x << " - " << file_name << std::endl;

            std::ofstream wav_file(dir_name + "\\" +  file_name + ".wav", std::ios::binary);

            for (; data_vec.substr(x - 0x5c, 11) != "Logic Pro X"; ++x)
            {
                wav_file << data_vec[x];
            }

            wav_file.close();
        }
    }
    else std::cout << "drag binary on to this file" << std::endl;

    return std::cin.get();
}