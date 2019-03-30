#include <iostream>
#include "INodeBlock.h"

int main(int argc, char** argv)
{
    new SuperBlock();
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (std::string(argv[i]).find("-help") != std::string::npos)
                std::cout << "First argument should be path to root of new fs.\n"\
                "Binary output is stored in fs.bin\n Use --debug to get human readable output.\n"\
                "Human readable output is stored in fs.txt\n";
            else if (std::string(argv[i]).find("-debug") != std::string::npos)
                Block::debug = true;
            else new INodeBlock(argv[i]);
        }
    }
    else
        new INodeBlock(".");
    for (auto& block : Block::blocks)
        block->process();
    std::ofstream output;
    if (Block::debug)
        output.open("fs.txt", std::ofstream::trunc);
    else
        output.open("fs.bin", std::ofstream::trunc | std::ofstream::binary);
    for (auto& block : Block::blocks)
        output << (std::string) *block;
    Block::blocks.clear();
    return 0;
}