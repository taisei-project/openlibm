#ifndef OPENLIBM_DEFS_H_
#define OPENLIBM_DEFS_H_

#ifdef OLM_TAISEI_NO_EXPORT
#define OLM_DLLEXPORT __attribute__ ((visibility("hidden")))
#else

#ifdef _WIN32
# ifdef IMPORT_EXPORTS
#  define OLM_DLLEXPORT __declspec(dllimport)
# else
#  define OLM_DLLEXPORT __declspec(dllexport)
# endif
#else
#define OLM_DLLEXPORT __attribute__ ((visibility("default")))
#endif

#endif // OLM_TAISEI_NO_EXPORT

#endif // OPENLIBM_DEFS_H_
