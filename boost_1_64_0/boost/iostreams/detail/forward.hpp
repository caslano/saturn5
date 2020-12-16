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
XSd+ecxeizN9Ypa4NTZjn6V1mKb9IVX830KDVRjI84izr8UqCmlwJd4BJpKnQHFClUoJduuEeF9obcVh3BGZR5Ok+nPQ/9zRr7x0dWgtzRHVact5Fc4XaBtfCPu52vOpnPfnfEBq2TYunTZa0P/ENrrdtL1CbaPa9rRuQ/aWe4qeqUPTTiPapLHzu1MXXd2M+JD1SG3aZPoAV5ucJQvMIn9jvNoe4bzGbM+2h65nW/Jqd+h6js/GXnmG+N9odSAXy93jFGk9J2+hGc/6i97VVnNntEJaWVMkXVW17gbqmLIoxT0elb1Wzam3RwbENrZEjhkJHvXTM/QeXxvIXCK24bk2bs2cq7rqZ3ZuUTqrbmYvyC0o9LgXCPWvoxLGb+Zzx8n5JKsZ/49BPOpTr2NHjkUmzlfEv6ZX/RI29vpVXXffN3X2oPjdh22uOGqO+Zhm/Ajm2T2X+h3R7coo0sSsQ/xQ3AqsajJfV/LBUVpeafobv1r0XrcaUwO3IvdqO9ot+nkzCl3t7UXRXWudxZXyrYCxsf+YuM+1quPjXGunXmvBrIUEL72PmiZ6Nex2/D8BeQ15X8vqVA3jrrtnRL+q2LbfReEeq8p3oBTKrso0Y2fYjFmq06Aadu1wS4hbelVI51PVaaQ6WdU0Hnvp/Qnx/gR7DgMhep5joYYpIkzACVN16WNmLIzQWYvOx4mOzrLEkM6hCJ2d6Hzh6FRZNjWkczRCp6RUp4vRcY+7EfcZcSlCkUGpIvxd9r1B1P7qMfYmRB9P1Z47h/bX75G6rS1sWZX2V+mqEn/ovthxcOL3HFMJ63lPbtpGvcHR17ER1rv/ajucJWG7efVJwnqN5Z5rp9D17OtmrGko17mH75A1mcXdzfMeXOMIvx/W/jZHwmeYfjZGzi8mnQMjf//NuLFf4vub1cCZKY84bT6fjA2uEfrtX7pGfvybnaTNa5g5Nczv/6bINt+B86oRv/+DSfQQhHP5/c9HKqXEfg9A/sxvSYq0Tb3/NG3lpPeq7jZbrntV8/1YJ+kPoEAqw/6wnnOvOiSiHTu7dOlvj8dzqFkTdqGEe9WuTYt+wfb8rdG4ba9+YeKpMyRY712cFmbV9mrzxOPZX8xzZ33x78fKqzqe7d4dPqeurOOY6blmUHQ92725Vz9P/N+wX7UDnm1ew0eO+yatU8T/qP2JHZpvTy8QtyQJ82AwzPycGfmm3TcU/84+ntmwP+mT34xMxqX26A5Nld+D30b+HoR0stAZ5ujUWPaR6hAuXKfI6CxvGakzhXPyZp73ztO2P1z7wgg40gjnZcgoZDRyWgxrnZ1+03XYye/BUqTPePelBI++5FyDNoCbtAHtN9HH//j6lhzfBvCHX8PW9JvDw1z9ZlFuQd6sxSf0lbbaxqsMlz3YAm3pFWciNyL5vrHW/f4O1ujAAusPgThdG67xcrVzA5VMu1J3r3FfwsVHCRcfEW5kmvTBooUFuRIuIUq4UndapeuZU0Ya1z3MupHo0GcbaTu9QPI5P9CK+7rrsUB90L7T2uh7QNZYJka5lrpH/C4tPJ/6kDQmRwmn7iftq3dIevoGFrPPkxNXapS4UiPyOzoNBylfZ/l76RrdJiPQIa4z7bHkq5XV05+n17KtxVIWI32jsCSdpOusWoj+Zn83f6XI5xxzj3qhhBtLuJ/Zb9nD6N9Nw5+XtazvHSV2BVg5W9M8Q78g8afbp1ivmPGl32jZ24371cG6dtXWa7xlV2a3gmx7kvWEXd08c18gfj59xi7Nhx/L02/blbAbmxK2z1YjTc9xKa9HA53wHcS65E98N9vrArWsJF3XWl3bfC3/Jjvi2c3YRdgpeepAP5H86LXH+0az294=
*/