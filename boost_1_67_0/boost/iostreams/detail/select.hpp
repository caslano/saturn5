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