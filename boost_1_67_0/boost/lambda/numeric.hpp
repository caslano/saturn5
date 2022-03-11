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