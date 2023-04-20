#include "test.h"

//TASK4, Task5
class Tree{
private:
    std::string name;
    std::vector<Tree*> branch;
public:     
    Tree(std::string name) {this->name=name;}

    std::string GetName()
    {
        return this->name;
    }

    std::vector<Tree*> GetBranches()
    {
        return this->branch;
    }

    Tree* AddSub(std::string name)
    {
        Tree* NewBranch = new Tree(name);
        branch.push_back(NewBranch);
        return NewBranch;
    }

    void print(int indent)
    {   
        //print tabulator indent times + name of current branch
        std::cout << std::string(indent, '\t') << this->GetName() << "\n"; 
            
        //loop through all subbranches
        for (Tree* i : this->GetBranches())
        {   if (i!=nullptr)
            { 
                i->print(indent+1);
            }
        }
    }
    //TODO: How linux print directories
    void print(int indent,bool numbers)
    {
        //print tabulator indent times + name of current branch
        std::cout <<". "<< this-> GetName() << "\n"; 
            
        for (size_t i = 0; i < this->GetBranches().size(); i++)
        {
            if (this->GetBranches()[i]!=nullptr)
            { 
                std::cout << std::string(indent+1, '\t');
                if (numbers)
                {
                    std::cout<<i+1<<"";
                    if (indent>0)
                    {   
                        for (size_t i = 0; i < indent; i++)
                        {
                            std::cout<<".x";
                        }
                        
                        
                    }
                    
                }
                       
                this->GetBranches()[i]->print(indent+1,numbers);
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
    //  void Del(int child)
    //  {
    //     if (this->GetBranches()[child] !=nullptr )
    //     {   //Tree* i : this->GetBranches()[child]->GetBranches()
    //         for (int i=0; i<this->GetBranches().size();i++)
    //         {   
    //             if (this->GetBranches())
                
    //             if (i!=nullptr)
    //             { Del(int child)  }
    //         }         
    //         delete(this->GetBranches()[child])
    //     }
    //  }
     //void operator delete(void * p);
     //void print(int depth,bool printnmber);
};

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

    Tree* root = new Tree("root");
    // std::cout<<root<<"\n";
    // for (Tree* i :root->branch)
    // {
    //    std::cout<<i<<"\n"; 
    // }
    

    Tree* galaz1= root->AddSub("galaz 1");
    Tree* galaz2 = root->AddSub("galaz 2");

    Tree* galaz3 = root->AddSub("galaz 3");

    Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");

    Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");

    Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");

    Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.1");

    root->print(0,true);
    std::cout<<root->GetSubCount()<<"\n";
    std::cout<<galaz1->GetSubCount()<<"\n";
    std::cout<<root->GetAllSubCount()<<"\n";

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

