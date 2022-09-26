#include <windows.h>
#include <iostream>
#include <fstream>

auto main(unsigned __int32 argc, char* argv[]) -> __int32 // x64, c++20
{
    if (argc == 2)
    {
        std::ifstream data_file(argv[1], std::ios::binary);

        std::string data_vec((std::istreambuf_iterator<char>(data_file))
            , std::istreambuf_iterator<char>());

        for (unsigned __int64 x = 0; x < data_vec.size() - 0xf; ++x)
        {
            if (data_vec.substr(x + 0xb, 4) != "RIFF")
                continue;

            static std::string file_name;

            if (std::isprint(data_vec[x - 0x100]) != 0)
            {
                file_name.erase();

                for (unsigned __int64 base = x - 0x100; data_vec[base] != 0; ++base)
                {
                    file_name.push_back(data_vec[base]);
                }
            }
            else file_name += "Second";

            std::ofstream wav_file(file_name + ".wav", std::ios::binary);

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