#ifndef BASE_POINTER_H_
#define BASE_POINTER_H_

#include <stdexcept>
#include <algorithm>

template<typename T> class BasePointer {
    protected:
        enum PointerType {
            HEAP_VALUE,
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

        virtual ~BasePointer() = default;

        BasePointer(const BasePointer&) = delete;
        BasePointer& operator=(BasePointer other) = delete;
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

        void clear() {
            if (mPointer != nullptr) {
                mPointer = nullptr;
                mType = PointerType::NULLP;
            }
        }

        protected:
            T* get() const { return mPointer; }
            void set(T* other) { mPointer = other; }
            const PointerType& getType() const { return mType; }

            virtual void dealloc() = 0;
};

#endif // BASE_POINTER_H_