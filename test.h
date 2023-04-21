#include <iostream>
#include <vector>
#include <string>
uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length); //TASK1
uint32_t GetBitsFromUint32(std::string inputValue, uint8_t bitOffset, uint8_t Length); //TASK2
std::vector<bool> GetBitsVector(uint32_t inputValue); //TASK3
std::vector<bool> GetBitsVector(std::string inputValue); //TASK3

void PrintVectorRevers(std::vector<char> elements);//TASK6
uint32_t HexStringToInt (std::string str); //auxiliary function for TASK2 and TASK3
uint8_t CharToInt(const char c); //auxiliary function for TASK2 and TASK3
