//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/move/unique_ptr.hpp>

//!\file
//!This header provides utilities to define a unique_ptr that plays nicely with managed segments.

namespace boost{
namespace interprocess{

//For backwards compatibility
using ::boost::movelib::unique_ptr;

//!Returns the type of a unique pointer
//!of type T with boost::interprocess::deleter deleter
//!that can be constructed in the given managed segment type.
template<class T, class ManagedMemory>
struct managed_unique_ptr
{
   typedef boost::movelib::unique_ptr
   < T
   , typename ManagedMemory::template deleter<T>::type
   > type;
};

//!Returns an instance of a unique pointer constructed
//!with boost::interproces::deleter from a pointer
//!of type T that has been allocated in the passed managed segment
template<class T, class ManagedMemory>
inline typename managed_unique_ptr<T, ManagedMemory>::type
   make_managed_unique_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_unique_ptr<T, ManagedMemory>::type
      (constructed_object, managed_memory.template get_deleter<T>());
}

}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

/* unique_ptr.hpp
GYaG4GLlyWiQPbKIo5FeHVXs4amcuZ9sdZbjqSGZ6w/iyUi4H6CSyGweKC7o2fr4Iaf5vpogExMjy0ZPo4ZRrlB1naZhrAoW5zO38N2pBCRIJlE3ZRfDYGbS+DvGeVxADohn6YThzPGhOisdxFNoPXI1ttczUjCsHL/QDZA87L5tTs/pkhvhh3y8LF+R70HP4nvMijBGg/Abcz5/jgkad4gRBmFwjy9alfDAsiezGFsmDnfGb4OJtr22k33LoZcDbMy6daQtz5SUDMhHv+Vqjpwvt19fe9JEUtrSxMle/wrvuPJgCL8XvgLheXqeiNSBHQCBNqJr0Mm5cR1mxgycZwJ9A/k+DZESTqVyK1yZCYADuO3Jytzk2tqiQLIgn5f7X29dRV3NJ/yGKOtp8zVs+uunS44w2db+8nFf+m2Qk978AfY9Z2yqzbaBVyvnAP1bZ4qFwndQ3hupVDqO0VCyK5UIFXa6HTOzmjHKUG5Hx2Sd7foyY0eM6QS8XycLjCgEdpk2z0iEg8OBxJsgBWma0UW7IKHduGWyAIs7/2+NSoSQ5Vh0fpGsAlRV87T6vlx/gaT6sZdamzYboM/he5hHeTT9lsZQjZc3nfRJ52x1KaM/FrnZy/d4eQA8tR+iEHPgL86RPS31r+5v4owix/xs5Y6Ss1PfBRmVcu62Vg81ORnKFXVpse6NJKnh4VJSiYt/EP3L6mED1Wv/zx94
*/