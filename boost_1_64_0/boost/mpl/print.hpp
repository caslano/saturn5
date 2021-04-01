
#ifndef BOOST_MPL_PRINT_HPP_INCLUDED
#define BOOST_MPL_PRINT_HPP_INCLUDED

// Copyright David Abrahams 2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace mpl {
  
namespace aux {
#if defined(BOOST_MSVC)
# pragma warning(push, 3)
// we only want one warning from MSVC, so turn off the other one
# pragma warning(disable: 4307)
#elif defined(__MWERKS__)
# pragma warn_hidevirtual on
   struct print_base { virtual void f() {} };
#endif

#if defined(__EDG_VERSION__)
  template <class T>
  struct dependent_unsigned
  {
      static const unsigned value = 1;
  };
#endif
} // namespace aux

template <class T>
struct print
    : mpl::identity<T>
#if defined(__MWERKS__)
    , aux::print_base
#endif 
{
#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wc++11-extensions"
    const int m_x = 1 / (sizeof(T) - sizeof(T));
# pragma clang diagnostic pop
#elif defined(BOOST_MSVC)
    enum { n = sizeof(T) + -1 };
#elif defined(__MWERKS__)
    void f(int);
#else 
    enum {
        n =
# if defined(__EDG_VERSION__)
           aux::dependent_unsigned<T>::value > -1
# else 
           sizeof(T) > -1
# endif 
        };
#endif 
};

#if defined(BOOST_MSVC)
# pragma warning(pop)
#elif defined(__MWERKS__)
# pragma warn_hidevirtual reset
#endif

}}

#endif // BOOST_MPL_PRINT_HPP_INCLUDED

/* print.hpp
//WanhBBONO8U4zf7jvTPQB74bXF48q4UNIOCF19SgX/FxapeWmaCW4rsSAWpuASZedtNSIxbUlisr/j4gcNuu0AJfV3bDBwZ9H45U8qxm6hObyxwUL3sHkyAPfkSeCFbwvU8v9G+e80vrGKpXflo96+P/TPCjJhtrSCRvjYDWYG+Y/tAj6HK+8vLh8iUapAsFVTWhaNBPklywLYienBUZhST6CPXugaY7iRYC809LHyvFXuRMGvwOz3X/2BdmhP+TVhxZDMB/sWb9tJDpvkepYKKy+hRsat7YoeRCZTKPh5RyxBeWxYx3Bp34D7LTCwecR3/q1CG8XTkhCgHKtiZB5IUZFvFAxMy0mA1NIrHH6qZo84XVjHC7ZSzx50Tgc7UkpxFDqOOHndHOzsFGH90dnN3iRTQ654ns+0DMwu0tk9yRIcts0IjEWbwkh7mtCv5/g9ZHcNJ0oBkTZB8bW4DeI2ToBlL2xJMGgbGyxqn8ejGqY5KUmCnY8q64t3/RV6kSDK8zHrbqgalJkVuSjSYlCnudXbuBrUW/DUfI0eCpc+eJ2CLAw/MI0t+w==
*/