
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