// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the metafunction select, which mimics the effect of a chain of
// nested mpl if_'s.
//
// -----------------------------------------------------------------------------
//
// Usage:
//      
// typedef typename select<
//                      case1,  type1,
//                      case2,  type2,
//                      ...
//                      true_,  typen
//                  >::type selection;
//
// Here case1, case2, ... are models of MPL::IntegralConstant with value type
// bool, and n <= 12.

#ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED
#define BOOST_IOSTREAMS_SELECT_HPP_INCLUDED   

#if defined(_MSC_VER)
# pragma once
#endif                  
 
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace iostreams { 

typedef mpl::true_ else_;

template< typename Case1 = mpl::true_,
          typename Type1 = mpl::void_,
          typename Case2 = mpl::true_,
          typename Type2 = mpl::void_,
          typename Case3 = mpl::true_,
          typename Type3 = mpl::void_,
          typename Case4 = mpl::true_,
          typename Type4 = mpl::void_,
          typename Case5 = mpl::true_,
          typename Type5 = mpl::void_,
          typename Case6 = mpl::true_,
          typename Type6 = mpl::void_,
          typename Case7 = mpl::true_,
          typename Type7 = mpl::void_,
          typename Case8 = mpl::true_,
          typename Type8 = mpl::void_,
          typename Case9 = mpl::true_,
          typename Type9 = mpl::void_,
          typename Case10 = mpl::true_,
          typename Type10 = mpl::void_,
          typename Case11 = mpl::true_,
          typename Type11 = mpl::void_,
          typename Case12 = mpl::true_,
          typename Type12 = mpl::void_ >
struct select {
    typedef typename
            mpl::eval_if<
                Case1, mpl::identity<Type1>, mpl::eval_if<
                Case2, mpl::identity<Type2>, mpl::eval_if<
                Case3, mpl::identity<Type3>, mpl::eval_if<
                Case4, mpl::identity<Type4>, mpl::eval_if<
                Case5, mpl::identity<Type5>, mpl::eval_if<
                Case6, mpl::identity<Type6>, mpl::eval_if<
                Case7, mpl::identity<Type7>, mpl::eval_if<
                Case8, mpl::identity<Type8>, mpl::eval_if<
                Case9, mpl::identity<Type9>, mpl::eval_if<
                Case10, mpl::identity<Type10>, mpl::eval_if<
                Case11, mpl::identity<Type11>, mpl::if_<
                Case12, Type12, mpl::void_ > > > > > > > > > > >
            >::type type;
};

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SELECT_HPP_INCLUDED

/* select.hpp
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
*/