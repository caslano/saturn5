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
NFyXT3C6aBa3HsTJ4WF1PjlEA9dgnAZSTFgsTXLjMh3xCG6iNPRYPD0uP/G84/6h97a6/+bbt6+3jC3jKdpV6gxDUyQYOULH7QIAbSl6F0i08t5/YweydeFxlYzFZ+5tqA628BDmtQCYlMwdjSmYlN9qFEveuIpG8s/SnARMhCR1wVP/AX38BThLGWFhMWZh4qNXWpQjMBOis2GW+F9AXtTgY8lpZWUhKz3zCItuUC4/Ly6Ivm7Ok4NOITofvVCBvp2Ax32GDgop5QBGOQDuWCx4oosMpp8EFVUCzKSxnufS3TMSc+dyYNmND1Z3WILrwu7Pv14Xfnllfv175Q+1zYR7JlXIS7vT6w8dKkGYVNqtH/uWZZdgMDhzzru9j13KRgOgBEv5yJklHsIwVQgIaRT64jaNGZkswZr4W4qZUtyGsxQ9Nr524Bi2t0H4YK7f0XyEZhHFeppFWOsp2t2hZXesxpXVbAwb2amdZs8aOKe9bnYk1C3HM6AGWYjFW8ZM1RbU+N6S2GvzuggFlaMKcF28Ns0s1c9KyWPFxy3AGAsqua8qQ2Yxe2DAxpOAapnHcxwe3Ex1haMKmZW5QGB/IaMogJy7aEARGkGgCB3OkqmDDUQ0kTu7gG9lFIam8CI3peOgZCZrxERNRYJd
*/