// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED   

#if defined(_MSC_VER)
# pragma once
#endif                  
 
#include <boost/config.hpp> // BOOST_MSVC, BOOST_NO_SFINAE
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/config/limits.hpp>
#include <boost/iostreams/detail/push_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/type_traits/is_same.hpp>

//------Macros for defining forwarding constructors and open overloads--------//
    
//
// Macro: BOOST_IOSTREAMS_FORWARD(class, impl, device, params, args)
// Description: Defines constructors and overloads of 'open' which construct
//      a device using the specified argument list and pass it to the specified
//      helper function
//   class - The class name
//   impl - The helper function
//   device - The device type
//   params - The list of formal parameters trailing the device parameter in
//     the helper function's signature
//   params - The list of arguments passed to the helper function, following the
//     device argument
//
#define BOOST_IOSTREAMS_FORWARD(class, impl, device, params, args) \
    class(const device& t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    class(device& t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    class(const ::boost::reference_wrapper<device>& ref params()) \
    { this->impl(ref args()); } \
    void open(const device& t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    void open(device& t params()) \
    { this->impl(::boost::iostreams::detail::wrap(t) args()); } \
    void open(const ::boost::reference_wrapper<device>& ref params()) \
    { this->impl(ref args()); } \
    BOOST_PP_REPEAT_FROM_TO( \
        1, BOOST_PP_INC(BOOST_IOSTREAMS_MAX_FORWARDING_ARITY), \
        BOOST_IOSTREAMS_FORWARDING_CTOR, (class, impl, device) \
    ) \
    BOOST_PP_REPEAT_FROM_TO( \
        1, BOOST_PP_INC(BOOST_IOSTREAMS_MAX_FORWARDING_ARITY), \
        BOOST_IOSTREAMS_FORWARDING_FN, (class, impl, device) \
    ) \
    /**/
#define BOOST_IOSTREAMS_FORWARDING_CTOR(z, n, tuple) \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename U)> \
    BOOST_PP_TUPLE_ELEM(3, 0, tuple) \
    (BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, const U, &u) \
      BOOST_IOSTREAMS_DISABLE_IF_SAME(U0, BOOST_PP_TUPLE_ELEM(3, 2, tuple))) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( BOOST_PP_TUPLE_ELEM(3, 2, tuple) \
        (BOOST_PP_ENUM_PARAMS_Z(z, n, u)) ); } \
    template< typename U100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
              BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), typename U) > \
    BOOST_PP_TUPLE_ELEM(3, 0, tuple) \
    ( U100& u100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
      BOOST_PP_ENUM_BINARY_PARAMS_Z(z, BOOST_PP_DEC(n), const U, &u) \
      BOOST_IOSTREAMS_DISABLE_IF_SAME(U100, BOOST_PP_TUPLE_ELEM(3, 2, tuple))) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( BOOST_PP_TUPLE_ELEM(3, 2, tuple) \
        ( u100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
          BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), u)) ); } \
    /**/
#define BOOST_IOSTREAMS_FORWARDING_FN(z, n, tuple) \
    template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename U)> \
    void open(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, const U, &u) \
      BOOST_IOSTREAMS_DISABLE_IF_SAME(U0, BOOST_PP_TUPLE_ELEM(3, 2, tuple))) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( BOOST_PP_TUPLE_ELEM(3, 2, tuple) \
        (BOOST_PP_ENUM_PARAMS_Z(z, n, u)) ); } \
    template< typename U100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
              BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), typename U) > \
    void open \
    ( U100& u100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
      BOOST_PP_ENUM_BINARY_PARAMS_Z(z, BOOST_PP_DEC(n), const U, &u) \
      BOOST_IOSTREAMS_DISABLE_IF_SAME(U100, BOOST_PP_TUPLE_ELEM(3, 2, tuple))) \
    { this->BOOST_PP_TUPLE_ELEM(3, 1, tuple) \
      ( u100 BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
        BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_DEC(n), u) ); } \
    /**/

// Disable forwarding constructors if first parameter type is the same
// as the device type
#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
# define BOOST_IOSTREAMS_DISABLE_IF_SAME(device, param) \
    , typename boost::disable_if< boost::is_same<device, param> >::type* = 0 \
    /**/
#else 
# define BOOST_IOSTREAMS_DISABLE_IF_SAME(device, param)
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FORWARD_HPP_INCLUDED

/* forward.hpp
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
*/