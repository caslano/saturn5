
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
u8cYquDBuAplmHEwroAV4nygQNavlTr363E7qjOWn1covHXpj+q676YyjtfHMueUkj67cAik8F5XWh3L57fapppt0EF0cHiQ/Jt1Wg00dN+d02vrdAblCTl3M5+gGFIfE6Y/ONFx3xWcEDwkq0NUYcVJc1ZtzqiCuQl67z1qXEqHfOO2NeLwLjAWJ7Ayp5zRmpvKm+SNZm4QalA225tuJqYrvp2eMbOSsURffHI+oBK4/0imdFbnW4uc6MP0uOAs1Z/agrwtK9iLBx5+mv9yu+Tu++T6HVO1YocuTh01bw9XRArGI255wkp30PdRzTVQ5pTaL2D0JPieyjNJ4R7LO4W8uPqaqS845NL6N8Lcrc89UVaCwOOxueiMwP3fObuLoDiiBADDSIAFgiQEtwWCW3B3grsHl+DuMFhwh+AQ3Bd3h8Hd3V0GdxhsZta1tmrl0NV96T50vctfTz50domjmKeaE8fjqxPyk9yT9WtSkZ/fTmzZUQ6zXEt0pp6VD0luc2tQU2C/YYXtCh7vG5LdF6X5vAHx442u9+7ODMka18YtH6NGn0afFVrSyIUODqWr/3C7OJQO+MOj0fVtYc1vuGAPY2BDMo1fmclL35R9dDWy3XeKYkIy2NU0+q4G8WrssnfV6EJ9Tw72jYzeCkGWk2k2TZpr9mtEF3j22c2qeoxkJeuD4t9rkf3UrSKo9WaWWJttfKwzucWF60iY
*/