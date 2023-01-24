/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_SET_FORWARD_CTOR_09162005_1115)
#define FUSION_SET_FORWARD_CTOR_09162005_1115

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/set/detail/cpp03/set_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_SET_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    set(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* set_forward_ctor.hpp
DCrKyJexFGVkJ5gYrlfjtQcgjhaOUg16/lDeJDrw/5HOTjxPs+Q8AbqTHPxqPpSUS+CTODuYgimUTyEmlclL0weWgN5m84LNkA3xEt8LHeBtKZ7vwuL5sniUze/hxEypBcE1GCrkQ/Ol4jge0xdcaR2Kg0KH9OGKtPqs1ZtqkX9aMON4hzPOvkrEnZ3pl9wZ+nmFzUX6XOLLBm2xTcYpgNVyMvoFAEPXY8p1hkUVw5OaIRYjg4Z2gWphN2YDtln+aLEycg5+IzpQr3UY7GlMbsbslmB+60TPcmSiuxB5knUXMNEoPwXbKji/Em2c9PExyKBg8PIPzRO/oXMLck0fiok+HpnojdaDjd/Sg2cClJPNUZy3JghEJvq614+kOC440JVnkdTkCAd56BaWXY9gg2ZjqlWPbzkfGdRlwYfh8Ccx3XWPdvwejdZLW8HxYl8zDQR5PIIkyP91Lk6qylRz0bmMPXMl8G8/AKf/YHG/5UPxM0imUvY4M+vj0JIRNk7dkhHOqmI6q4rpuPj5CqdhTr+GLuqLWbNTzbUToDTv4qubuNlY6mIMFUVcW8ibd9jePRf5aecVyyzhLXL5Asbygu35xNt+BtJSIimOOwsktt+yxHbQGZri8D+0gV8YwA289iLcwB9/USoO52cpxeF/hyjF4bKjQGI7j6aP4RNOrPhzSGI712CJ7QYZAiEn61ny4LqjK8l9isno95GL
*/