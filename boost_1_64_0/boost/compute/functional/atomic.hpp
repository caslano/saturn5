//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP
#define BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP

#include <boost/compute/cl.hpp>
#include <boost/compute/function.hpp>

#ifndef BOOST_COMPUTE_DOXYGEN_INVOKED
#ifdef BOOST_COMPUTE_CL_VERSION_1_1
  #define BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "atomic_"
#else
  #define BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "atom_"
#endif
#endif // BOOST_COMPUTE_DOXYGEN_INVOKED

namespace boost {
namespace compute {

template<class T>
class atomic_add : public function<T (T*, T)>
{
public:
    atomic_add()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "add")
    {
    }
};

template<class T>
class atomic_sub : public function<T (T*, T)>
{
public:
    atomic_sub()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "sub")
    {
    }
};

template<class T>
class atomic_xchg : public function<T (T*, T)>
{
public:
    atomic_xchg()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "xchg")
    {
    }
};

template<class T>
class atomic_inc : public function<T (T*)>
{
public:
    atomic_inc()
        : function<T (T*)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "inc")
    {
    }
};

template<class T>
class atomic_dec : public function<T (T*)>
{
public:
    atomic_dec()
        : function<T (T*)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "dec")
    {
    }
};

template<class T>
class atomic_cmpxchg : public function<T (T*, T, T)>
{
public:
    atomic_cmpxchg()
        : function<T (T*, T, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "cmpxchg")
    {
    }
};

template<class T>
class atomic_max : public function<T (T*, T)>
{
public:
    atomic_max()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "max")
    {
    }
};

template<class T>
class atomic_min : public function<T (T*, T)>
{
public:
    atomic_min()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "min")
    {
    }
};

template<class T>
class atomic_and : public function<T (T*, T)>
{
public:
    atomic_and()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "and")
    {
    }
};

template<class T>
class atomic_or : public function<T (T*, T)>
{
public:
    atomic_or()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "or")
    {
    }
};

template<class T>
class atomic_xor : public function<T (T*, T)>
{
public:
    atomic_xor()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "xor")
    {
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP

/* atomic.hpp
+13+GWtSduZpifaTcIL5gZ5H5uH25+jULt9sMfIcYeEs8W32LR5mO1DWywKMjIv684jiUzKc8NlgPcY5gMB7F1R4czEvUkgZg2KezLxV3o0sp6n2Oh+M8VBB9Rn9W9vxnB3q2FrIcKlW1Xu/NsAJSmVOxedaH6vkyrkQc1aHcp4L8UjOakvzIS+Ss47PjQwvK+eFkJORs3lbgEdy1pi8EPIOKueOkCtyFl/k7AAR+7bf8K7HtrXw+hQL37vTvut/g8PFb+j5hm/0MfyGHy8J1t6uG8LJt2vzphRX8Wq9CoJlbb5DMSlT3rkRjPUMr6x5d12PUpN7GhZzx6jJPVPp9bSjUucidX+mj0W/T1YJsIQxOPx9gw9lcKqka6HmxkUGvIcjaJhL7fJ/5Es4xTwO1QjOis7jRO9WJZazo/ecDbv6us/va5WjdjAb45Th20k9g5O/5/8XWs+n9dl0aeuGLd1RW3pHczhRWzomcjhRW3pjTrMY/yzUkRCnCI1d43vJ2l+zq0d4qvdJsF+nsHi5gbNjgwZH+s7el5ZZbEfPmdHZ23MBhn8tKrYQYFTKz/PLPkaFit5ZoL9xWNPevfHcXQ+Dpglpw9GuDcNu7/seiQs9LN5zm0i+w1jR5rO4JPbVu2CxtN1nybj/a3s98J167n/XLYpngyj1sbWvHoSH4zH+efe/U64GUjrf6grwcN7cH2I4RK1rTbGsQ/TeHZ1XnjpFf9zxcL1fdbj+Z4trwDMs2F98LHzXsfBXwbIBD/UTO8vhNZU8+H1q5WQDHy+vLsfLBDTK6c1wnEqqzPqzHLLRdZwki9Nv6IJXzkyG4yqsnFqGk+oROWlMmOU0rURjwny8aZ3TvmzmMjzZADkt40/IwfjNPinnbwFWadefcxne6kx/Jn8POe36cybDy/ZnLcPJ9udsxIn7s57Bs/05l+Fk+3M+w8n2ZyPixP25EOHt+tP8I+Zpf8q61u8dh670fhuiw7+uNr/b3VcsWL9rQwnRj+A6gsYXiJ/7o80zDPzk3lnFnZ8bFB94R4Dh58yg+JE/CXZQP9ehvMDPSRkOVxXRcVyxwAfKeXdu3Iv2+xdlfNIu8u+b13wJDlX+vc6ntjlnt19wPWdXxu6bLCbdrdjMvMW8AFLP3rR1DYNE/f2uo3Jwetj/Dcb5E1LONs4w4HfFNpcmCTsqlTEDR3TkaMfhKKX0cBT1m8dYzJ3HizkTauMd9Ay/3lXC4UG/vqtVPNZe5/y2ycEDLJpM6Z7Uu1ksirOLep2hyVunubu7jhvUOujZkIqPTQ7yZDb9aQnJt/8eFk+3hY5JXH9Pd53zMPZ4v4FyL3s9ih877uOuJ/wklW2Uh88LXvHrqfHf/SwueiJtwAscCta9abOsqq3r9PPuv7fDg0mrziluJm9wNEIiSP/+2QhHksXgzIcIp+Wa9y0hVonvvepQi0tUqPdencGwdq1X4Rofz/72ZF3vTzP2nkl21UIsOBPTYpG1a529NmHtwe8QJ1onVyF9r+Sr6X29G7ZvwKr43ezwDOCOm2M8nPvNZu9H1N4aj8PPjktQ3124OYcj4yOfW3NwSvF9Q4M2Wo4LhZ2TGZb4+mVtOCi3P7YVP5GWl8nJ30v/8kNjTnZeW0/zaZ0xa9+vtO5dOW841HHSs8wsIZgLvsXjEH/kcXobyomK0r76m6vP9m07e+3qtJ7jy365QzM4rxxWhjgPj5cHEYC3//kBIVd3PercInlgyBlP1J+ah/hYeIZJ43gfC9ch+k/wsTDmTx7mY+5lxN1sb5nEr+ncZSbLszMpiP5vzGV5HEvAGbjefvTZLAfTZEEdjsSuGU76o3XN0cKvVxE9j3g8+ee5VPNNGK8=
*/