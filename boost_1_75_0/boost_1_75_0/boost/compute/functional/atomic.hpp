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
X1Yk33JujoakUG+Me759SEfct4SfWTnwIfco++1XAOmRWU5s6DvL4M/JwYfPN7+7qiHFb/4Hv+Ns4N+KTQpy720DjCy9D+795cUNQ6mz7VJbSV38J/Mivb2LgkM9mRdkjurZRwcc7fj8l07nw63I/WjytYy/WJ0Yqz566qj6kuDKh+WR55gz8cUDHzVuusrvyskCd9MLctOUuqjq2+3SW6av8X9NDX0YPHd/7Lk4/dTn9EOdM4kBgGTuzteAKVH+vuB9Z8zLI1HbmAPCB6uHm+0br0tnxrQCII7a80K0lqKYd+S5TESvO7avqC6A9Owhu0Ve2L+suHUxUWcktFEwFUBaYE60cFUpkwCIy1lIDLZLiW7Ha8/PvnHNCXd068C5v4jkF56djH9WJ7N3W39royY6Z7xFnmL6CufdBZ86wg4JgD/y3QdYVLtOorXlh0eK+siu1P/j805cWRqm4ITxDX2a2nfECX3XEOyySknZR1Dnld8VRsRdVW/kk/y2C/pBN8GXXfSHDechR6IEgINtZ246u2HOqhsD97tKWkZqZqyCpEzG5qUJkpB3Uq/x1V93v3vKP1UYJPLv+O1/K/iy9/oUFO3wXrpK7iiv/VXyHVA/RjLywEM6IImKhr+mZmG+U6WHJysf69/+BJQD3EIfZL4YFGE77HMNmUzFuGyTe4dEdu8FnhiUDXYjbqlPD/HKQiWP/Nj7C+erbvqW
*/