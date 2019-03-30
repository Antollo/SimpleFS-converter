#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include <fstream>
#include <streambuf>
#include "SuperBlock.h"

class DataBlock : public Block
{
public:
    DataBlock(std::filesystem::path p)
    {
        blocks.push_back(this);
        std::ifstream file(p);
        contents = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        size = contents.size();
        SuperBlock::offset += size;
    }
    operator std::string() override
    {
        if (Block::debug)
            return contents + "\n";
        return contents;
    }
    friend class INodeBlock;
private:
    std::string contents;
    std::size_t size;
};


#endif /* !DATABLOCK_H_ */
