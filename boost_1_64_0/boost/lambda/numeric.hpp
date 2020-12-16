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
2RPzQhWncA4OD5FcrZWe7O9NFz+LRej5l8zDvCtS1tQF8n4mSoM8mHeReierd8m/K/1Kxa8KAhG/Qgklj7iXpxBrHaY7R8KJSUG9eJRVAdZwTKvCXxhmK7b7DFvtk29lVaEmop0TzJMY1+0d94QR27MMiyRecWlpofUDlSXl1XMgUWtexnSX+KTrHVKfZp1XmjjjK6t129Ncrk+TIb3T7MU4KxrIhtF8yhVPHlZJePwk6azy2XhU9b7G9p5VYMWRfb+99XxXV1cWzy+z1eFan7wZ256tCntLQz59g6t2ub4+v9rFlSWKvw3H33nYU+1yo6/cJJRKV8l/k4Qrq5xdjlNQdm3DJv/7fdLxDuldrkSmudmeZk1pDfqeqptHtekxlIa/Lfa0ShdD2uUldv626tNjSC/+VJrb7GlWF5fKAGBL8zl9mgypL/N2e5olxdXltva4U5MeQ9kTU3W9S8JfUlE+83hb3K3eNRyD3vRJ3wplS1j0p3okGer+/QJOT4v4u80XguZaBjUOr3vmi91li2SvUn7TVfa6OYwax/WerpM452AH3aG/c8+h9nqtMRkOv8FuJWPTXXpawrTns2ncK88unuc0/H37u8Q/UZ3FRKs4DslnSBQCkVej4Vmj+m16l/+9dnXW+LHsobPctnO+Ibb3Bn+P9Q4H77To6f17B/t5SNPWrMcE4G45EPGStzr1i1eyKllQU6PyVud5NRJvpC1cRXGt2xaOclpqhcNTKvSXilDnKeAjLQnZ5kaUhjZ3hkSU4d/Q0NDI1iHKti0d/j1B1rmgpbuUyLjViNsL7yNDkiJahUZF4ocR1B2RvfE+A2TVV7Xwg35i+72JbOFjkKSXgzgtjfr0W6CR9EG8TFBfUBaoH6g/aAAoGzQQNAg0GDQkgDMSqx4WSX5Sd16/r3ALf+P+LN6xmwd8ryv6gcteD9KH+DmsL1Mn+Y21qmrrwxQDdYkEZvisxNvikHf4S/Y+wuQeL01fYD7sC+92rb8zzO2WSYCqs5hQ/3coMn6DfqF+a1XiRhjTIONY3pOamNA4rY+ux9uJOhqaZOGJzx49ZwudQHGUl+fsBOXFO1VeNa6NV3M0qJrA2/c3MeoiGvz2uvSdunCvOqufABZa6RjS3tejrqMi2N6TA2/v8YxbEFHf3iNMq7E3D7itrxW++klajbdV/n4Qz4+OsJwEozntUffWl9PvpErCclzLafzMa6wnz9HMc3mkty5QK8r2MPNsfCKH+oasjoLhIqQzTMYGb15EBgHYx3pkcDRSL4OoZlp+7NNFlW9uE2WwooVeBimN5+klg2/BdynSGe4jg9wmyMBzjniY/CSq3zugXXIDfmQqqPIaEWC5c3x0NjozQCeWu0ibD0sLZ/WPI+BxOuKfaZW3mRHqimzeSvFxEmWewvP/WazzUpZ5jS8v9csy7fgXDfxEwpuNzgE8ehUjwecokDW4Zqj5gD9+G//uH2imvvteeg3bWvm0Z8o4qrmmXBSxR46jAzi/9rpnmCHbM0A7yjCFefksSFQ+Y5rYbh5lyE4MkMoy5TMf7cKH7SYd4daA8qxx1Qh1RDZveZyPJrQbDy+do/XjRR150U247WPFWQGW3TM+bY7WjxVrGsnPPk50Q/xVoLE+48RZJ1H2lBh92TeTFz8LIpXnuADLPtpT9hh92bc1mp8aOKT8nZHGKtB4n/KPO5nyt/bzvSQ/fhasKs+zm1r+f7F3LXBVFWl8zn0AylXAQBFQyScqGprPUgMlUzPDNxoKCCgmIioUmraYVrqRUVn5arOXWlppuWW7tllrm5W7WelmpcmWlZYWlZlbZvs/H/87HK4Hws1tX/f8ft/9nzPzzcw33zzumfk=
*/