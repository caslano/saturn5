 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_condition_any.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

typedef windows_named_condition_any windows_named_condition;

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_CONDITION_HPP

/* named_condition.hpp
WtQHS0okSgZgG8QA5GaJ4cjPe0/8D1hpzvblOnW/tV/OxRvWc/syzVYsudP0qUPdBcoM3o8uPC4mD+TtDhbuDhTulezLqcapa8jYrPyUlSfgoBJ5d2flepfIreM8wNHAkUyBwm0Yf0RLNCs3ZcUJK/sF5d2dNdV7I8i2svGZxUNavFn5aSWw20KvQxEDsjorN+1m2N1Put4ASu73Yxw+iPVQOVtxE3Ig7/Fg4eOBQjk5z5YU
*/