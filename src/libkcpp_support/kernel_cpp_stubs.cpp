#include <stddef.h>

extern "C" {

// Pure virtual function called (undefined behavior — panic or halt)
void __cxa_pure_virtual() {
    // You can replace with kernel panic
    while (true) { }
}

// Called if a deleted virtual function is invoked (C++20+)
void __cxa_deleted_virtual() {
    while (true) { }
}

// Exception stubs (only needed if using -fexceptions)
void __cxa_throw(void*, void*, void(*)(void*)) {
    while (true) { }
}

void* __cxa_allocate_exception(size_t) {
    return nullptr;
}

void __cxa_free_exception(void*) { }

void __cxa_begin_catch(...) { }
void __cxa_end_catch() { }

}
