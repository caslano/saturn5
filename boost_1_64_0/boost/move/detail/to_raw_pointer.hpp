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
5cBUsDJuJ9b/Kg1V1h+NZ5COsDOPm0TVb8HP2fDYsAlT7nJwwrly5Sbyj/PQ+wJikZYnqAgPd6qTdBAunmg3W2X5wgeFel/ynvzw64GwRHpJx5uTEd5IZzxjwwCBcljTARG+UqHmcCAw7B3O950p3/SDjchN9bGtgRtY+AU9DxIZhHpicnsrsEk+5FjZeIpvnuj/39pP4ke6zzXtUq24B1Nr9qHmmCAH0vJpCwZWJnxtJeUptMo5H4BguYhUdThs8uL0Z6mddtIwNDZvKXJnip7/X0q87dOhvpSm7vyHn7hQYj14KOwlXQU0SQB6p1GJjUIyef8UhLpBU7pLL0a99mGPM2bQ2dn7+NfGgrhk3gpov6dH1JhqzyUEnyD6ceSI/jYlU64gS+UhPYpneEESZwqyripvFSa75ZFbAvFTmUOCRlWsB6KTXpGpevdb+OUkNLK6XDphhl7fyBRBdMmao73k4Q81wDNoyY+AG+xO87iApKloAvA/24eDatXwhsEfkSISti5JI8mLX+kfJq/7+SN3WVmks1OWi12hLBD/OIMYi5jS7Qy1gHBqcg==
*/