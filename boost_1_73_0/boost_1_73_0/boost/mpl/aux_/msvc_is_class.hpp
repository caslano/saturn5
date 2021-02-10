
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
D+ajenDj5t/9GwP5H+vywk93+fex4Pu5vO2/rbpO8XO/X27Miq+yk0Lt49Cpt2/91x3SOG+McGfWnlWELi7d2CbOu4rTsvyc0euczduXrXH+wS4v/nQffB8Lfr+wkxl8mXVNfZWK9fX/bP8AUEsDBAoAAAAIAC1nSlKU69P+XQQAADQVAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAyNlVUBQABtkgkYO2YbW/iOBCAv0fiP7isVre7ggYSoMCFSt2+n/qCCtfu3ZeVcSYkaohztilHf/2NYyB023Kl16721JUqGieeGc8zM3YmngKpGJWwbXlREnD8dw3TCRe+3LaO+v1u9kMO9/vm4jOVESN0rEIz3ouGqMDc8Oxc1LONtnekB+IGRFlGPliegDSebluWt1Euk51YgUioAqJCICgHAq+omhtJ/Ln6ECg+lISmKVBBooQIkClPJEiiuAWJHAswsrkqn4NMflFkRBXa2STl8tzwQSRQqYC/xplyKpfdKJGJ4MmQpFRK7Uwm5/lU0WqlYpjY1c0qqVWq5AzAn62Wi2UlBcu43SanERNc8kCVj497dn2zUrB2eaIgUeX+NIU2UfC3skM1in8lLKRCgupEkpebzXqrXM0nn0AyVGGbOFsF
*/