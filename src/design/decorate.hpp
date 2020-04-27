

#include <string>
#include <iostream>
#include <vector>

using namespace std;
//装饰器模式 
class Phone{
    public :	
        Phone()	{}	
        virtual ~Phone()	{}	
        virtual void showDecorate()	{}

    };
    class iPhone  : public Phone  //具体手机类
    {
        private:	string name;
        public:	
            iPhone(string _name):name(_name){}	
            ~iPhone()	{}	
            void showDecorate()	{		
                cout << name<<"的装饰"<< endl;	
            }
    };
    class NokiaPhone : public  Phone{
        private:	string name;
        public :	
            NokiaPhone(string _name):name(_name){}	
            ~NokiaPhone()	{}	
            void  showDecorate(){		
                cout << name <<"的装饰"<< endl;
            }
    }; 
    class DecoratorPhone :public Phone{
        private :	Phone* m_phone; 
        public:	DecoratorPhone(Phone *phone):m_phone(phone)	{

        }	
    virtual void showDecorate()	{	m_phone->showDecorate();}
    };

    class DecoratePhoneA : public DecoratorPhone {
        public:
            DecoratePhoneA(Phone* ph)	:DecoratorPhone(ph)	{}	
        void showDecorate()	{		
            DecoratorPhone::showDecorate();		AddDecorate();	
        }
        private:	void AddDecorate(){		cout <<"增加挂件" << endl;	}
    };
    class DecoratePhoneB : public DecoratorPhone{
        public:	DecoratePhoneB(Phone* ph):DecoratorPhone(ph){}	
        void showDecorate()	{DecoratorPhone::showDecorate();	AddDecorate();	}
        private:	void  AddDecorate()	{		cout << "屏幕贴膜"<< endl;	}
    };