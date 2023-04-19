#include "test.h"


int main()
{

/* I used uintx_t types to be sure that this variable has actually x amount of bits */
    uint32_t res = GetBitsFromUint32(0xABCDEF12, 4, 12);//TASK1
    printf("res: %08x \n",res);
    uint32_t res1 = GetBitsFromUint32("0xaBCDEF12", 4, 12);//TASK2
    printf("res1: %08x \n",res1);
    
 
 
    std::vector<bool> a = GetBitsVector(149); //TASK3
    for (auto i:a)
    {
        std::cout<<i<<"\n";
    }

    std::vector<bool> g = GetBitsVector("0x95"); //TASK3
    for (auto i:g)
    {
        std::cout<<i<<"\n";
    }

    std::cout<<"vector are same: "<<((a==g) ? true:false)<<"\n";

    Tree* root=new Tree("root");

    std::vector<char> b ={'a','b','c','d'};
    PrintVectorRevers(b);//TASK6
    
    
    
    return 0;
} 


//TASK1
uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t Length)
{   
    // shift right + mask(2^Length)-1
    uint32_t res=(inputValue>>bitOffset)&(1<<Length)-1;
    return res;
}

//TASK2
uint32_t GetBitsFromUint32(std::string inputValue, uint8_t bitOffset, uint8_t Length)
{   
    return GetBitsFromUint32(HexStringToInt(inputValue), bitOffset, Length);
}

//auxiliary function for TASK2 and TASK3
uint32_t HexStringToInt (std::string str)
{
    uint32_t res;

    //loop from last to 2nd element ([0,1]=0x prefix)
    for (size_t i = str.size()-1; i >1 ; i--)
    {
        //convert current element
        uint8_t t=CharToInt(str[i]);

        //iterator to track subsequent octet
        int k=(str.size()-i-1);

        //add following octet to result
        res+=t<<(4*k);        
    }

    return res;
}

//auxiliary function for TASK2 and TASK3
uint8_t CharToInt(const char c)
{
    //char to int using ASCII table
    return  (c>'9') ? c -( c>'F' ? 'a' : 'A' )+10 : c-'0';
}

//TASK3
std::vector<bool> GetBitsVector(uint32_t inputValue)
{ 
    std::vector<bool> res;
    for (size_t i = 0; i < sizeof(uint32_t)*8; i++)
    {   //check each bit, start from LSB
        (inputValue &(0x1<<i)) ? res.push_back(true) : res.push_back(false);
    }
  return res;
}

//TASK3
std::vector<bool> GetBitsVector(std::string inputValue)
{
    return GetBitsVector(HexStringToInt(inputValue));
}

//TASK4
class Tree{
private:
    std::string name; 
public:    
    Tree(std::string name) {this->name=name;}
     uint32_t GetSubCount();
     uint32_t GetAllSubCount();
     void operator delete(void * p);
     void print(int depth,bool printnmber);
 
};


//TASK6
//TODO: template & better solution
void PrintVectorRevers(std::vector<char> elements)
{
   if (elements.size()>0)
    {
        std::cout<< elements.back()<<"\n";
        elements.pop_back();
        return PrintVectorRevers(elements);
    }       
}

