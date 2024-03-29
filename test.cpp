#include "test.h"

// TASK4, Task5
class Tree
{
private:
    std::string name;
    Tree *parent;
    std::vector<Tree *> branch;
    std::vector<Tree *> &GetBranches() { return this->branch; }
    Tree *&GetParent() { return this->parent; }

public:
    Tree(std::string name)
    {
        this->name = name;
        this->parent = nullptr;
    }
    ~Tree()
    {
        // root or detached branch -> delete branches
        while (!this->GetBranches().empty())
        {
            this->Del(0);
        }

        if (parent != nullptr)
        {
            for (size_t i = 0; i < parent->GetBranches().size(); i++)
            {
                if (parent->GetBranches()[i] == this)
                {
                    parent->GetBranches().erase(parent->GetBranches().begin() + i);
                    this->parent = nullptr;
                    break;
                }
            }
        }
    }

    std::string GetName()
    {
        return this->name;
    }

    std::string GetIndex(Tree *par, Tree *child)
    {
        std::string res = "";
        if (par != nullptr)
        {
            int i = 1;
            for (Tree *pa : par->GetBranches())
            {
                if (pa == child)
                {
                    res += GetIndex(par->GetParent(), par) + std::to_string(i) + ".";
                    return res;
                }
                i++;
            }
        }
        return res;
    }

    Tree *AddSub(std::string name)
    {
        Tree *NewBranch = new Tree(name);
        NewBranch->parent = this;
        branch.push_back(NewBranch);
        return NewBranch;
    }

    void print(int indent, std::ostream &os = std::cout)
    {
        print(indent, false, os);
    }

    void print(int indent, bool numbers, std::ostream &os = std::cout)
    {
        // print tabulator indent times + name of current branch
        os << std::string(indent, '\t');
        if (numbers && this->GetParent() != nullptr)
        {
            os << (this->GetIndex(this->GetParent(), this)) << " ";
        }
        os << this->GetName() << "\n";

        // loop through all subbranches
        for (Tree *i : this->GetBranches())
        {
            if (i != nullptr)
            {
                i->print(indent + 1, numbers, os);
            }
        }
    }

    uint32_t GetSubCount()
    {
        return this->branch.size();
    }

    uint32_t GetAllSubCount()
    {
        // all subbranches
        int subs = 0;
        // loop through all subbranches
        for (Tree *i : this->GetBranches())
        {
            if (i != nullptr)
            {
                subs++;
                subs += i->GetAllSubCount();
            }
        }
        return subs;
    }

    void Del(int child)
    {

        if (child < this->GetBranches().size())
        {
            // child has memory allocation
            if (this->GetBranches()[child] != nullptr)
            {
                // delete all branches of requested child
                while (this->GetBranches()[child]->GetBranches().empty() == false)
                {
                    this->GetBranches()[child]->Del(this->GetBranches()[child]->GetBranches().size() - 1); // first element is deleted till vector becomes empty (after deletion, branch size is reduced)
                }
                // free memory
                delete (this->GetBranches()[child]);
            }
        }
    }
};

// TASK1
uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length)
{
    // shift right + mask(2^Length)-1
    uint32_t res = (inputValue >> bitOffset) & (1 << Length) - 1;
    return res;
}

// TASK2
uint32_t GetBitsFromUint32(std::string inputValue, uint8_t bitOffset, uint8_t Length)
{
    return GetBitsFromUint32(HexStringToInt(inputValue), bitOffset, Length);
}

// auxiliary function for TASK2 and TASK3
uint32_t HexStringToInt(std::string str)
{
    uint32_t res = 0;

    // loop from last to 2nd element ([0,1]=0x prefix)
    for (size_t i = str.size() - 1; i > 1; i--)
    {
        // convert current element
        uint8_t t = CharToInt(str[i]);

        // iterator to track subsequent octet
        int k = (str.size() - i - 1);

        // add following octet to result
        res += t << (4 * k);
    }

    return res;
}

// auxiliary function for TASK2 and TASK3
uint8_t CharToInt(const char c)
{
    // char to int using ASCII table
    return (c > '9') ? c - (c > 'F' ? 'a' : 'A') + 10 : c - '0';
}

// TASK3
std::vector<bool> GetBitsVector(uint32_t inputValue)
{
    std::vector<bool> res;
    for (size_t i = 0; i < sizeof(uint32_t) * 8; i++)
    { // check each bit, start from LSB
        (inputValue & (0x1 << i)) ? res.push_back(true) : res.push_back(false);
    }
    return res;
}

// TASK3
std::vector<bool> GetBitsVector(std::string inputValue)
{
    return GetBitsVector(HexStringToInt(inputValue));
}

// TASK6
void PrintVectorRevers(std::vector<char> elements, std::ostream &os = std::cout)
{
    if (elements.size() > 0)
    {
        os << elements.back();
        if (elements.size() > 1)
            os << ",";

        elements.pop_back();
        return PrintVectorRevers(elements, os);
    }
}

// TASK 7
BitStream::BitStream(/* args */)
{
    Stream = new uint8_t[MAX_LENGTH]();
    bit = 0;
    byte = 0;
}

BitStream::~BitStream()
{
    delete[] Stream;
}

uint8_t *BitStream::GetStream()
{
    return this->Stream;
}

uint32_t BitStream::Add(uint32_t bitLength, void *dataAddr)
{
    // 8bites in 1byte
    uint8_t *data = static_cast<uint8_t *>(dataAddr);

    for (uint32_t i = 0; i < bitLength; i++)
    {
        uint8_t bytes = i / 8;
        uint8_t bits = i % 8;

        // Stream[this->byte] += ((Mask[bits] & (data[bytes])) << this->bit);

        uint8_t dataBit = Mask[bits] & (data[bytes]);
        bool shift = dataBit > 0;
        Stream[this->byte] += (shift << this->bit);
        this->MoveBitForward();
    }
    return this->GetBitLength();
}

uint32_t BitStream::Get(uint32_t bitLength, void *dataAddr)
{ // stream collected enough bits to response for request
    if (bitLength <= this->GetBitLength() && bitLength > 0 && dataAddr != nullptr)
    {
        uint8_t *data = static_cast<uint8_t *>(dataAddr);
        bitLength--; // bit "pointer" is set up one bit behind

        for (uint32_t i = bitLength; i != -1 && this->GetBitLength() > 0; i--)
        {
            this->MoveBitBackward();
            uint8_t bytes = i / 8; // get amount of bytes
            uint8_t bits = i % 8;  // get amount of bits

            if ((data[bytes] & Mask[bits]) != (Mask[this->bit] & (this->Stream[this->byte]))) // data XOR Stream
                data[bytes] ^= (1 << bits);                                                   // toggle bit by XOR
        }
    }

    return this->GetBitLength();
}

uint32_t BitStream::GetBitLength()
{
    return (this->byte) * 8 + (this->bit);
}

uint32_t BitStream::GetData(void *addr, uint32_t maxBitLength)
{
    int j = 0; // current bit in stream

    // stream is non zero and dedicated memory for external addr is non zero
    if (maxBitLength > 0 && this->GetBitLength() > 0 && addr != nullptr)
    {
        uint32_t streamLength = this->GetBitLength(); // move bit "pointer" backward

        uint8_t *data = static_cast<uint8_t *>(addr); // pointer casting
        // int i=maxBitLength-1; //bit "pointer" is set up one bit behind

        for (int i = 0; i < (maxBitLength - 1) && j < streamLength; i++, j++)
        {
            uint8_t exByte = i / 8;  // external byte "pointer"
            uint8_t exBit = i % 8;   // external Bit "pointer"
            uint8_t strByte = j / 8; // stream byte "pointer"
            uint8_t strBit = j % 8;  // stream Bit "pointer"

            if ((data[exByte] & Mask[exBit]) != (Mask[strBit] & (this->Stream[strByte]))) // data XOR Stream
                data[exByte] ^= (1 << exBit);                                             // toggle bit by XOR
        }
    }

    return j;
}

void BitStream::ResetData()
{
    this->bit = 0;
    this->byte = 0;
    for (size_t i = 0; i < MAX_LENGTH; i++)
    {
        Stream[i] = 0;
    }
}

void BitStream::MoveBitForward()
{
    // move bit "pointer" forward
    this->bit++;

    // if there is currently more bits than 8 -> increase byte "pointer"
    if (this->bit > 7)
    {
        this->bit = 0;
        this->byte++;
    }
}

void BitStream::MoveBitBackward()
{
    if (this->bit > 0 || this->byte > 0)
    {
        if (this->bit > 0)
        {
            // move bit "pointer" backward
            this->bit--;
        }
        else
        {
            // move byte "pointer" backward
            this->byte--;
            this->bit = 7;
        }
    }
}

/******************************   TESTS   ************************/

// #define CATCH_CONFIG_MAIN
// ////#define CATCH_CONFIG_RUNNER (user's main)

// #include "catch.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("TASK1")
{
    REQUIRE(GetBitsFromUint32(0xABCDEF12, 4, 12) == 0x00000ef1);
}

TEST_CASE("TASK2")
{
    REQUIRE(GetBitsFromUint32("0xaBCDEF12", 4, 12) == 0x00000ef1);
}

TEST_CASE("TASK3", "[task3]")
{
    SECTION("Bit order correctness")
    {
        std::vector<bool> a = GetBitsVector(149);
        uint32_t a_int = 149;
        for (size_t i = 0; i < a.size(); i++)
        {
            bool res = a_int & (1 << i);
            // INFO("bit: "+i);
            REQUIRE(a[i] == res);
        }
    }
    SECTION("vectors are identical")
    {
        std::vector<bool> b = GetBitsVector(0x95);
        std::vector<bool> c = GetBitsVector("0x95");
        REQUIRE(b == c);
    }
}

TEST_CASE("TASK4/5")
{
    Tree *root = new Tree("root");

    Tree *galaz1 = root->AddSub("galaz 1");
    Tree *galaz2 = root->AddSub("galaz 2");

    Tree *galaz3 = root->AddSub("galaz 3");

    Tree *galaz1_1 = galaz1->AddSub("galaz 1.1");

    Tree *galaz2_1 = galaz2->AddSub("galaz 2.1");

    Tree *galaz2_2 = galaz2->AddSub("galaz 2.2");

    Tree *galaz2_1_1 = galaz2_1->AddSub("galaz 2.1.1");
    REQUIRE((root->GetSubCount()) == 3);
    REQUIRE((galaz1->GetSubCount()) == 1);
    REQUIRE((root->GetAllSubCount()) == 7);

    std::ostringstream oss;
    root->print(0, true, oss);

    std::string directory = "root\n\t1. galaz 1\n\t\t1.1. galaz 1.1\n\t2. galaz 2\n\t\t2.1. galaz 2.1\n\t\t\t2.1.1. galaz 2.1.1\n\t\t2.2. galaz 2.2\n\t3. galaz 3\n";
    REQUIRE(oss.str() == directory);

    delete (galaz1);
    REQUIRE(root->GetAllSubCount() == 5);
    root->Del(1);
    delete (galaz2);
    delete (root);
}

TEST_CASE("TASK6")
{
    std::vector<char> a = {'a', 'b', 'c', 'd'};
    std::ostringstream oss;
    PrintVectorRevers(a, oss);
    REQUIRE(oss.str() == "d,c,b,a");
}

TEST_CASE("TASK7")
{
    BitStream Bitstr;
    SECTION("Main Case")
    {
        BitStream Bitstr;
        uint16_t Var0 = 15;
        uint16_t Var1 = 16;
        uint16_t Var2 = 17;
        uint16_t Var3 = 18;
        uint16_t Var4 = 19;
        uint16_t Var5 = 20;
        uint16_t Var6 = 21;
        REQUIRE(Bitstr.Add(4, &Var0) == 4);
        REQUIRE(Bitstr.Add(2, &Var1) == 6);
        REQUIRE(Bitstr.Add(5, &Var2) == 11);
        REQUIRE(Bitstr.Add(1, &Var3) == 12);
        REQUIRE(Bitstr.Add(8, &Var4) == 20);
        REQUIRE(Bitstr.Add(16, &Var5) == 36);
        REQUIRE(Bitstr.Add(4, &Var6) == 40);
        REQUIRE(Bitstr.GetBitLength() == 40);

        uint16_t Var10 = 0;
        uint16_t Var11 = 0;
        uint16_t Var12 = 0;
        uint16_t Var13 = 0;
        uint16_t Var14 = 0;
        uint16_t Var15 = 0; // 11 1000 1111 911
        uint16_t Var16 = 0; // 1110 0011 227

        REQUIRE(Bitstr.Get(4, &Var16) == 36);
        REQUIRE(Var16 == (Var6 & 0x0F));

        REQUIRE(Bitstr.Get(16, &Var15) == 20);
        REQUIRE(Var15 == (Var5 & 0xFFFF));

        REQUIRE(Bitstr.Get(8, &Var14) == 12);
        REQUIRE(Var14 == (Var4 & 0xFF));

        REQUIRE(Bitstr.Get(1, &Var13) == 11);
        REQUIRE(Var13 == (Var3 & 0x01));

        REQUIRE(Bitstr.Get(5, &Var12) == 6);
        REQUIRE(Var12 == (Var2 & 0x1F));

        REQUIRE(Bitstr.Get(2, &Var11) == 4);
        REQUIRE(Var11 == (Var1 & 0x03));

        REQUIRE(Bitstr.Get(4, &Var10) == 0);
        REQUIRE(Var10 == (Var0 & 0x0F));
        REQUIRE(Bitstr.GetBitLength() == 0);

        Bitstr.ResetData();

        BitStream Bitstr2;
        uint32_t databuffer = 99;
        uint16_t databuffer2 = 0;
        uint16_t databuffer3 = 0;
        REQUIRE(Bitstr2.Add(2, &databuffer) == 2);
        REQUIRE(Bitstr2.GetData(&databuffer3, sizeof(databuffer3) * 8) == 2);
        REQUIRE(databuffer3 == 3);

        REQUIRE(Bitstr2.Add(8, &databuffer) == 10);
        REQUIRE(Bitstr2.GetData(&databuffer3, sizeof(databuffer3) * 8) == 10);
        REQUIRE(databuffer3 == 399);

        REQUIRE(Bitstr2.Add(2, &databuffer) == 12);
        REQUIRE(Bitstr2.GetData(&databuffer3, sizeof(databuffer3) * 8) == 12);
        REQUIRE(databuffer3 == 3471);
    }
}
