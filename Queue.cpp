





// chat GPT


#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <vector>
#include <functional>
using namespace std;



struct myPacket{
    public:
        string original;
        string changed;
        string answer;

        myPacket(){}
        myPacket (string s): original(s), changed(s),answer(""){}

        void printMyPacket(){
            cout<<"original: "<<this->original<<endl;
            cout<<"changed: "<<this->changed<<endl;
            cout<<"answer: "<<this->answer<<endl;
            cout<<endl;
        }
};


template <typename T>
class SafeQueue{
    public:
        void push(myPacket item) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(item);
            // cout<<"added an item to the queue"<<endl;
            
        }

        myPacket pop() {
            std::lock_guard<std::mutex> lock(m_mutex);
            myPacket item = m_queue.front();
            m_queue.pop();
            // cout<<"took an item from the queue"<<endl;
            // cout<<item.original<<endl;
            return item;
        }

        bool IsEmpty(){
           if (m_queue.size()>0){
            return false;
           }
           else{
            return true;
           }
        }

    private:
        std::queue<myPacket> m_queue;
        std::mutex m_mutex;
};



// std::function<void(myPacket)> myfunc): myFunc(myfunc) inside

template <typename T>
class ActiveObject{
    public:
        SafeQueue<myPacket> sq{};
        std::thread m_thread;
        std::atomic<bool> m_stop{false};
        std::function <void (myPacket)> myFunc;



        ActiveObject(std::function<void(myPacket)> myfunc): myFunc(myfunc){
            m_thread = std::thread([this]() {
                while (!m_stop) {
                    myPacket task;
                    while(!sq.IsEmpty()){
                        task=sq.pop();
                        process(task);
                    }
                }
            });
        }  

        ~ActiveObject() {
            m_stop = true;
            m_thread.join(); 
        }

        void push(myPacket task) {
            sq.push(task);
        }

        void process(myPacket task) {
            // processing code goes here
            // this->myFunc(task);
        }  

        void earlystop() {
            ~ActiveObject();
        }



};


/*
// template <typename T>

// class ActiveObject{
//     public:
//         // ActiveObject(void (*processFunc)(myPacket)) : m_processFunc(processFunc) {
//             ActiveObject(std::function<void(myPacket)> myfunc) : myFunc(myfunc){
//             // this->myFunc=myfunc;
//             m_thread = std::thread([this]() {
//                 while (!m_stop) {
//                     myPacket task;
//                     if(!m_queue.IsEmpty()){
//                         task=m_queue.pop();
//                         process(task);
//                     }
//                 }
//             });
//         }

//         ~ActiveObject() {
//             m_stop = true;
//             m_thread.join(); 
//         }

//         void push(myPacket task) {
//             m_queue.push(task);
//         }

//         void process(myPacket task) {
//             // processing code goes here
//             // this->m_processFunc(task);
//         }


//     private:
//         SafeQueue<myPacket> m_queue{};
//         std::thread m_thread;
//         std::atomic<bool> m_stop{false};
//         // void (*m_processFunc)(myPacket);
//         std::function <void (myPacket)> myFunc;

// };
*/
template <typename T>
class Pipeline{
    public:
        ActiveObject<SafeQueue<myPacket>> stage1;
        ActiveObject<SafeQueue<myPacket>> stage2;
        ActiveObject<SafeQueue<myPacket>> stage3;
        ActiveObject<SafeQueue<myPacket>> stage4;


    Pipeline(ActiveObject<SafeQueue<myPacket>> a, 
             ActiveObject<SafeQueue<myPacket>> b,
             ActiveObject<SafeQueue<myPacket>> c, 
             ActiveObject<SafeQueue<myPacket>> d) stage1(a), stage2(b), stage3(c), stage4(d){}

    


        



};





// template <typename T>
// class Pipeline{
//     public:
//         Pipeline(std::vector<ActiveObject<myPacket>*> stages) : m_stages(stages) {}

//         void push(myPacket data) {
//             m_stages[0]->push(data);
//         }

//         void addStage(ActiveObject<myPacket>* stage) {
//             m_stages.push_back(stage);
//         }

//     private:
//         std::vector<ActiveObject<myPacket>*> m_stages;
// };






void* func_stage1(myPacket &p){
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
    return NULL;
    
}

void* func_stage2(myPacket &p){
    // change all non letters to ' '
    // and all letters to uppercase
    for( int i=0; i< p.changed.length(); i++){
        if(isalpha(p.changed[i])){
            p.changed[i]=toupper(p.changed[i]);
        }
        else{
            p.changed[i]=' ';
        }
    }
    return NULL;
    
}

void* func_stage3(myPacket &p){
    // check if palindrome
    int length= p.changed.length() ;
    int flag=0;
    for(int i=0;i < length/2 +1;i++){
        if(p.changed[i] != p.changed[length-i-1]){
            flag = 1;
            break;
        }
    }
    if (flag==0){
        p.answer="YES";
    }
    else{
        p.answer="NO";
    }
    return NULL;
    
}

void* func_stage4(myPacket &p){
    // print origina and answer
    cout<<"original:"<<p.original<<endl;
    cout<<"palindrome:"<<p.answer<<endl;
  return NULL;
}




// auto lambdaProcess1 = [](myPacket &p){
//     // processing code goes here
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
   
// };



