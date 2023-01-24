
#ifndef BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

#if BOOST_WORKAROUND(__HP_aCC, <= 53800)
// the type of non-type template arguments may not depend on template arguments
template< typename T, long N > struct integral_c;
#else
template< typename T, T N > struct integral_c;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE
BOOST_MPL_AUX_ADL_BARRIER_DECL(integral_c)

#endif // BOOST_MPL_INTEGRAL_C_FWD_HPP_INCLUDED

/* integral_c_fwd.hpp
UGFuEb3ZQs/FwPhlgZpdiGFsybSGa7JleRQmcfUu7A8EWNvv8H5Qv8cqSYowz+g11Jyvf3QNm5iM2gws0t9ZWiXfCX/tZycmyRrIUNNvcoXZFQ2J6oxy215a6hoGdQgNVzUx38N7AvxDarCcpQ7Dy0bQBB1usVee3zTeK7ShZ2wz+1KwSr/X4f7egwyQsJK6Gay6lsVfNeMVpi3gnFQxMu8yzu2fB5e8W2gTN7EJPB9Ta9SVGYVNkB+KLx5/uzNNfmWe5OnBJeaJVJdIaKXwNwsNpCzpppkq6MzuNB4IxNinjGk8tPNsXIKKtjIGrsAJx39ngxmu4btu1fAZjqspB74rkbjcoF+DfpOh7SYoiJh6Lc6DWxByOI1Z+6PqivUPzvNJpsT+APtOk6666r5zMA4rFv+V+I2llM43/cISpVjTfdBU/Ar1Gi3QZWgdG9YR4J+vWmQuXYjg69s9U1evI71seL/fM6kp8Gld9Ramk1y3SbwfonnoVjseeJXItMu52bUgzbD81A2ce+Yb6b88P6JdZg/bPO5WeaDfMMTuxQ3IuHrug2H3kjpjBFFSoQfBKLGCkMLYLxuXb678f3r2XWIBsWqQY32XpL2YL5rXYn2X5CbiLxfV++xOxhtwuFZfXo/W3X5YeQWfXvkbV2p9P0PF06PurSQ7u7SmL3UNrBMbQCiuX/54EuVwrMMg+57tDQ0o1FTJPwiH8DfX
*/