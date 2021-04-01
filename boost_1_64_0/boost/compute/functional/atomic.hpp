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
oSxaSSGbOQiUxLUXxyfTgZKmt9CT4/pNKrBviBOh621RfBbD7Asol0XNBY/gm8ri4+WrS9ZkFi8VB+ctVAvt1Py2YNnWMOxignkYsmfrOKYqh+4MTfZWEW8SCP8oE5S42sNU2HmryqoaQdd8ZYoqf3zQTdnY/ndMZK9CmkQfTJW8mxH+afUx+FhogvTFJ44PpRVBF1OvFoRY1Zosh2089DswqAJZc5lu0Fl3xh0/NXahBnpU7XSTTR+1QRlMuru72AqGOBWKsq6MEKWfrHMJlJ8bjEKUY1hItPpRugIoxh5bvmxITpNNuEBr08+JWPBeLOdjIjZKIesYluiySRbn8dhTCTW3Z7wtbzyx4RcglGl5AmGFAMJntYjc91qdzB5zEQp3KMQnaNTSRie2hvj2lp+iZexNxFdwE2BXTNi7RO8A5Qe8oaYOysrUYbBAXWsr25xkIWAECDoWrjVMA5uNwhI/JyZSsdfVFKVGIvv4c3vJimKx0xgvbUGcF2D15XytV0A76BLVZzxRQ3xwHWlnVrR1RqNt2Gy2mFNd8QnzvM5iS5Hf7oiz7Q1gog==
*/