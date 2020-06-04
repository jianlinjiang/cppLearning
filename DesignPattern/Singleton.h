#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
template<typename T>
class Singleton{
    public:
        template<typename... Args>
        static T& getInstance(Args&&... args){
            std::call_once(s_flag,[&](){
                instance_.reset(new T(std::forward<Args>(args)...));    
            });
            return *instance_;
        }
        ~Singleton() = default;
        void PrintAddress() const {
            std::cout << this << std::endl;
        }
    private:
        Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
    private:
        static std::unique_ptr<T> instance_;
        static std::once_flag s_flag;   //flag，内部保存着一个state状态，默认值为0。通过原子地加载和修改state的状态，来判断是否已经
};
template<typename Test> std::unique_ptr<Test> Singleton<Test>::instance_;
template<typename T> std::once_flag Singleton<T>::s_flag;

/*  How to use 
1.先定义需要使用的类
class Test{
    public:
        Test(int a,int b,int c):a_(a),b_(b),c_(c){
            std::cout<<"three Constructor"<<std::endl;
        }
        Test(int a,int b):a_(a),b_(b),c_(0) { 
            std::cout<<"two Constructor"<<std::endl;
        }
        ~Test(){
            std::cout<<"Destructor"<<std::endl;
        }
        void PrintAddress() const {
            std::cout << this << std::endl;
        }
        Test(const Test&) = delete;
        Test& operator=(const Test&) = delete;
    private:
        int a_;
        int b_;
        int c_;
};
2.在多线程中进行使用
void print(){
    Test& s1 = Singleton<Test>::getInstance(1,2);
    s1.PrintAddress();
}
int main() {
    std::thread t(print);
    std::thread t2(print);
    t.join();
    t2.join();
    return 0;
}
*/