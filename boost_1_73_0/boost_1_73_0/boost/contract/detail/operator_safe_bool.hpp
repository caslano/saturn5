
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
cy9DVVJMT1BUX0NPTk5FQ1RfT05MWS4zVVQFAAG2SCRgrVZdU9tGFH3Xr7h1X4BRZAjtUBqSqXBEUDGSxpIhnvGMZi2t0DayVt1dAZ6S/967K9nGKdPwEDO2tKv7ce65565w5gM4+GEfy9Hh4Luf1HxT/OB17RQJ/hfN1MsOafoE3R86zvH6ilRD2Ho9pfvwKq8n2DNeaZ/rTN+n6SvSzTVI/TPUzvNU3+JO59n7j3izEuyuVLA32oej09Pf4A28PTw6teEjqRmtIFa0XlBxZ8NZbnb+KMnjoyPpBxuoAlI5OwGTkkmQvFAPRFDA+4pltJY0ByIhpzITbIELVoMqKRSsojAKo5kffLLhoWRZ2cdZ8RZkydsqh5LcUxA0o+y+C9MQoYAXGAHj50wqjNkqxmsH01NQVCxlH0aDIJXkQO4Jq8gC0xEFpVKN/H04zFpRYSXDnGdymK2pcEq1/KaqGaJZkhXwRoHi0Epqg7a3YclzVugrUoSbTbuomCztLSxMWOdDLkDSqurDoSujsiuBQtyzZWtLaBA9U/oieS11toeSL3cMkdY+UNGKGtMhLWiXcyTehrbOqTD2hoh1lp5lQ/l3WrbFngOvERUM3Bj8eAALIpm04dZPLsNpArfuZOIGyQzCC3CDWR/vyg8+
*/