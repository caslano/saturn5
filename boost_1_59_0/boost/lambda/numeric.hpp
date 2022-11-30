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
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
*/