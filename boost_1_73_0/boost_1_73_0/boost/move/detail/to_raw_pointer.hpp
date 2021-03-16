/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2017-2017
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP
#define BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>
#include <boost/move/detail/pointer_element.hpp>

namespace boost {
namespace movelib {

template <class T>
BOOST_MOVE_FORCEINLINE T* to_raw_pointer(T* p)
{  return p; }

template <class Pointer>
BOOST_MOVE_FORCEINLINE typename boost::movelib::pointer_element<Pointer>::type*
to_raw_pointer(const Pointer &p)
{  return ::boost::movelib::to_raw_pointer(p.operator->());  }

} //namespace movelib
} //namespace boost

#include <boost/move/detail/config_end.hpp>

#endif //BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP

/* to_raw_pointer.hpp
yxjDUpkGYr9C7FeI6AAhsB03sdS1jkZ8rRBfK0QzjZBlLDXKqFOIOoVICKh2SMTzBuIbhfhGIdoyAswmRdbqCaNW3yrEtwpxog+RayC+U4jvFKKTr1bmsPpeIb5XiNMYAWvEVNnnnxqIzxXic4U4ixEQQ54se3C5gdipEDsV4hxGdHBEh0dYKsVoR61C1CpEH187ZhllLBIuglOIyGkU8ahCPKoQgxtFPKEQTyjEhRoh++M7A/GUQjylEMN9Zdw=
*/