
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
b2zjSphX1XJ84fKpGgM2uyxAsDNEsMQCYWlQh1BopJflCYwfigIX39DtXa2MI/gsPXGstvQeixt8MLuAmBU4u+JXNzxgv/6oYEV2R5Zj1Ja7MWGtfCWAFyXTEwayNEmw35PhHd6pnnSg9A2BqMckAFKHEjrvhwA/pii03FCSilFqXBIFS1UUtdlspG4SjzM2nS9W1f2STyNhuXis2J7YXmrPZtcF5hUqs2ZRckgv/S+PeR6ZybFTM9H2ijDO+DT5izAp4Sf1tgGMJ+JSFI83Md4OysgGWmNjFqm9XoPvRuAoP1FJ+q0NFrDYJFp09CJ49Ey2bw8YzUPZerIY+GMv7KTDFyKNE9cZPwGxG7GhwWCNN7VRJYQp+Mfix5vOYG6c5/iPTRk8Bcvz23VQwLHeWsWmz18eV/eLhwxu65qGUL5gFxncGe3j/X0nvfYdx4/XGWT/3ZPzLoKdFmTn/+ANUEsDBAoAAAAIAC1nSlIn42KRrgEAANsCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTgwMFVUBQABtkgkYGVSXW/bMAx8F+D/oGHIS1FPsVcMqyAE0LKiydA0WePuXbBpx4gjGZLcLf++lJUPFPODbPKORx5l4cH5UjmYEdHq2uBrD8e/
*/