#include "test.h"

#if 0
#define CATCH_CONFIG_MAIN
////#define CATCH_CONFIG_RUNNER

#include "catch.hpp"


TEST_CASE("Catching proof") {
    CHECK(1 == 1);   
}

TEST_CASE("TASK1") {
REQUIRE( GetBitsFromUint32(0xABCDEF12, 4, 12) ==  0x00000ef1);   
}

TEST_CASE("TASK2") {
REQUIRE( GetBitsFromUint32("0xaBCDEF12", 4, 12) ==  0x00000ef1);   
}

TEST_CASE("TASK3","[task3]") {
    SECTION("Bit order correctness")
    {
        std::vector<bool> a = GetBitsVector(149);
        uint32_t a_int=149;
    for (size_t i = 0; i < a.size(); i++)
    {
        bool res = a_int & (1<<i);
        INFO("bit: "+i);
        CHECK( a[i] ==  res); 
    }
    }
    SECTION("vectors are identical")
    {
    std::vector<bool> b = GetBitsVector(0x95);
    std::vector<bool> c = GetBitsVector("0x95");
    REQUIRE( b ==  c);  
    } 
}

// TEST_CASE("TASK4/5") {
    // Tree* root = new Tree("root");

    // Tree* galaz1= root->AddSub("galaz 1");
    // Tree* galaz2 = root->AddSub("galaz 2");

    // Tree* galaz3 = root->AddSub("galaz 3");

    // Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");

    // Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");

    // Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");

    // Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.1");

    // root->print(0,true);

    // // root->Del(0);

    // // delete(galaz2_2);


    // std::cout<<root->GetSubCount()<<"\n";
    // std::cout<<galaz1->GetSubCount()<<"\n";
    // std::cout<<root->GetAllSubCount()<<"\n";
// }



TEST_CASE("TASK6") {
    std::vector<char> a ={'a','b','c','d'};
    std::ostringstream oss;
    PrintVectorRevers(a,oss);
    //assert(oss && oss.str() == "Hello");
    REQUIRE( oss.str() ==  "d,c,b,a");   
}

TEST_CASE("TASK7") {
    BitStream Bitstr;
    SECTION("Add")
    {
    uint32_t databuffer=99;
    REQUIRE(Bitstr.Add(2,&databuffer)==2);
    uint32_t databuffer1;
    REQUIRE(Bitstr.Add(8,&databuffer)==10);
    //REQUIRE(Bitstr.GetData(&databuffer1,sizeof(databuffer1*8))==1);

    }
    
    SECTION("Get")
    {
    uint16_t databuffer2=0;
    REQUIRE(Bitstr.Get(10,&databuffer2)==0);
    REQUIRE(databuffer2==399);
    }  
}
#endif

//TASK4, Task5
class Tree{
private:
    std::string name;
    Tree* parent;
    std::vector<Tree*> branch;
    std::vector<Tree*> &GetBranches() {return this->branch;} 
    Tree* &GetParent() {return this->parent;}  
public:     
    Tree(std::string name) {this->name=name; this->parent=nullptr;}
    ~Tree()
    {       
        std::cout << "Destructor: "<<this->GetName()<<"\n";

        if (parent != nullptr)
        {
            for (size_t i = 0; i < parent->GetBranches().size(); i++)
            {
                //this found as child in parent interface
                if (this == parent->GetBranches()[i])
                {
                    //delete this object from parent interface
                    parent->Del(i);
                }
                
                
            }
            //this object is not responsible for parrent allocation set null
            parent = nullptr;
        }
        else
        {
            //root or detached branch -> delete branches
            while (! this->GetBranches().empty())
            {
                this->Del(0);
            }  
        }
    }


    

    std::string GetName()
    {
        return this->name;
    }

    std::string GetIndex(Tree* par,Tree* child)
    {
        std::string res="";
        if (par!=nullptr)
        {   
            int i=1;
            for (Tree* pa : par->GetBranches())
            {
                if (pa==child)
                {
                    res+=GetIndex(par->GetParent(),par) + std::to_string(i) + ".";
                    return res;
                }
                i++;
            }
        }
        return res;       
    }

    Tree* AddSub(std::string name)
    {
        Tree* NewBranch = new Tree(name);
        NewBranch->parent=this;
        branch.push_back(NewBranch);
        return NewBranch;
    }

    void print(int indent)
    {   
        print(indent,false);
    }

    void print(int indent,bool numbers)
    {
        //print tabulator indent times + name of current branch
        std::cout << std::string(indent, '\t');
        if (numbers && this->GetParent() != nullptr)
        {
            std::cout<< (this->GetIndex(this->GetParent(),this))<<" ";
        }
        std::cout<< this->GetName() << "\n"; 
            
        //loop through all subbranches
        for (Tree* i : this->GetBranches())
        {   if (i!=nullptr)
            { 
                i->print(indent+1,numbers);
            }
        }
    }

     uint32_t GetSubCount()
     {
        return this->branch.size();
     }

     uint32_t GetAllSubCount()
     {
        //all subbranches
        int subs=0;
        //loop through all subbranches
        for (Tree* i : this->GetBranches())
        {   if (i!=nullptr)
            {   subs++;
                subs+=i->GetAllSubCount();
            }
        }
        return subs;
     }

     void Del(int child)
     {

        if (child<this->GetBranches().size())
        {
            //child has memory allocation
           if (this->GetBranches()[child] !=nullptr )
           {    
                //delete all branches of requested child
                while (! this->GetBranches()[child]->GetBranches().empty())
                {
                    this->GetBranches()[child]->Del(0); //first element is deleted till vector becomes empty (after deletion, branch size is reduced) 
                }
                //unlink parent from pointer
                this->GetBranches()[child]->parent=nullptr;
                //free memory
                delete (this->GetBranches()[child]);
                //remove requested child from branches
                this->GetBranches().erase(this->GetBranches().begin()+child);    
           }
        }

        
    }
};



#if 1
int main()
{
 

    std::getchar();  
    std::cout<<"adam";
 
    // std::vector<bool> a = GetBitsVector(149); //TASK3
    // for (auto i:a)
    // {
    //     std::cout<<i<<"\n";
    // }

    // std::vector<bool> g = GetBitsVector("0x95"); //TASK3
    // for (auto i:g)
    // {
    //     std::cout<<i<<"\n";
    // }

    // std::cout<<"vector are same: "<<((a==g) ? true:false)<<"\n";

    // std::cout<<"\n"<<"TASK 7"<<"\n";

    return 0;
} 
#endif



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




//TASK6
void PrintVectorRevers(std::vector<char> elements,std::ostream& os = std::cout)
{
   if (elements.size()>0)
    {
        os<< elements.back();
        if (elements.size()>1)
            os<<",";
        
        elements.pop_back();
        return PrintVectorRevers(elements,os);
    }       
}

//TASK 7
BitStream::BitStream(/* args */)
{
     Stream = new uint8_t[MAX_LENGTH]();
     bit=0;
     byte=0;
}

BitStream::~BitStream()
{ 
    delete [] Stream;

}

uint8_t* BitStream::GetStream()
{
    return this->Stream;
}

uint32_t BitStream::Add(uint32_t bitLength, void * dataAddr)
{
    //8bites in 1byte
   uint8_t* data= static_cast<uint8_t*>(dataAddr);

    for (uint32_t i = 0; i < bitLength; i++)
    {
       uint8_t bytes = i / 8;
       uint8_t bits = i % 8;
       printf("Stream vor : %02x \n",this->Stream[this->byte]);

       uint8_t dataBit = Mask[bits] & (data[bytes]);
       bool shift = dataBit>0;
       printf("bit data: %02x \n",dataBit);
       printf("current bit: %d \n",this->bit);
       printf("current byte: %d \n",this->byte);
       printf("bites: %d \n",bits);
       printf("bytes: %d \n",bytes);
       Stream[this->byte] +=(shift << this->bit );
       printf("Stream nach : %02x \n",Stream[this->byte]);
       this->MoveBitForward();
    }  
    return this->GetBitLength();
}

    uint32_t BitStream::Get(uint32_t bitLength, void* dataAddr)
    {   //stream collected enough bits to response for request 
        if (bitLength <= this->GetBitLength() && bitLength>0)
        {
            uint8_t* data= static_cast<uint8_t*>(dataAddr);
            bitLength--; //bit "pointer" is set up one bit behind

            for (uint32_t i = bitLength; i != -1 ; i--)
            {
                this->MoveBitBackward();
                uint8_t bytes = i / 8; //get amount of bytes
                uint8_t bits = i % 8; //get amount of bits
                printf("data vor : %02x \n",data[bytes]);

                uint8_t dataBit = Mask[this->bit] & (this->Stream[this->byte]);
                bool shift = dataBit>0;
                printf("bit data: %02x \n",dataBit);
                printf("current bit: %d \n",this->bit);
                printf("current byte: %d \n",this->byte);
                printf("bites: %d \n",bits);
                printf("bytes: %d \n",bytes);
                data[bytes] +=(shift << bits );
                printf("data nach : %02x \n",data[bytes]);                
            }
        }
        
         return this->GetBitLength();      
    } 

uint32_t BitStream::GetBitLength()
{
    return (this->byte) *8 + (this->bit);
}

uint32_t BitStream::GetData(void * addr, uint32_t maxBitLength)
{
    return this->Get(maxBitLength,addr);
}

void BitStream::ResetData()
{
    this->bit=0;
    this->byte=0;
    for (size_t i = 0; i < MAX_LENGTH; i++)
    {
        Stream[i]=0;
    }
}

void BitStream::MoveBitForward()
{
    //move bit "pointer" forward
    this->bit ++;

    //if there is currently more bits than 8 -> increase byte "pointer"
    if (this->bit > 7)
    {
        this->bit = 0;
        this->byte ++;
    }
}

void BitStream::MoveBitBackward()
{   
    if (this->bit > 0 || this->byte > 0)
    {
        if (this->bit > 0)
        {
            //move bit "pointer" backward
            this->bit --;
        }
        else
        {
            //move byte "pointer" backward
            this->byte --;
            this->bit = 7;           
        }
        
    }
}


