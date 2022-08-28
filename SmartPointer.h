#ifndef SMART_POINTER_H_
#define SMART_POINTER_H_

#include <stdexcept>


template<typename T> class SmartPointer {
    private:
        enum PointerType {
            ALLOC,
            NULLP
        };

        T* mPtr;
        PointerType mType;
        bool mIsCopy;

        void __copy(const SmartPointer& other) {
            mPtr = other.mPtr;
            mType = other.mType;
            mIsCopy = other.mIsCopy;
        }

        void __reset(SmartPointer& sp) {
            sp.mPtr = nullptr;
            sp.mType = PointerType::NULLP;
        }

        void __move(SmartPointer& other) {
            __copy(other);
            __reset(other);
        }

        void __dealloc() {
            if (mPtr != nullptr)
			    delete mPtr;
        }

    public:
        SmartPointer() :
            mPtr(nullptr), mType(PointerType::NULLP), mIsCopy(false) {}

        SmartPointer(T* heap_alloc_mem_) :
            mPtr(heap_alloc_mem_), mType(PointerType::ALLOC), mIsCopy(false) {}

        SmartPointer(std::nullptr_t) :
            mPtr(nullptr), mType(PointerType::NULLP), mIsCopy(false) {}

        ~SmartPointer() {
            if (!mIsCopy)
                __dealloc();
        }

        SmartPointer(const SmartPointer& other) : mPtr(other.mPtr), mType(other.mType), mIsCopy(true) {}

        SmartPointer& operator=(const SmartPointer& other) {
            if (this != &other) {
                __copy(other);
            
                if (!mIsCopy)
                    mIsCopy = true;
            }

            return *this;
        }

        SmartPointer& operator=(std::nullptr_t) {
            __reset(*this);
            return *this;
        }

        SmartPointer(SmartPointer&& other) {
            __move(other);
        }

        SmartPointer& operator=(SmartPointer&& other) {
            if (this != &other) {
                __dealloc();
                __move(other);
            }
            
            return *this;
        }

        T* operator->() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Nullptr doesn't point to anything!");

            return mPtr;
        }

        T& operator*() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't dereference nullptr!");

            return *mPtr;
        }
};

template<typename T> class SmartPointer<T[]> {
    private:
        enum PointerType {
            ALLOC,
            NULLP
        };

        T* mPtr;
        PointerType mType;
        bool mIsCopy;

        void __copy(const SmartPointer& other) {
            mPtr = other.mPtr;
            mType = other.mType;
            mIsCopy = other.mIsCopy;
        }

        void __reset(SmartPointer& sp) {
            sp.mPtr = nullptr;
            sp.mType = PointerType::NULLP;
        }

        void __move(SmartPointer& other) {
            __copy(other);
            __reset(other);
        }

        void __dealloc() {
            if (mPtr != nullptr)
			    delete[] mPtr;
        }

    public:
        SmartPointer() :
            mPtr(nullptr), mType(PointerType::NULLP), mIsCopy(false) {}

        SmartPointer(T* heap_alloc_mem_) :
            mPtr(heap_alloc_mem_), mType(PointerType::ALLOC), mIsCopy(false) {}

        SmartPointer(std::nullptr_t) :
            mPtr(nullptr), mType(PointerType::NULLP), mIsCopy(false) {}

        ~SmartPointer() {
            if (!mIsCopy)
                __dealloc();
        }

        SmartPointer(const SmartPointer& other) : mPtr(other.mPtr), mType(other.mType), mIsCopy(true) {}

        SmartPointer& operator=(const SmartPointer& other) {
            if (this != &other) {
                __copy(other);
            
                if (!mIsCopy)
                    mIsCopy = true;
            }

            return *this;
        }

        SmartPointer& operator=(std::nullptr_t) {
            __reset(*this);
            return *this;
        }

        SmartPointer(SmartPointer&& other) {
            __move(other);
        }

        SmartPointer& operator=(SmartPointer&& other) {
            if (this != &other) {
                __dealloc();
                __move(other);
            }
            
            return *this;
        }

        T* operator->() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Nullptr doesn't point to anything!");

            return mPtr;
        }

        T& operator*() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't dereference nullptr!");

            return *mPtr;
        }    

        T& operator[](const int& index) {
		    if(index < 0)
		        throw std::runtime_error("Memory_Access_Violation: Negative index out of bound!");

		    return mPtr[index];
	    }
};

#endif  // SMART_POINTER_H_