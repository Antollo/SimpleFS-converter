#ifndef BLOCK_H_
#define BLOCK_H_

#include <cstdint>
#include <string>
#include <list>

union convertingUnion
{
    std::int32_t int32;
    char bytes[4];
};

class Block
{
public:
    virtual operator std::string() { return "ERROR"; };
    virtual void process() {};
    static inline std::list<Block*> blocks;
    static inline bool debug = false;
};

std::string to_string(std::int32_t value)
{
    if (Block::debug)
        return std::to_string(value) + "|";
    convertingUnion u;
    u.int32 = value;
    return std::string(u.bytes);
}
#endif /* !BLOCK_H_ */
