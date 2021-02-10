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
PnqYni/Z/swkAwvwFa9jlPjNt3A21FKliyy7NkllezNHWjIiOZwKAAWZL98hN2jwrXG+nFDxz49FpjTiwrSRPGsCg4uh4pKbbGHpfHST5WTK+aXPU5yuXALMhQRFznYslBmn5pB01iJK2lgbaPvTT7ZX0PSNXHfr0042cHr3KsGUeHJtq+FJfR8DbEgtd6h+2nLZIfcK4ZydVWordcj/TnXTw1hrXe606FkGgkSKyOP1cZ8C19lomubcAMzYi3pQHr4nC34a9NvtSGIUtvr3K47rdmAQH7FCG6bMU/o+f7VWwYGcnHVHjqAE7tTAzkVtJ/IdzWIyGQzbLpQpv3kPbHo2xMZZt8kUfNfl6JcKWiplcj22TziRtD46an9SgO4ZmauO7ww9BQc+8m2htAH7Pw5jjZfx2GjYbMEeGDmS/Fz1ZbQY+6wq7U13oMQZowG9CIaNP5WENOto79Sf/NTeMnH8Rs3IvMUYrJ/bBQvXIn+/XgLhF4i6/DN/MK2eBH57gPMko7DFSdi6QgzOCapi+d0VpUbWXOv5A9OH7zoJXQWykEx4D7wqxOCRvjVONxX4ZQOWxJysQT/JZzjMr+4PjKDb41sCaT6SqHbY1SvQHkciF9pl5qpLgjuJ2ifoRV/IRooP8FtlTPfXPcjl
*/