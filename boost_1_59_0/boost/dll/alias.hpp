// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
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