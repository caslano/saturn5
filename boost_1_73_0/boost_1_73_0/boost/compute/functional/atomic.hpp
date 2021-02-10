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
ZzD0p+1H+D4Q7KYs9cz1gnpRyhVH1eEIaqfAhheSQ71lcyDCpzKybvhgcwW+uKCmKzIb9ULf8GQeOfZ+pXF8TknEEyyh4JbrM1bcFGFJr9oFagY1Aihd2tyQM4/quG97PDYs2i7jrTikquUf9hyPL3Spfxy9tUE1+n9zW8aLYZ4Z0SpAXtWWJ3Qra3Xewi3NHyHnTtO4Iqlyyla3LyyySvVHe8C0YwT/cTqhSrPcjNvTxumsWiEMqOAsjfDGuYP7waXj/VvyfT9dfJV5xSXJGZd8PS0JT4D53/iES+TklFH+TplHuBNKLa9nMD3NJJ2tw5WUmgtNEtW4LkPCTY+VSuuty0FJaM/F6lh02zo/2vGNca9yjNvzhkm49MYDOoE0RN21TndEdX1/itRuKMotRWlXqYK8VNeyWvAP5TC+jb2qIXZ7WWsnbTd4mEYSd9TpgwaW3aZAX8RKd/tBTl4e7QfZM1P6lrinzi58tIh1F03fu6oVH+2pPxn2EY9TzzfdMHBZx/T7e91ao4sxaC71SS3HF2vW7nfsoTqfwIFCvMgYlUBpEUdfpGsG2MRHke97v5aGJRDpR0qflwC46QnR9uW/zM2nrR4vjfc93yfub0Vc7xPhm6PZrm5ORNuSaG/uTX9kxgs+vL1hIOfb
*/