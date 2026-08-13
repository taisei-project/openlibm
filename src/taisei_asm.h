
#ifdef OLM_TAISEI_NO_EXPORT
    #ifdef _WIN32
        // no export by default
        #define VISIBILITY(x)
    #elif defined __MACH__
        // equivalent to __attribute__((visibility("hidden")))
        #define VISIBILITY(x) .private_extern CNAME(x);
    #else
        // equivalent to __attribute__((visibility("hidden")))
        #define VISIBILITY(x) .hidden CNAME(x);
    #endif
#else
    #ifdef _WIN32
        // equivalent to __declspec(dllexport)
        #define VISIBILITY(x) .section .drectve; .ascii " -export:", #x;
    #elif defined __MACH__
        // exported by default
        #define VISIBILITY(x)
    #else
        // exported by default
        #define VISIBILITY(x)
    #endif
#endif
