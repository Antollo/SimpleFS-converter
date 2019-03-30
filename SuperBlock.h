#ifndef SUPERBLOCK_H_
#define SUPERBLOCK_H_

#include <limits>
#include <filesystem>
#include <map>
#include "Block.h"

class SuperBlock : public Block
{
public:
    SuperBlock()
    {
        blocks.push_back(this);
        offset += size;
    }
    operator std::string() override
    {
        if (Block::debug)
            return to_string(magic) + to_string(start) +
            to_string(offset) + to_string(iNodeCounter) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max())
            + "\n";
        return to_string(magic) + to_string(start) +
            to_string(offset) + to_string(iNodeCounter) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max()) +
            to_string(std::numeric_limits<std::uint32_t>::max());
    }
    friend class INodeBlock;
    friend class DirectoryBlock;
    friend class DataBlock;
private:
    static inline std::int32_t magic = 0xAD1FC;
    static inline std::int32_t start = 0;
    static inline std::int32_t offset = 0;
    static inline std::int32_t iNodeCounter = 0;
    
    static constexpr std::size_t size = 8 * sizeof(std::int32_t);

    static inline std::map<std::string, std::int32_t> canonicalPathToINode;
};

#endif /* !SUPERBLOCK_H_ */
