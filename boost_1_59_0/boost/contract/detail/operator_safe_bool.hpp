
#ifndef BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL_HPP_
#define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/name.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// NOTE: This code is inspired by <boost/shared_ptr/detail/operator_bool.hpp>.

/* PRIVATE */

// operator! is redundant, but some compilers need it.
#define BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr) \
    bool operator!() const BOOST_NOEXCEPT { return !(bool_expr); }
    
/* PUBLIC */

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && \
        !defined(BOOST_NO_CXX11_NULLPTR)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        explicit operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, < 0x570) ) || \
        defined(__CINT__)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif defined(_MANAGED)
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        static void BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func)( \
                this_type***) {} \
        typedef void (*BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type))( \
                this_type***); \
        operator BOOST_CONTRACT_DETAIL_NANE(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? \
                    &BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#elif (defined(__MWERKS__) && BOOST_WORKAROUND(__MWERKS__, < 0x3200)) || \
        (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ < 304)) || \
        (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, <= 0x590))
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        void BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func)() const {} \
        typedef void (this_type::*BOOST_CONTRACT_DETAIL_NAME1( \
                operator_safe_bool_type))() const; \
        operator BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? &this_type:: \
                    BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_func) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#else
    #define BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
        void* BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_data); \
        typedef void* this_type::*BOOST_CONTRACT_DETAIL_NAME1( \
                operator_safe_bool_type);\
        operator BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_type)() \
                const BOOST_NOEXCEPT { \
            return (bool_expr) ? &this_type:: \
                    BOOST_CONTRACT_DETAIL_NAME1(operator_safe_bool_data) : 0; \
        } \
        BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)
#endif

#endif // #include guard


/* operator_safe_bool.hpp
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
*/