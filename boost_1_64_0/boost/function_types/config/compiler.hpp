
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_CONFIG_COMPILER_HPP_INCLUDED
#define BOOST_FT_CONFIG_COMPILER_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if defined(BOOST_MSVC)

#   if BOOST_MSVC < 1310
#     error "unsupported compiler version"
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS

      // enable clrcall calling covention (call to .NET managed code) when
      // compiling with /clr 
#     if BOOST_MSVC >= 1400 && defined(__cplusplus_cli)
#       ifndef BOOST_FT_CC_CLRCALL
#       define BOOST_FT_CC_CLRCALL callable_builtin
#       endif
#     endif

      // Intel x86 architecture specific calling conventions
#     ifdef _M_IX86
#       define BOOST_FT_COMMON_X86_CCs callable_builtin
#       if BOOST_MSVC < 1400
          // version 7.1 is missing a keyword to specify the thiscall cc ...
#         ifndef BOOST_FT_CC_IMPLICIT_THISCALL
#         define BOOST_FT_CC_IMPLICIT_THISCALL non_variadic|member|callable_builtin
#         ifndef BOOST_FT_CONFIG_OK
#           pragma message("INFO| /Gd /Gr /Gz will compiler options will cause")
#           pragma message("INFO| a compile error.")
#           pragma message("INFO| Reconfigure Boost.FunctionTypes in this case.")
#           pragma message("INFO| This message can be suppressed by defining")
#           pragma message("INFO| BOOST_FT_CONFIG_OK.")
#         endif
#         endif
#       else 
          // ...introduced in version 8
#         ifndef BOOST_FT_CC_THISCALL
#         define BOOST_FT_CC_THISCALL non_variadic|member|callable_builtin
#         endif
#       endif
#     endif
#   endif

#elif defined(__GNUC__) && !defined(BOOST_INTEL_LINUX)

#   if __GNUC__ < 3
#     error "unsupported compiler version"
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS

#     if defined(__i386__)
#       // see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=20439
#       // see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=29328
#       if BOOST_WORKAROUND(__GNUC__,BOOST_TESTED_AT(4))
#         ifndef BOOST_FT_CC_IMPLICIT 
#         define BOOST_FT_CC_IMPLICIT member|callable_builtin
#         endif
#         define BOOST_FT_COMMON_X86_CCs non_member|callable_builtin
#       else
#         define BOOST_FT_COMMON_X86_CCs callable_builtin
#       endif
#     else
#       ifndef BOOST_FT_CC_IMPLICIT
#       define BOOST_FT_CC_IMPLICIT callable_builtin
#       endif
#     endif
#   endif

#   if (defined(BOOST_FT_CC_CDECL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__cdecl)
#     define __cdecl __attribute__((__cdecl__))
#   endif
#   if (defined(BOOST_FT_CC_STDCALL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__stdcall)
#     define __stdcall __attribute__((__stdcall__))
#   endif
#   if (defined(BOOST_FT_CC_FASTCALL) || defined(BOOST_FT_COMMON_X86_CCs)) \
        && !defined(__fastcall)
#     define __fastcall __attribute__((__fastcall__))
#   endif

#elif defined(__BORLANDC__)

#   if __BORLANDC__ < 0x550
#     error "unsupported compiler version"
#   elif __BORLANDC__ > 0x565
#     pragma message("WARNING: library untested with this compiler version")
#   endif

#   ifdef BOOST_FT_AUTODETECT_CALLING_CONVENTIONS
#     define BOOST_FT_COMMON_X86_CCs callable_builtin
#   endif

    // syntactic specialities of cc specifier
#   define BOOST_FT_SYNTAX(result,lparen,cc_spec,type_mod,name,rparen) \
                        result() cc_spec() lparen() type_mod() name() rparen()
#else
    // only enable default calling convention
#   define BOOST_FT_CC_IMPLICIT callable_builtin
#endif


#endif


/* compiler.hpp
vJJUD45m/85uHPpwFNIjZzFjezW+XLkhi3Zl0GqoNQa/+ogbjQ0w+KjM57tviU21nXn203o5d8gNbr2mQZ3kAxy2oxHZ03tCfakBNpsCW0/ZS41P13F7RjWOLjnN29YdheYVN35X/Azhf5rbKsGHP3/CNP0Xfqje5/s1x+StAHu+n5sLP51PLFXMYrvD1fSrKJJTvKzhpDxSDitcyv1vXMR9V21EP1WWSvmGKGrybfnnKviyYxMP/xuMowsDpXjSH5HalmL43Qe0XQP55fwBdD31GQ+DLyPPCdI/2gHXzKdgx5eryPlAFu56xmarW7O7sicMowUaOzVQJ7anVN78HMvaG8kBC6OgUmQmX7ZZwOx7XjKi731o/1snl5+dBuF/nLlTluBU0l0MEt+xLv2ibOs6lVUbfrAiPIPZzu+R07M/8rLbotMHZyZF38XvvI0wT62Vzc7PwpzVxzB8jB477PRG8MTHKB0SIV59GofGp91Q2y6BLdv5StUDeUxTN+Bcr1xOWfVCjA4fyOYfOshSDXOqsFDqtX5M23sH5TPrF/z15zc3/bHEh9+2mL/OEgW/FqDtthIMudJCLDi1lC17bJMVyWYsj9Rke/1jKFtkJtfUNHDalAVi1usITj0l5e6COlToHJIugxbhgY6ByK8dicTz11hv5YW46B5499aFNQ6TZcPiRXxZ5EC58zr33DSkyaNLzHY0xGrvY4w95C42Liyh79FasTxbFXfmf4RfSztE93KQAT+eU6XqKGOjOjH1vTr/ah7iqmk98fu8Bqsu5dBwxz5mXvXG+8+RUPJ0Ew+CmuPbnukwbKlLj4JYaZrbCPMXE+DsAurrPcQ6P3V+2TVUZOn14VWDrmLLM3sOHr4JSf5LmbV7uhxfW81fw93k9L4/2WxBvWxItOWu0WHQXNGVfZa0F33UD2HcR19psHchws5GCt8eh5Dc2k+0Pt4e8xeXM6j7WlhotxEV10ZAg8482f8OR+96h3YpNeCidrQ2CsaOkZFi4fdzVC8vk/qXrWlmPRAev4pwP8AMgxsNsfveazw/fgcj/JbKax2DcHbtOT5K3sVg3au80PYhxybvR+vcgVhvFCisTg5FaeEmObdNDRfNbSV+WWyn2cBO4pCNI2+a/pXVvhUsDNERq6Yup4P7IhH2RIMeB6JEmVsaXukbyOBpu5gmpgMn99OleyVz90fyRDxgv+k8W3brINt4/ka/6we4syISPuYWHP0yg18+95LdR55gZ+Uf4qzpLfTasptVx/3peM9RrpEKXJDiIv1cFvCclwo6Rf7Bn1IFzHReiSm3rYTy/BKeXGYh8rwDm7wrpVUXK/5OOSD9Qk0RYZnNQt2TPJnxgLvHBvPn6n8wH/IQlyMpN4+oQqxaOpXOZiJ65St6hfrTfVOxvLRnBf10XnPTtPb0XKEh7G9PQeIvdTb/at7kVw+L0gSJqvVbReC8dO6x3iT/2SRifsolUVNoSzfTGOZtVmGbzbvwJOg1HYuOsrq8nGtWH5enlzth2Ktm4mVAFkMfbpJtnCw4QtFBJh5uyZwLzphwwgMFffVl15kF8A3whqXleLbbM5lb1qexpqOB3Fyli2fHQ8W9g2Npc3gc/ts4H6rfvgrf60uooLmN1yeUw/jeAlEwwZEzd34UT1qV451nubCvXEvFea1EM1eB/VbbOKzuMssueYlRN1Yw81GV7PT0P0QoaYm5R0vQ89QuadxqCs3nr8EV07PYGZMvZ53picfzvdjbqxSzD/qIS+8nMzGsiOU5M6g+rYLe0z/j/ciNUlF/N35GxAr3q6E8s1VZ+FsE4oNtP9GwojWy7uwVfsG5vKBuCQOLNVycpMs/SysR96gVPO4=
*/