
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
inP4d3E1nMiukJMG6Q+OkIaU+iJc3ZZDCb6ZUUJ0u6rtGPfXZcgqTPbUi2DZei4HvXiFVmKm/8+5Fc4xWNaw0ZzDnfIPSJpDtMoyTtmRhNOq1Dus8DFn9XURahsBFK6U6QKTNQlCdNTvW28Lro1JefqEksCVKPb73DoXNpWwEPkGf8+29QiC3TLR5TeadKu7C+k3lJjG7whIYgTbKWneqv+qrbZWEfedV9w4EXXmj8dgn70cAgqyT9VG3HHv8nwMRpdGRWOehzji1B2uW/AWCPqTo7qSMwgJ68beSR6npCebrwVDSxF1/BCZle26bxDzbLPZd6Zal37Rhr4D3fF0vBMy4/Aj32spyxeARCkUijsKBaeALIiu8RnYyXPPRqNpABvuOlZ2dxlAF8uaieds0WD0ETgb4khj8RiBYtNrf5uDT2ww0F/RENxTceaWYBPw1U1dSZ59N/vTRoqxkepHYYRy3o0ARvxWFItvYjWNXZZufPsxdGKZgoeAI/PMpz1e8zSYKPamgYWVeH52ADT5PCJUUxScGOeULd8aK6WjZVwGiyWx7eeDph3P2A==
*/