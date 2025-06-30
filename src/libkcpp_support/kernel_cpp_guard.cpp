extern "C" {

// Static local guard — prevents double initialization of static variables
int __cxa_guard_acquire(char* pGuardObject) {
    return (*pGuardObject == 0); // 1 if not initialized yet
}

void __cxa_guard_release(char* pGuardObject) {
    *pGuardObject = 1; // Mark as initialized
}

void __cxa_guard_abort(char* pGuardObject) {
    *pGuardObject = 0; // Optional: reset if constructor throws
}

} // extern "C"
