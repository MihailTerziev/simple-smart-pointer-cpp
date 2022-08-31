#ifndef BASE_POINTER_H_
#define BASE_POINTER_H_

#include <stdexcept>
#include <algorithm>

template<typename T> class BasePointer {
    protected:
        enum PointerType {
            HEAP_VALUE,
            NULLP
        };
        
    private:
        T* mPointer;
        PointerType mType;

    public:
        BasePointer() : 
            mPointer(nullptr), mType(PointerType::NULLP) {}

        BasePointer(T* mPointer_, PointerType mType_) : 
            mPointer(mPointer_), mType(mType_) {}

        BasePointer(std::nullptr_t) :
            mPointer(nullptr), mType(PointerType::NULLP) {}

        virtual ~BasePointer() = default;

        BasePointer& operator=(std::nullptr_t) {
            mPointer = nullptr;
            mType = PointerType::NULLP;

            return *this;
        }

        BasePointer(const BasePointer&) = delete;
        BasePointer& operator=(const BasePointer&) = delete;
        BasePointer(BasePointer &&) = delete;
        BasePointer& operator=(BasePointer &&) = delete;

        friend void swap(BasePointer& first, BasePointer& second) {
            std::swap(first.mPointer, second.mPointer);
            std::swap(first.mType, second.mType);
        }

        T* operator->() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Nullptr doesn't point to anything!");

            return mPointer;
        }

        T& operator*() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't dereference nullptr!");

            return *mPointer;
        }

        protected:
            T* get() const { return mPointer; }
            void set(T* other) { mPointer = other; }

            const PointerType& getType() const { return mType; }
            void setType(const PointerType& newType) { mType = newType; }

            virtual void dealloc() = 0;
};

template<typename T> class BasePointer<T[]> {
    protected:
        enum PointerType {
            HEAP_ARRAY,
            NULLP
        };
        
    private:
        T* mPointer;
        PointerType mType;

    public:
        BasePointer() : 
            mPointer(nullptr), mType(PointerType::NULLP) {}

        BasePointer(T* mPointer_, PointerType mType_) : 
            mPointer(mPointer_), mType(mType_) {}

        BasePointer(std::nullptr_t) :
            mPointer(nullptr), mType(PointerType::NULLP) {}

        virtual ~BasePointer() = default;

        BasePointer& operator=(std::nullptr_t) {
            mPointer = nullptr;
            mType = PointerType::NULLP;

            return *this;
        }

        BasePointer(const BasePointer&) = delete;
        BasePointer& operator=(const BasePointer&) = delete;
        BasePointer(BasePointer &&) = delete;
        BasePointer& operator=(BasePointer &&) = delete;

        friend void swap(BasePointer& first, BasePointer& second) {
            std::swap(first.mPointer, second.mPointer);
            std::swap(first.mType, second.mType);
        }

        T* operator->() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Nullptr doesn't point to anything!");

            return mPointer;
        }

        T& operator*() { 
            if (mType == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't dereference nullptr!");

            return *mPointer;
        }

        T& operator[](const int& index) {
		    if(index < 0)
		        throw std::runtime_error("Memory_Access_Violation: Negative index out of bound!");

		    return mPointer[index];
	    }

        void operator++(int) {
            mPointer++;
        }

        void operator--(int) {
            mPointer--;
        }

        protected:
            T* get() const { return mPointer; }
            void set(T* other) { mPointer = other; }

            const PointerType& getType() const { return mType; }
            void setType(const PointerType& newType) { mType = newType; }

            virtual void dealloc() = 0;
};

#endif // BASE_POINTER_H_