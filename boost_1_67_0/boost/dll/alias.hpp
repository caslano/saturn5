// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright 2015-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_ALIAS_HPP
#define BOOST_DLL_ALIAS_HPP

#include <boost/dll/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/predef/compiler.h>
#include <boost/predef/os.h>
#include <boost/dll/detail/aggressive_ptr_cast.hpp>

#if BOOST_COMP_GNUC // MSVC does not have <stdint.h> and defines it in some other header, MinGW requires that header.
#include <stdint.h> // intptr_t
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
# pragma once
#endif

/// \file boost/dll/alias.hpp
/// \brief Includes alias methods and macro. You can include this header or
/// boost/dll/shared_library.hpp to reduce dependencies
/// in case you do not use the refcountable functions.

namespace boost { namespace dll {

#ifdef BOOST_DLL_DOXYGEN
/// Define this macro to explicitly specify translation unit in which alias must be instantiated.
/// See section 'Limitations' for more info. You may find usage examples in source codes of almost each tutorial.
/// Must be used in code, when \forcedmacrolink{BOOST_DLL_FORCE_NO_WEAK_EXPORTS} is defined
#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION

/// Define this macro to disable exporting weak symbols and start using the \forcedmacrolink{BOOST_DLL_FORCE_ALIAS_INSTANTIATION}.
/// This may be useful for working around linker problems or to test your program for compatibility with linkers that do not support export of weak symbols.
#define BOOST_DLL_FORCE_NO_WEAK_EXPORTS
#endif

#if defined(_MSC_VER) // MSVC, Clang-cl, and ICC on Windows

#define BOOST_DLL_SELECTANY __declspec(selectany)

#define BOOST_DLL_SECTION(SectionName, Permissions)                                             \
    BOOST_STATIC_ASSERT_MSG(                                                                    \
        sizeof(#SectionName) < 10,                                                              \
        "Some platforms require section names to be at most 8 bytes"                            \
    );                                                                                          \
    __pragma(section(#SectionName, Permissions)) __declspec(allocate(#SectionName))             \
    /**/

#else // #if BOOST_COMP_MSVC


#if BOOST_OS_WINDOWS || BOOST_OS_ANDROID || BOOST_COMP_IBM
// There are some problems with mixing `__dllexport__` and `weak` using MinGW
// See https://sourceware.org/bugzilla/show_bug.cgi?id=17480
//
// Android had an issue with exporting weak symbols
// https://code.google.com/p/android/issues/detail?id=70206
#define BOOST_DLL_SELECTANY
#else // #if BOOST_OS_WINDOWS
/*!
* \brief Macro that allows linker to select any occurrence of this symbol instead of
* failing with 'multiple definitions' error at linktime.
*
* This macro does not work on Android, IBM XL C/C++ and MinGW+Windows
* because of linker problems with exporting weak symbols
* (See https://code.google.com/p/android/issues/detail?id=70206, https://sourceware.org/bugzilla/show_bug.cgi?id=17480)
*/
#define BOOST_DLL_SELECTANY __attribute__((weak))
#endif // #if BOOST_OS_WINDOWS

// TODO: improve section permissions using following info:
// http://stackoverflow.com/questions/6252812/what-does-the-aw-flag-in-the-section-attribute-mean

#if !BOOST_OS_MACOS && !BOOST_OS_IOS
/*!
* \brief Macro that puts symbol to a specific section. On MacOS all the sections are put into "__DATA" segment.
* \param SectionName Name of the section. Must be a valid C identifier without quotes not longer than 8 bytes.
* \param Permissions Can be "read" or "write" (without quotes!).
*/
#define BOOST_DLL_SECTION(SectionName, Permissions)                                             \
    BOOST_STATIC_ASSERT_MSG(                                                                    \
        sizeof(#SectionName) < 10,                                                              \
        "Some platforms require section names to be at most 8 bytes"                            \
    );                                                                                          \
    __attribute__ ((section (#SectionName)))                                                    \
    /**/
#else // #if !BOOST_OS_MACOS && !BOOST_OS_IOS

#define BOOST_DLL_SECTION(SectionName, Permissions)                                             \
    BOOST_STATIC_ASSERT_MSG(                                                                    \
        sizeof(#SectionName) < 10,                                                              \
        "Some platforms require section names to be at most 8 bytes"                            \
    );                                                                                          \
    __attribute__ ((section ( "__DATA," #SectionName)))                                         \
    /**/

#endif // #if #if !BOOST_OS_MACOS && !BOOST_OS_IOS

#endif // #if BOOST_COMP_MSVC


// Alias - is just a variable that pointers to original data
//
// A few attempts were made to avoid additional indirection:
// 1) 
//          // Does not work on Windows, work on Linux
//          extern "C" BOOST_SYMBOL_EXPORT void AliasName() {
//              reinterpret_cast<void (*)()>(Function)();
//          }
//
// 2) 
//          // Does not work on Linux (changes permissions of .text section and produces incorrect DSO)
//          extern "C" BOOST_SYMBOL_EXPORT void* __attribute__ ((section(".text#"))) 
//                  func_ptr = *reinterpret_cast<std::ptrdiff_t**>(&foo::bar);
//
// 3)       // requires mangled name of `Function` 
//          //  AliasName() __attribute__ ((weak, alias ("Function")))  
//
//          // hard to use
//          `#pragma comment(linker, "/alternatename:_pWeakValue=_pDefaultWeakValue")`

/*!
* \brief Makes an alias name for exported function or variable.
*
* This macro is useful in cases of long mangled C++ names. For example some `void boost::foo(std::string)`
* function name will change to something like `N5boostN3foosE` after mangling.
* Importing function by `N5boostN3foosE` name does not looks user friendly, especially assuming the fact
* that different compilers have different mangling schemes. AliasName is the name that won't be mangled
* and can be used as a portable import name.
*
*
* Can be used in any namespace, including global. FunctionOrVar must be fully qualified,
* so that address of it could be taken. Multiple different aliases for a single variable/function
* are allowed.
*
* Make sure that AliasNames are unique per library/executable. Functions or variables
* in global namespace must not have names same as AliasNames.
*
* Same AliasName in different translation units must point to the same FunctionOrVar.
*
* Puts all the aliases into the \b "boostdll" read only section of the binary. Equal to
* \forcedmacrolink{BOOST_DLL_ALIAS_SECTIONED}(FunctionOrVar, AliasName, boostdll).
*
* \param FunctionOrVar Function or variable for which an alias must be made.
* \param AliasName Name of the alias. Must be a valid C identifier.
*
* \b Example:
* \code
* namespace foo {
*   void bar(std::string&);
*
*   BOOST_DLL_ALIAS(foo::bar, foo_bar)
* }
*
* BOOST_DLL_ALIAS(foo::bar, foo_bar_another_alias_name)
* \endcode
*
* \b See: \forcedmacrolink{BOOST_DLL_ALIAS_SECTIONED} for making alias in a specific section.
*/
#define BOOST_DLL_ALIAS(FunctionOrVar, AliasName)                       \
    BOOST_DLL_ALIAS_SECTIONED(FunctionOrVar, AliasName, boostdll)       \
    /**/


#if ((BOOST_COMP_GNUC && BOOST_OS_WINDOWS) || BOOST_OS_ANDROID || BOOST_COMP_IBM || defined(BOOST_DLL_FORCE_NO_WEAK_EXPORTS)) \
    && !defined(BOOST_DLL_FORCE_ALIAS_INSTANTIATION) && !defined(BOOST_DLL_DOXYGEN)

#define BOOST_DLL_ALIAS_SECTIONED(FunctionOrVar, AliasName, SectionName)                        \
    namespace _autoaliases {                                                                    \
        extern "C" BOOST_SYMBOL_EXPORT const void *AliasName;                                   \
    } /* namespace _autoaliases */                                                              \
    /**/

#define BOOST_DLL_AUTO_ALIAS(FunctionOrVar)                                                     \
    namespace _autoaliases {                                                                    \
        extern "C" BOOST_SYMBOL_EXPORT const void *FunctionOrVar;                               \
    } /* namespace _autoaliases */                                                              \
    /**/
#else    
// Note: we can not use `aggressive_ptr_cast` here, because in that case GCC applies
// different permissions to the section and it causes Segmentation fault.
// Note: we can not use `boost::addressof()` here, because in that case GCC 
// may optimize away the FunctionOrVar instance and we'll get a pointer to unexisting symbol.
/*!
* \brief Same as \forcedmacrolink{BOOST_DLL_ALIAS} but puts alias name into the user specified section.
*
* \param FunctionOrVar Function or variable for which an alias must be made.
* \param AliasName Name of the alias. Must be a valid C identifier.
* \param SectionName Name of the section. Must be a valid C identifier without quotes not longer than 8 bytes.
*
* \b Example:
* \code
* namespace foo {
*   void bar(std::string&);
*
*   BOOST_DLL_ALIAS_SECTIONED(foo::bar, foo_bar, sect_1) // section "sect_1" now exports "foo_bar"
* }
* \endcode
*
*/
#define BOOST_DLL_ALIAS_SECTIONED(FunctionOrVar, AliasName, SectionName)                        \
    namespace _autoaliases {                                                                    \
        extern "C" BOOST_SYMBOL_EXPORT const void *AliasName;                                   \
        BOOST_DLL_SECTION(SectionName, read) BOOST_DLL_SELECTANY                                \
        const void * AliasName = reinterpret_cast<const void*>(reinterpret_cast<intptr_t>(      \
            &FunctionOrVar                                                                      \
        ));                                                                                     \
    } /* namespace _autoaliases */                                                              \
    /**/

/*!
* \brief Exports variable or function with unmangled alias name.
*
* This macro is useful in cases of long mangled C++ names. For example some `void boost::foo(std::string)`
* function name will change to something like `N5boostN3foosE` after mangling.
* Importing function by `N5boostN3foosE` name does not looks user friendly, especially assuming the fact
* that different compilers have different mangling schemes.*
*
* Must be used in scope where FunctionOrVar declared. FunctionOrVar must be a valid C name, which means that
* it must not contain `::`.
*
* Functions or variables
* in global namespace must not have names same as FunctionOrVar.
*
* Puts all the aliases into the \b "boostdll" read only section of the binary. Almost same as
* \forcedmacrolink{BOOST_DLL_ALIAS}(FunctionOrVar, FunctionOrVar).
*
* \param FunctionOrVar Function or variable for which an unmangled alias must be made.
*
* \b Example:
* \code
* namespace foo {
*   void bar(std::string&);
*   BOOST_DLL_AUTO_ALIAS(bar)
* }
*
* \endcode
*
* \b See: \forcedmacrolink{BOOST_DLL_ALIAS} for making an alias with different names.
*/

#define BOOST_DLL_AUTO_ALIAS(FunctionOrVar)                                                     \
    namespace _autoaliases {                                                                    \
        BOOST_DLL_SELECTANY const void * dummy_ ## FunctionOrVar                                \
            = reinterpret_cast<const void*>(reinterpret_cast<intptr_t>(                         \
                &FunctionOrVar                                                                  \
            ));                                                                                 \
        extern "C" BOOST_SYMBOL_EXPORT const void *FunctionOrVar;                               \
        BOOST_DLL_SECTION(boostdll, read) BOOST_DLL_SELECTANY                                   \
        const void * FunctionOrVar = dummy_ ## FunctionOrVar;                                   \
    } /* namespace _autoaliases */                                                              \
    /**/


#endif


}} // namespace boost::dll


#endif // BOOST_DLL_ALIAS_HPP


/* alias.hpp
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
*/