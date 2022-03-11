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
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
*/