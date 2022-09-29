#ifndef UNIQUE_POINTER_H_
#define UNIQUE_POINTER_H_

#include "BasePointer.h"

template<typename T> class UniquePointer : public BasePointer<T> {
    private:
        void* operator new(size_t) = delete;
    
        void reset(UniquePointer& other) {
            other.set(nullptr);
            other.setType(BasePointer<T>::PointerType::NULLP);
        }

        void move(UniquePointer& other) {
            BasePointer<T>::set(other.get());
            BasePointer<T>::setType(other.getType());

            reset(other);
        }

        void dealloc() override {
            if (BasePointer<T>::get() != nullptr)
                delete BasePointer<T>::get();
        }

    public:
        UniquePointer() : BasePointer<T>() {}
        UniquePointer(T* value) : BasePointer<T>(value, BasePointer<T>::PointerType::HEAP_VALUE) {}
        UniquePointer(std::nullptr_t) : BasePointer<T>(nullptr) {}

        ~UniquePointer() {
            dealloc();
        }

        UniquePointer(const UniquePointer&) = delete;
        UniquePointer& operator=(const UniquePointer&) = delete;

        UniquePointer(UniquePointer&& other) {
            move(other);
        }

        UniquePointer& operator=(UniquePointer&& other) {
            dealloc();
            move(other);

            return *this;
        }

        UniquePointer& operator=(std::nullptr_t) {
            reset(*this);
            return *this;
        }
};

template<typename T> class UniquePointer<T[]> : public BasePointer<T[]> {
    private:
        void* operator new[](size_t) = delete;
    
        void reset(UniquePointer& other) {
            other.set(nullptr);
            other.setType(BasePointer<T[]>::PointerType::NULLP);
        }

        void move(UniquePointer& other) {
            BasePointer<T[]>::set(other.get());
            BasePointer<T[]>::setType(other.getType());

            reset(other);
        }

        void dealloc() override {
            if (BasePointer<T[]>::get() != nullptr)
                delete[] BasePointer<T[]>::get();
        }

    public:
        UniquePointer() : BasePointer<T[]>() {}
        UniquePointer(T* array) : BasePointer<T[]>(array, BasePointer<T[]>::PointerType::HEAP_ARRAY) {}
        UniquePointer(std::nullptr_t) : BasePointer<T[]>(nullptr) {}

        ~UniquePointer() {
            dealloc();
        }

        UniquePointer(const UniquePointer&) = delete;
        UniquePointer& operator=(const UniquePointer&) = delete;

        UniquePointer(UniquePointer&& other) {
            move(other);
        }

        UniquePointer& operator=(UniquePointer&& other) {
            dealloc();
            move(other);

            return *this;
        }

        UniquePointer& operator=(std::nullptr_t) {
            reset(*this);
            return *this;
        }
};

#endif  // UNIQUE_POINTER_H_
