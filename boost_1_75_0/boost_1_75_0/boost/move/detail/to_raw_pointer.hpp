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
+jbWPMsw/X9FvhbWAbBFNOc3n6PKTIziwhOoXahGIYHZ0I0aYkN3XOT08TUA0DCZx+qz65HtNnTmwTZl3iIHUAgvFqulpfIqZaq6SqmXDJBWCnEUtagsRAHzFxkc/xs+k9ax3AIZ2eWMsTro/Tb7+0sgoyxCX9jtk64RI3wPvE71Mc8A8EdIGtXHOK6ws6um0t6Au5kOhv8Yex0eICUVSYvkpDJDjkktarFWA5xoNVHDaMTKJ0icUGn8+b+hN6uQZBZv7xYAmiRCW0idzDlC54V2M0aLhHwstoMgZKBZQkgc0i+rJFu/rIMMt8OabeqqBr1/wP7+IfY+0W1tNt+n9Y5Ava+DegeH1PsSFKFx6FweWHCQvEP07A73AWpWkKJmBezcrJtGGW8rmUiijF8WQ1KV3CbVCylljpoUPoT8h97tWguI6pNhp9RRI2HviS0+OasEoZ3pJ76FglC3TPqJjVClN0n9tgLwmoeMNTXUsykmuAnNITPmhm0/4MxN0Vr0HNaFRvFeamAYVhuVqFwulmsvqg1KkXw3i90tpyN3azzmIondZ0qifK+KyTLz55sIwCpIj0EKMhtCnLyaW5/LEXqP17TTrqe1z9eZ2JWFsT/QJaf3DGWihGqW4Q+F1aJPalQ3a+3exXrcNz/QQk2Z4t4HsVbLQ04Ywk5UHajGhYHD/J8V0HgNB9W4pgUavVr6LMdmq3sZvkVtdbOG
*/