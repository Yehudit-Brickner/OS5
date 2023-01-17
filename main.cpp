

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include "Queue.cpp"
// #include "ActiveObject.cpp"
using namespace std;




// void func_stage1(myPacket &p){
//     // get rid of speacial charectors
//     // anything wth ascii <=31
//     // anything with ascii >=127
//     string newChanged="";
//     for( int i=0; i< p.changed.length(); i++){
//         if (p.changed[i]>= 32 && p.changed[i]<=126){
//             newChanged+=p.changed[i];
//         }
//     }
//     p.changed=newChanged;
    
// }

// void func_stage2(myPacket &p){
//     // change all non letters to ' '
//     // and all letters to uppercase
//     for( int i=0; i< p.changed.length(); i++){
//         if(isalpha(p.changed[i])){
//             p.changed[i]=toupper(p.changed[i]);
//         }
//         else{
//             p.changed[i]=' ';
//         }
//     }
    
// }

// void func_stage3(myPacket &p){
//     // check if palindrome
//     int length= p.changed.length() ;
//     int flag=0;
//     for(int i=0;i < length/2 +1;i++){
//         if(p.changed[i] != p.changed[length-i-1]){
//             flag = 1;
//             break;
//         }
//     }
//     if (flag==0){
//         p.answer="YES";
//     }
//     else{
//         p.answer="NO";
//     }
    
// }

// void func_stage4(myPacket &p){
//     // print origina and answer
//     cout<<"original:"<<p.original<<endl;
//     cout<<"palindrome:"<<p.answer<<endl;
  
// }

auto lambdaProcess1 = [](myPacket &p){
    // processing code goes here
    // get rid of speacial charectors
    // anything wth ascii <=31
    // anything with ascii >=127
    string newChanged="";
    for( int i=0; i< p.changed.length(); i++){
        if (p.changed[i]>= 32 && p.changed[i]<=126){
            newChanged+=p.changed[i];
        }
    }
    p.changed=newChanged;
};



int main(){
   
   ActiveObject<SafeQueue<myPacket>> stage1(lambdaProcess1);    
  

    // q.push(myPacket ("this is string1"));
    // q.push(myPacket ("this is a string2"));
    // q.push(myPacket ("this is a string3"));
    // q.push(myPacket ("this is a string4"));
    // myPacket mp;
    // mp= q.pop();
    // mp.printMyPacket();
    // mp= q.pop();
    // mp.printMyPacket();
    // mp= q.pop();
    // mp.printMyPacket();
    // mp= q.pop();
    // mp.printMyPacket();


    // cout<<"\n\n"<<endl;
    // myPacket mp2("hello world! \n?? dlrow olleh");
    // mp2.printMyPacket();
    // func_stage1(mp2);
    // mp2.printMyPacket();
    // func_stage2(mp2);
    // mp2.printMyPacket();
    // func_stage3(mp2);
    // mp2.printMyPacket();
    // func_stage4(mp2);
    // mp2.printMyPacket();

    ActiveObject<SafeQueue<myPacket>> stage1(lambdaProcess1);    

    // ActiveObject<SafeQueue<myPacket>> stage2;
    // ActiveObject<SafeQueue<myPacket>> stage3;
    // ActiveObject<SafeQueue<myPacket>> stage4;
    // stage1.push(myPacket ("this is string1"));
    // stage1.push(myPacket ("this is string2"));
    // stage1.push(myPacket ("this is string3"));
    // stage1.push(myPacket ("this is string4"));
    // stage1.push(myPacket ("this is string5"));
    // stage1.push(myPacket ("this is string6"));

    string s= "this is string";
    for (int i=0; i<100;i++){
        string s1=s;
        s1+=i;
        stage1.push(myPacket(s1));
    }



    
    
    
    // ActiveObject<myPacket> stage1 (void (*func_stage1)(myPacket)), stage2(void (*func_stage2)(myPacket)), stage3(void (*func_stage3)(myPacket)), stage4(void (*func_stage4)(myPacket));

    // ActiveObject<myPacket> stage1 (lambdaProcess1);
    


    // stage1.push(myPacket("hello"));


    // std::vector<ActiveObject<SafeQueue<myPacket>>> stages = {stage1};

    
   
  
    // Pipeline<myPacket> myPipeline({&stage1, &stage2, &stage3, &stage4});
    


    // add the ActiveObjects to a vector
    // std::vector<ActiveObject<myPacket>*> stages = {};

    // create an instance of the Pipeline class
    // Pipeline<myPacket> pipeline(stages);
   

    return 0;
}