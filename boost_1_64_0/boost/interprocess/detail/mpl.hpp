//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2016.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP
#define BOOST_INTERPROCESS_DETAIL_MPL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template <class T, T val>
struct integral_constant
{
   static const T value = val;
   typedef integral_constant<T,val> type;
};

template< bool C_ >
struct bool_ : integral_constant<bool, C_>
{
   static const bool value = C_;
};

typedef bool_<true>        true_;
typedef bool_<false>       false_;

typedef true_  true_type;
typedef false_ false_type;

typedef char yes_type;
struct no_type
{
   char padding[8];
};

template <bool B, class T = void>
struct enable_if_c {
  typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};

template <class Cond, class T = void>
struct disable_if : public enable_if_c<!Cond::value, T> {};

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

template<
      typename T1
    , typename T2
    , typename T3
    >
struct if_
{
   typedef typename if_c<0 != T1::value, T2, T3>::type type;
};


template<std::size_t S>
struct ls_zeros
{
   static const std::size_t value = (S & std::size_t(1)) ? 0 : (1u + ls_zeros<(S >> 1u)>::value);
};

template<>
struct ls_zeros<0>
{
   static const std::size_t value = 0;
};

template<>
struct ls_zeros<1>
{
   static const std::size_t value = 0;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MPL_HPP


/* mpl.hpp
jxhcbAH8sDxq4Ngk+fhPdTwVjMtjBq7H5XED1+Oy0cDD4/KEwdXj8qSBc1x4rvopwv0zMTbJ3+yG6tPTpMejc6OpFO2PZV0qpGz+3MOlbKJ+s+g1/jOi5/LFdxSjHvat092+ms3xuQDmzdk/r+v9e9ZfQH3FNNx+xudUvOjrko2e7iVXd/yMorLi0pISXou/RdNV5cfSMu+Pc9Iaru+BeEXH/H2xr+p68pD79q2AYcc+d4y7jcg9x4s2KCfwGCnk/CKEE0cScV4LcMCmZvjzuslR/OFzqgMcwGkvrKmvqq6LVXtnWr5h4Pxuxt+04HWxVNrD39JxI36/CsOrUsu8vPl1gMODRMR+E8DUsG23YFXK3btvB3D4FEP9OwE9lDbaC2vq0Tuc4w5gsdwI7YPV9RQ3Dt97BiYBxLluHafxH7vdYWC8FJPd/l7DcXkQcMg++wcF49PkE/UyyUfz3MLB/ZwYIf4m+lDD8K6ieKS6IaIsv0I//qjz6Cx/Dv+fbBiOI3h/bChe5affR1aOpNHHVrzRvXaD5sQFx7Kh2iI+FUyJlpcFvE9W4SyJytzCZwE9pyzNjQcwdazxeQCTOBO+y8Q5vjxnLjidT4Q1kdx+IZgXHm189TcNT1N61OE1LnSudRBPN9G51gE9l2/EvhaM4yl3BnzDGH/4lHtrH3brevcCBNT/Xdf7c1r/COjV/VXfBrAlyp7hPTrm9z3/1PX+PMx3AX2K/EJsr4lV1fO4zMliDI/uKcqvrChksxDhGSbO43uqa5mhuD+dRvthQ3n+tBrth22Rl/btkJ1Mnm837Wxi2pzsPiYuV70zp0sIhy+fR05XkyNn/nE4uxkcOdOnu4n5ttQsE8NloGoY9w3hcBjxHT08Dm0bzqtUbBT7GZjsZcw2MLkfI0cwMMFInemp6eWejV6aXtbQ9BZ9WbFYWxHrY2AStr4GJvaTfho2q7BihrejnvD+Jq6tYfqBitNRNA3R5Yll3l7gAQFcLiWlsO0fxF2Y/R6oYrwILNUIA+bFPMet4/VJdneAqtdm0nmOW8XxRicKyyBVz7NU/v5bFVP24A1W9coevINUPZXyxStohgzL4hAbHjiP5GCTI10Xcw4xOXXVqbQ2dj3U5MSjTTpnqMmRqRlO12FBjneHLpez4QYud4IfZmJixGfOCJMjRnxu70YaHMOIj2E93MajlhrxIwxcv0d+lIHTsTFeWEcbuJLs7EeuyvG/8MU2OcbAtWxBzliVY2wk4Hlxg8MGXs6XcSqO93XjhYlYfsdrmKwVnqDq6VJp1E9U9cqZB0epemWvxtGqXka1GLdJKoYtsVl2jzE5aiLR/LbOMb+Avfltg0d5imuXOM+mBDmSZ4jnBXBJa94XrOKYV5QHUw09DrnQTYGOJby1d4Wq3tuww3k6TcUCd5ZO9zA58MI/E3mGiVnHH0UmLzD+4Llqk+ePK2aaGLWQ/I5iE8fSG5yPm2XnUaYwZ7adw107hbXEwokxVmpi/tkkcyxYyhLOMhsvEM5yO4fDSeWhwuNIH4/6StFrffhcX19cUjKzshRyyPvmp3lqC14Lo/doA9ZHjOM8k8O1w+uU6F3zLbxUo4yfFgRwNmAjdkIAwwM8GFtoYDIGOTGA0REHkVgDuz0pgOPMEWNVAUwduywKYqmljWn3Ik0un9UeTl/VcDZl2Xy9shBvsZWnVhbi1Vh56mCdwhWx8NQ5+agFV791ay24VBjiLAnhqGPhpTYOn6MRs2Bq2p5swekURZ6PtuJ6GOvsHA4jhaNe4+AAEnd2ee+Jh+Dq+oFECIczDznJEA5nHNbPUzQODkgxjA2angek5BzTORXAeeCJfqYDWCP72ajpyTMa3pA=
*/