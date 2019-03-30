#ifndef INODEBLOCK_H_
#define INODEBLOCK_H_

#include "DirectoryBlock.h"
#include "DataBlock.h"

class INodeBlock : public Block
{
public:
    INodeBlock(std::filesystem::path p) : path(p)
    {
        blocks.push_back(this);
        SuperBlock::offset += size;
        SuperBlock::iNodeCounter++;
        iNode = SuperBlock::iNodeCounter;
        SuperBlock::canonicalPathToINode[std::filesystem::canonical(path).string()] = iNode;

        if (std::filesystem::is_directory(path))
        {
            for(auto& p: std::filesystem::directory_iterator(path))
                new INodeBlock(p.path());
        }
    }
    operator std::string() override
    {
        if (Block::debug)
            return to_string(iNode) + to_string(blockPtr) +
            to_string(blockOffset) + to_string(attribute) +
            to_string(fileMode) + to_string(oId) +
            to_string(gId) + to_string(links) +
            to_string(ctime) + "\n";
            
        return to_string(iNode) + to_string(blockPtr) +
            to_string(blockOffset) + to_string(attribute) +
            to_string(fileMode) + to_string(oId) +
            to_string(gId) + to_string(links) +
            to_string(ctime);
    }
    void process() override
    {
        if (processed) return;
        processed = true;
        if (std::filesystem::is_regular_file(path))
        {
            attribute = 1;
            blockPtr = SuperBlock::offset;
            DataBlock* directoryBlock = new DataBlock(path);
            blockOffset = directoryBlock->size;
        }
        else if (std::filesystem::is_directory(path))
        {
            attribute = 2;
            blockPtr = SuperBlock::offset;
            DirectoryBlock* directoryBlock = new DirectoryBlock(path);
            blockOffset = directoryBlock->size;
        }
    }
private:
    std::int32_t iNode;
    std::int32_t blockPtr;
    std::int32_t blockOffset;
    std::int32_t attribute = 0;
    std::int32_t fileMode = 0;
    std::int32_t oId = 0;
    std::int32_t gId = 0;
    std::int32_t links = 0;
    std::int32_t ctime = 0;

    std::filesystem::path path;
    bool processed = false;
    static constexpr std::size_t size = 9 * sizeof(std::int32_t);
};

#endif /* !INODEBLOCK_H_ */
