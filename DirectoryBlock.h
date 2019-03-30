#ifndef DIRECTORYBLOCK_H_
#define DIRECTORYBLOCK_H_

#include "SuperBlock.h"

class DirectoryBlock : public Block
{
public:
    DirectoryBlock(std::filesystem::path p)
    {
        blocks.push_back(this);
        if (SuperBlock::canonicalPathToINode.count(std::filesystem::canonical(p / "..").string()))
            contents.emplace_back(SuperBlock::canonicalPathToINode[std::filesystem::canonical(p / "..").string()], "..");
        contents.emplace_back(SuperBlock::canonicalPathToINode[std::filesystem::canonical(p).string()], ".");
        for (auto& p: std::filesystem::directory_iterator(p))
            contents.emplace_back(SuperBlock::canonicalPathToINode[std::filesystem::canonical(p.path()).string()], p.path().filename().string());
        size = contents.size() * (sizeof(std::int32_t) + 64);
        SuperBlock::offset += size;
    }
    operator std::string() override
    {
        std::string ret;
        for (const auto& p: contents)
        {
            if (Block::debug)
                ret += std::to_string(p.iNode) + " <" + p.name + ">| ";
            else
                ret += to_string(p.iNode) + p.name;
        }
        if (Block::debug)
            ret += "\n";

        return ret;
    }
    friend class INodeBlock;
private:
    class entry
    {
    public:
        entry(std::int32_t i, std::string n) : iNode(i), name(n)
        {
            if (!Block::debug)
                while (name.size() < 64)
                    name += (char)0;
        }
        std::int32_t iNode;
        std::string name;
    };
    std::list<entry> contents;
    std::size_t size;
};

#endif /* !DIRECTORYBLOCK_H_ */
