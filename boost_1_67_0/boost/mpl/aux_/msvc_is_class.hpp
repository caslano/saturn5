
#ifndef BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>

#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct is_class_helper
{
    typedef int (T::* type)();
};

// MSVC 6.x-specific lightweight 'is_class' implementation; 
// Distinguishing feature: does not instantiate the type being tested.
template< typename T >
struct msvc_is_class_impl
{
    template< typename U>
    static yes_tag  test(type_wrapper<U>*, /*typename*/ is_class_helper<U>::type = 0);
    static no_tag   test(void const volatile*, ...);

    enum { value = sizeof(test((type_wrapper<T>*)0)) == sizeof(yes_tag) };
    typedef bool_<value> type;
};

// agurt, 17/sep/04: have to check for 'is_reference' upfront to avoid ICEs in
// complex metaprograms
template< typename T >
struct msvc_is_class
    : if_<
          is_reference<T>
        , false_
        , msvc_is_class_impl<T>
        >::type
{
};

}}}

#endif // BOOST_MPL_AUX_MSVC_IS_CLASS_HPP_INCLUDED

/* msvc_is_class.hpp
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
*/