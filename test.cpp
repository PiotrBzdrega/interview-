#include <iostream>
#include <stdio.h>
#include <vector>

uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length);

int main()
{

/* I used uintx_t types to be sure that this variable has actually x amount of bits */
    uint32_t res = GetBitsFromUint32(0xABCDEF12, 4, 12);
    std::vector<int> a={1,2,3};
    std::cout<<&a[0]<<"\n";
    std::cout<<&a[1]<<"\n";
    std::cout<<&a[2]<<"\n";
    printf("%08x ",res);


    
    return 0;
}



uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length)
{
    //uint32_t =
    return inputValue>>bitOffset;
}