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
    !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x592))
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