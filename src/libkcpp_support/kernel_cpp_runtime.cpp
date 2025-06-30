extern "C" {

// ---------- Static Destructor Registration ----------

struct DestructorEntry {
    void (*pFunc)(void*);
    void* pArg;
    void* pDsoHandle;
};

constexpr int MAX_DESTRUCTORS = 128;
static DestructorEntry g_aDestructors[MAX_DESTRUCTORS];
static int g_nDestructorCount = 0;

// Register destructor (called by compiler for global/static C++ objects)
int __cxa_atexit(void (*pFunc)(void*), void* pArg, void* pDsoHandle) {
    if (g_nDestructorCount >= MAX_DESTRUCTORS)
        return -1;

    g_aDestructors[g_nDestructorCount++] = { pFunc, pArg, pDsoHandle };
    return 0;
}

// Call registered destructors (called at shutdown or poweroff)
void __cxa_finalize(void* pDsoHandle) {
    for (int nIndex = g_nDestructorCount - 1; nIndex >= 0; --nIndex) {
        if (pDsoHandle == nullptr || g_aDestructors[nIndex].pDsoHandle == pDsoHandle) {
            g_aDestructors[nIndex].pFunc(g_aDestructors[nIndex].pArg);
            // Optional: mark as called
        }
    }
}

} // extern "C"
