
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl {

template< typename T >
struct is_void_
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_void_
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_void_<void_>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

BOOST_MPL_AUX_NA_SPEC(1, is_void_)
BOOST_MPL_AUX_NA_SPEC(1, is_not_void_)

}}

#endif // BOOST_MPL_VOID_HPP_INCLUDED

/* void.hpp
HaDiXQgq+dak2xg4V7YhkWTz0Yvet7ogKt9vBkNPTYUrKUraX9ufxyE2mrfo6J7uV79V7x88PwuGO/rt38VFayekRs32NpSfdz7cR5GW+hx1gJvU8Fw9QLQKu4W8KbGk1YxDvIL4KrrRdG3ZscZYkha0EelsDTekmBJM4tVmJiJ0Hn9AyS9b+M68fEThcY44G6+l4mWd0J2b5xdhZCQdg6aqmpqa+Z2V1V69Y8XJyEXFtMkfguE/QjFzR3ycuXKj4nlGcx/5QGPr9RPzm06qrHHfXpZDf7bc5DL6+alQODs4f7llkHZWh68anis+pXOaRtTlCi8uujX3VJX1DEcNvvjJ8pMYxfmRPzMBQR9YVCFEvDosam4tzGjrIyH1vH+6ZrNuxroe+xDZQPT6aBtsvs4lze8Rr42Xhi83t09Sjc834JsCH05BKIazDBejNC2c6lkGrZ1lZj+5dc+lF2IJxycyXUdvFmOFi0jbsiqY0thK91MOVCZS5924IfnLRDhxDa5Egjo3hnTETuD+Jh5DtlZUneThKMnxdIm2ivfr7wpPfrhzL+GpThZIuEd7hsYsKPDNlpJzSs9zlw19+NM+XM5XWjoIbiddbsatOMkgkpJhr7M22lYIe/5YlFp5MOgCiZ5OT2oVJqX2HN/wX/jOsNPIF+AJX5NjEwvcVHU8WyZ9nqTmZ5dT4ULu71vR/xpwSg4nCDTOGWKW1eiz
*/