#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template<typename T> class SmartPointer {
    enum PointerType {
        VALUE,
        ARRAY,
        NULLP
    };

    T* pointer;
    PointerType type;
    size_t size;

    public:
        SmartPointer() : 
            pointer(nullptr), type(PointerType::NULLP), size(0) {}

        SmartPointer(const T& value) : 
            pointer(new T(value)), type(PointerType::VALUE), size(1) {}

        SmartPointer(T* array, const size_t& size_) : 
            pointer(array), type(PointerType::ARRAY), size(size_) {}

        SmartPointer(const SmartPointer& other) : 
            pointer(nullptr), type(other.type), size(other.size) 
            {   
                if (type == PointerType::VALUE)
                    pointer = new T(*other.pointer);

                else if (type == PointerType::ARRAY)
                    std::copy(other.pointer, other.pointer + size, pointer);
            }

        ~SmartPointer() {
            if (type == PointerType::VALUE)
                delete pointer;

            else if (type == PointerType::ARRAY)
                delete[] pointer;
        }

        SmartPointer(SmartPointer &&other) = delete;
        SmartPointer& operator=(SmartPointer &&other) = delete;

        friend void swap(SmartPointer& first, SmartPointer& second) {
            std::swap(first.pointer, second.pointer);
            std::swap(first.type, second.type);
            std::swap(first.size, second.size);
        }

        SmartPointer& operator=(SmartPointer other) {
            swap(*this, other);
            return *this;
        }

        T* operator->() { 
            if (type == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Nullptr doesn't point to anything!");

            return pointer; 
        }

        T& operator*() { 
            if (type == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't dereference nullptr!");

            return *pointer;
        }

        T& operator[](const size_t& index) {
            if (type == PointerType::NULLP)
                throw std::runtime_error("Reference_Error: Can't access nullptr!");

            else if (type == PointerType::VALUE)
                throw std::runtime_error("Reference_Error: Pointer to single value!");

            else if (index < 0 || index >= size)
                throw std::out_of_range("Memory_Access_Violation: Index out of range!");

            return pointer[index];
        }

        void clear() {
            if (pointer != nullptr) {
                pointer = nullptr;
                type = PointerType::NULLP;
                size = 0;
            }
        }
};

#endif