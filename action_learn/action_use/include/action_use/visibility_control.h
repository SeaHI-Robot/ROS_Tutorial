#ifndef ACTION_USE__VISIBILITY_CONTROL_H_
#define ACTION_USE__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ACTION_USE_EXPORT __attribute__ ((dllexport))
    #define ACTION_USE_IMPORT __attribute__ ((dllimport))
  #else
    #define ACTION_USE_EXPORT __declspec(dllexport)
    #define ACTION_USE_IMPORT __declspec(dllimport)
  #endif
  #ifdef ACTION_USE_BUILDING_DLL
    #define ACTION_USE_PUBLIC ACTION_USE_EXPORT
  #else
    #define ACTION_USE_PUBLIC ACTION_USE_IMPORT
  #endif
  #define ACTION_USE_PUBLIC_TYPE ACTION_USE_PUBLIC
  #define ACTION_USE_LOCAL
#else
  #define ACTION_USE_EXPORT __attribute__ ((visibility("default")))
  #define ACTION_USE_IMPORT
  #if __GNUC__ >= 4
    #define ACTION_USE_PUBLIC __attribute__ ((visibility("default")))
    #define ACTION_USE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ACTION_USE_PUBLIC
    #define ACTION_USE_LOCAL
  #endif
  #define ACTION_USE_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // ACTION_USE__VISIBILITY_CONTROL_H_
