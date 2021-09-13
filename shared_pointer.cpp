
#include <iostream>
template <class T>
class SharedPointer
{
public:
    
    SharedPointer() : mPtr(nullptr),mRefCount(new unsigned int(0)) {}

    SharedPointer(T *obj) : mPtr(obj),mRefCount(new unsigned int(1)) {}

    SharedPointer(const SharedPointer &obj)
    {   
        mPtr = obj.mPtr;
        mRefCount = obj.mRefCount;
        if(obj.mPtr != nullptr)
        {
            (*mRefCount)++;
        }  
    }

    SharedPointer& operator=(const SharedPointer &obj)
    {
        cleaning(); //cleaning in case the variable we asign to already points to some other memory
        mPtr = obj.mPtr;
        mRefCount = obj.mRefCount;
        if(obj.mPtr != nullptr)
        {
            (*mRefCount)++;
        }
    }

    SharedPointer(SharedPointer &&dyingObj)
    {
        mPtr = dyingObj.mPtr;
        mRefCount = dyingObj.mRefCount;
        //dyingObj.mRefCount = nullptr;
        dyingObj.mPtr = nullptr;
    }

    SharedPointer& operator=(SharedPointer &&dyingObj)
    {
        cleaning(); //cleaning in case the variable we asign to already points to some other memory
        mPtr = dyingObj.mPtr;
        mRefCount = dyingObj.mRefCount;
        //dyingObj.mRefCount = nullptr;
        dyingObj.mPtr  = nullptr;
    }

    ~SharedPointer()
    {
        cleaning();
    }

    T getPtr()
    {
        return mPtr;
    }
    unsigned int getRefCount()
    {
        return *mRefCount;
    }
private:
    T *mPtr = nullptr;
    unsigned int *mRefCount = nullptr;

    void cleaning()
    {
        (*mRefCount)--;
        if (*mRefCount == 0)
		{
			if (nullptr != mPtr)
				delete mPtr;
			delete mRefCount;
		}
    }
};

int main()
{
    {SharedPointer<int> myPtr1(new int);
    std::cout<<"CountPtr: " << myPtr1.getRefCount() << std::endl;
    {
    SharedPointer<int> myPtr2(myPtr1);
    std::cout<<"CountPtr: " << myPtr1.getRefCount() << std::endl;
    }
    SharedPointer<int> myPtr3(new int);
    SharedPointer<int> myPtr4(new int);
    myPtr3 = myPtr1;
    myPtr4 = myPtr3;
    
    std::cout<<"CountPtr: " << myPtr1.getRefCount() << std::endl;
    SharedPointer<int> myPtr5 = std::move(myPtr4);
    
    std::cout<<"CountPtr: " << myPtr1.getRefCount() << std::endl;
    std::cout<<"CountPtr: " << myPtr3.getRefCount() << std::endl;

}
    

    return 0;
}