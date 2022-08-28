# simple-smart-pointer-cpp
This is simple implementation of a smart pointer class. It allows save usage of dynamic memory allocation. The class encapsulates raw pointer logic and deallocates resources automatically. Instances can be copyied, copy-assigned, moved and move-assigned so that working with them would be flexible and convenient for the user.

However, dynamic instantiating of the class should not be done, as there will be memory leak if the user doesn't call the destructor manually. Purpose of the class is to encapsulate pointer to dynamic memory and free it when not needed anymore, so it should be located on the stack. That way the compiler takes care of everything, otherwise pointer to pointer logic would be redundant.

I hope you like it!
