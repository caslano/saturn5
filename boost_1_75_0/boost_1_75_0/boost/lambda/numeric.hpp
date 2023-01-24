// -- numeric.hpp -- Boost Lambda Library -----------------------------------
// Copyright (C) 2002 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2002 Gary Powell (gwpowell@hotmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org

#ifndef BOOST_LAMBDA_NUMERIC_HPP
#define BOOST_LAMBDA_NUMERIC_HPP

#include "boost/lambda/core.hpp"

#include <numeric>

namespace boost {
  namespace lambda {

namespace ll {

// accumulate ---------------------------------

struct accumulate {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::accumulate(a, b, c); }

  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::accumulate(a, b, c, d); }
};

// inner_product ---------------------------------

struct inner_product {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<4, Args>::type 
     >::type type; 
  };

  template <class A, class B, class C, class D>
  D
  operator()(A a, B b, C c, D d) const
  { return ::std::inner_product(a, b, c, d); }

  template <class A, class B, class C, class D, class E, class F>
  D
  operator()(A a, B b, C c, D d, E e, F f) const
  { return ::std::inner_product(a, b, c, d, e, f); }
};


// partial_sum ---------------------------------

struct partial_sum {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::partial_sum(a, b, c); }

  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::partial_sum(a, b, c, d); }
};

// adjacent_difference ---------------------------------

struct adjacent_difference {
  
  template <class Args>
  struct sig { 
    typedef typename boost::remove_const<
        typename boost::tuples::element<3, Args>::type 
     >::type type; 
  };

  template <class A, class B, class C>
  C
  operator()(A a, B b, C c) const
  { return ::std::adjacent_difference(a, b, c); }

  template <class A, class B, class C, class D>
  C
  operator()(A a, B b, C c, D d) const
  { return ::std::adjacent_difference(a, b, c, d); }
};

} // end of ll namespace

} // end of lambda namespace
} // end of boost namespace



#endif

/* numeric.hpp
nVC42c5ORcrhvZVvra9kjzT0a51T/jzX3h2w700sY45yBtaOZ8pdaZijxW9pj5NigOONPEZXpjtaL1UMGRUarz1CRQyCpLpeJ68S0GhT0XpMBtlaFXzket4XZRKUBUP5zwaRO6AEPAf1NClgbwY9YW/1KZoEfsU4lZoBClMk6nlZ80p7RIcaSzDLufCbJRhteFeLD++s2buhVfwl3mNIVWdakaFb/S2drMx/rVl8bTSDJUbqHy2hFs3UTlhlvDoi3OTPNQWXb83V8RgumPvaWMl7b1kSJVAbWNEtNUqIzyxVPJ3qtqdqDH+LkY5b6+MVOKW1o+482ZiKWiDu3f1m+sEoc5tdLOnxHm2b5DEyvuMLhSQlclaG6OoQst/z+eDNBagx+XNsoKx+j44u5dYHCjG6mUQChrEfibUNp0upOzqkKvSlR1fWMyDmEFC11vggkpqhPGK33hqQtXVpfosJ5X7wJoOhrzD2/caftPVIKZukDHDp8T0lv51zDWJJfsyd0/3i3ii/uR8f/vo67Emh+Ci6sJ+8e7m8UJKcf15mkBmjavfdeDrkN9F3Jb326Qejvbe4o8EQWqSML7e7t96xBpaWO/IgnjgxehtEd+z4qGa5PqvaH9aQcsU0G3m1qe5T09cbR5Z3x4ovic3zbYCyM8H7FuJ3spzFF9dTd8FG8+KTPRjLHQ08FM8bY3fcCNWHaXLU0FRtWE08LhDk
*/