
#include <iostream>
#include <vector>
#include <string>
uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length); //TASK1
uint32_t GetBitsFromUint32(std::string inputValue, uint8_t bitOffset, uint8_t Length); //TASK2
std::vector<bool> GetBitsVector(uint32_t inputValue); //TASK3
std::vector<bool> GetBitsVector(std::string inputValue); //TASK3

void PrintVectorRevers(std::vector<char> elements,std::ostream& os);//TASK6
uint32_t HexStringToInt (std::string str); //auxiliary function for TASK2 and TASK3
uint8_t CharToInt(const char c); //auxiliary function for TASK2 and TASK3

static uint8_t Mask[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
class BitStream //TASK7
{   
    const uint32_t MAX_LENGTH=100;
private:
    
    uint32_t byte;
    uint32_t bit;
    uint8_t* Stream;
public:

    BitStream();
    ~BitStream();
    uint8_t* GetStream(); //return Stream member
    uint32_t Add(uint32_t bitLength, void * dataAddr);//returns actual position after adding data to stream
    uint32_t Get(uint32_t bitLength, void* dataAddr); // returns position after reading bits and storing unter dataAddr
    uint32_t GetBitLength(); // returns amount of added bits 
    uint32_t GetData(void * addr, uint32_t maxBitLength); // allows to get full stream, returns  number of bits
    void ResetData(); // clears internal buffer
    void MoveBitForward(); //update current bit position in BitStream
    void MoveBitBackward(); //update current bit position in BitStream

};


