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
SepsrXE1Z6EuAijVH5xxXwOG+MTSL6H3Vy4hKkJeiDwjtxLSVjKBdDgaMz5yHJrdLRoz0kb/ZLzPWKQ6c/YRLcE7U3ssoX6Le9+OCgggbvuE9Mgodzr/QNUXmTDYhKN4oKp48n4VsbkmybIfYA6UDYS1LeXiqmyROh34vMd+zJT4ekupWhINBHzhg1j9v6WAE76IvNuXhObZxj9pnRGfEh/pP9H98/pEdksCJWUQPhEkQ9v9EPIzFl1F2x0X2p2B627pfWJgWbAkWJFpPhBjrwh7PxXLy5xmEwjF8yJyEXlmvg4iJ6mT2Z3Jv1f0ouLHnfOee/PT7N6bORbZj27Tw5MWPoS4uSXIZ/yozRu3pLTG9iIaA6Qld1RCeB99CMsGLMQQ7TF4z7TZXcGMaVrlVR/dp5klVBO0aOSgrl9OhP+ZN3hltg3et2zIa98ugKBfqXIzy+lnwYOL3NgDj3RP2hwPNzOTm31owK1mG0Pm3KBF4c+rGvEoK55rXARL2yayQLI8jdWEyOaxsaU/eycoGesKuvKnzkoHKviggY5/Xmmy+Nz+kfABw3xM+Ss51FPY/rQYq38znBPIelGoOqHnSzWyFP5EYXPEeex9g1t3okmaZcvEjkFzSmN+8qOgVS6f5YpeQBlBSXSXXpIBO6M56P3nSVzun0/aCIgxl8OZgmnYyPKSOV0JS/zWhHjOiLWF6P9C2FUGxREm0QQN
*/