
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

#elif defined(BOOST_BORLANDC)

#   if BOOST_BORLANDC < 0x550
#     error "unsupported compiler version"
#   elif BOOST_BORLANDC > 0x565
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
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
*/